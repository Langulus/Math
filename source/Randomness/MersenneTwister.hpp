///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "../Common.hpp"
#include <random>


namespace Langulus::Math
{

   ///                                                                        
   /// Mersenne Twister random number generator                               
   ///                                                                        
   class MersenneTwister {
   private:
      ::std::mt19937_64 mStdGenerator;

   public:
      /// Provide random numbers for different number types                   
      /// Integer types provide random numbers is the entire integer range    
      /// Real types provide random numbers in the range [-1:1]               
      ///   @tparam T - type of the number                                    
      ///   @return the newly generated number                                
      template<CT::Number T> 
      T Get() noexcept {
         if constexpr (CT::Integer<T>) {
            ::std::uniform_int_distribution<T> dist(
               ::std::numeric_limits<T>::min(),
               ::std::numeric_limits<T>::max()
            );
            return dist(mStdGenerator);
         }
         else if constexpr (CT::Real<T>) {
            ::std::uniform_real_distribution<T> dist(-1, 1);
            return dist(mStdGenerator);
         }
         else LANGULUS_ERROR("Unsupported number type");
      }

      /// Provide random numbers for different number types, in a range       
      ///   @attention assumes min < max                                      
      ///   @attention assumes than when using non-inclusive limits for       
      ///      generating integers, the provided range (if T is integer) is   
      ///      at least 4 units wide, in order to preserve uniformity when    
      ///      offsetting from limits                                         
      ///   @tparam T - type of the number (deducible)                        
      ///   @tparam MIN_INCLUSIVE - whether minimum limit is inclusive        
      ///   @tparam MAX_INCLUSIVE - whether maximum limit is inclusive        
      ///   @param min - the lower end of the range                           
      ///   @param max - the higher end of the range                          
      ///   @return the newly generated number                                
      template<CT::Number T, bool MIN_INCLUSIVE = true, bool MAX_INCLUSIVE = true>
      T Get(const T& min, const T& max) noexcept {
         LANGULUS_ASSUME(UserAssumes, min < max,
            "Lower limit is not below higher limit");
         LANGULUS_ASSUME(UserAssumes, 
            (MIN_INCLUSIVE && MAX_INCLUSIVE)
            || CT::Real<T> || max - min >= T {4},
            "Non-inclusive range can't be uniform - range too small"
         );

         T result;
         if constexpr (CT::Integer<T>) {
            ::std::uniform_int_distribution<T> dist(min, max);
            result = dist(mStdGenerator);
         }
         else if constexpr (CT::Real<T>) {
            ::std::uniform_real_distribution<T> dist(min, max);
            result = dist(mStdGenerator);
         }
         else LANGULUS_ERROR("Unsupported number type");

         if constexpr (!MIN_INCLUSIVE) {
            // Offset from lower limit                                  
            if (result == min) {
               if constexpr (CT::Integer<T>)
                  result += T {1};
               else
                  result += (max - min) * T {0.1};
            }
         }
         
         if constexpr (!MAX_INCLUSIVE) {
            // Offset from higher limit                                 
            if (result == max) {
               if constexpr (CT::Integer<T>)
                  result -= T {1};
               else
                  result -= (max - min) * T {0.1};
            }
         }

         return result;
      }
   };

   using RNG = MersenneTwister;

} // namespace Langulus::Math
