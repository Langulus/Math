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
   
   /// Pick a shorter token, based on member count and type                   
   /// This should be made more elegant when true constexpr string literals   
   /// become available in the standard                                       
   TEMPLATE()
   constexpr Token TME()::GenerateClassName() noexcept {
      if constexpr (DEFAULT != 0)
         return RTTI::LastNameOf<TME()>();

      switch (MemberCount) {
      case 1:
         /*if constexpr (CT::Same<TypeOf<T>, Real>)
            return "Vec1";
         else if constexpr (CT::Same<TypeOf<T>, signed int>)
            return "Vec1i";
         else if constexpr (CT::Same<TypeOf<T>, unsigned int>)
            return "Vec1u";
         else*/ if constexpr (CT::Same<TypeOf<T>, bool>)
            return "Vec1b";
         else if constexpr (CT::Same<TypeOf<T>, Float>)
            return "Vec1f";
         else if constexpr (CT::Same<TypeOf<T>, Double>)
            return "Vec1d";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint8_t>)
            return "Vec1u8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint16_t>)
            return "Vec1u16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint32_t>)
            return "Vec1u32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint64_t>)
            return "Vec1u64";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int8_t>)
            return "Vec1i8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int16_t>)
            return "Vec1i16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int32_t>)
            return "Vec1i32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int64_t>)
            return "Vec1i64";
         else
            return RTTI::LastNameOf<TME()>();
      case 2:
         /*if constexpr (CT::Same<TypeOf<T>, Real>)
            return "Vec2";
         else if constexpr (CT::Same<TypeOf<T>, signed int>)
            return "Vec2i";
         else if constexpr (CT::Same<TypeOf<T>, unsigned int>)
            return "Vec2u";
         else*/ if constexpr (CT::Same<TypeOf<T>, bool>)
            return "Vec2b";
         else if constexpr (CT::Same<TypeOf<T>, Float>)
            return "Vec2f";
         else if constexpr (CT::Same<TypeOf<T>, Double>)
            return "Vec2d";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint8_t>)
            return "Vec2u8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint16_t>)
            return "Vec2u16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint32_t>)
            return "Vec2u32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint64_t>)
            return "Vec2u64";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int8_t>)
            return "Vec2i8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int16_t>)
            return "Vec2i16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int32_t>)
            return "Vec2i32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int64_t>)
            return "Vec2i64";
         else
            return RTTI::LastNameOf<TME()>();
      case 3:
         /*if constexpr (CT::Same<TypeOf<T>, Real>)
            return "Vec3";
         else if constexpr (CT::Same<TypeOf<T>, signed int>)
            return "Vec3i";
         else if constexpr (CT::Same<TypeOf<T>, unsigned int>)
            return "Vec3u";
         else*/ if constexpr (CT::Same<TypeOf<T>, bool>)
            return "Vec3b";
         else if constexpr (CT::Same<TypeOf<T>, Float>)
            return "Vec3f";
         else if constexpr (CT::Same<TypeOf<T>, Double>)
            return "Vec3d";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint8_t>)
            return "Vec3u8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint16_t>)
            return "Vec3u16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint32_t>)
            return "Vec3u32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint64_t>)
            return "Vec3u64";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int8_t>)
            return "Vec3i8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int16_t>)
            return "Vec3i16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int32_t>)
            return "Vec3i32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int64_t>)
            return "Vec3i64";
         else
            return RTTI::LastNameOf<TME()>();
      case 4:
         /*if constexpr (CT::Same<TypeOf<T>, Real>)
            return "Vec4";
         else if constexpr (CT::Same<TypeOf<T>, signed int>)
            return "Vec4i";
         else if constexpr (CT::Same<TypeOf<T>, unsigned int>)
            return "Vec4u";
         else if constexpr (CT::Same<TypeOf<T>, bool>)
            return "Vec4b";
         else*/ if constexpr (CT::Same<TypeOf<T>, Float>)
            return "Vec4f";
         else if constexpr (CT::Same<TypeOf<T>, Double>)
            return "Vec4d";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint8_t>)
            return "Vec4u8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint16_t>)
            return "Vec4u16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint32_t>)
            return "Vec4u32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::uint64_t>)
            return "Vec4u64";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int8_t>)
            return "Vec4i8";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int16_t>)
            return "Vec4i16";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int32_t>)
            return "Vec4i32";
         else if constexpr (CT::Same<TypeOf<T>, ::std::int64_t>)
            return "Vec4i64";
         else
            return RTTI::LastNameOf<TME()>();
      default:
         return RTTI::LastNameOf<TME()>();
      }
   }

   /// Default vector constructor initialized all components to DefaultMember 
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector() noexcept {
      for (auto& v : mArray)
         v = DefaultMember;
   }

   /// Copy (and convert) from same/bigger vectors of same/different types    
   /// Also acts as a copy-constructor                                        
   ///   @param a - vector to copy                                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const TVEC(ALT)& a) noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const N& a) noexcept requires IsCompatible<N> {
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
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const N* a) noexcept requires IsCompatible<N> {
      for (auto& v : mArray)
         v = Adapt(*(a++));
   }
   
   /// Construction from a bounded array                                      
   ///   @param a - array to copy                                             
   TEMPLATE()
   template<CT::Array N>
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const N& a) noexcept requires IsCompatible<Decay<N>> {
      static_assert(ExtentOf<N> >= S,
         "This vector is too powerful for your array");

      const Decay<N>* source = a;
      for (auto& v : mArray)
         v = Adapt(*(source++));
   }

   /// Manual construction via a variadic head-tail                           
   /// Any of the elements can be another vector, as long all vectors'        
   /// element counts and scalars sum up to this vector type's size           
   TEMPLATE()
   template<class HEAD, class... TAIL>
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const HEAD& head, const TAIL&... tail) noexcept requires (S > 1 && sizeof...(TAIL) > 0) {
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
   LANGULUS(ALWAYSINLINE) constexpr TME()::TVector(const TVectorComponent<N, D>& a) noexcept
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
   LANGULUS(ALWAYSINLINE) constexpr decltype(auto) TME()::Adapt(const N& item) const noexcept requires IsCompatible<N> {
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
   LANGULUS(ALWAYSINLINE) constexpr const T& TME()::Get(const Offset i) const noexcept {
      LANGULUS_ASSUME(UserAssumes, i < S, "Index is out of limits");
      return mArray[i];
   }

   /// Get the value of a specific component index (with static check)        
   ///   @return a reference to the component                                 
   TEMPLATE()
   template<Offset I>
   LANGULUS(ALWAYSINLINE) constexpr const T& TME()::GetIdx() const noexcept {
      static_assert(I < S, "Index is out of limits");
      return Get(I);
   }

   /// Get Nth vector element (mutable)                                       
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr T& TME()::operator [] (const Offset a) noexcept {
      return const_cast<T&>(Get(a));
   }

   /// Get Nth vector element                                                 
   ///   @attention assumes index is in vector's size limits                  
   ///   @param a - index of the element (0, 1, 2 correspond to X, Y, Z)      
   ///   @returns a reference to the component                                
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr const T& TME()::operator [] (const Offset a) const noexcept {
      return Get(a);
   }

   /// Get the raw array                                                      
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr const T* TME()::GetRaw() const noexcept {
      return mArray;
   }

   /// Get the raw array (mutable)                                            
   ///   @return a pointer to the first component inside this vector          
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr T* TME()::GetRaw() noexcept {
      return mArray;
   }

   /// Get the number of components                                           
   ///   @return the number of components                                     
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr Count TME()::GetCount() const noexcept {
      return MemberCount;
   }

   /// Get the squared magnitute of the vector                                
   ///   @return the length of the vector, before the Sqrt operation          
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr T TME()::LengthSquared() const noexcept {
      auto start = mArray;
      const auto end = mArray + S;
      T accum = Math::Sq(*(start++));
      while (start != end)
         accum += Math::Sq(*(start++));
      return accum;
   }

   /// Get the magnitute of the vector                                        
   ///   @return the length of the vector                                     
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr T TME()::Length() const noexcept {
      return Math::Sqrt(LengthSquared());
   }

   /// Check if vector is a degenerate, that is at least one component is 0   
   ///   @return true if vector is degenerate                                 
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr bool TME()::IsDegenerate() const noexcept {
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
   LANGULUS(ALWAYSINLINE) decltype(auto) TME()::Swz() noexcept {
      if constexpr (sizeof...(TAIL) == 0)
         return mArray[HEAD];
      else
         return Inner::TProxyVector<T, S, HEAD, TAIL...> {*this};
   }

   /// Immutable swizzle, just returns a shuffled vector                      
   ///   @returns a simple vector with the selected copied components         
   TEMPLATE()
   template<Offset HEAD, Offset... TAIL>
   LANGULUS(ALWAYSINLINE) constexpr decltype(auto) TME()::Swz() const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr TVector<AS, S> TME()::AsCast() const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Volume() const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr auto& TME()::operator = (const N& scalar) noexcept {
      new (this) TVector {scalar};
      return *this;
   }

   /// Copy vector                                                            
   ///   @param vec - the vector to copy                                      
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto& TME()::operator = (const TVEC(ALT)& vec) noexcept {
      new (this) TVector {vec};
      return *this;
   }

   /// Set only a specific component                                          
   ///   @param com - the component to overwrite                              
   ///   @return a reference to this vector                                   
   TEMPLATE()
   template<CT::DenseNumber N, CT::Dimension D>
   LANGULUS(ALWAYSINLINE) constexpr auto& TME()::operator = (const TVectorComponent<N, D>& com) noexcept {
      static_assert(D::Index < S, "LHS doesn't have such dimension");
      mArray[D::Index] = Adapt(com.mValue);
      return *this;
   }

   /// Dot product                                                            
   ///   @param other - the vector to dot with                                
   ///   @return the dot product of both vectors                              
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr T TME()::Dot(const TVEC(ALT)& other) const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr TVector<T, 3> TME()::Cross(const TVEC(ALT)& rhs) const noexcept requires (S >= 3 && ALTS >= 3) {
      return {
         mArray[1] * rhs[2] - mArray[2] * rhs[1],
         mArray[2] * rhs[0] - mArray[0] * rhs[2],
         mArray[0] * rhs[1] - mArray[1] * rhs[0]
      };
   }

   /// Normalize                                                              
   ///   @return the normalized vector                                        
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Normalize() const requires (S > 1) {
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
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Clamp(const TVEC(MIN)& min, const TVEC(MAX)& max) const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::ClampRev(const TVEC(MIN)& min, const TVEC(MAX)& max) const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Round() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Round(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round down each vector component                                       
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Floor() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Floor(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Round up each vector component                                         
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Ceil() const noexcept {
      if constexpr (CT::Real<T>) {
         T result[S];
         SIMD::Store(SIMD::Ceil(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Invert negative components of vector                                   
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Abs() const noexcept {
      if constexpr (CT::Signed<T>) {
         T result[S];
         SIMD::Store(SIMD::Abs(mArray), result);
         return result;
      }
      else return *this;
   }

   /// Get biggest possible vector of the type                                
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr TME() TME()::Max() noexcept {
      return ::std::numeric_limits<T>::max();
   }

   /// Get scalar maximum of each element                                     
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Max(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Max(mArray, limit), result);
      return result;
   }

   /// Get maximum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Max(const TVEC(ALT)& limits) const noexcept {
      T result[Math::Min(S, ALTS)];
      SIMD::Store(SIMD::Max(mArray, limits.mArray), result);
      return result;
   }

   /// Get smallest possible vector of the type                               
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr TME() TME()::Min() noexcept {
      if constexpr (CT::Real<T>)
         return {::std::numeric_limits<T>::lowest()};
      else
         return {::std::numeric_limits<T>::min()};
   }

   /// Get scalar minimum of each element                                     
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Min(const T& limit) const noexcept {
      T result[S];
      SIMD::Store(SIMD::Min(mArray, limit), result);
      return result;
   }

   /// Get minimum of each element                                            
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Min(const TVEC(ALT)& limits) const noexcept {
      T result[Min(S, ALTS)];
      SIMD::Store(SIMD::Min(mArray, limits.mArray), result);
      return result;
   }
   
   /// Horizontal max                                                         
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::HMax() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Math::Max(*(start++), t);
      return t;
   }

   /// Horizontal min                                                         
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::HMin() const noexcept {
      // Related: https://stackoverflow.com/questions/22256525/         
      auto start = mArray;
      const auto end = mArray + S;
      T t = *(start++);
      while (start != end)
         t = Math::Min(*(start++), t);
      return t;
   }

   /// Horizontal sum                                                         
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::HSum() const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::HMul() const noexcept {
      T product {1};
      for (auto& v : mArray)
         product *= v;
      return product;
   }

   /// Sign                                                                   
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Sign() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sign(v);
      return result;
   }

   /// Modulate via a scalar                                                  
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Mod(const T& period) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Mod(v, period);
      return result;
   }

   /// Modulate via a vector                                                  
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Mod(const TVEC(ALT)& period) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = period.mArray;
      for (auto& v : result)
         v = Math::Mod(*(lhs++), *(rhs++));
      return result;
   }

   /// Step via a scalar                                                      
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Step(const T& edge) const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Step(edge, v);
      return result;
   }

   /// Step via a vector                                                      
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Step(const TVEC(ALT)& edge) const noexcept {
      T result[Min(S, ALTS)];
      const T* lhs = mArray;
      const T* rhs = edge.mArray;
      for (auto& v : result)
         v = Math::Step(*(rhs++), *(lhs++));
      return result;
   }

   /// Power via a scalar                                                     
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Pow(const T& exponent) const noexcept {
      return SIMD::PowerWrap<TVector>(mArray, exponent);
   }

   /// Power via a vector                                                     
   TEMPLATE()
   template<TARGS(ALT)>
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Pow(const TVEC(ALT)& exponents) const noexcept {
      return SIMD::PowerWrap<TVector>(mArray, exponents.mArray);
   }

   /// Fraction                                                               
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Frac() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Frac(v);
      return result;
   }

   /// Square root                                                            
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Sqrt() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sqrt(v);
      return result;
   }

   /// Exponent                                                               
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Exp() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Exp(v);
      return result;
   }

   /// Sine                                                                   
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Sin() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Sin(v);
      return result;
   }

   /// Cosine                                                                 
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Cos() const noexcept {
      T result[S];
      T* it = result;
      for (auto& v : mArray)
         *(it++) = Math::Cos(v);
      return result;
   }

   /// Quicksort                                                              
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) auto& TME()::Sort() noexcept {
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
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr auto TME()::Warp(const T& scalar) const noexcept {
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
   LANGULUS(ALWAYSINLINE) constexpr TME()::operator const T& () const noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Implicitly convert to a number if size is 1 (mutable)                  
   TEMPLATE()
   LANGULUS(ALWAYSINLINE) constexpr TME()::operator T& () noexcept requires (S == 1) {
      return (*this)[0];
   }

   /// Explicit cast to a compatible number of different type                 
   TEMPLATE()
   template<CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) constexpr TME()::operator N () const noexcept requires (S == 1 && IsCompatible<N>) {
      return static_cast<N>(*mArray);
   }
   
   TEMPLATE()
   template<Count ALTS>
   LANGULUS(ALWAYSINLINE) TME()::operator TVector<T, ALTS>& () noexcept requires (ALTS < S) {
      return reinterpret_cast<TVector<T, ALTS>&>(*this);
   }

   TEMPLATE()
   template<Count ALTS>
   LANGULUS(ALWAYSINLINE) TME()::operator const TVector<T, ALTS>& () const noexcept requires (ALTS < S) {
      return reinterpret_cast<const TVector<T, ALTS>&>(*this);
   }


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   /// Returns an inverted vector                                             
   template<TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator - (const TVEC(RHS)& me) noexcept {
      return me * Decay<RHST>(-1);
   }

   /// Returns the sum of any two vectors                                     
   /// Only the intersecting elements are added and returned:                 
   ///   v[4] + v[2] = v[2]                                                   
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator + (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::AddWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector + Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator + (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] + other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::AddWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar + Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator + (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other + me[0];   // 1D vectors decay to a number        
      else
         return me + other;
   }

   /// Returns the difference of two vectors                                  
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator - (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::SubtractWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector - Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator - (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] - other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::SubtractWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar - Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator - (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other - me[0];   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::SubtractWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the product of two vectors                                     
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator * (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::MultiplyWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector * Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator * (const TVEC(LHS)& me, const N& other) noexcept {
      if constexpr (LHSS == 1)
         return me[0] * other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::MultiplyWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar * Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator * (const N& other, const TVEC(RHS)& me) noexcept {
      if constexpr (RHSS == 1)
         return other * me[0];   // 1D vectors decay to a number        
      else 
         return me * other;
   }

   /// Returns the division of two vectors                                    
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator / (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::DivideWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector / Scalar                                                        
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator / (const TVEC(LHS)& me, const N& other) {
      if constexpr (LHSS == 1)
         return me[0] / other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::DivideWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar / Vector                                                        
   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator / (const N& other, const TVEC(RHS)& me) {
      if constexpr (RHSS == 1)
         return other / me[0];   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::DivideWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the left-shift of two integer vectors                          
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator << (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::ShiftLeftWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector << Scalar                                                       
   template<TARGS(LHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator << (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] << other;   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::ShiftLeftWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar << Vector                                                       
   template<TARGS(RHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator << (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
      if constexpr (RHSS == 1)
         return other << me[0];   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::ShiftLeftWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the right-shift of two integer vectors                         
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator >> (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::ShiftRightWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector >> Scalar                                                       
   template<TARGS(LHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator >> (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] >> other;   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::ShiftRightWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar >> Vector                                                       
   template<TARGS(RHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator >> (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
      if constexpr (RHSS == 1)
         return other >> me[0];   // 1D vectors decay to a number       
      else {
         using TYPE = Lossless<RHST, N>;
         return SIMD::ShiftRightWrap<TVector<TYPE, RHSS>>(other, me.mArray);
      }
   }

   /// Returns the xor of two integer vectors                                 
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator ^ (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires CT::Integer<LHST, RHST> {
      using TYPE = Lossless<LHST, RHST>;
      return SIMD::XOrWrap<TVector<TYPE, Math::Min(LHSS, RHSS)>>(me.mArray, other.mArray);
   }

   /// Vector ^ Scalar                                                        
   template<TARGS(LHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator ^ (const TVEC(LHS)& me, const N& other) noexcept requires CT::Integer<LHST> {
      if constexpr (LHSS == 1)
         return me[0] ^ other;   // 1D vectors decay to a number        
      else {
         using TYPE = Lossless<LHST, N>;
         return SIMD::XOrWrap<TVector<TYPE, LHSS>>(me.mArray, other);
      }
   }

   /// Scalar ^ Vector                                                        
   template<TARGS(RHS), CT::Integer N>
   LANGULUS(ALWAYSINLINE) auto operator ^ (const N& other, const TVEC(RHS)& me) noexcept requires CT::Integer<RHST> {
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
   LANGULUS(ALWAYSINLINE) auto& operator += (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Add(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Add vector and a scalar                                                
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto& operator += (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Add(me.mArray, other, me.mArray);
      return me;
   }

   /// Subtract vectors                                                       
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto& operator -= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Subtract(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Subtract vector and a scalar                                           
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto& operator -= (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Subtract(me.mArray, other, me.mArray);
      return me;
   }

   /// Multiply vectors                                                       
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto& operator *= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
      SIMD::Multiply(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Multiply vector by a scalar                                            
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto& operator *= (TVEC(LHS)& me, const N& other) noexcept {
      SIMD::Multiply(me.mArray, other, me.mArray);
      return me;
   }

   /// Divide dense vectors                                                   
   /// This function will throw on division by zero                           
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto& operator /= (TVEC(LHS)& me, const TVEC(RHS)& other) {
      SIMD::Divide(me.mArray, other.mArray, me.mArray);
      return me;
   }

   /// Divide dense vector and a scalar                                       
   /// This function will throw on division by zero                           
   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto& operator /= (TVEC(LHS)& me, const N& other) {
      SIMD::Divide(me.mArray, other, me.mArray);
      return me;
   }


   ///                                                                        
   ///   Compare                                                              
   ///                                                                        
   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator < (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::Lesser(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator < (const TVEC(LHS)& me, const N& other) {
      return SIMD::Lesser(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator < (const N& other, const TVEC(RHS)& me) {
      return SIMD::Lesser(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator <= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::EqualsOrLesser(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator <= (const TVEC(LHS)& me, const N& other) {
      return SIMD::EqualsOrLesser(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator <= (const N& other, const TVEC(RHS)& me) {
      return SIMD::EqualsOrLesser(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator > (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::Greater(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator > (const TVEC(LHS)& me, const N& other) {
      return SIMD::Greater(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator > (const N& other, const TVEC(RHS)& me) {
      return SIMD::Greater(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) auto operator >= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      return SIMD::EqualsOrGreater(me.mArray, other.mArray);
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator >= (const TVEC(LHS)& me, const N& other) {
      return SIMD::EqualsOrGreater(me.mArray, other);
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) auto operator >= (const N& other, const TVEC(RHS)& me) {
      return SIMD::EqualsOrGreater(other, me.mArray);
   }

   template<TARGS(LHS), TARGS(RHS)>
   LANGULUS(ALWAYSINLINE) bool operator == (const TVEC(LHS)& me, const TVEC(RHS)& other) {
      bool result = false;
      SIMD::Equals(me.mArray, other.mArray, result);
      return result;
   }

   template<TARGS(LHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) bool operator == (const TVEC(LHS)& me, const N& other) {
      bool result = false;
      SIMD::Equals(me.mArray, other, result);
      return result;
   }

   template<TARGS(RHS), CT::DenseNumber N>
   LANGULUS(ALWAYSINLINE) bool operator == (const N& other, const TVEC(RHS)& me) {
      bool result = false;
      SIMD::Equals(other, me.mArray, result);
      return result;
   }

} // namespace Langulus::Math

