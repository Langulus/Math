///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "TVector.hpp"
#include "../Numbers/TNumber.inl"
#include <type_traits>

#define TARGS(a)     CT::ScalarBased a##T, Count a##S, int a##D
#define TVEC(a)      TVector<a##T, a##S, a##D>
#define TEMPLATE()   template<CT::ScalarBased T, Count S, int DEFAULT>
#define TME()        TVector<T, S, DEFAULT>


namespace Langulus::Math
{

   /// Default vector constructor - initialize components to Default          
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector() noexcept {
      if constexpr (S > 1) {
         static_assert(CT::Vector<TVector>,
            "Vectors should match CT::Vector, if their size is larger than 1");
      }
      else {
         static_assert(CT::Scalar<TVector>,
            "Vectors should match CT::Scalar, if their size is 1");
      }

      static_assert(not CT::QuaternionBased<TVector>,
         "Vectors shouldn't match CT::QuaternionBased");
      static_assert(CT::VectorBased<TVector>,
         "Vectors should match CT::VectorBased");
      static_assert(sizeof(TVector) == sizeof(T) * S,
         "Vectors should match T*4 size");
      static_assert(CountOf<TVector> == S,
         "Vectors size should correspond to CountOf");
      static_assert(CT::Exact<TypeOf<TVector>, T>,
         "Vectors should have type");

      for (auto& e : all)
         e = Default;
   }
   
   /// Construct from any vector (with conversion)                            
   ///   @param a - vector to use                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector(const CT::Vector auto& source) noexcept {
      SIMD::Convert<DEFAULT>(DeintCast(source), all);
   }

   /// Construct from any scalar (with conversion)                            
   ///   @param a - vector to use                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TVector(const CT::Scalar auto& source) noexcept {
      SIMD::Convert<DEFAULT>(DeintCast(source), all);
   }

   /// Manual construction via a variadic head-tail                           
   /// Excessive elements are ignored, while missing elements are defaulted   
   TEMPLATE() template<class T1, class T2, class...TN> LANGULUS(INLINED)
   constexpr TME()::TVector(const T1& t1, const T2& t2, const TN&...tn) noexcept {
      constexpr auto C1 = Math::Min(CountOf<T1>, MemberCount);
      if constexpr (CT::Vector<T1>) {
         // First element is vector/array, copy its elements            
         for (Offset i = 0; i < C1; ++i)
            all[i] = Adapt(t1[i]);
      }
      else {
         // First element is a scalar, copy it                          
         all[0] = Adapt(t1);
      }

      constexpr auto C2 = Math::Min(CountOf<T2>, MemberCount - C1);
      if constexpr (C2) {
         if constexpr (CT::Vector<T2>) {
            // Second element is vector/array, copy its elements        
            for (Offset i = C1; i < C1 + C2; ++i)
               all[i] = Adapt(t2[i - C1]);
         }
         else {
            // Second element is a scalar, copy it                      
            all[C1] = Adapt(t2);
         }

         // Combine all the rest of the arguments in a vector           
         if constexpr (sizeof...(TN)) {
            constexpr auto C3 = Math::Min(CountOf<TN...>, MemberCount - (C1 + C2));
            if constexpr (C3) {
               const TVector<T, C3> theRest {tn...};
               for (Offset i = C1 + C2; i < MemberCount; ++i)
                  all[i] = theRest[i - (C1 + C2)];
            }
         }
      }
   }

   /// Construct from a vector component                                      
   ///   @param a - component to set                                          
   TEMPLATE() template<CT::ScalarBased N, CT::Dimension D> LANGULUS(INLINED)
   constexpr TME()::TVector(const TVectorComponent<N, D>& source) noexcept
      : TVector {} {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      all[D::Index] = Adapt(source.mValue);
   }

   /// Construct from a SIMD register                                         
   ///   @param source - register                                             
   TEMPLATE() LANGULUS(INLINED)
   TME()::TVector(const CT::SIMD auto& source) noexcept {
      SIMD::Store(source, all);
   }

   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TME()::TVector(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TVector");

      // Attempt initializing without any conversion                    
      auto initialized = describe->ExtractData(all);
      if (not initialized) {
         // Attempt converting anything to T                            
         initialized = describe->ExtractDataAs(all);
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
            all[initialized] = all[0];
         break;
      default:
         // Initialize unavailable elements to the vector's default     
         for (; initialized < S; ++initialized)
            all[initialized] = Default;
         break;
      }
   }

   /// Write the body of the vector (reused in vector specializations)        
   ///   @return the resulting body                                           
   TEMPLATE() template<CT::Serial AS, class TOKEN>
   AS TME()::Serialize() const {
      AS result;
      constexpr bool SCOPED = S > 1 or not CT::Same<TVector, TOKEN>;
      if constexpr (SCOPED) {
         result += MetaDataOf<TOKEN>();
         result += '(';
      }

      Anyness::MakeBlock(all).Serialize(result);

      if constexpr (SCOPED)
         result += ')';
      return Abandon(result);
   }

   /// Stringify vector for debugging                                         
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      return Serialize<Anyness::Text, TVector>();
   }

   /// Serialize vector as code                                               
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      return Serialize<Flow::Code, TVector>();
   }

   /// Adapt a component to the vector's internal type                        
   ///   @param x - the component to adapt                                    
   ///   @return the adapted component                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr decltype(auto) TME()::Adapt(const CT::ScalarBased auto& x) noexcept {
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
   constexpr auto TME()::Get(const Offset i) const noexcept -> const T& {
      return all[i];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Get(const Offset i) noexcept -> T& {
      return all[i];
   }

   /// Get the value of a specific component index (with static check)        
   ///   @return a reference to the component                                 
   TEMPLATE() template<Offset I> LANGULUS(INLINED)
   constexpr auto TME()::GetIdx() const noexcept -> const T& {
      static_assert(I < S, "Index is out of limits");
      return all[I];
   }

   /// Get Nth vector element                                                 
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator [] (const Offset a) noexcept -> T& {
      return all[a];
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator [] (const Offset a) const noexcept -> const T& {
      return all[a];
   }

   /// Get the number of components                                           
   ///   @return the number of components                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::GetCount() const noexcept -> Count {
      return MemberCount;
   }

   /// Get the squared magnitute of the vector                                
   ///   @return the length of the vector, before the Sqrt operation          
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::LengthSquared() const noexcept -> T {
      auto start = all;
      const auto end = start + S;
      T accum = Math::Sq(*(start++));
      while (start != end)
         accum += Math::Sq(*(start++));
      return accum;
   }

   /// Get the magnitute of the vector                                        
   ///   @return the length of the vector                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Length() const noexcept -> T {
      return Math::Sqrt(LengthSquared());
   }

   /// Check if vector is a degenerate, that is at least one component is 0   
   ///   @return true if vector is degenerate                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      auto start = all;
      const auto end = start + S;
      while (start != end) {
         if (*(start++) == T {})
            return true;
      }

      return false;
   }

   /// Mutable swizzle                                                        
   ///   @returns a proxy vector with the selected components                 
   TEMPLATE() template<Offset E1, Offset...EN> LANGULUS(INLINED)
   decltype(auto) TME()::Swz() noexcept {
      if constexpr (sizeof...(EN) == 0)
         return (all[E1]);
      else
         return Inner::TProxyArray<T, S, DEFAULT, E1, EN...> {all};
   }

   /// Immutable swizzle, just returns a shuffled vector                      
   ///   @returns a simple vector with the selected copied components         
   TEMPLATE() template<Offset E1, Offset...EN> LANGULUS(INLINED)
   constexpr decltype(auto) TME()::Swz() const noexcept {
      if constexpr (sizeof...(EN) == 0)
         return (all[E1]);
      else
         return TVector<T, sizeof...(EN) + 1, DEFAULT> {all[E1], all[EN]...};
   }

   /// Cast the vector to another number type, with the ability to normalize  
   ///   @tparam AS - the type of number to cast to                           
   ///   @tparam NORMALIZE - whether or not to normalize the result           
   ///   @return the converted vector                                         
   TEMPLATE() template<class AS, bool NORMALIZE> LANGULUS(INLINED)
   constexpr TVector<AS, S> TME()::AsCast() const noexcept {
      AS converted[S];
      SIMD::Convert<0>(all, converted);

      if constexpr (NORMALIZE) {
         // Normalize all elements by the old numeric limits            
         constexpr AS factor = AS {1} / AS {::std::numeric_limits<T>::max()};
         return SIMD::Multiply(converted, factor);
      }
      else return converted;
   }

   /// Multiply all components together                                       
   ///   @tparam ALTS - number of dimensions to multiply together             
   ///   @return the product                                                  
   TEMPLATE() template<Count ALTS> LANGULUS(INLINED)
   constexpr auto TME()::Volume() const noexcept {
      static_assert(ALTS >  1, "Degenerated volume, use higher rank");
      static_assert(ALTS <= S, "Rank out of limits");

      T product {1};
      auto start = all;
      const auto end = start + ALTS;
      while (start != end)
         product *= *(start++);
      return product;
   }

   /// Copy scalar                                                            
   ///   @param scalar - the scalar value                                     
   ///   @return a reference to this vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const CT::Scalar auto& scalar) noexcept -> TVector& {
      return *new (this) TVector {scalar};
   }

   /// Copy vector                                                            
   ///   @param vec - the vector to copy                                      
   ///   @return a reference to this vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::operator = (const CT::Vector auto& vec) noexcept -> TVector& {
      return *new (this) TVector {vec};
   }

   /// Set only a specific component                                          
   ///   @param com - the component to overwrite                              
   ///   @return a reference to this vector                                   
   TEMPLATE() template<CT::ScalarBased N, CT::Dimension D> LANGULUS(INLINED)
   constexpr auto TME()::operator = (const TVectorComponent<N, D>& com) noexcept -> TVector& {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      all[D::Index] = Adapt(com.mValue);
      return *this;
   }

   /// Dot product                                                            
   ///   @param other - the vector to dot with                                
   ///   @return the dot product of both vectors                              
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Dot(const CT::VectorBased auto& other) const noexcept -> T {
      auto source = other.all;
      auto start = all;
      const auto end = start + Math::Min(S, CountOf<decltype(other)>);
      T accum = *(start++) * *(source++);
      while (start != end)
         accum += *(start++) * *(source++);
      return accum;
   }

   /// Cross product                                                          
   ///   @param rhs - the vector to cross with                                
   ///   @return the cross product of both vectors                            
   TEMPLATE() template<CT::VectorBased V> requires (S >= 3 and CountOf<V> >= 3)
   constexpr auto TME()::Cross(const V& rhs) const noexcept -> TVector<T, 3> {
      return { y * rhs.z - z * rhs.y,
               z * rhs.x - x * rhs.z,
               x * rhs.y - y * rhs.x };
   }

   /// Normalize                                                              
   ///   @return the normalized vector                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Normalize() const -> TVector requires (S > 1) {
      const auto l = Length();
      if (l == T {})
         LANGULUS_THROW(Arithmetic, "Degenerate vector");
      return *this * (T {1} / l);
   }

   /// Clamp between a minimum and maximum                                    
   ///   @param min - lower limit                                             
   ///   @param max - higher limit                                            
   ///   @return the clamped equivalent of this vector                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Clamp(const auto& min, const auto& max) const noexcept -> TVector {
      TVector result {*this};
      auto minp = min.all;
      auto maxp = max.all;
      auto start = result.all;
      const auto end = start
         + Math::Min(S, CountOf<decltype(min)>, CountOf<decltype(max)>);

      while (start != end) {
         *start = Math::Clamp(*start, *(minp++), *(maxp++));
         ++start;
      }
      return result;
   }

   /// Clamp outide a minimum and maximum                                     
   ///   @param min - lower limit                                             
   ///   @param max - higher limit                                            
   ///   @return the clamped equivalent of this vector                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::ClampRev(const auto& min, const auto& max) const noexcept -> TVector {
      TVector result {*this};
      auto minp = min.all;
      auto maxp = max.all;
      auto start = result.all;
      const auto end = start
         + Math::Min(S, CountOf<decltype(min)>, CountOf<decltype(max)>);

      while (start != end) {
         *start = Math::ClampRev(*start, *(minp++), *(maxp++));
         ++start;
      }
      return result;
   }

   /// Round each element of the vector                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Round() const noexcept -> TVector {
      if constexpr (CT::Real<T>)
         return SIMD::Round(*this);
      else
         return *this;
   }

   /// Round down each vector component                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Floor() const noexcept -> TVector {
      if constexpr (CT::Real<T>)
         return SIMD::Floor(*this);
      else
         return *this;
   }

   /// Round up each vector component                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Ceil() const noexcept -> TVector {
      if constexpr (CT::Real<T>)
         return SIMD::Ceil(*this);
      else
         return *this;
   }

   /// Invert negative components of vector                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Abs() const noexcept -> TVector {
      if constexpr (CT::Signed<T>)
         return SIMD::Abs(*this);
      else
         return *this;
   }

   /// Get biggest possible vector of the type                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Max() noexcept -> TVector {
      return ::std::numeric_limits<T>::max();
   }

   /// Get smallest possible vector of the type                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Min() noexcept -> TVector {
      if constexpr (CT::Real<T>)
         return {::std::numeric_limits<T>::lowest()};
      else
         return {::std::numeric_limits<T>::min()};
   }

   /// Get maximum of each element                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Max(const auto& limits) const noexcept {
      using Ret = LosslessVector<TVector, decltype(limits)>;
      return Ret {SIMD::Max(*this, limits)};
   }

   /// Get minimum of each element                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Min(const auto& limits) const noexcept {
      using Ret = LosslessVector<TVector, decltype(limits)>;
      return Ret {SIMD::Min(*this, limits)};
   }
   
   /// Horizontal max                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMax() const noexcept -> T {
      auto start = all;
      const auto end = start + S;
      T t = *(start++);
      while (start != end)
         t = Math::Max(*(start++), t);
      return t;
   }

   /// Horizontal min                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMin() const noexcept -> T {
      auto start = all;
      const auto end = start + S;
      T t = *(start++);
      while (start != end)
         t = Math::Min(*(start++), t);
      return t;
   }

   /// Horizontal sum                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HSum() const noexcept -> T {
      auto start = all;
      const auto end = start + S;
      T t = *(start++);
      while (start != end)
         t += *(start++);
      return t;
   }

   /// Horizontal multiply (similar to Volume)                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::HMul() const noexcept -> T {
      T product {1};
      for (auto& i : all)
         product *= i;
      return product;
   }

   /// Sign                                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sign() const noexcept -> TVector {
      if constexpr (CT::Unsigned<T>)
         return TVector {1};
      else {
         T result[S];
         T* it = result;
         for (auto& i : all)
            *(it++) = Math::Sign(i);
         return result;
      }
   }

   /// Modulate                                                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Mod(const auto& period) const noexcept -> TVector {
      using RHS = Deref<decltype(period)>;

      if constexpr (CT::Scalar<RHS>) {
         T result[S];
         T* it = result;
         for (auto& i : all)
            *(it++) = Math::Mod(i, period);
         return result;
      }
      else {
         T result[Math::Min(S, CountOf<RHS>)];
         const T* lhs = all;
         const T* rhs = period.all;
         for (auto& i : result)
            i = Math::Mod(*(lhs++), *(rhs++));
         return result;
      }
   }

   /// Step                                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Step(const auto& edge) const noexcept -> TVector {
      using RHS = Deref<decltype(edge)>;

      if constexpr (CT::Scalar<RHS>) {
         T result[S];
         T* it = result;
         for (auto& i : result)
            *(it++) = Math::Step(edge, i);
         return result;
      }
      else {
         T result[Min(S, CountOf<RHS>)];
         const T* lhs = all;
         const T* rhs = edge.all;
         for (auto& i : result)
            i = Math::Step(*(rhs++), *(lhs++));
         return result;
      }
   }

   /// Power via a vector                                                     
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Pow(const auto& exponents) const noexcept -> TVector {
      return SIMD::Power(all, exponents);
   }

   /// Fraction                                                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Frac() const noexcept -> TVector {
      if constexpr (not CT::Real<T>)
         return {0};
      else {
         T result[S];
         T* it = result;
         for (auto& i : all)
            *(it++) = Math::Frac(i);
         return result;
      }
   }

   /// Square root                                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sqrt() const noexcept -> TVector {
      T result[S];
      T* it = result;
      for (auto& i : all)
         *(it++) = Math::Sqrt(i);
      return result;
   }

   /// Exponent                                                               
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Exp() const noexcept -> TVector {
      T result[S];
      T* it = result;
      for (auto& i : all)
         *(it++) = Math::Exp(i);
      return result;
   }

   /// Sine                                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Sin() const noexcept -> TVector {
      T result[S];
      T* it = result;
      for (auto& i : all)
         *(it++) = Math::Sin(i);
      return result;
   }

   /// Cosine                                                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Cos() const noexcept -> TVector {
      T result[S];
      T* it = result;
      for (auto& i : all)
         *(it++) = Math::Cos(i);
      return result;
   }

   /// Quicksort                                                              
   TEMPLATE() LANGULUS(INLINED)
   auto& TME()::Sort() noexcept {
      const auto compare = [](const void* p1, const void* p2) noexcept {
         auto g1 = static_cast<const T*>(p1);
         auto g2 = static_cast<const T*>(p2);
         if (*g1 < *g2)
            return -1;
         else if (*g1 > *g2)
            return  1;
         else
            return  0;
      };

      qsort(all, S, sizeof(T), compare);
      return *this;
   }

   /// Warp (used for periodic boundary conditions)                           
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::Warp(const T& scalar) const noexcept -> TVector {
      if constexpr (CT::Signed<T>) {
         const auto absScale = Abs(scalar);
         const auto halfScale = absScale / T {2};
         T result[S];
         T* it = result;
         for (auto& i : all) {
            *(it++) = i > halfScale
               ? i - absScale : i < -halfScale
                  ? i + absScale : i;
         }

         return result;
      }
      else {
         T result[S];
         T* it = result;
         for (auto& i : all)
            *(it++) = i > scalar ? i - scalar : i;
         return result;
      }
   }

   /// Implicitly convert to a number if size is 1 (mutable)                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator T& () const noexcept requires (S == 1) {
      return const_cast<T&>(all[0]);
   }

   /// Explicitly convert to bool                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::operator bool () const noexcept {
      return *this != (TME() {});
   }

   /// Explicit cast to a compatible number of different type                 
   TEMPLATE() template<CT::ScalarBased N>
   requires (S == 1 and CT::Convertible<N, T>) LANGULUS(INLINED)
   constexpr TME()::operator N () const noexcept {
      return static_cast<N>(all[0]);
   }
   
   TEMPLATE() template<Count ALTS> requires (ALTS < S) LANGULUS(INLINED)
   TME()::operator TVector<T, ALTS>& () const noexcept {
      return const_cast<TVector<T, ALTS>&>(
         reinterpret_cast<const TVector<T, ALTS>&>(*this)
      );
   }
   
   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::begin() noexcept -> T* {
      return all;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::end() noexcept -> T* {
      return all + S;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::last() noexcept -> T* {
      return all + S - 1;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::begin() const noexcept -> const T* {
      return all;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::end() const noexcept -> const T* {
      return all + S;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr auto TME()::last() const noexcept -> const T* {
      return all + S - 1;
   }



   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   ///   All operations rely on IF_CONSTEXPR() to check whether function is   
   /// executed in constexpr context or not, and then picking an optimized    
   /// SIMD routine, or a default constexpr one                               
   ///                                                                        
   ///   All operations work only on the overlapping elements, if vectors     
   /// are of different counts. Examples:                                     
   ///   v[4] + v[2] = v[2]                                                   
   ///   v[3] + v[8] = v[3]                                                   
   ///                                                                        
   ///   When operating with scalars, the vector sized is picked. Note, that  
   /// arrays of size [1] are also considered scalars! Examples:              
   ///   v[4] + s    = v[4]                                                   
   ///   v[4] + v[1] = v[4]                                                   
   ///      s + v[8] = v[8]                                                   
   ///                                                                        

   ///                                                                        
   /// Inversion (unary subtraction)                                          
   /// Returns an inverted vector                                             
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& rhs) noexcept {
      return rhs * Decay<TypeOf<decltype(rhs)>> {-1};
   }

   LANGULUS(INLINED)
   constexpr auto operator - (const CT::ProxyArray auto& rhs) noexcept {
      return rhs.GetBase() * Decay<TypeOf<decltype(rhs)>> {-1};
   }

   ///                                                                        
   /// Addition                                                               
   /// Vector + Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Vector + Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Scalar + Vector                                                        
   constexpr auto operator + (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Add(lhs, rhs)};
   }

   /// Vector + Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Add(lhs.GetBase(), rhs)};
   }

   /// Proxy + Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Add(lhs, rhs.GetBase())};
   }

   /// Proxy + Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator + (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Add(lhs.GetBase(), rhs)};
   }

   /// Scalar + Proxy                                                         
   constexpr auto operator + (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Add(lhs, rhs.GetBase())};
   }


   ///                                                                        
   /// Subtraction                                                            
   /// Returns the difference of two vectors                                  
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }

   /// Vector - Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }

   /// Scalar - Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs, rhs)};
   }


   /// Proxy - Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs.GetBase(), rhs)};
   }

   /// Vector - Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Subtract(lhs, rhs.GetBase())};
   }

   /// Proxy - Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Subtract(lhs.GetBase(), rhs)};
   }

   /// Scalar - Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator - (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Subtract(lhs, rhs.GetBase())};
   }


   ///                                                                        
   /// Multiplication                                                         
   /// Returns the Hadamard product of two vectors                            
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs)};
   }

   /// Vector * Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs)};
   }

   /// Scalar * Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs, rhs)};
   }


   /// Proxy * Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs.GetBase(), rhs)};
   }

   /// Vector * Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Multiply(lhs, rhs.GetBase())};
   }

   /// Proxy * Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Multiply(lhs.GetBase(), rhs)};
   }

   /// Scalar * Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator * (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Multiply(lhs, rhs.GetBase())};
   }


   ///                                                                        
   /// Division                                                               
   /// Returns the division of two vectors                                    
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }

   /// Vector / Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }

   /// Scalar / Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs, rhs)};
   }


   /// Proxy / Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs.GetBase(), rhs)};
   }

   /// Vector / Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Divide(lhs, rhs.GetBase())};
   }

   /// Proxy / Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::Divide(lhs.GetBase(), rhs)};
   }

   /// Scalar / Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator / (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::Divide(lhs, rhs.GetBase())};
   }


   ///                                                                        
   /// Shift left                                                             
   /// Int Vector << Int Vector                                               
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::VectorBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }

   /// Int Vector << Int Scalar                                               
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::VectorBasedInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }

   /// Int Scalar << Int Vector                                               
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::ScalarBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs, rhs)};
   }
   

   /// Int Proxy << Int Vector                                                
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::ProxyArrayInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs.GetBase(), rhs)};
   }

   /// Int Vector << Int Proxy                                                
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::VectorBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::ShiftLeft(lhs, rhs.GetBase())};
   }

   /// Int Proxy << Int Scalar                                                
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::ProxyArrayInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::ShiftLeft(lhs.GetBase(), rhs)};
   }

   /// Int Scalar << Int Proxy                                                
   LANGULUS(INLINED)
   constexpr auto operator << (const CT::ScalarBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::ShiftLeft(lhs, rhs.GetBase())};
   }
   

   ///                                                                        
   /// Shift right                                                            
   /// Int Vector >> Int Vector                                               
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::VectorBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }

   /// Int Vector >> Int Scalar                                               
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::VectorBasedInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }

   /// Int Scalar >> Int Vector                                               
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::ScalarBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs, rhs)};
   }
   

   /// Int Proxy >> Int Vector                                                
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::ProxyArrayInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs.GetBase(), rhs)};
   }

   /// Int Vector >> Int Proxy                                                
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::VectorBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::ShiftRight(lhs, rhs.GetBase())};
   }

   /// Int Proxy >> Int Scalar                                                
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::ProxyArrayInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::ShiftRight(lhs.GetBase(), rhs)};
   }

   /// Int Scalar >> Int Proxy                                                
   LANGULUS(INLINED)
   constexpr auto operator >> (const CT::ScalarBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::ShiftRight(lhs, rhs.GetBase())};
   }
   

   ///                                                                        
   /// XOR                                                                    
   /// Int Vector xor Int Vector                                              
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::VectorBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept{
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }

   /// Int Vector xor Int Scalar                                              
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::VectorBasedInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }

   /// Int Scalar xor Int Vector                                              
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::ScalarBasedInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs, rhs)};
   }


   /// Int Proxy xor Int Vector                                               
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::ProxyArrayInt auto& lhs, const CT::VectorBasedInt auto& rhs) noexcept{
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs.GetBase(), rhs)};
   }

   /// Int Vector xor Int Proxy                                               
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::VectorBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept{
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::XOr(lhs, rhs.GetBase())};
   }

   /// Int Proxy xor Int Scalar                                               
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::ProxyArrayInt auto& lhs, const CT::ScalarBasedInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs.GetBase()), decltype(rhs)>;
      return Ret {SIMD::XOr(lhs.GetBase(), rhs)};
   }

   /// Int Scalar xor Int Proxy                                               
   LANGULUS(INLINED)
   constexpr auto operator ^ (const CT::ScalarBasedInt auto& lhs, const CT::ProxyArrayInt auto& rhs) noexcept {
      using Ret = LosslessVector<decltype(lhs), decltype(rhs.GetBase())>;
      return Ret {SIMD::XOr(lhs, rhs.GetBase())};
   }



   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        

   ///                                                                        
   /// Destructive addition                                                   
   /// Vector += Vector                                                       
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Add(lhs, rhs, lhs);
      return lhs;
   }

   /// Vector += Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Add(lhs, rhs, lhs);
      return lhs;
   }


   /// Proxy += Vector                                                        
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Add(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }

   /// Vector += Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      SIMD::Add(lhs, rhs.GetBase(), lhs);
      return lhs;
   }

   /// Proxy += Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto& operator += (CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Add(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }


   ///                                                                        
   /// Destructive subtraction                                                
   /// Vector -= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Subtract(lhs, rhs, lhs);
      return lhs;
   }

   /// Vector -= Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Subtract(lhs, rhs, lhs);
      return lhs;
   }


   /// Proxy -= Vector                                                        
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Subtract(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }

   /// Vector -= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      SIMD::Subtract(lhs, rhs.GetBase(), lhs);
      return lhs;
   }

   /// Proxy -= Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto& operator -= (CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Subtract(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }


   ///                                                                        
   /// Destructive multiplication                                             
   /// Vector *= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Multiply(lhs, rhs, lhs);
      return lhs;
   }

   /// Vector *= Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Multiply(lhs, rhs, lhs);
      return lhs;
   }


   /// Proxy *= Vector                                                        
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      SIMD::Multiply(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }

   /// Vector *= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      SIMD::Multiply(lhs, rhs.GetBase(), lhs);
      return lhs;
   }

   /// Proxy *= Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto& operator *= (CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      SIMD::Multiply(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }


   /// Vector /= Vector                                                       
   ///   @attention throws on division by zero                                
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) {
      SIMD::Divide(lhs, rhs, lhs);
      return lhs;
   }

   /// Vector /= Scalar                                                       
   ///   @attention throws on division by zero                                
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) {
      SIMD::Divide(lhs, rhs, lhs);
      return lhs;
   }


   /// Proxy /= Vector                                                        
   ///   @attention throws on division by zero                                
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) {
      SIMD::Divide(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }

   /// Vector /= Proxy                                                        
   ///   @attention throws on division by zero                                
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) {
      SIMD::Divide(lhs, rhs.GetBase(), lhs);
      return lhs;
   }

   /// Proxy /= Scalar                                                        
   ///   @attention throws on division by zero                                
   LANGULUS(INLINED)
   constexpr auto& operator /= (CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) {
      SIMD::Divide(lhs.GetBase(), rhs, lhs.GetBase());
      lhs.Commit();
      return lhs;
   }



   ///                                                                        
   ///   Compare                                                              
   ///                                                                        
   
   ///                                                                        
   /// Lesser                                                                 
   /// Vector < Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }

   /// Vector < Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }

   /// Scalar < Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs);
   }


   /// Proxy < Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs.GetBase(), rhs);
   }

   /// Vector < Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs.GetBase());
   }

   /// Proxy < Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Lesser(lhs.GetBase(), rhs);
   }

   /// Scalar < Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator < (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Lesser(lhs, rhs.GetBase());
   }


   ///                                                                        
   /// Lesser or equal                                                        
   /// Vector <= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }

   /// Vector <= Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }

   /// Scalar <= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs);
   }


   /// Proxy <= Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs.GetBase(), rhs);
   }

   /// Vector <= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs.GetBase());
   }

   /// Proxy <= Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs.GetBase(), rhs);
   }

   /// Scalar <= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator <= (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::EqualsOrLesser(lhs, rhs.GetBase());
   }


   ///                                                                        
   /// Greater                                                                
   /// Vector > Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }

   /// Vector > Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }

   /// Scalar > Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs);
   }


   /// Proxy > Vector                                                         
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Greater(lhs.GetBase(), rhs);
   }

   /// Vector > Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs.GetBase());
   }

   /// Proxy > Scalar                                                         
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Greater(lhs.GetBase(), rhs);
   }

   /// Scalar > Proxy                                                         
   LANGULUS(INLINED)
   constexpr auto operator > (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Greater(lhs, rhs.GetBase());
   }


   ///                                                                        
   /// Greater or equal                                                       
   /// Vector >= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }

   /// Vector >= Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }

   /// Scalar >= Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs);
   }


   /// Proxy >= Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs.GetBase(), rhs);
   }

   /// Vector >= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs.GetBase());
   }

   /// Proxy >= Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs.GetBase(), rhs);
   }

   /// Scalar >= Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator >= (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::EqualsOrGreater(lhs, rhs.GetBase());
   }


   ///                                                                        
   /// Equal                                                                  
   /// Vector == Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }

   /// Vector == Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }

   /// Scalar == Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs);
   }


   /// Proxy == Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return SIMD::Equals(lhs.GetBase(), rhs);
   }

   /// Vector == Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs.GetBase());
   }

   /// Proxy == Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return SIMD::Equals(lhs.GetBase(), rhs);
   }

   /// Scalar == Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator == (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return SIMD::Equals(lhs, rhs.GetBase());
   }


   ///                                                                        
   /// Inequal                                                                
   /// Vector != Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   /// Vector != Scalar                                                       
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }

   /// Scalar != Vector                                                       
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::ScalarBased auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs == rhs);
   }


   /// Proxy != Vector                                                        
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::ProxyArray auto& lhs, const CT::VectorBased auto& rhs) noexcept {
      return not (lhs.GetBase() == rhs);
   }

   /// Vector != Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::VectorBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return not (lhs == rhs.GetBase());
   }

   /// Proxy != Scalar                                                        
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::ProxyArray auto& lhs, const CT::ScalarBased auto& rhs) noexcept {
      return not (lhs.GetBase() == rhs);
   }

   /// Scalar != Proxy                                                        
   LANGULUS(INLINED)
   constexpr auto operator != (const CT::ScalarBased auto& lhs, const CT::ProxyArray auto& rhs) noexcept {
      return not (lhs == rhs.GetBase());
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
   template<CT::Number T = Real>
   constexpr TVector<T, 4> X {1, 0, 0, 0};
   
   /// Canonical Y axis                                                       
   template<CT::Number T = Real>
   constexpr TVector<T, 4> Y {0, 1, 0, 0};

   /// Canonical Z axis                                                       
   template<CT::Number T = Real>
   constexpr TVector<T, 4> Z {0, 0, 1, 0};

   /// Canonical W axis                                                       
   template<CT::Number T = Real>
   constexpr TVector<T, 4> W {0, 0, 0, 1};
   
   /// Canonical world origin                                                 
   template<CT::Number T = Real>
   constexpr TVector<T, 4> Origin {0, 0, 0, 0};

   /// Canonical forward vector, pointing towards the screen, in positive Z   
   template<CT::Number T = Real>
   constexpr auto Forward = Z<T>;

   /// Canonical backward vector, towards the human device, in negative Z     
   template<CT::Number T = Real>
   constexpr auto Backward = -Z<T>;

   /// Canonical up vector, pointing from the ground up, in positive Y        
   template<CT::Number T = Real>
   constexpr auto Up = Y<T>;

   /// Canonical down vector, pointing in gravity's direction, in negative Y  
   template<CT::Number T = Real>
   constexpr auto Down = -Y<T>;

   /// Canonical right vector, pointing to right hand, in positive X          
   template<CT::Number T = Real>
   constexpr auto Right = X<T>;

   /// Canonical left vector, pointing to left hand, in negative X            
   template<CT::Number T = Real>
   constexpr auto Left = -X<T>;

} // Langulus::Axes


LANGULUS_DEFINE_CONSTANT(AxisForward, ::Langulus::Axes::Forward<>,
   "Axes::Forward", "A canonical forward vector")
LANGULUS_DEFINE_CONSTANT(AxisBackward, ::Langulus::Axes::Backward<>,
   "Axes::Backward", "A canonical backward vector")
LANGULUS_DEFINE_CONSTANT(AxisUp, ::Langulus::Axes::Up<>,
   "Axes::Up", "A canonical up vector")
LANGULUS_DEFINE_CONSTANT(AxisDown, ::Langulus::Axes::Down<>,
   "Axes::Down", "A canonical down vector")
LANGULUS_DEFINE_CONSTANT(AxisRight, ::Langulus::Axes::Right<>,
   "Axes::Right", "A canonical right vector")
LANGULUS_DEFINE_CONSTANT(AxisLeft, ::Langulus::Axes::Left<>,
   "Axes::Left", "A canonical left vector")

LANGULUS_DEFINE_CONSTANT(AxisX, ::Langulus::Axes::X<>,
   "Axes::X", "A canonical X axis")
LANGULUS_DEFINE_CONSTANT(AxisY, ::Langulus::Axes::Y<>,
   "Axes::Y", "A canonical Y axis")
LANGULUS_DEFINE_CONSTANT(AxisZ, ::Langulus::Axes::Z<>,
   "Axes::Z", "A canonical Z axis")
LANGULUS_DEFINE_CONSTANT(AxisW, ::Langulus::Axes::W<>,
   "Axes::W", "A canonical W axis")

LANGULUS_DEFINE_CONSTANT(AxisOrigin, ::Langulus::Axes::Origin<>,
   "Origin", "A canonical zero vector")
