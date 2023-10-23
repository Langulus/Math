///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"
#include "../Numbers/TNumber.inl"
#include <type_traits>

#define TARGS(a) CT::Dense a##T, Count a##S, int a##D
#define TVEC(a) TVector<a##T, a##S, a##D>
#define TEMPLATE() template<CT::Dense T, Count S, int DEFAULT>
#define TME() TVector<T, S, DEFAULT>


namespace Langulus::Math
{

   /// Default vector constructor - initialize components to DefaultMember    
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector() noexcept {
      if constexpr (S > 1) {
         static_assert(CT::Vector<TME()>,
            "Vectors should match CT::Vector, if their size is larger than 1");
      }
      else {
         static_assert(CT::Scalar<TME()>,
            "Vectors should match CT::Scalar, if their size is 1");
      }

      static_assert(not CT::QuaternionBased<TME()>,
         "Vectors shouldn't match CT::QuaternionBased");
      static_assert(CT::VectorBased<TME()>,
         "Vectors should match CT::VectorBased");
      static_assert(sizeof(TME()) == sizeof(T) * S,
         "Vectors should match T*4 size");
      static_assert(CountOf<TME()> == S,
         "Vectors size should correspond to CountOf");
      static_assert(CT::Exact<TypeOf<TME()>, T>,
         "Vectors should have type");

      for (auto& v : mArray)
         v = DefaultMember;
   }

   /// Construct from any vector (with conversion)                            
   ///   @param a - vector to use                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector(const CT::Vector auto& a) noexcept {
      SIMD::Convert<DEFAULT>(a, mArray);
   }

   /// Construct from any scalar (with conversion)                            
   ///   @param a - vector to use                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector(const CT::Scalar auto& a) noexcept {
      SIMD::Convert<DEFAULT>(a, mArray);
   }

   /// Manual construction via a variadic head-tail                           
   /// Any of the elements can be another vector, as long all vectors'        
   /// element counts and scalars sum up to this vector type's size           
   TEMPLATE()
   template<class T1, class T2, class... TAIL>
   LANGULUS(INLINED)
   constexpr TME()::TVector(const T1& t1, const T2& t2, const TAIL&... tail) noexcept {
      if constexpr (CT::Vector<T1>) {
         // First element is a vector...                                
         if constexpr (T1::MemberCount < MemberCount) {
            // ... but that vector is smaller than this one             
            for (auto i = 0u; i < T1::MemberCount; ++i)
               mArray[i] = Adapt(t1[i]);

            // Form the tail as a new vector and copy the rest          
            const TVector<T, MemberCount - T1::MemberCount> theRest {t2, tail...};
            for (auto i = T1::MemberCount; i < MemberCount; ++i)
               mArray[i] = theRest.mArray[i - T1::MemberCount];
         }
         else LANGULUS_ERROR("More elements provided than required");
      }
      else {
         // First element is a scalar, so copy it...                    
         mArray[0] = Adapt(t1);

         if constexpr (MemberCount - 1 > 0) {
            // Form the tail as a new vector and copy the rest          
            const TVector<T, MemberCount - 1> theRest {t2, tail...};
            for (auto i = 1u; i < MemberCount; ++i)
               mArray[i] = theRest.mArray[i - 1];
         }
      }
   }

   /// Construct from a vector component                                      
   ///   @param a - component to set                                          
   TEMPLATE()
   template<CT::DenseNumber N, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr TME()::TVector(const TVectorComponent<N, D>& a) noexcept
      : TVector {} {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      mArray[D::Index] = Adapt(a.mValue);
   }
   
   #if LANGULUS_SIMD(128BIT)
      TEMPLATE()
      TME()::TVector(const simde__m128& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m128d& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m128i& r) noexcept {
         SIMD::Store(r, mArray);
      }
   #endif

   #if LANGULUS_SIMD(256BIT)
      TEMPLATE()
      TME()::TVector(const simde__m256& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m256d& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m256i& r) noexcept {
         SIMD::Store(r, mArray);
      }
   #endif

   #if LANGULUS_SIMD(512BIT)
      TEMPLATE()
      TME()::TVector(const simde__m512& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m512d& r) noexcept {
         SIMD::Store(r, mArray);
      }

      TEMPLATE()
      TME()::TVector(const simde__m512i& r) noexcept {
         SIMD::Store(r, mArray);
      }
   #endif

   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TME()::TVector(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TVector");

      // Attempt initializing without any conversion                    
      auto initialized = describe->ExtractData(mArray);
      if (not initialized) {
         // Attempt converting anything to T                            
         initialized = describe->ExtractDataAs(mArray);
      }

      switch (initialized) {
      case 0:
         // Nothing was initialized. This is always an error in the     
         // context of the descriptor-constructor. If descriptor was    
         // empty, the default constructor would've been explicitly     
         // called, instead of this one. This way we can differentiate  
         // whether or not a vector object was successfully initialized.
         LANGULUS_OOPS(Construct, "Bad TVector descriptor", 
            ", nothing was initialized: ", *describe);
      case 1:
         // Only one provided element is handled as scalar constructor  
         // Copy first element in array to the rest                     
         for (; initialized < S; ++initialized)
            mArray[initialized] = mArray[0];
         break;
      default:
         // Initialize unavailable elements to the vector's default     
         for (; initialized < S; ++initialized)
            mArray[initialized] = static_cast<T>(DEFAULT);
         break;
      }
   }

   /// Write the body of the vector (reused in vector specializations)        
   ///   @return the resulting body                                           
   TEMPLATE()
   template<class TOKEN>
   Flow::Code TME()::Serialize() const {
      Flow::Code result;
      if constexpr (S > 1 or not CT::Same<TME(), TOKEN>) {
         result += MetaOf<TOKEN>();
         result += Flow::Code::OpenScope;
      }

      auto data = Anyness::Block::From(mArray, S);
      result += Flow::Serialize<Flow::Code>(data);

      if constexpr (S > 1 or not CT::Same<TME(), TOKEN>)
         result += Flow::Code::CloseScope;

      return Abandon(result);
   }

   /// Convert from any vector to text                                        
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      return Serialize<TME()>();
   }

   /// Adapt a component to the vector's internal type                        
   ///   @param x - the component to adapt                                    
   ///   @return the adapted component                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr decltype(auto) TME()::Adapt(const CT::DenseNumber auto& x) const noexcept {
      using N = Deref<decltype(x)>;
      static_assert(CT::Convertible<N, T>, "Incompatible number");

      if constexpr (not CT::Same<N, T>)
         return static_cast<T>(x);
      else
         return x;
   }


   ///                                                                        
   ///   Access                                                               
   ///                                                                        
   /// Get the value of a specific component index                            
   ///   @attention assumes index is in vector's size limits                  
   ///   @param i - index of the component (0, 1, 2 correspond to X, Y, Z)    
   ///   @return a reference to the component                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T& TME()::Get(const Offset i) const noexcept {
      //LANGULUS_ASSUME(UserAssumes, i < S, "Index is out of limits");
      return mArray[i];
   }

   /// Get the value of a specific component index (with static check)        
   ///   @return a reference to the component                                 
   TEMPLATE()
   template<Offset I>
   LANGULUS(INLINED)
   constexpr const T& TME()::GetIdx() const noexcept {
      static_assert(I < S, "Index is out of limits");
      return Get(I);
   }

   /// Get Nth vector element (mutable)                                       
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr T& TME()::operator [] (const Offset a) noexcept {
      return const_cast<T&>(Get(a));
   }

   /// Get Nth vector element                                                 
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T& TME()::operator [] (const Offset a) const noexcept {
      return Get(a);
   }

   /// Get the raw array                                                      
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T* TME()::GetRaw() const noexcept {
      return mArray;
   }

   /// Get the raw array (mutable)                                            
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE() LANGULUS(INLINED)
   constexpr T* TME()::GetRaw() noexcept {
      return mArray;
   }

   /// Get the number of components                                           
   ///   @return the number of components                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr Count TME()::GetCount() const noexcept {
      return MemberCount;
   }

   /// Get the squared magnitute of the vector                                
   ///   @return the length of the vector, before the Sqrt operation          
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::LengthSquared() const noexcept {
      auto start = mArray;
      const auto end = mArray + S;
      T accum = Math::Sq(*(start++));
      while (start != end)
         accum += Math::Sq(*(start++));
      return accum;
   }

   /// Get the magnitute of the vector                                        
   ///   @return the length of the vector                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::Length() const noexcept {
      return Math::Sqrt(LengthSquared());
   }

   /// Check if vector is a degenerate, that is at least one component is 0   
   ///   @return true if vector is degenerate                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      auto start = mArray;
      const auto end = mArray + S;
      while (start != end) {
         if (*(start++) == T {})
            return true;
      }

      return false;
   }

   /// Mutable swizzle                                                        
   ///   @returns a proxy vector with the selected components                 
   TEMPLATE()
   template<Offset HEAD, Offset... TAIL>
   LANGULUS(INLINED)
   decltype(auto) TME()::Swz() noexcept {
      if constexpr (sizeof...(TAIL) == 0)
         return mArray[HEAD];
      else
         return Inner::TProxyVector<T, S, HEAD, TAIL...> {*this};
   }

   /// Immutable swizzle, just returns a shuffled vector                      
   ///   @returns a simple vector with the selected copied components         
   TEMPLATE()
   template<Offset HEAD, Offset... TAIL>
   LANGULUS(INLINED)
   constexpr decltype(auto) TME()::Swz() const noexcept {
      if constexpr (sizeof...(TAIL) == 0)
         return mArray[HEAD];
      else
         return TVector<T, sizeof...(TAIL) + 1> {mArray[HEAD], mArray[TAIL]...};
   }

   /// Cast the vector to another number type, with the ability to normalize  
   ///   @tparam AS - the type of number to cast to                           
   ///   @tparam NORMALIZE - whether or not to normalize the result           
   ///   @return the converted vector                                         
   TEMPLATE()
   template<class AS, bool NORMALIZE>
   LANGULUS(INLINED)
   constexpr TVector<AS, S> TME()::AsCast() const noexcept {
      auto converted = SIMD::Convert<0, Decay<AS>>(mArray);
      if constexpr (NORMALIZE) {
         // Normalize all elements by the old numeric limits            
         constexpr AS factor = AS {1} / AS {::std::numeric_limits<T>::max()};
         converted = SIMD::Inner::Multiply(converted, SIMD::Set(factor));
      }

      TVector<AS, S> result;
      SIMD::Store(converted, result.mArray);
      return result;
   }

   /// Multiply all components together                                       
   ///   @tparam ALTS - number of dimensions to multiply together             
   ///   @return the product                                                  
   TEMPLATE()
   template<Count ALTS>
   LANGULUS(INLINED)
   constexpr auto TME()::Volume() const noexcept {
      static_assert(ALTS > 1, "Degenerated volume, use higher rank");
      static_assert(ALTS <= S, "Rank out of limits");

      T product {1};
      auto start = mArray;
      const auto end = mArray + ALTS;
      while (start != end)
         product *= *(start++);
      return product;
   }

   /// Copy scalar                                                            
   ///   @param scalar - the scalar value                                     
   ///   @return a reference to this vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::Scalar auto& scalar) noexcept {
      new (this) TVector {scalar};
      return *this;
   }

   /// Copy vector                                                            
   ///   @param vec - the vector to copy                                      
   ///   @return a reference to this vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::Vector auto& vec) noexcept {
      new (this) TVector {vec};
      return *this;
   }

   /// Set only a specific component                                          
   ///   @param com - the component to overwrite                              
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<CT::DenseNumber N, CT::Dimension D>
   LANGULUS(INLINED)
   constexpr auto& TME()::operator = (const TVectorComponent<N, D>& com) noexcept {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      mArray[D::Index] = Adapt(com.mValue);
      return *this;
   }

   /// Dot product                                                            
   ///   @param other - the vector to dot with                                
   ///   @return the dot product of both vectors                              
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr T TME()::Dot(const TVEC(ALT)& other) const noexcept {
      auto source = other.mArray;
      auto start = mArray;
      const auto end = mArray + Min(S, ALTS);
      T accum = *(start++) * *(source++);
      while (start != end)
         accum += *(start++) * *(source++);
      return accum;
   }

   /// Cross product                                                          
   ///   @param rhs - the vector to cross with                                
   ///   @return the cross product of both vectors                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr TVector<T, 3> TME()::Cross(const TVEC(ALT)& rhs) const noexcept requires (S >= 3 && ALTS >= 3) {
      return {
         mArray[1] * rhs[2] - mArray[2] * rhs[1],
         mArray[2] * rhs[0] - mArray[0] * rhs[2],
         mArray[0] * rhs[1] - mArray[1] * rhs[0]
      };
   }

   /// Normalize                                                              
   ///   @return the normalized vector                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Normalize() const requires (S > 1) {
      const auto l = Length();
      if (l == T {}) UNLIKELY()
         LANGULUS_THROW(Arithmetic, "Degenerate vector");
      return *this * (T {1} / l);
   }

   /// Clamp between a minimum and maximum                                    
   ///   @param min - lower limit                                             
   ///   @param max - higher limit                                            
   ///   @return the clamped equivalent of this vector                        
   TEMPLATE()
   template<TARGS(MIN), TARGS(MAX)>
   LANGULUS(INLINED)
   constexpr auto TME()::Clamp(const TVEC(MIN)& min, const TVEC(MAX)& max) const noexcept {
      TVector result {*this};
      auto minp = min.mArray;
      auto maxp = max.mArray;
      auto start = result.mArray;
      const auto end = result.mArray + Min(S, MINS, MAXS);
      while (start != end) {
         *start = Clamp(*start, *(minp++), *(maxp++));
         ++start;
      }
      return result;
   }

   /// Clamp outide a minimum and maximum                                     
   ///   @param min - lower limit                                             
   ///   @param max - higher limit                                            
   ///   @return the clamped equivalent of this vector                        
   TEMPLATE()
   template<TARGS(MIN), TARGS(MAX)>
   LANGULUS(INLINED)
   constexpr auto TME()::ClampRev(const TVEC(MIN)& min, const TVEC(MAX)& max) const noexcept {
      TVector result {*this};
      auto minp = min.mArray;
      auto maxp = max.mArray;
      auto start = result.mArray;
      const auto end = result.mArray + Min(S, MINS, MAXS);
      while (start != end) {
         *start = ClampRev(*start, *(minp++), *(maxp++));
         ++start;
      }
      return result;
   }

   /// Round each element of the vector                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Round() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Round(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round down each vector component                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Floor() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Floor(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round up each vector component                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Ceil() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Ceil(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Invert negative components of vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Abs() const noexcept {
      if constexpr (CT::Signed<T>) {
         T result[S];
         SIMD::Store(SIMD::Abs(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Get biggest possible vector of the type                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Max() noexcept {
      return ::std::numeric_limits<T>::max();
   }

   /// Get scalar maximum of each element                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Max(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Max(mArray, limit), result);
      return result;
   }

   /// Get maximum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr auto TME()::Max(const TVEC(ALT)& limits) const noexcept {
      T result[Math::Min(S, ALTS)];
      SIMD::Store(SIMD::Max(mArray, limits.mArray), result);
      return result;
   }

   /// Get smallest possible vector of the type                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Min() noexcept {
      if constexpr (CT::Real<T>)
         return {::std::numeric_limits<T>::lowest()};
      else
         return {::std::numeric_limits<T>::min()};
   }

   /// Get scalar minimum of each element                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Min(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Min(mArray, limit), result);
      return result;
   }

   /// Get minimum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr auto TME()::Min(const TVEC(ALT)& limits) const noexcept {
      T result[Min(S, ALTS)];
      SIMD::Store(SIMD::Min(mArray, limits.mArray), result);
      return result;
   }
   
   /// Horizontal max                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMax() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Math::Max(*(start++), t);
      return t;
   }

   /// Horizontal min                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMin() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Math::Min(*(start++), t);
      return t;
   }

   /// Horizontal sum                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HSum() const noexcept {
      // Related: https://stackoverflow.com/questions/6996764/          
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t += *(start++);
      return t;
   }

   /// Horizontal multiply (similar to Volume)                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMul() const noexcept {
      T product {1};
      for (auto& v : mArray)
         product *= v;
      return product;
   }

   /// Sign                                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sign() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sign(v);
      return result;
   }

   /// Modulate via a scalar                                                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Mod(const T& period) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Mod(v, period);
      return result;
   }

   /// Modulate via a vector                                                  
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr auto TME()::Mod(const TVEC(ALT)& period) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = period.mArray;
      for (auto& v : result)
         v = Math::Mod(*(lhs++), *(rhs++));
      return result;
   }

   /// Step via a scalar                                                      
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Step(const T& edge) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Step(edge, v);
      return result;
   }

   /// Step via a vector                                                      
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(INLINED)
   constexpr auto TME()::Step(const TVEC(ALT)& edge) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = edge.mArray;
      for (auto& v : result)
         v = Math::Step(*(rhs++), *(lhs++));
      return result;
   }

   /// Power via a vector                                                     
   TEMPLATE()
   template<class ALT>
   LANGULUS(INLINED)
   constexpr TME() TME()::Pow(const ALT& exponents) const noexcept {
      return SIMD::Power(mArray, exponents);
   }

   /// Fraction                                                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Frac() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Frac(v);
      return result;
   }

   /// Square root                                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sqrt() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sqrt(v);
      return result;
   }

   /// Exponent                                                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Exp() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Exp(v);
      return result;
   }

   /// Sine                                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sin() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sin(v);
      return result;
   }

   /// Cosine                                                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Cos() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Cos(v);
      return result;
   }

   /// Quicksort                                                              
   TEMPLATE() LANGULUS(INLINED)
   auto& TME()::Sort() noexcept {
      const auto compare = [](const void* p1, const void* p2) noexcept {
         auto g1 = static_cast<const T*>(p1);
         auto g2 = static_cast<const T*>(p2);
         if constexpr (CT::Sparse<T>) {
            if (**g1 < **g2)        return -1;
            else if (**g1 > **g2)   return  1;
            else                    return  0;
         }
         else {
            if (*g1 < *g2)          return -1;
            else if (*g1 > *g2)     return  1;
            else                    return  0;
         }
      };

      qsort(mArray, S, sizeof(T), compare);
      return *this;
   }

   /// Warp (used for periodic boundary conditions)                           
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Warp(const T& scalar) const noexcept {
      if constexpr (CT::Signed<T>) {
         const auto absScale = Abs(scalar);
         const auto halfScale = absScale / T {2};
         T result[S];
         T* it = result;
         for (auto& v : mArray) {
            *(it++) = v > halfScale
               ? v - absScale : v < -halfScale
                  ? v + absScale : v;
         }

         return result;
      }
      else {
         T result[S];
         T* it = result;
         for (auto& v : mArray)
            *(it++) = v > scalar ? v - scalar : v;
         return result;
      }
   }

   /// Implicitly convert to a number if size is 1                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator const T& () const noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Implicitly convert to a number if size is 1 (mutable)                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator T& () noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Explicit cast to a compatible number of different type                 
   TEMPLATE()
   template<CT::DenseNumber N>
   LANGULUS(INLINED)
   constexpr TME()::operator N () const noexcept requires (S == 1 and CT::Convertible<N, T>) {
      return static_cast<N>(*mArray);
   }
   
   TEMPLATE()
   template<Count ALTS>
   LANGULUS(INLINED)
   TME()::operator TVector<T, ALTS>& () noexcept requires (ALTS < S) {
      return reinterpret_cast<TVector<T, ALTS>&>(*this);
   }

   TEMPLATE()
   template<Count ALTS>
   LANGULUS(INLINED)
   TME()::operator const TVector<T, ALTS>& () const noexcept requires (ALTS < S) {
      return reinterpret_cast<const TVector<T, ALTS>&>(*this);
   }


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// All operations rely on IF_CONSTEXPR() to check whether function is     
   /// executed in constexpr context or not, and then picking an optimized    
   /// SIMD routine, or a default constexpr one                               
   ///                                                                        

   /// Returns an inverted vector                                             
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& rhs) noexcept {
      return rhs * Decay<TypeOf<decltype(rhs)>> {-1};
   }

   /// Returns the sum of any two vectors                                     
   /// Only the intersecting elements are added and returned:                 
   ///   v[4] + v[2] = v[2]                                                   
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Vector + Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Scalar + Vector                                                        
   constexpr auto operator + (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Returns the difference of two vectors                                  
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }

   /// Vector - Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }

   /// Scalar - Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }

   /// Returns the product of two vectors                                     
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs)};
   }

   /// Vector * Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      typename Ret::ArrayType uninitialized;
      SIMD::Multiply(lhs, rhs, uninitialized);
      return Ret {uninitialized};
   }

   /// Scalar * Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs)};
   }

   /// Returns the division of two vectors                                    
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }

   /// Vector / Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }

   /// Scalar / Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }

   /// Vector << Vector                                                       
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator << (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }

   /// Vector << Scalar                                                       
   template<CT::VectorBased LHS, CT::DenseScalar RHS>
   LANGULUS(INLINED)
   constexpr auto operator << (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }

   /// Scalar << Vector                                                       
   template<CT::DenseScalar LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator << (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }
   
   /// Vector >> Vector                                                       
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator >> (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }

   /// Vector >> Scalar                                                       
   template<CT::VectorBased LHS, CT::DenseScalar RHS>
   LANGULUS(INLINED)
   constexpr auto operator >> (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }

   /// Scalar >> Vector                                                       
   template<CT::DenseScalar LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator >> (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }
   
   /// Vector xor Vector                                                      
   template<CT::VectorBased LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }

   /// Vector xor Scalar                                                      
   template<CT::VectorBased LHS, CT::DenseScalar RHS>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }

   /// Scalar xor Vector                                                      
   template<CT::DenseScalar LHS, CT::VectorBased RHS>
   LANGULUS(INLINED)
   constexpr auto operator ^ (const LHS& lhs, const RHS& rhs)
   noexcept requires CT::Integer<TypeOf<LHS>, TypeOf<RHS>> {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add vectors                                                            
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Add(lhs, rhs, lhs);
      return lhs;
   }

   /// Add vector and a scalar                                                
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      SIMD::Add(lhs, rhs, lhs);
      return lhs;
   }

   /// Subtract vectors                                                       
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Subtract(lhs, rhs, lhs);
      return lhs;
   }

   /// Subtract vector and a scalar                                           
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      SIMD::Subtract(lhs, rhs, lhs);
      return lhs;
   }

   /// Multiply vectors                                                       
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Multiply(lhs, rhs, lhs);
      return lhs;
   }

   /// Multiply vector by a scalar                                            
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      SIMD::Multiply(lhs, rhs, lhs);
      return lhs;
   }

   /// Divide dense vectors                                                   
   /// This function will throw on division by zero                           
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) {
      SIMD::Divide(lhs, rhs, lhs);
      return lhs;
   }

   /// Divide dense vector and a scalar                                       
   /// This function will throw on division by zero                           
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) {
      SIMD::Divide(lhs, rhs, lhs);
      return lhs;
   }


   ///                                                                        
   ///   Compare                                                              
   ///                                                                        
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator < (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator < (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator > (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator > (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator > (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator == (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::DenseScalar auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   LANGULUS(INLINED)
   constexpr auto operator != (const CT::DenseScalar auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }


   ///                                                                        
   ///   Iteration                                                            
   ///                                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr T* TME()::begin() noexcept {
      return mArray;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr T* TME()::end() noexcept {
      return mArray + S;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr T* TME()::last() noexcept {
      return mArray + S - 1;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const T* TME()::begin() const noexcept {
      return mArray;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const T* TME()::end() const noexcept {
      return mArray + S;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const T* TME()::last() const noexcept {
      return mArray + S - 1;
   }

} // namespace Langulus::Math

#undef TARGS
#undef TVEC
#undef TEMPLATE
#undef TME


///                                                                           
///   Canonical vectors                                                       
///                                                                           
namespace Langulus::Axes
{
   using namespace ::Langulus::Math;

   /// Canonical X axis                                                       
   template<CT::DenseNumber T = Real>
   constexpr TVector<T, 4> X {1, 0, 0, 0};
   
   /// Canonical Y axis                                                       
   template<CT::DenseNumber T = Real>
   constexpr TVector<T, 4> Y {0, 1, 0, 0};

   /// Canonical Z axis                                                       
   template<CT::DenseNumber T = Real>
   constexpr TVector<T, 4> Z {0, 0, 1, 0};

   /// Canonical W axis                                                       
   template<CT::DenseNumber T = Real>
   constexpr TVector<T, 4> W {0, 0, 0, 1};
   
   /// Canonical world origin                                                 
   template<CT::DenseNumber T = Real>
   constexpr TVector<T, 4> Origin {0, 0, 0, 0};

   /// Canonical forward vector, pointing towards the screen, in positive Z   
   template<CT::DenseNumber T = Real>
   constexpr auto Forward = Z<T>;

   /// Canonical backward vector, towards the human device, in negative Z     
   template<CT::DenseNumber T = Real>
   constexpr auto Backward = -Z<T>;

   /// Canonical up vector, pointing from the ground up, in positive Y        
   template<CT::DenseNumber T = Real>
   constexpr auto Up = Y<T>;

   /// Canonical down vector, pointing in gravity's direction, in negative Y  
   template<CT::DenseNumber T = Real>
   constexpr auto Down = -Y<T>;

   /// Canonical right vector, pointing to right hand, in positive X          
   template<CT::DenseNumber T = Real>
   constexpr auto Right = X<T>;

   /// Canonical left vector, pointing to left hand, in negative X            
   template<CT::DenseNumber T = Real>
   constexpr auto Left = -X<T>;

} // Langulus::Cardinal
