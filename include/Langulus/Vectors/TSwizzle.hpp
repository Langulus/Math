///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once

namespace Langulus::Math::Inner
{
   ///                                                                        
   ///   Proxy array (a.k.a. a swizzled vector, intermediate type)            
   ///                                                                        
   /// Creates a shuffled representation of a source vector, and commits      
   /// any changes to it upon destruction                                     
   ///                                                                        
   template<TARGS(V) = 0, size_t...I>
   struct TSwizzle : TVector<VT, sizeof...(I), VD> {
      using CTTI_ReflectAs    = void;
      using CTTI_CustomVector = No;
      using CTTI_Swizzled     = Yup;
      using Base              = TVector<VT, sizeof...(I), VD>;

   private:
      // The original data source, will be changed upon destruction     
      VT (&mSource)[VS];

      /// Commit the changes                                                  
      template<size_t...I2>
      constexpr void CommitInner(ExpandedSequence<I2...>) noexcept {
         static_assert(sizeof...(I) == sizeof...(I2));
         ((mSource[I] = Base::all[I2]), ...);
      }

   public:
      TSwizzle() = delete;
      TSwizzle(const TSwizzle&) = delete;
      TSwizzle(TSwizzle&&) = delete;

      /// Create a proxy array - copy relevant contents and save a ref for    
      /// later, when local changes have to be commited to the original       
      explicit TSwizzle(VT (&source)[VS]) noexcept
         : Base    {source[I]...}
         , mSource {source} {}

      /// Intermediate type destructor - commits any local changes to the     
      /// original array, making sure no information is lost                  
      ~TSwizzle() noexcept { Commit(); }

      using Base::operator =;

      auto GetBase() noexcept -> Base& {
         return static_cast<Base&>(*this);
      }

      auto GetBase() const noexcept -> Base const& {
         return static_cast<Base const&>(*this);
      }

      void Commit() noexcept {
         CommitInner(Sequence<sizeof...(I)>::Expand);
      }
   };
}