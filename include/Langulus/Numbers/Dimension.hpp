///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include <Langulus/TTag.hpp>


namespace Langulus::CT
{
   namespace Inner
   {
      template<class T>
      concept Dimension = CT::DefineTag<T> and requires {
         {T::Index} -> Same<size_t>;
      };
   }

   /// Dimension is any tag, defined with a Dimension property.               
   /// Used for accessing individual vector components.                       
   template<class... T>
   concept Dimension = (CT::Inner::Dimension<T> and ...);
}
