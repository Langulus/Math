///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "Primitive.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector>
      struct TBox;

      template<CT::Vector>
      struct TBoxRounded;

      using Box2 = TBox<Vec2>;
      using Box3 = TBox<Vec3>;

      using BoxRounded2 = TBoxRounded<Vec2>;
      using BoxRounded3 = TBoxRounded<Vec3>;

      using Box = Box3;
      using BoxRounded = BoxRounded3;

   } // namespace Langulus::Math

   namespace A
   {

      /// An abstract box                                                     
      struct Box : Primitive {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Box;
         LANGULUS_BASES(Primitive);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing box primitives                           
      template<class...T>
      concept Box = (DerivedFrom<T, A::Box> and ...);

   } // namespace Langulus::CT

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                     |  
   /// 2D/3D box with varying dimensions, centered around origin           |  
   ///                                                                     |  
   /// An example unit 2D quad, centered at origin:                        |  
   ///           ^ +Y                                                      |  
   ///           |                                                         |  
   ///   +-------+-------+   (.5, .5) mOffsets from origin                 |  
   ///   |               |                                                 |  
   ///   |               |                                                 |  
   ///   |       +       |--> +X                                           |  
   ///   |     origin    |                                                 |  
   ///   |               |                                                 |  
   ///   +---------------+                                                 |  
   ///                                                                     |  
   template<CT::Vector T>
   struct TBox : A::Box {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = RTTI::LastCppNameOf<TBox>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "Box")
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
      LANGULUS(NAME) GenerateToken();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Box);
      LANGULUS_CONVERTS_TO(Anyness::Text, Flow::Code);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Can't have one-dimensional box");

      T mOffsets {.5};

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;

      NOD() explicit operator Anyness::Text() const;
      NOD() explicit operator Flow::Code() const;
   };


   ///                                                                     |  
   /// 2D/3D rounded box with varying dimensions, centered around origin   |  
   ///                                                                     |  
   ///           ^ +Y                                                      |  
   ///           |                                                         |  
   ///    ,------+------, +   (.5, .5) mOffsets from origin                |  
   ///   /               \                                                 |  
   ///  |                 |                                                |  
   ///  |        +        |--> +X                                          |  
   ///  |      origin     |                                                |  
   ///   \               /                                                 |  
   ///    '-------------'   <- mRadius from origin of rounded parts        |  
   ///                                                                     |  
   template<CT::Vector T>
   struct TBoxRounded : TBox<T> {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = RTTI::LastCppNameOf<TBoxRounded>();
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
      LANGULUS(NAME) GenerateToken();
      LANGULUS_CONVERTS_TO(Anyness::Text, Flow::Code);

      using Base = TBox<T>;
      using typename Base::PointType;
      using Base::MemberCount;
      using Base::mOffsets;

      TypeOf<T> mRadius;

      NOD() constexpr bool IsDegenerate() const noexcept;
      NOD() constexpr bool IsHollow() const noexcept;
      NOD() auto SignedDistance(const T&) const;

      NOD() explicit operator Anyness::Text() const;
      NOD() explicit operator Flow::Code() const;
   };

} // namespace Langulus::Math