///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"


namespace Langulus::Math
{
   template<CT::CustomVector> struct TBox;
   template<CT::CustomVector> struct TBoxRounded;

   using Box2 = TBox<Vec2>;
   using Box3 = TBox<Vec3>;

   using BoxRounded2 = TBoxRounded<Vec2>;
   using BoxRounded3 = TBoxRounded<Vec3>;

   /// An abstract box that depends on context, defaulting to a 3D box        
   struct Box : Primitive {
      using CTTI_Abstract  = Yup;
      using CTTI_Concrete  = Box3;
      using CTTI_Bases     = Primitive;
   };

   /// An abstract rounded box that depends on context, defaulting to a 3D box
   struct BoxRounded : Box {
      using CTTI_Concrete  = BoxRounded3;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing box primitives                              
   template<class...T>
   concept Box = (DerivedFrom<T, Math::Box> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   /// 2D/3D box with varying dimensions, centered around origin              
   ///                                                                        
   /// An example unit 2D quad, centered at origin:                           
   ///           ^ +Y                                                         
   ///           |                                                            
   ///   +-------+-------+   (.5, .5) mOffsets from origin                    
   ///   |               |                                                    
   ///   |               |                                                    
   ///   |       +       |--> +X                                              
   ///   |     origin    |                                                    
   ///   |               |                                                    
   ///   +---------------+                                                    
   ///                                                                        
   template<CT::CustomVector T>
   struct TBox : Box {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TBox>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (ExtentOf<T> > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "Box")
            name[offset++] = i;

         // Write size                                                  
         --offset;
         name[offset++] = '0' + ExtentOf<T>;

         // Write suffix                                                
         for (auto i : SuffixOf<TypeOf<T>>())
            name[offset++] = i;
         return name;
      }

   public:
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Box;

      using PointType = T;
      static_assert(ExtentOf<T> > 1, "Can't have one-dimensional box");

      T mOffsets {.5};

      /// Check if box is degenerate                                          
      ///   @return true if at least one offset is zero                       
      constexpr bool IsDegenerate() const noexcept {
         return mOffsets.IsDegenerate();
      }

      /// Check if box is hollow                                              
      ///   @return true if at least one of the offsets is negative           
      constexpr bool IsHollow() const noexcept {
         return mOffsets[0] < TypeOf<T> {0};
      }
   };


   ///                                                                        
   /// 2D/3D rounded box with varying dimensions, centered around origin      
   ///                                                                        
   ///           ^ +Y                                                         
   ///           |                                                            
   ///    ,------+------, +   (.5, .5) mOffsets from origin                   
   ///   /               \.                                                   
   ///  |      origin     |                                                   
   ///  |        +        |--> +X                                             
   ///  |                 |                                                   
   ///   \               /                                                    
   ///    '-------------'   <- mRadius from origin of rounded parts           
   ///                                                                        
   template<CT::CustomVector T>
   struct TBoxRounded : TBox<T> {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TBoxRounded>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "BoxRounded")
            name[offset++] = i;

         // Write size                                                  
         --offset;
         name[offset++] = '0' + T::MemberCount;

         // Write suffix                                                
         for (auto i : SuffixOf<TypeOf<T>>())
            name[offset++] = i;
         return name;
      }

   public:
      using CTTI_Named = Yes<GenerateToken()>;
      using Base = TBox<T>;
      using Base::mOffsets;

      TypeOf<T> mRadius;

      constexpr bool IsDegenerate() const noexcept {
         return mOffsets.Length() - mRadius, TypeOf<T> {0};
      }

      constexpr bool IsHollow() const noexcept {
         return mOffsets[0] - mRadius < TypeOf<T> {0};
      }
   };
}