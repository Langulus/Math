///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::Vector>
      struct TLine;

      template<CT::Vector>
      struct TLineLoop;

      template<CT::Vector>
      struct TLineStrip;

      using Line2      = TLine<Vec2>;
      using Line3      = TLine<Vec3>;
      using LineLoop2  = TLineLoop<Vec2>;
      using LineLoop3  = TLineLoop<Vec3>;
      using LineStrip2 = TLineStrip<Vec2>;
      using LineStrip3 = TLineStrip<Vec3>;

      using Line       = Line3;
      using LineLoop   = LineLoop3;
      using LineStrip  = LineStrip3;

   } // namespace Langulus::Maht

   namespace A
   {

      /// An abstract line, also used as a topology type                      
      struct Line : Topology {
         LANGULUS(CONCRETE) Math::Line;
         LANGULUS_BASES(Topology);
      };

      /// An abstract line loop, also used as a topology type                 
      struct LineLoop : Line {
         LANGULUS(CONCRETE) Math::LineLoop;
         LANGULUS_BASES(Line);
      };

      /// An abstract line strip, also used as a topology type                
      struct LineStrip : Line {
         LANGULUS(CONCRETE) Math::LineStrip;
         LANGULUS_BASES(Line);
      };

   } // namespace Langulus::A

   namespace CT
   {

      /// Concept for distinguishing line primitives                          
      template<class...T>
      concept Line = (DerivedFrom<T, A::Line> and ...);

      /// Concept for distinguishing line loop primitives                     
      template<class...T>
      concept LineLoop = (DerivedFrom<T, A::LineLoop> and ...);

      /// Concept for distinguishing line strip primitives                    
      template<class...T>
      concept LineStrip = (DerivedFrom<T, A::LineStrip> and ...);

   } // namespace Langulus::CT

   
   /// Custom name generator at compile-time for lines                        
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TLine<T>>&&) noexcept {
      using CLASS = Math::TLine<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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
   
   /// Custom name generator at compile-time for line loop                    
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TLineLoop<T>>&&) noexcept {
      using CLASS = Math::TLineLoop<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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
   
   /// Custom name generator at compile-time for line loop                    
   template<CT::Vector T>
   consteval auto CustomName(Of<Math::TLineStrip<T>>&&) noexcept {
      using CLASS = Math::TLineStrip<T>;
      constexpr auto defaultClassName = RTTI::LastCppNameOf<CLASS>();
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

} // namespace Langulus

namespace Langulus::Math
{

   ///                                                                        
   ///   Templated line segment                                               
   ///                                                                        
   #pragma pack(push, 1)
   template<CT::Vector T>
   struct TLine : A::Line {
      LANGULUS(NAME) CustomNameOf<TLine>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(POD) CT::POD<T>;
      LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::Line);

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1, "Lines don't exist below two dimensions");

      T mAB[2] {};

   public:
      constexpr TLine() noexcept;

      template<CT::Vector ALT_T = T>
      constexpr TLine(const ALT_T&, const ALT_T&) noexcept;

      template<CT::Vector ALT_T = T>
      constexpr TLine(const ALT_T*) noexcept;

      template<CT::Vector ALT_T = T, CT::Integer IDX>
      constexpr TLine(const ALT_T*, const IDX(&)[2]) noexcept;

      NOD() bool IsDegenerate() const noexcept;

      NOD() ::std::array<TLine, 2> Subdivide() const noexcept;

      NOD() auto SignedDistance(const PointType&) const;

      NOD() auto& operator [] (Offset) const noexcept;
      NOD() auto& operator [] (Offset) noexcept;

      template<CT::Vector ALT>
      NOD() explicit operator TLine<ALT>() const noexcept;
   };
   #pragma pack(pop)


   ///                                                                        
   ///   Templated line loop                                                  
   /// Essentially a list of points, where each next point forms a line with  
   /// the previous, and the last point forms a line with the first one       
   ///                                                                        
   template<CT::Vector T>
   struct TLineLoop : A::LineLoop {
      LANGULUS(NAME) CustomNameOf<TLineLoop>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::LineLoop);

      Anyness::TMany<T> mPoints;

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1,
         "Lines don't exist below two dimensions");
   };


   ///                                                                        
   ///   Templated line strip                                                 
   /// Essentially a list of points, where each next point forms a line with  
   /// the previous                                                           
   ///                                                                        
   template<CT::Vector T>
   struct TLineStrip : A::LineStrip {
      LANGULUS(NAME) CustomNameOf<TLineStrip>::Generate();
      LANGULUS(ABSTRACT) false;
      LANGULUS(TYPED) TypeOf<T>;
      LANGULUS_BASES(A::LineStrip);

      Anyness::TMany<T> mPoints;

      using PointType = T;
      static constexpr Count MemberCount = T::MemberCount;
      static_assert(MemberCount > 1,
         "Lines don't exist below two dimensions");
   };

} // namespace Langulus::Math