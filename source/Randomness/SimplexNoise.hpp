///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "Hashes.hpp"

namespace Langulus::Math
{

   ///                                                                        
   ///   Simplex noise functions                                              
   ///                                                                        
   ///   @tparam DOUT - number of output dimensions                           
   ///   @tparam DIN - number of input dimensions                             
   ///   @tparam T - real number type to use for computation                  
   template<Count DOUT, Count DIN, CT::Real T = Real>
   struct TSimplex {
      static_assert(DIN >= 1 and DIN <= 4,
         "Simplex noise functions work only for inputs of 1-4 components");
      static_assert(DOUT >= 1 and DOUT <= 4,
         "Simplex noise functions work only for outputs of 1-4 components");

      // Vector type                                                    
      using V = TVector<T, 4>;

      // Hash function                                                  
      using HF = THoskins<DIN, DIN, T>;

      /// Perform the noise function, or get an equivalent shader code        
      ///   @tparam GET_GLSL - true to get shader code equivalent to function 
      template<bool GET_GLSL = false>
      NOD() static auto Hash(V p = {}) noexcept(not GET_GLSL) {
         (void)p;

         if constexpr (DIN == 1) {
            if constexpr (DOUT == 1) {
               ///  1 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 1");
         }
         else if constexpr (DIN == 2) {
            if constexpr (DOUT == 1) {
               ///  1 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return R"shader(
                     float SimplexNoise1(in vec2 p) {
                        const float K1 = 0.366025404; // (sqrt(3)-1)/2;
                        const float K2 = 0.211324865; // (3-sqrt(3))/6;

                        vec2 i = floor(p + (p.x + p.y) * K1);
                        vec2 a = p - i + (i.x + i.y) * K2;
                        vec2 o = (a.x > a.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
                        vec2 b = a - o + K2;
                        vec2 c = a - 1.0 + 2.0 * K2;
                        vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
                        vec3 n = h * h * h * h * vec3(
                           dot(a, HoskinsHash22(i + 0.0)),
                           dot(b, HoskinsHash22(i + o)),
                           dot(c, HoskinsHash22(i + 1.0))
                        );
                        return dot(n, vec3(70.0));
                     }
                  )shader";
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 2");
         }
         else if constexpr (DIN == 3) {
            if constexpr (DOUT == 1) {
               ///  1 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return R"shader(
                     float SimplexNoise1(in vec3 p) {
                        // 1. find current tetrahedron T and it's four vertices
                        //    s, s+i1, s+i2, s+1.0 - absolute skewed (integer) coordinates of T vertices
                        //    x, x1, x2, x3 - unskewed coordinates of p relative to each of T vertices

                        // calculate s and x
                        vec3 s = floor(p + dot(p, vec3(F3)));
                        vec3 x = p - s + dot(s, vec3(G3));

                        // calculate i1 and i2
                        vec3 e = step(vec3(0.0), x - x.yzx);
                        vec3 i1 = e * (1.0 - e.zxy);
                        vec3 i2 = 1.0 - e.zxy * (1.0 - e);

                        // x1, x2, x3
                        vec3 x1 = x - i1 + G3;
                        vec3 x2 = x - i2 + 2.0 * G3;
                        vec3 x3 = x - 1.0 + 3.0 * G3;

                        // 2. find four surflets and store them in d
                        vec4 w, d;

                        // calculate surflet weights
                        w.x = dot(x, x);
                        w.y = dot(x1, x1);
                        w.z = dot(x2, x2);
                        w.w = dot(x3, x3);

                        // w fades from 0.6 at the center of the surflet to 0.0 at the margin
                        w = max(0.6 - w, 0.0);

                        // calculate surflet components
                        d.x = dot(HoskinsHash33(s), x);
                        d.y = dot(HoskinsHash33(s + i1), x1);
                        d.z = dot(HoskinsHash33(s + i2), x2);
                        d.w = dot(HoskinsHash33(s + 1.0), x3);

                        // multiply d by w^4
                        w *= w;
                        w *= w;
                        d *= w;

                        // 3. return the sum of the four surflets
                        return dot(d, vec4(52.0));
                     }
                  )shader";
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 3");
         }
         else if constexpr (DIN == 4) {
            if constexpr (DOUT == 1) {
               ///  1 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  TODO();
               }
               else {
                  TODO();
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 4");
         }
         else LANGULUS_ERROR("Hash function with this input doesn't exist");
      }
   };

} // namespace Langulus::Math