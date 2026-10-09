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
   template<CT::CustomVector>
   struct TLine;

   template<CT::CustomVector>
   struct TLineLoop;

   template<CT::CustomVector>
   struct TLineStrip;

   using Line2      = TLine<Vec2>;
   using Line3      = TLine<Vec3>;
   using LineLoop2  = TLineLoop<Vec2>;
   using LineLoop3  = TLineLoop<Vec3>;
   using LineStrip2 = TLineStrip<Vec2>;
   using LineStrip3 = TLineStrip<Vec3>;

   /// An abstract line, also used as a topology type                         
   struct Line : Topology {
      using CTTI_Concrete  = Math::Line3;
      using CTTI_Bases     = Math::Topology;
   };

   /// An abstract line loop, also used as a topology type                    
   struct LineLoop : Line {
      using CTTI_Concrete  = Math::LineLoop3;
      using CTTI_Bases     = Math::Line;
   };

   /// An abstract line strip, also used as a topology type                   
   struct LineStrip : Line {
      using CTTI_Concrete  = Math::LineStrip3;
      using CTTI_Bases     = Math::Line;
   };
}

namespace Langulus::CT
{
   /// Concept for distinguishing line primitives                             
   template<class...T>
   concept Line = (DerivedFrom<T, Math::Line> and ...);

   /// Concept for distinguishing line loop primitives                        
   template<class...T>
   concept LineLoop = (DerivedFrom<T, Math::LineLoop> and ...);

   /// Concept for distinguishing line strip primitives                       
   template<class...T>
   concept LineStrip = (DerivedFrom<T, Math::LineStrip> and ...);
}

namespace Langulus::Math
{
   ///                                                                        
   ///   Templated line segment                                               
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::CustomVector T>
   struct TLine : Line {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TLine>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "Line")
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
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Nullable  = Maybe<CT::Nullable<T>>;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::Line;

      using PointType = T;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Lines don't exist below two dimensions");

      T mAB[2] {};

   public:
      /// Default construction (along x)                                      
      constexpr TLine() noexcept {
         mAB[1][0] = TypeOf<T> {0};
      }

      /// Manual construction from two points of any type                     
      template<CT::Vector ALT_T = T>
      constexpr TLine(const ALT_T& p1, const ALT_T& p2) noexcept
         : mAB {T{p1}, T{p2}} {}

      /// Manual construction from two points of any type (unsafe)            
      template<CT::CustomVector ALT_T = T>
      constexpr TLine(const ALT_T* points) noexcept
         : mAB {points[0], points[1]} {}

      /// Manual construction from two points of any type, indexed            
      template<CT::CustomVector ALT_T = T, CT::Integer IDX>
      constexpr TLine(const ALT_T* points, const IDX(&indices)[2]) noexcept
         : mAB {points[indices[0]], points[indices[1]]} {}

      /// Check if line is degenerate                                         
      ///   @return true if line has no radius or no length                   
      bool IsDegenerate() const noexcept {
         return (mAB[0] - mAB[1]).Length() == TypeOf<T> {0};
      }

      /// Subdivide line                                                      
      ///   @return the two new lines                                         
      auto Subdivide() const noexcept -> ::std::array<TLine, 2> {
         const T midpoint = mAB[0] + (mAB[1] - mAB[0]) / TypeOf<T> {2};
         return {{mAB[0], midpoint}, {midpoint, mAB[1]}};
      }

      /// Access points                                                       
      auto& operator [] (this auto&& self, size_t i) noexcept {
         return self.mAB[i];
      }

      /// Convert to other kinds of lines                                     
      ///   @tparam ALT - alternative point type (deducible)                  
      template<CT::CustomVector ALT>
      explicit operator TLine<ALT>() const noexcept {
         return {static_cast<ALT>(mAB[0]), static_cast<ALT>(mAB[1])};
      }
   };
   #pragma pack(pop)


   ///                                                                        
   ///   Templated line loop                                                  
   /// Essentially a list of points, where each next point forms a line with  
   /// the previous, and the last point forms a line with the first one       
   ///                                                                        
   template<CT::CustomVector T>
   struct TLineLoop : LineLoop {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TLineLoop>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "LineLoop")
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
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_Abstract  = No;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::LineLoop;
      
      Annies::TMany<T> mPoints;

      using PointType = T;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Lines don't exist below two dimensions");
   };


   ///                                                                        
   ///   Templated line strip                                                 
   /// Essentially a list of points, where each next point forms a line with  
   /// the previous                                                           
   ///                                                                        
   template<CT::CustomVector T>
   struct TLineStrip : LineStrip {
   private:
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TLineStrip>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (T::MemberCount > 3) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         for (auto i : "LineStrip")
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
      using CTTI_Named     = Yes<GenerateToken()>;;
      using CTTI_Abstract  = No;
      using CTTI_Typed     = TypeOf<T>;
      using CTTI_Bases     = Math::LineStrip;

      Annies::TMany<T> mPoints;

      using PointType = T;
      static constexpr size_t MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Lines don't exist below two dimensions");
   };
}