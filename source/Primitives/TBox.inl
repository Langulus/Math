///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TBox.hpp"
#include "../SignedDistance/TBox.inl"
#include "../SignedDistance/TBoxRounded.inl"

#define TEMPLATE()   template<CT::Vector T>
#define TME()        TBox<T>


namespace Langulus::Math
{

   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      return mOffsets.IsDegenerate();
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsHollow() const noexcept {
      return mOffsets[0] < TypeOf<T> {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }

   /// Stringify box for debugging                                            
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      return mOffsets.template Serialize<TME()>();
   }

   /// Serialize box as code                                                  
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      return mOffsets.template Serialize<TME()>();
   }

} // namespace Langulus::Math

#undef TME
#define TME() TBoxRounded<T>


namespace Langulus::Math
{

   /// Check if box is degenerate                                             
   ///   @return true if at least one offset is zero                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsDegenerate() const noexcept {
      return mOffsets.Length() - mRadius, TypeOf<T> {0};
   }

   /// Check if box is hollow                                                 
   ///   @return true if at least one of the offsets is negative              
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsHollow() const noexcept {
      return mOffsets[0] - mRadius < TypeOf<T> {0};
   }

   /// Calculate signed distance                                              
   ///   @param point - point to check distance from                          
   ///   @return the distance to the primitive                                
   TEMPLATE() LANGULUS(INLINED)
   auto TME()::SignedDistance(const T& point) const {
      return Math::SignedDistance(point, *this);
   }

   /// Stringify box for debugging                                            
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      using Flow::Code;
      Code result;
      result += MetaDataOf<TME()>();
      result += Code::Operator::OpenScope;
      Anyness::Block::From(mOffsets.GetRaw(), MemberCount).Serialize(result);
      result += ", ";
      Anyness::Block::From(&mRadius, 1).Serialize(result);
      result += Code::Operator::CloseScope;
      return Abandon(result);
   }

   /// Serialize box as code                                                  
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      return operator Anyness::Text();
   }

} // namespace Langulus::Math

#undef TEMPLATE
#undef TME
