///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TVector.hpp"
#include "../Numbers/TVectorComponent.hpp"

namespace Langulus::Math
{
   
   /// Default vector constructor initialized all components to DefaultMember 
   TEMPLATE()
   constexpr TME()::TVector() noexcept {
      for (auto& v : mArray)
         v = DefaultMember;
   }

   /// Copy (and convert) from same/bigger vectors of same/different types    
   /// Also acts as a copy-constructor                                        
   ///   @param a - vector to copy                                            
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr TME()::TVector(const TVEC(ALT)& a) noexcept {
      if constexpr (S == 1) {
         // No loop, just use first element                             
         *mArray = Adapt(*a.mArray);
      }
      else if constexpr (ALTS == 1) {
         // Prepare the scalar and set all elements to it               
         const auto scalar = Adapt(a[0]);
         for (auto& v : mArray)
            v = scalar;
      }
      else {
         // Convert element-by-element                                  
         const ALTT* source = a.mArray;
         T* start = mArray;
         auto end = mArray + Math::Min(S, ALTS);

         // Copy the available components                               
         while (start != end)
            *(start++) = Adapt(*(source++));

         if constexpr (ALTS < S) {
            // And fill the rest with the default value                 
            end = mArray + S;
            while (start != end)
               *(start++) = DefaultMember;
         }
      }
   }

   /// Construction from scalar                                               
   ///   @param a - scalar to copy                                            
   TEMPLATE()
   template<CT::DenseNumber N>
   constexpr TME()::TVector(const N& a) noexcept requires IsCompatible<N> {
      if constexpr (S == 1)
         *mArray = Adapt(a);
      else {
         const auto scalar = Adapt(a);
         for (auto& v : mArray)
            v = scalar;
      }
   }
   
   /// Construction from an unbounded array                                   
   ///   @attention very unsafe                                               
   ///   @param a - array to copy                                             
   TEMPLATE()
   template<CT::DenseNumber N>
   constexpr TME()::TVector(const N* a) noexcept requires IsCompatible<N> {
      for (auto& v : mArray)
         v = Adapt(*(a++));
   }
   
   /// Construction from a bounded array                                      
   ///   @param a - array to copy                                             
   TEMPLATE()
   template<CT::Array N>
   constexpr TME()::TVector(const N& a) noexcept requires IsCompatible<Decay<N>> {
      static_assert(ExtentOf<N> >= S,
         "This vector is too powerful for your array");

      const Decay<N>* source = a;
      for (auto& v : mArray)
         v = Adapt(*(source++));
   }

   /// Manual construction via a variadic head-tail                           
   /// Any of the elements can be another vector, as long all all vectors'    
   /// element counts and scalars sum up to this vector type's size           
   TEMPLATE()
   template<class HEAD, class... TAIL>
   constexpr TME()::TVector(const HEAD& head, const TAIL&... tail) noexcept requires (S > 1 && sizeof...(TAIL) > 0) {
      if constexpr (CT::Vector<HEAD>) {
         if constexpr (HEAD::MemberCount < MemberCount) {
            for (Offset i = 0; i < HEAD::MemberCount; ++i)
               mArray[i] = Adapt(head[i]);
            const TVector<T, MemberCount - HEAD::MemberCount> theRest {tail...};
            for (Offset i = HEAD::MemberCount; i < MemberCount; ++i)
               mArray[i] = theRest.mArray[i - HEAD::MemberCount];
         }
         else LANGULUS_ERROR("More elements provided than required");
      }
      else if constexpr (IsCompatible<HEAD>) {
         mArray[0] = Adapt(head);
         const TVector<T, MemberCount - 1> theRest {tail...};
         for (Offset i = 1; i < MemberCount; ++i)
            mArray[i] = theRest.mArray[i - 1];
      }
      else LANGULUS_ERROR(
         "Bad element type in dense vector unfolding constructor"
         " - must be CT::Vector or a number");
   }

   /// Construct from component, if its index is smaller than SIZE            
   ///   @param a - component to set                                          
   TEMPLATE()
   template<CT::DenseNumber N, CT::Dimension D>
   constexpr TME()::TVector(const TVectorComponent<N, D>& a) noexcept
      : TVector {} {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      mArray[D::Index] = Adapt(a.mValue);
   }

   /// Write the body of the vector (reused in vector specializations)        
   ///   @param result - [out] the resulting body                             
   TEMPLATE()
   template<class TOKEN>
   Flow::Code TME()::Serialize() const {
      Flow::Code result;
      if constexpr (S > 1 || !CT::Same<TME(), TOKEN>) {
         result += MetaOf<TOKEN>();
         result += Flow::Code::OpenScope;
      }

      for (Offset i = 0; i < S; ++i) {
         result += Text {mArray[i]};
         if (i < S - 1)
            result += ", ";
      }

      if constexpr (S > 1 || !CT::Same<TME(), TOKEN>)
         result += Flow::Code::CloseScope;

      return Abandon(result);
   }

   /// Convert from any vector to text                                        
   TEMPLATE()
   TME()::operator Flow::Code() const {
      return Serialize<TME()>();
   }

   /// Get the value of a specific component index                            
   TEMPLATE()
   template<CT::DenseNumber N>
   constexpr decltype(auto) TME()::Adapt(const N& item) const noexcept requires IsCompatible<N> {
      if constexpr (!CT::Same<N, T>)
         return static_cast<T>(item);
      else
         return item;
   }


   ///                                                                        
   ///   Access                                                               
   ///                                                                        
   /// Get the value of a specific component index                            
   ///   @attention assumes index is in vector's size limits                  
   ///   @param i - index of the component (0, 1, 2 correspond to X, Y, Z)    
   ///   @return a reference to the component                                 
   TEMPLATE()
   constexpr const T& TME()::Get(const Offset i) const noexcept {
      LANGULUS_ASSUME(UserAssumes, i < S, "Index is out of limits");
      return mArray[i];
   }

   /// Get the value of a specific component index (with static check)        
   ///   @return a reference to the component                                 
   TEMPLATE()
   template<Offset I>
   constexpr const T& TME()::GetIdx() const noexcept {
      static_assert(I < S, "Index is out of limits");
      return Get(I);
   }

   /// Get Nth vector element (mutable)                                       
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE()
   constexpr T& TME()::operator [] (const Offset a) noexcept {
      return const_cast<T&>(Get(a));
   }

   /// Get Nth vector element                                                 
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE()
   constexpr const T& TME()::operator [] (const Offset a) const noexcept {
      return Get(a);
   }

   /// Get the raw array                                                      
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE()
   constexpr const T* TME()::GetRaw() const noexcept {
      return mArray;
   }

   /// Get the raw array (mutable)                                            
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE()
   constexpr T* TME()::GetRaw() noexcept {
      return mArray;
   }

   /// Get the number of components                                           
   ///   @return the number of components                                     
   TEMPLATE()
   constexpr Count TME()::GetCount() const noexcept {
      return MemberCount;
   }

   /// Get the squared magnitute of the vector                                
   ///   @return the length of the vector, before the Sqrt operation          
   TEMPLATE()
   constexpr T TME()::LengthSquared() const noexcept {
      auto start = mArray;
      const auto end = mArray + S;
      T accum = Sq(*(start++));
      while (start != end)
         accum += Sq(*(start++));
      return accum;
   }

   /// Get the magnitute of the vector                                        
   ///   @return the length of the vector                                     
   TEMPLATE()
   constexpr T TME()::Length() const noexcept {
      return Math::Sqrt(LengthSquared());
   }

   /// Check if vector is a degenerate, that is at least one component is 0   
   ///   @return true if vector is degenerate                                 
   TEMPLATE()
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
   NOD() constexpr TVector<AS, S> TME()::AsCast() const noexcept {
      auto converted = SIMD::Convert<0, Decay<AS>>(mArray);
      if constexpr (NORMALIZE) {
         // Normalize all elements by the old numeric limits            
         constexpr AS factor = AS {1} / AS {::std::numeric_limits<T>::max()};
         converted = SIMD::MultiplyInner(converted, SIMD::Set(factor));
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
   TEMPLATE()
   template<CT::DenseNumber N>
   constexpr auto& TME()::operator = (const N& scalar) noexcept {
      new (this) TVector {scalar};
      return *this;
   }

   /// Copy vector                                                            
   ///   @param vec - the vector to copy                                      
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto& TME()::operator = (const TVEC(ALT)& vec) noexcept {
      static_assert(S <= ALTS, "LHS must be of same or smaller size than RHS");
      new (this) TVector {vec};
      return *this;
   }

   /// Set only a specific component                                          
   ///   @param com - the component to overwrite                              
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<CT::DenseNumber N, CT::Dimension D>
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
   constexpr TVector<T, 3> TME()::Cross(const TVEC(ALT)& rhs) const noexcept requires (S >= 3 && ALTS >= 3) {
      return {
         mArray[1] * rhs[2] - mArray[2] * rhs[1],
         mArray[2] * rhs[0] - mArray[0] * rhs[2],
         mArray[0] * rhs[1] - mArray[1] * rhs[0]
      };
   }

   /// Normalize                                                              
   ///   @return the normalized vector                                        
   TEMPLATE()
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
   TEMPLATE()
   constexpr auto TME()::Round() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Round(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round down each vector component                                       
   TEMPLATE()
   constexpr auto TME()::Floor() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Floor(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round up each vector component                                         
   TEMPLATE()
   constexpr auto TME()::Ceil() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Ceil(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Invert negative components of vector                                   
   TEMPLATE()
   constexpr auto TME()::Abs() const noexcept {
      if constexpr (CT::Signed<T>) {
         T result[S];
         SIMD::Store(SIMD::Abs(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Get biggest possible vector of the type                                
   TEMPLATE()
   constexpr TME() TME()::Max() noexcept {
      return ::std::numeric_limits<T>::max();
   }

   /// Get scalar maximum of each element                                     
   TEMPLATE()
   constexpr auto TME()::Max(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Max(mArray, limit), result);
      return result;
   }

   /// Get maximum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto TME()::Max(const TVEC(ALT)& limits) const noexcept {
      T result[Min(S, ALTS)];
      SIMD::Store(SIMD::Max(mArray, limits.mArray), result);
      return result;
   }

   /// Get smallest possible vector of the type                               
   TEMPLATE()
   constexpr TME() TME()::Min() noexcept {
      if constexpr (CT::Real<T>)
         return {::std::numeric_limits<T>::lowest()};
      else
         return {::std::numeric_limits<T>::min()};
   }

   /// Get scalar minimum of each element                                     
   TEMPLATE()
   constexpr auto TME()::Min(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Min(mArray, limit), result);
      return result;
   }

   /// Get minimum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto TME()::Min(const TVEC(ALT)& limits) const noexcept {
      T result[Min(S, ALTS)];
      SIMD::Store(SIMD::Min(mArray, limits.mArray), result);
      return result;
   }
   
   /// Horizontal max                                                         
   TEMPLATE()
   constexpr auto TME()::HMax() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Max(*(start++), t);
      return t;
   }

   /// Horizontal min                                                         
   TEMPLATE()
   constexpr auto TME()::HMin() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Min(*(start++), t);
      return t;
   }

   /// Horizontal sum                                                         
   TEMPLATE()
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
   TEMPLATE()
   constexpr auto TME()::HMul() const noexcept {
      T product {1};
      for (auto& v : mArray)
         product *= v;
      return product;
   }

   /// Sign                                                                   
   TEMPLATE()
   constexpr auto TME()::Sign() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Sign(v);
      return result;
   }

   /// Modulate via a scalar                                                  
   TEMPLATE()
   constexpr auto TME()::Mod(const T& period) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Mod(v, period);
      return result;
   }

   /// Modulate via a vector                                                  
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto TME()::Mod(const TVEC(ALT)& period) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = period.mArray;
      for (auto& v : result)
         v = Mod(*(lhs++), *(rhs++));
      return result;
   }

   /// Step via a scalar                                                      
   TEMPLATE()
   constexpr auto TME()::Step(const T& edge) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Step(edge, v);
      return result;
   }

   /// Step via a vector                                                      
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto TME()::Step(const TVEC(ALT)& edge) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = edge.mArray;
      for (auto& v : result)
         v = Step(*(rhs++), *(lhs++));
      return result;
   }

   /// Power via a scalar                                                     
   TEMPLATE()
   constexpr auto TME()::Pow(const T& exponent) const noexcept {
      return SIMD::PowerWrap<TVector>(mArray, exponent);
   }

   /// Power via a vector                                                     
   TEMPLATE()
   template<TARGS(ALT)>
   constexpr auto TME()::Pow(const TVEC(ALT)& exponents) const noexcept {
      return SIMD::PowerWrap<TVector>(mArray, exponents.mArray);
   }

   /// Fraction                                                               
   TEMPLATE()
   constexpr auto TME()::Frac() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Frac(v);
      return result;
   }

   /// Square root                                                            
   TEMPLATE()
   constexpr auto TME()::Sqrt() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Sqrt(v);
      return result;
   }

   /// Exponent                                                               
   TEMPLATE()
   constexpr auto TME()::Exp() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Exp(v);
      return result;
   }

   /// Sine                                                                   
   TEMPLATE()
   constexpr auto TME()::Sin() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Sin(v);
      return result;
   }

   /// Cosine                                                                 
   TEMPLATE()
   constexpr auto TME()::Cos() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Cos(v);
      return result;
   }

   /// Quicksort                                                              
   TEMPLATE()
   auto& TME()::Sort() noexcept {
      const auto compare = [](const void* p1, const void* p2) noexcept {
         auto g1 = static_cast<const T*>(p1);
         auto g2 = static_cast<const T*>(p2);
         if constexpr (CT::Sparse<T>) {
            if (**g1 < **g2)         return -1;
            else if (**g1 > **g2)   return  1;
            else                     return  0;
         }
         else {
            if (*g1 < *g2)            return -1;
            else if (*g1 > *g2)      return  1;
            else                     return  0;
         }
      };

      qsort(mArray, S, sizeof(T), compare);
      return *this;
   }

   /// Warp (used for periodic boundary conditions)                           
   TEMPLATE()
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
   TEMPLATE()
   constexpr TME()::operator const T& () const noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Implicitly convert to a number if size is 1 (mutable)                  
   TEMPLATE()
   constexpr TME()::operator T& () noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Explicit cast to a compatible number of different type                 
   TEMPLATE()
   template<CT::DenseNumber N>
   constexpr TME()::operator N () const noexcept requires (S == 1 && IsCompatible<N>) {
      return static_cast<N>(*mArray);
   }
   

   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted vector                                             
   template<TARGS(RHS)>
   auto operator - (const TVEC(RHS)& me) noexcept {
      return me * Decay<RHST>(-1);
   }

   /// Returns the sum of any two vectors                                     
   /// Only the intersecting elements are added and returned:                 
   ///   v[4] + v[2] = v[2]                                                   
   template<TARGS(LHS), TARGS(RHS)>
   auto operator + (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::AddWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector + Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   auto operator + (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] + other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::AddWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar + Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   auto operator + (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other + me[0];   // 1D vectors decay to a number        
      else
         return me + other;
   }

   /// Returns the difference of two vectors                                  
   template<TARGS(LHS), TARGS(RHS)>
   auto operator - (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::SubtractWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector - Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   auto operator - (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] - other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::SubtractWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar - Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   auto operator - (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other - me[0];   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::SubtractWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the product of two vectors                                     
   template<TARGS(LHS), TARGS(RHS)>
   auto operator * (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::MultiplyWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector * Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   auto operator * (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] * other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::MultiplyWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar * Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   auto operator * (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other * me[0];   // 1D vectors decay to a number        
      else 
         return me * other;
   }

   /// Returns the division of two vectors                                    
   template<TARGS(LHS), TARGS(RHS)>
   auto operator / (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::DivideWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector / Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   auto operator / (const TVEC(LHS)& me, const N& other) {
      if constexpr (LHSS == 1)
         return me[0] / other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::DivideWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar / Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   auto operator / (const N& other, const TVEC(RHS)& me) {
      if constexpr (RHSS == 1)
         return other / me[0];   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::DivideWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   auto operator << (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::ShiftLeftWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector << Scalar                                                       
   template<TARGS(LHS), CT::Integer N>
   auto operator << (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] << other;   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::ShiftLeftWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar << Vector                                                       
   template<TARGS(RHS), CT::Integer N>
   auto operator << (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
      if constexpr (RHSS == 1)
         return other << me[0];   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::ShiftLeftWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   auto operator >> (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::ShiftRightWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector >> Scalar                                                       
   template<TARGS(LHS), CT::Integer N>
   auto operator >> (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] >> other;   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::ShiftRightWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar >> Vector                                                       
   template<TARGS(RHS), CT::Integer N>
   auto operator >> (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
      if constexpr (RHSS == 1)
         return other >> me[0];   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::ShiftRightWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   auto operator ^ (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::XOrWrap<TVector<TYPE, Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector ^ Scalar                                                        
   template<TARGS(LHS), CT::Integer N>
   auto operator ^ (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] ^ other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::XOrWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar ^ Vector                                                        
   template<TARGS(RHS), CT::Integer N>
   auto operator ^ (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
      if constexpr (RHSS == 1)
         return other ^ me[0];   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::XOrWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add vectors                                                            
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator += (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Add(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Add vector and a scalar                                                
   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator += (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Add(me.mArray, other, me.mArray);
      return me;
   }

   /// Subtract vectors                                                       
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator -= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Subtract(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Subtract vector and a scalar                                           
   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator -= (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Subtract(me.mArray, other, me.mArray);
      return me;
   }

   /// Multiply vectors                                                       
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator *= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Multiply(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Multiply vector by a scalar                                            
   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator *= (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Multiply(me.mArray, other, me.mArray);
      return me;
   }

   /// Divide dense vectors                                                   
   /// This function will throw on division by zero                           
   template<TARGS(LHS), TARGS(RHS)>
   auto& operator /= (TVEC(LHS)& me, const TVEC(RHS)& other) {
      SIMD::Divide(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Divide dense vector and a scalar                                       
   /// This function will throw on division by zero                           
   template<TARGS(LHS), CT::DenseNumber N>
   auto& operator /= (TVEC(LHS)& me, const N& other) {
      SIMD::Divide(me.mArray, other, me.mArray);
      return me;
   }


   ///                                                                        
   ///   Compare                                                              
   ///                                                                        
   template<TARGS(LHS), TARGS(RHS)>
   auto operator < (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::Lesser(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   auto operator < (const TVEC(LHS)& me, const N& other) {
      return SIMD::Lesser(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   auto operator < (const N& other, const TVEC(RHS)& me) {
      return SIMD::Lesser(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   auto operator <= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::EqualsOrLesser(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   auto operator <= (const TVEC(LHS)& me, const N& other) {
      return SIMD::EqualsOrLesser(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   auto operator <= (const N& other, const TVEC(RHS)& me) {
      return SIMD::EqualsOrLesser(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   auto operator > (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::Greater(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   auto operator > (const TVEC(LHS)& me, const N& other) {
      return SIMD::Greater(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   auto operator > (const N& other, const TVEC(RHS)& me) {
      return SIMD::Greater(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   auto operator >= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::EqualsOrGreater(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   auto operator >= (const TVEC(LHS)& me, const N& other) {
      return SIMD::EqualsOrGreater(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   auto operator >= (const N& other, const TVEC(RHS)& me) {
      return SIMD::EqualsOrGreater(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   bool operator == (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::Equals(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   bool operator == (const TVEC(LHS)& me, const N& other) {
      return SIMD::Equals(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   bool operator == (const N& other, const TVEC(RHS)& me) {
      return SIMD::Equals(other, me.mArray);
   }

} // namespace Langulus::Math

