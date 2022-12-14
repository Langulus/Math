///                                                                           
/// Langulus::Math                                                            
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>                    
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
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
   template<CT::Real T>
   struct THoskins {
      /// Perform the specific hashing function                               
      template<Count DOUT, Count DIN, bool GET_GLSL = false>
      NOD() static constexpr auto Hash(TVector<T, DIN> p = {}) noexcept {
         static_assert(DIN >= 1 && DIN <= 4, 
            "Hoskin's hashes work only for inputs of 1-4 components");
         static_assert(DOUT >= 1 && DOUT <= 4, 
            "Hoskin's hashes work only for outputs of 1-4 components");

         constexpr TVector<T, 4> seed = {.1031, .1030, .0973, .1099};

         if constexpr (DIN == 1) {
            if constexpr (DOUT == 1) {
               ///  1 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "float HoskinsHash11(float p) {\n"
                     "   p = fract(p * " + seed[0] + ");\n"
                     "   p *= p + 33.33;\n"
                     "   p *= p + p;\n"
                     "   return fract(p);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed[0]);
                  p *= p + T(33.33);
                  p *= p + p;
                  return T(pcFrac(p));
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec2 HoskinsHash21(float p) {\n"
                     "   Vec3 p3 = fract(p * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p3 += dot(p3, p3.yzx + 31.32);\n"
                     "   return fract((p3.xx + p3.yz) * p3.zy);\n"
                     "}\n\n";
               }
               else {
                  auto p3 = pcFrac(p[0] * TVec<T, 3>(seed));
                  p3 += p3.Dot(p3.yzx() + T(31.32));
                  return pcFrac((p3.xx() + p3.yz()) * p3.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec3 HoskinsHash31(float p) {\n"
                     "   Vec3 p3 = fract(p * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p3 += dot(p3, p3.yzx + 33.33);\n"
                     "   return fract((p3.xxy + p3.yzz) * p3.zyx);\n"
                     "}\n\n";
               }
               else {
                  auto p3 = pcFrac(p[0] * TVec<T, 3>(seed));
                  p3 += p3.Dot(p3.yzx() + T(33.33));
                  return pcFrac((p3.xxy() + p3.yzz()) * p3.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 1 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec4 HoskinsHash41(float p) {\n"
                     "   Vec4 p4 = fract(p * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p4 += dot(p4, p4.wzxy + 33.33);\n"
                     "   return fract((p4.xxyz + p4.yzzw) * p4.zywx);\n"
                     "}\n\n";
               }
               else {
                  auto p4 = pcFrac(p[0] * seed);
                  p4 += p4.Dot(p4.wzxy() + T(33.33));
                  return pcFrac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 1");
         }
         else if constexpr (DIN == 2) {
            if constexpr (DOUT == 1) {
               ///  1 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "float HoskinsHash12(Vec2 p) {\n"
                     "   Vec3 p3 = fract(p.xyx * " + seed[0] + ");\n"
                     "   p3 += dot(p3, p3.yzx + 33.33);\n"
                     "   return fract((p3.x + p3.y) * p3.z);\n"
                     "}\n\n";
               }
               else {
                  auto p3 = pcFrac(p.xyx() * seed[0]);
                  p3 += p3.Dot(p3.yzx() + T(33.33));
                  return T(pcFrac((p3[0] + p3[1]) * p3[2]));
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec2 HoskinsHash22(Vec2 p) {\n"
                     "   Vec3 p3 = fract(p.xyx * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p3 += dot(p3, p3.yzx + 33.33);\n"
                     "   return fract((p3.xx + p3.yz) * p3.zy);\n"
                     "}\n\n";
               }
               else {
                  auto p3 = pcFrac(p.xyx() * TVec<T, 3>(seed));
                  p3 += p3.Dot(p3.yzx() + T(33.33));
                  return pcFrac((p3.xx() + p3.yz()) * p3.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec3 HoskinsHash22(Vec2 p) {\n"
                     "   Vec3 p3 = fract(p.xyx * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p3 += dot(p3, p3.yxz + 33.33);\n"
                     "   return fract((p3.xxy + p3.yzz) * p3.zyx);\n"
                     "}\n\n";
               }
               else {
                  auto p3 = pcFrac(p.xyx() * TVec<T, 3>(seed));
                  p3 += p3.Dot(p3.yxz() + T(33.33));
                  return pcFrac((p3.xxy() + p3.yzz()) * p3.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 2 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec4 HoskinsHash22(Vec2 p) {\n"
                     "   Vec4 p4 = fract(p.xyxy * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p4 += dot(p4, p4.wzxy + 33.33);\n"
                     "   return fract((p4.xxyz + p4.yzzw) * p4.zywx);\n"
                     "}\n\n";
               }
               else {
                  auto p4 = pcFrac(p.xyxy() * seed);
                  p4 += p4.Dot(p4.wzxy() + T(33.33));
                  return pcFrac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 2");
         }
         else if constexpr (DIN == 3) {
            if constexpr (DOUT == 1) {
               ///  1 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "float HoskinsHash13(Vec3 p) {\n"
                     "   p = fract(p * " + seed[0] + ");\n"
                     "   p += dot(p, p.zyx + 31.32);\n"
                     "   return fract((p.x + p.y) * p.z);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed[0]);
                  p += p.Dot(p.zyx() + T(31.32));
                  return T(pcFrac((p[0] + p[1]) * p[2]));
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec2 HoskinsHash23(Vec3 p) {\n"
                     "   p = fract(p * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p += dot(p, p.yzx + 33.33);\n"
                     "   return fract((p.xx + p.yz) * p.zy);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * TVec<T, 3>(seed));
                  p += p.Dot(p.yzx() + T(33.33));
                  return pcFrac((p.xx() + p.yz()) * p.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec3 HoskinsHash33(Vec3 p) {\n"
                     "   p = fract(p * Vec3(" + seed[0] + ", " + seed[1] + ", " + seed[2] + "));\n"
                     "   p += dot(p, p.yxz + 33.33);\n"
                     "   return fract((p.xxy + p.yxx) * p.zyx);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * TVec<T, 3>(seed));
                  p += p.Dot(p.yxz() + T(33.33));
                  return pcFrac((p.xxy() + p.yxx()) * p.zyx());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 3 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec4 HoskinsHash43(Vec3 p) {\n"
                     "   Vec4 p4 = fract(p.xyzx * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p4 += dot(p4, p4.wzxy + 33.33);\n"
                     "   return fract((p4.xxyz + p4.yzzw) * p4.zywx);\n"
                     "}\n\n";
               }
               else {
                  auto p4 = pcFrac(p.xyzx() * seed);
                  p4 += p4.Dot(p4.wzxy() + T(33.33));
                  return pcFrac((p4.xxyz() + p4.yzzw()) * p4.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 3");
         }
         else if constexpr (DIN == 4) {
            if constexpr (DOUT == 1) {
               ///  1 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "float HoskinsHash14(Vec4 p) {\n"
                     "   p = fract(p * " + seed[0] + ");\n"
                     "   p += dot(p, p.ywxz + 32.31);\n"
                     "   return fract((p.x + p.y) * (p.z + p.w));\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed[0]);
                  p += p.Dot(p.ywxz() + T(32.31));
                  return T(pcFrac((p[0] + p[1]) * (p[2] + p[3])));
               }
            }
            else if constexpr (DOUT == 2) {
               ///  2 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec2 HoskinsHash24(Vec4 p) {\n"
                     "   p = fract(p * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p += dot(p, p.wzxy + 33.33);\n"
                     "   return fract((p.xw + p.yz) * p.zy);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed);
                  p += p.Dot(p.wzxy() + T(33.33));
                  return pcFrac((p.xw() + p.yz()) * p.zy());
               }
            }
            else if constexpr (DOUT == 3) {
               ///  3 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec3 HoskinsHash34(Vec4 p) {\n"
                     "   p = fract(p * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p += dot(p, p.wzxy + 33.33);\n"
                     "   return fract((p.zwx + p.yxw) * p.zwy);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed);
                  p += p.Dot(p.wzxy() + T(33.33));
                  return pcFrac((p.zwx() + p.yxw()) * p.zwy());
               }
            }
            else if constexpr (DOUT == 4) {
               ///  4 out, 4 in...                                            
               if constexpr (GET_GLSL) {
                  return Text() +
                     "Vec4 HoskinsHash44(Vec4 p) {\n"
                     "   p = fract(p * Vec4(" + seed[0] + ", " + seed[1] + ", " + seed[2] + ", " + seed[3] + "));\n"
                     "   p += dot(p, p.wzxy + 33.33);\n"
                     "   return fract((p.xxyz + p.yzzw) * p.zywx);\n"
                     "}\n\n";
               }
               else {
                  p = pcFrac(p * seed);
                  p += p.Dot(p.wzxy() + T(33.33));
                  return pcFrac((p.xxyz() + p.yzzw()) * p.zywx());
               }
            }
            else LANGULUS_ERROR("Hash function with this output doesn't exist, for input 4");
         }
         else LANGULUS_ERROR("Hash function with this input doesn't exist");
      }
   };

   /// Sine hashes                                                            
   /// These may be inconsistent on different GPUs and degrade with larger n  
   template<class T>
   NOD() T pcMSinHash(const T& n) noexcept {
      return pcFrac(pcSin(n) * T(43758.5453123));
   }

   template<class T>
   NOD() T pcMSinHash(const TVector<T, 2>& p) noexcept {
      T h = pcDot(p, TVector<T, 2>(T(127.1), T(311.7)));
      return pcFrac(pcSin(h) * T(43758.5453123));
   }

   template<class T>
   NOD() T pcMSinHash(const TVector<T, 3>& p) noexcept {
      T h = pcDot(p, TVector<T, 3>(T(127.1), T(311.7), T(758.5453123)));
      return pcFrac(pcSin(h) * T(43758.5453123));
   }

   /// Integer hashes                                                         
   template<class T>
   NOD() auto pcMIntHash(const T& n) noexcept {
      return n * (n ^ (n >> 15));
   }

} // namespace Langulus::Math