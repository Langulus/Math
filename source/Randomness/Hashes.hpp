///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Functions/Arithmetics.hpp"
#include "../Vectors/TVector.hpp"


namespace Langulus::Math
{

   ///                                                                        
   ///   Hashes without Sine                                                  
   ///                                                                        
   ///   Credit to David Hoskins - https://www.shadertoy.com/view/4djSRW      
   ///   Trying to find a Hash function that is the same on all systems       
   /// and doesn't rely on trigonometry functions that lose accuracy with     
   /// high values.                                                           
   ///                                                                        
   ///   @tparam DOUT - number of output dimensions                           
   ///   @tparam DIN - number of input dimensions                             
   ///   @tparam T - real number type to use for computation                  
   template<Count DOUT, Count DIN, CT::Real T = Real>
   struct THoskins {
      static_assert(DIN >= 1 && DIN <= 4,
         "Hoskin's hashes work only for inputs of 1-4 components");
      static_assert(DOUT >= 1 && DOUT <= 4,
         "Hoskin's hashes work only for outputs of 1-4 components");

      using V = TVector<T, 4>;
      static constexpr V seed {.1031, .1030, .0973, .1099};
      static constexpr auto v1 = CT::Same<Real, float> ? "float" : "double";
      static constexpr auto v2 = CT::Same<Real, float> ? "vec2" : "vec2d";
      static constexpr auto v3 = CT::Same<Real, float> ? "vec3" : "vec3d";
      static constexpr auto v4 = CT::Same<Real, float> ? "vec4" : "vec4d";

      /// Perform the hashing function, or get an equivalent shader code      
      template<bool GET_GLSL = false>
      NOD() static auto Hash(V p = {}) noexcept(!GET_GLSL) {
         if constexpr (DIN == 1) {
            if constexpr (DOUT == 1) {
               ///  1 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash1({0} p) {{
                           p = fract(p * {1});
                           p *= p + 33.33;
                           p *= p + p;
                           return fract(p);
                        }}
                     )shader",
                     v1, seed[0]
                  );
               }
               else {
                  p = Frac(p * seed[0]);
                  p *= p + T {33.33};
                  p *= p + p;
                  return T {Frac(p)};
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash2({1} p) {{
                           {2} p3 = fract(p * {2}({3}, {4}, {5}));
                           p3 += dot(p3, p3.yzx + 31.32);
                           return fract((p3.xx + p3.yz) * p3.zy);
                        }}
                     )shader",
                     v2, v1, v3,
                     seed[0], seed[1], seed[2]
                  );
               }
               else {
                  auto p3 = Frac(p[0] * TVector<T, 3> {seed});
                  p3 += p3.Dot(p3.yzx() + T {31.32});
                  return Frac((p3.xx() + p3.yz()) * p3.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash3({1} p) {{
                           {0} p3 = fract(p * {0}({2}, {3}, {4}));
                           p3 += dot(p3, p3.yzx + 33.33);
                           return fract((p3.xxy + p3.yzz) * p3.zyx);
                        }}
                     )shader",
                     v3, v1,
                     seed[0], seed[1], seed[2]
                  );
               }
               else {
                  auto p3 = Frac(p[0] * TVector<T, 3> {seed});
                  p3 += p3.Dot(p3.yzx() + T {33.33});
                  return Frac((p3.xxy() + p3.yzz()) * p3.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash4({1} p) {{
                           {0} p4 = fract(p * {0}({2}, {3}, {4}, {5}));
                           p4 += dot(p4, p4.wzxy + 33.33);
                           return fract((p4.xxyz + p4.yzzw) * p4.zywx);
                        }}
                     )shader",
                     v4, v1,
                     seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  auto p4 = Frac(p[0] * seed);
                  p4 += p4.Dot(p4.wzxy() + T {33.33});
                  return Frac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 1");
         }
         else if constexpr (DIN == 2) {
            if constexpr (DOUT == 1) {
               ///  1 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash1({1} p) {{
                           {2} p3 = fract(p.xyx * {3});
                           p3 += dot(p3, p3.yzx + 33.33);
                           return fract((p3.x + p3.y) * p3.z);
                        }}
                     )shader",
                     v1, v2, v3, seed[0]
                  );
               }
               else {
                  auto p3 = Frac(p.xyx() * seed[0]);
                  p3 += p3.Dot(p3.yzx() + T {33.33});
                  return T {Frac((p3[0] + p3[1]) * p3[2])};
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash2({0} p) {{
                           {1} p3 = fract(p.xyx * {1}({2}, {3}, {4}));
                           p3 += dot(p3, p3.yzx + 33.33);
                           return fract((p3.xx + p3.yz) * p3.zy);
                        }}
                     )shader",
                     v2, v3,
                     seed[0], seed[1], seed[2]
                  );
               }
               else {
                  auto p3 = Frac(p.xyx() * TVector<T, 3> {seed});
                  p3 += p3.Dot(p3.yzx() + T {33.33});
                  return Frac((p3.xx() + p3.yz()) * p3.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash3({1} p) {{
                           {0} p3 = fract(p.xyx * {0}({2}, {3}, {4}));
                           p3 += dot(p3, p3.yxz + 33.33);
                           return fract((p3.xxy + p3.yzz) * p3.zyx);
                        }}
                     )shader",
                     v3, v2,
                     seed[0], seed[1], seed[2]
                  );
               }
               else {
                  auto p3 = Frac(p.xyx() * TVector<T, 3> {seed});
                  p3 += p3.Dot(p3.yxz() + T {33.33});
                  return Frac((p3.xxy() + p3.yzz()) * p3.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash4({1} p) {{
                           {0} p4 = fract(p.xyxy * {0}({2}, {3}, {4}, {5}));
                           p4 += dot(p4, p4.wzxy + 33.33);
                           return fract((p4.xxyz + p4.yzzw) * p4.zywx);
                        }}
                     )shader",
                     v4, v2,
                     seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  auto p4 = Frac(p.xyxy() * seed);
                  p4 += p4.Dot(p4.wzxy() + T {33.33});
                  return Frac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 2");
         }
         else if constexpr (DIN == 3) {
            if constexpr (DOUT == 1) {
               ///  1 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash1({1} p) {{
                           p = fract(p * {2});
                           p += dot(p, p.zyx + 31.32);
                           return fract((p.x + p.y) * p.z);
                        }}
                     )shader",
                     v1, v3,
                     seed[0]
                  );
               }
               else {
                  p = Frac(p * seed[0]);
                  p += p.Dot(p.zyx() + T {31.32});
                  return T {Frac((p[0] + p[1]) * p[2])};
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash2({1} p) {{
                           p = fract(p * {1}({2}, {3}, {4}));
                           p += dot(p, p.yzx + 33.33);
                           return fract((p.xx + p.yz) * p.zy);
                        }}
                     )shader",
                     v2, v3, 
                     seed[0], seed[1], seed[2]
                  );
               }
               else {
                  p = Frac(p * TVector<T, 3> {seed});
                  p += p.Dot(p.yzx() + T {33.33});
                  return Frac((p.xx() + p.yz()) * p.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash3({0} p) {{
                           p = fract(p * {0}({1}, {2}, {3}));
                           p += dot(p, p.yxz + 33.33);
                           return fract((p.xxy + p.yxx) * p.zyx);
                        }}
                     )shader",
                     v3, seed[0], seed[1], seed[2]
                  );
               }
               else {
                  p = Frac(p * TVector<T, 3> {seed});
                  p += p.Dot(p.yxz() + T {33.33});
                  return Frac((p.xxy() + p.yxx()) * p.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash4({1} p) {{
                           {0} p4 = fract(p.xyzx * {0}({2}, {3}, {4}, {5}));
                           p4 += dot(p4, p4.wzxy + 33.33);
                           return fract((p4.xxyz + p4.yzzw) * p4.zywx);
                        }}
                     )shader",
                     v4, v3, seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  auto p4 = Frac(p.xyzx() * seed);
                  p4 += p4.Dot(p4.wzxy() + T {33.33});
                  return Frac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 3");
         }
         else if constexpr (DIN == 4) {
            if constexpr (DOUT == 1) {
               ///  1 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash1({1} p) {{
                           p = fract(p * {2});
                           p += dot(p, p.ywxz + 32.31);
                           return fract((p.x + p.y) * (p.z + p.w));
                        }}
                     )shader",
                     v1, v4, seed[0]
                  );
               }
               else {
                  p = Frac(p * seed[0]);
                  p += p.Dot(p.ywxz() + T {32.31});
                  return T {Frac((p[0] + p[1]) * (p[2] + p[3]))};
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash2({1] p) {{
                           p = fract(p * {1}({2}, {3}, {4}, {5}));
                           p += dot(p, p.wzxy + 33.33);
                           return fract((p.xw + p.yz) * p.zy);
                        }}
                     )shader",
                     v2, v4,
                     seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  p = Frac(p * seed);
                  p += p.Dot(p.wzxy() + T {33.33});
                  return Frac((p.xw() + p.yz()) * p.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash3({1} p) {{
                           p = fract(p * {1}({2}, {3}, {4}, {5}));
                           p += dot(p, p.wzxy + 33.33);
                           return fract((p.zwx + p.yxw) * p.zwy);
                        }}
                     )shader",
                     v3, v4,
                     seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  p = Frac(p * seed);
                  p += p.Dot(p.wzxy() + T {33.33});
                  return Frac((p.zwx() + p.yxw()) * p.zwy());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return TemplateFill(
                     R"shader(
                        {0} HoskinsHash4({0} p) {{
                           p = fract(p * {0}({1}, {2}, {3}, {4}));
                           p += dot(p, p.wzxy + 33.33);
                           return fract((p.xxyz + p.yzzw) * p.zywx);
                        }}
                     )shader",
                     v4, seed[0], seed[1], seed[2], seed[3]
                  );
               }
               else {
                  p = Frac(p * seed);
                  p += p.Dot(p.wzxy() + T {33.33});
                  return Frac((p.xxyz() + p.yzzw()) * p.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 4");
         }
         else LANGULUS_ERROR("Hash function with this input doesn't exist");
      }
   };


   ///                                                                        
   /// Sine-based hashes                                                      
   ///                                                                        
   /// These may be inconsistent on different GPUs and degrade with larger n  
   ///                                                                        

   /// 1-1 sin hash                                                           
   ///   @tparam T - real type to use (deducible)                             
   ///   @param n - the number to hash                                        
   template<CT::Real T>
   NOD() T SinHash(const T& n) noexcept {
      return Frac(Sin(n) * T {43758.5453123});
   }

   /// 1-2 sin hash                                                           
   ///   @tparam T - real type to use (deducible)                             
   ///   @param n - the number to hash                                        
   template<CT::Real T>
   NOD() T SinHash(const TVector<T, 2>& p) noexcept {
      T h = Dot(p, TVector<T, 2>(T {127.1}, T {311.7}));
      return Frac(Sin(h) * T {43758.5453123});
   }

   /// 1-3 sin hash                                                           
   ///   @tparam T - real type to use (deducible)                             
   ///   @param n - the number to hash                                        
   template<CT::Real T>
   NOD() T SinHash(const TVector<T, 3>& p) noexcept {
      T h = Dot(p, TVector<T, 3>(T {127.1}, T {311.7}, T {758.5453123}));
      return Frac(Sin(h) * T {43758.5453123});
   }

   /// Integer hashes                                                         
   ///   @tparam T - integer type to use (deducible)                          
   ///   @param n - the number to hash                                        
   template<CT::Integer T>
   NOD() auto IntHash(const T& n) noexcept {
      return n * (n ^ (n >> 15));
   }

} // namespace Langulus::Math