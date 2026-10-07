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
   template<CT::Vector> struct TBox;
   template<CT::Vector> struct TBoxRounded;

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
   template<CT::Vector T>
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

      constexpr bool IsDegenerate() const noexcept;
      constexpr bool IsHollow() const noexcept;
      auto SignedDistance(T const&) const;

      /*explicit operator Annies::Text() const;
      explicit operator Flow::Code() const;*/
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
   template<CT::Vector T>
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
      //LANGULUS_CONVERTS_TO(Annies::Text, Flow::Code);

      using Base = TBox<T>;
      //using typename Base::PointType;
      //using Base::MemberCount;
      using Base::mOffsets;

      TypeOf<T> mRadius;

      constexpr bool IsDegenerate() const noexcept;
      constexpr bool IsHollow() const noexcept;
      auto SignedDistance(T const&) const;

      /*explicit operator Annies::Text() const;
      explicit operator Flow::Code() const;*/
   };
}