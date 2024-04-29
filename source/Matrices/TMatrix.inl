///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// Distributed under GNU General Public License v3+                          
/// See LICENSE file, or https://www.gnu.org/licenses                         
///                                                                           
#pragma once
#include "TMatrix.hpp"
#include "../Vectors/TVector.inl"
#include "../Numbers/TAngle.inl"

#define TARGS(a) CT::ScalarBased a##T, Count a##C, Count a##R
#define TMAT(a) TMatrix<a##T, a##C, a##R>
#define TEMPLATE() template<CT::ScalarBased T, Count COLUMNS, Count ROWS>
#define TME() TMatrix<T, COLUMNS, ROWS>


namespace Langulus::Math
{

   /// Default constructor (identity)                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix() noexcept {
      for (Offset i = 0; i < Diagonal; ++i)
         mColumns[i][i] = T {1};
   }

   /// Copy constructor                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix(const TMatrix& other) noexcept {
      for (Count i = 0; i < Columns; ++i)
         mColumns[i] = other.mColumns[i];
   }

   /// Move constructor                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix(TMatrix&& other) noexcept {
      for (Count i = 0; i < Columns; ++i)
         mColumns[i] = ::std::move(other.mColumns[i]);
   }

   /// Construct from similar matrix                                          
   ///   @param a - differently sized matrix                                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix(const CT::MatrixBased auto& a) noexcept {
      using M = Deref<Desem<decltype(a)>>;
      if constexpr (M::Columns != Columns or M::Rows != Rows) {
         if constexpr (M::Columns < Columns or M::Rows < Rows) {
            // If copied region is smaller, make sure to reset          
            *this = Identity();
         }

         for (Offset col = 0; col < Math::Min(Columns, M::Columns); ++col) {
            for (Offset row = 0; row < Math::Min(Rows, M::Rows); ++row) {
               mColumns[col][row] = Adapt(DesemCast(a).mColumns[col][row]);
            }
         }
      }
      else if constexpr (not CT::Same<TypeOf<M>, T>) {
         for (int i = 0; i < MemberCount; ++i) {
            // Convert all elements                                     
            mArray[i] = Adapt(DesemCast(a).mArray[i]);
         }
      }
      else {
         // Direct memory copy (fastest)                                
         CopyMemory(mArray, DesemCast(a).mArray);
      }
   }
   
   /// Construct from scalar                                                  
   ///   @param x - spread across entire matrix diagonal                      
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix(const CT::ScalarBased auto& x) noexcept {
      const T xx = Adapt(DesemCast(x));
      for (Offset i = 0; i < Diagonal; ++i)
         mColumns[i][i] = xx;
   }

   /// Construct from vector                                                  
   ///   @param x - spread across entire matrix diagonal, if vector size is   
   ///      equal or smaller than the number of diagonal cells if vector is   
   ///      smaller, the remaining values default to 1 if vector is larger,   
   ///      the elements are copied sequentially with any missing elements    
   ///      defaulting to identity                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()::TMatrix(const CT::VectorBased auto& x) noexcept {
      using V = Deref<Desem<decltype(x)>>;
      constexpr auto D = Math::Min(Diagonal, CountOf<V>);
      for (Offset i = 0; i < D; ++i)
         mColumns[i][i] = Adapt(x[i]);
   }

   /// Manual initialization with variadic head-tail                          
   /// The count of elements in head and tail should sum to the matrix size   
   /// Unitialized elements will default to identity                          
   ///   @param t1, t2, tn.. - scalars or vector                              
   TEMPLATE() template<class T1, class T2, class...TN> LANGULUS(INLINED)
   constexpr TME()::TMatrix(const T1& t1, const T2& t2, const TN&...tn) noexcept {
      static_assert(not CT::MatrixBased<T1, T2, TN...>,
         "Sequential matrices not allowed");

      constexpr auto C1 = Math::Min(CountOf<T1>, MemberCount);
      if constexpr (CT::Vector<T1>) {
         // First element is vector/array, copy its elements            
         for (Offset i = 0; i < C1; ++i)
            mArray[i] = Adapt(t1[i]);
      }
      else {
         // First element is a scalar, copy it                          
         mArray[0] = Adapt(t1);
      }

      constexpr auto C2 = Math::Min(CountOf<T2>, MemberCount - C1);
      if constexpr (C2) {
         if constexpr (CT::Vector<T2>) {
            // Second element is vector/array, copy its elements        
            for (Offset i = C1; i < C1 + C2; ++i)
               mArray[i] = Adapt(t2[i - C1]);
         }
         else {
            // Second element is a scalar, copy it                      
            mArray[C1] = Adapt(t2);
         }

         // Combine all the rest of the arguments in a vector           
         if constexpr (sizeof...(TN)) {
            constexpr auto C3 = Math::Min(CountOf<TN...>, MemberCount - (C1 + C2));
            if constexpr (C3) {
               const TVector<T, C3> theRest {tn...};
               for (Offset i = C1 + C2; i < MemberCount; ++i)
                  mArray[i] = theRest[i - (C1 + C2)];
            }
         }
      }
   }
   
   /// Construct from a descriptor                                            
   ///   @param describe - the descriptor to scan                             
   TEMPLATE()
   TME()::TMatrix(Describe&& describe) {
      LANGULUS_ASSUME(UserAssumes, *describe,
         "Empty descriptor for TMatrix");

      // Attempt initializing without any conversion                    
      T all[MemberCount];
      auto initialized = describe->ExtractData(all);
      if (not initialized) {
         // Attempt converting anything to T                            
         initialized = describe->ExtractDataAs(all);
      }

      if (not initialized) {
         // Nothing was initialized. This is always an error in the     
         // context of the descriptor-constructor. If descriptor was    
         // empty, the default constructor would've been explicitly     
         // called, instead of this one. This way we can differentiate  
         // whether or not a matrix object was successfully initialized 
         LANGULUS_OOPS(Construct, "Bad TMatrix descriptor",
            ", nothing was initialized: ", *describe);
      }
      else if (initialized <= Diagonal) {
         // If number of values is below number of columns, create a    
         // scale matrix                                                
         for (Offset i = 0; i < initialized; ++i)
            mColumns[i][i] = all[i];
      }
      else {
         // Otherwise copy the provided elements, the rest is identity  
         ::std::memcpy(mArray, all, initialized * sizeof(T));
      }
   }

   /// Adapt a component to the matrix's internal type                        
   ///   @param x - the component to adapt                                    
   ///   @return the adapted component                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr decltype(auto) TME()::Adapt(const CT::ScalarBased auto& x) noexcept {
      using N = Deref<decltype(x)>;
      static_assert(CT::Convertible<N, T>, "Incompatible number");

      if constexpr (not CT::Same<N, T>)
         return static_cast<T>(x);
      else
         return x;
   }
   
   /// Look at constructor - LH lookat matrix                                 
   TEMPLATE()
   constexpr TME() TME()::LookAt(TVector<T, 3> forward, TVector<T, 3> up)
   requires (ROWS >= 2 and COLUMNS >= 2) {
      static_assert(IsSquare, "Can't make a look-at matrix from this one");

      forward = forward.Normalize();
      up = up.Normalize();
      if (forward.Abs() == up.Abs())
         throw Except::Arithmetic("Degenerate LookAt matrix - forward and up are the same");

      const auto right = up.Cross(forward).Normalize();
      up = forward.Cross(right);

      TME() result = Identity();
      result.mColumns[0][0] = right[0];
      result.mColumns[1][0] = right[1];
      result.mColumns[2][0] = right[2];
      result.mColumns[0][1] = up[0];
      result.mColumns[1][1] = up[1];
      result.mColumns[2][1] = up[2];
      result.mColumns[0][2] = forward[0];
      result.mColumns[1][2] = forward[1];
      result.mColumns[2][2] = forward[2];
      return result;
   }

   /// Create a rotational matrix (for 2x2 matrix, only around z)             
   TEMPLATE()
   constexpr TME() TME()::Rotate(
      const CT::Angle auto& roll
   ) noexcept requires (ROWS >= 2 and COLUMNS >= 2) {
      auto cosR = Math::Cos(roll);
      auto sinR = Math::Sin(roll);

      TME() r;
      r.mColumns[0][0] = cosR;
      r.mColumns[0][1] = sinR;
      r.mColumns[1][0] =-sinR;
      r.mColumns[1][1] = cosR;
      return r;
   }

   /// Create a rotational matrix based on axis and angle                     
   /// Builds a 3D rotation matrix created from normalized axis and an angle  
   TEMPLATE()
   constexpr TME() TME()::RotateAxis(
      const TVector<T, 3>& axis,
      const CT::Angle auto& a
   ) noexcept requires (ROWS >= 3 and COLUMNS >= 3) {
      const T c = Math::Cos(a);
      const T s = Math::Sin(a);

      const auto temp = (T {1} - c) * axis;

      TME() r;
      r[0][0] = c + temp[0] * axis[0];
      r[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
      r[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

      r[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
      r[1][1] = c + temp[1] * axis[1];
      r[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

      r[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
      r[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
      r[2][2] = c + temp[2] * axis[2];
      return r;
   }

   /// Rotational constructor in euler angles (for 3x3 matrix or above)       
   /// Creates a homogeneous 3D rotation matrix from euler angles (Y * X * Z) 
   TEMPLATE()
   constexpr TME() TME()::Rotate(
      const CT::Angle auto& pitch,
      const CT::Angle auto& yaw
   ) noexcept requires (ROWS >= 3 and COLUMNS >= 3) {
      const T tmp_ch = Math::Cos(yaw);
      const T tmp_sh = Math::Sin(yaw);
      const T tmp_cp = Math::Cos(pitch);
      const T tmp_sp = Math::Sin(pitch);
      constexpr T tmp_cb {1};
      constexpr T tmp_sb {0};

      TME() r;
      r[0][0] =  tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
      r[0][1] =  tmp_sb * tmp_cp;
      r[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
      r[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
      r[1][1] =  tmp_cb * tmp_cp;
      r[1][2] =  tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
      r[2][0] =  tmp_sh * tmp_cp;
      r[2][1] = -tmp_sp;
      r[2][2] =  tmp_ch * tmp_cp;
      return r;
   }
   
   /// Rotational constructor in euler angles (for 3x3 matrix or above)       
   /// Creates a homogeneous 3D rotation matrix from euler angles (Y * X * Z) 
   TEMPLATE()
   constexpr TME() TME()::Rotate(
      const CT::Angle auto& pitch,
      const CT::Angle auto& yaw,
      const CT::Angle auto& roll
   ) noexcept requires (ROWS >= 3 and COLUMNS >= 3) {
      const T tmp_ch = Math::Cos(yaw);
      const T tmp_sh = Math::Sin(yaw);
      const T tmp_cp = Math::Cos(pitch);
      const T tmp_sp = Math::Sin(pitch);
      const T tmp_cb = Math::Cos(roll);
      const T tmp_sb = Math::Sin(roll);

      TME() r;
      r[0][0] =  tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
      r[0][1] =  tmp_sb * tmp_cp;
      r[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
      r[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
      r[1][1] =  tmp_cb * tmp_cp;
      r[1][2] =  tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
      r[2][0] =  tmp_sh * tmp_cp;
      r[2][1] = -tmp_sp;
      r[2][2] =  tmp_ch * tmp_cp;
      return r;
   }

   /// Translational matrix                                                   
   ///   @param position - the position to set                                
   ///   @return the translation matrix                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Translate(const CT::VectorBased auto& position) noexcept {
      TMatrix temp {};
      return temp.SetPosition(position);
   }

   /// Uniform scale matrix                                                   
   ///   @attention diagonals beyond 3x3 matrix created with this routine     
   ///              will always be 1. If you want the entire diagonal set,    
   ///              use the scalar constructor instead                        
   ///   @param x - the uniform scale factor                                  
   ///   @return the scale matrix                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Scale(const CT::ScalarBased auto& x) noexcept {
      TMatrix temp {x};
      if constexpr (Diagonal >= 4) {
         for (Count i = 3; i < Diagonal; ++i)
            temp[i][i] = T {1};
      }
      return temp;
   }

   /// Non-uniform scale matrix                                               
   ///   @attention diagonals beyond the vector size will be defaulted to 1   
   ///   @param x - the scale factors                                         
   ///   @return the scale matrix                                             
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Scale(const CT::VectorBased auto& x) noexcept {
      return TMatrix {x};
   }

   /// Create an identity matrix - identical to the default constructor       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Identity() noexcept {
      return {};
   }

   /// Create a null matrix                                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Null() noexcept {
      return {0};
   }


   ///                                                                        
   ///   Assignment                                                           
   ///                                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const TMatrix& other) noexcept {
      for (Count i = 0; i < Columns; ++i)
         mColumns[i] = other.mColumns[i];
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (TMatrix&& other) noexcept {
      for (Count i = 0; i < Columns; ++i)
         mColumns[i] = ::std::move(other.mColumns[i]);
      return *this;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::MatrixBased auto& other) noexcept {
      return *new (this) TMatrix {other};
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::VectorBased auto& other) noexcept {
      return *new (this) TMatrix {other};
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::operator = (const CT::ScalarBased auto& other) noexcept {
      return *new (this) TMatrix {other};
   }

   TEMPLATE() template<CT::ScalarBased N, CT::Dimension D> LANGULUS(INLINED)
   constexpr auto& TME()::operator = (const TVectorComponent<N, D>& other) noexcept {
      static_assert(D::Index < Columns and D::Index < Rows,
         "Vector component out of limits");
      new (this) TME();
      mColumns[D::Index][D::Index] = Adapt(other.mValue);
      return *this;
   }
   

   ///                                                                        
   ///   Interpretation                                                       
   ///                                                                        

   /// Write the body of the matrix                                           
   ///   @return the resulting body                                           
   TEMPLATE() template<class TOKEN>
   Flow::Code TME()::Serialize() const {
      using Flow::Code;
      Code result;
      constexpr bool SCOPED = not CT::Same<TME(), TOKEN>;
      if constexpr (SCOPED) {
         result += MetaDataOf<TOKEN>();
         result += Code::Operator::OpenScope;
      }

      Anyness::MakeBlock(GetRaw(), MemberCount).Serialize(result);

      if constexpr (SCOPED)
         result += Code::Operator::CloseScope;
      return Abandon(result);
   }

   /// Stringify vector for debugging                                         
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Anyness::Text() const {
      return Serialize<TME()>();
   }

   /// Serialize vector as code                                               
   TEMPLATE() LANGULUS(INLINED)
   TME()::operator Flow::Code() const {
      return Serialize<TME()>();
   }


   ///                                                                        
   ///   ARITHMETICS                                                          
   ///                                                                        

   /// Multiply two matrices - not commutative                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator * (const TME()& lhs, const TME()& rhs) noexcept {
      TME() r = TME()::Null();
      for (Offset col = 0; col < COLUMNS; ++col) {
         auto& rc = r[col];
         auto& rhsc = rhs[col];
         for (Offset row = 0; row < ROWS; ++row)
            rc += lhs[row] * rhsc[row];
      }
      return r;
   }

   /// Add two matrices                                                       
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator + (const TME()& me, const TME()& other) noexcept {
      TME() result(me);
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         result[idx] += other.mArray[idx];
      return result;
   }

   /// Subtract two matrices                                                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator - (const TME()& me, const TME()& other) noexcept {
      TME() result(me);
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         result[idx] -= other.mArray[idx];
      return result;
   }

   /// Multiply matrix by a scalar                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator * (const TME()& me, const T& s) noexcept {
      TME() result(me);
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         result[idx] *= s;
      return result;
   }

   /// Multiply scalar by a matrix                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator * (const T& s, const TME()& me) noexcept {
      return me * s;
   }

   /// Divide the matrix by a scalar - not commutative                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator / (const TME()& me, const T& s) noexcept {
      const auto inv_s = T(1) / s;
      TME() result(me);
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         result[idx] *= inv_s;
      return result;
   }

   /// Divide the scalar by a matrix - not commutative                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() operator / (const T& s, const TME()& me) noexcept {
      TME() result(me);
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         result[idx] = s / result[idx];
      return result;
   }

   /// Destructive multiplication of two matrices (not commutative)           
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& operator *= (TME()& me, const TME()& other) noexcept {
      return me = me * other;
   }

   /// Destructive addition of two matrices. Not commutative                  
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& operator += (TME()& me, const TME()& other) noexcept {
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         me.mArray[idx] += other.mArray[idx];
      return me;
   }

   /// Destructive subtraction of two matrices. Not commutative               
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& operator -= (TME()& me, const TME()& other) noexcept {
      for (Offset idx = 0; idx < me.MemberCount; ++idx)
         me.mArray[idx] -= other.mArray[idx];
      return me;
   }

   /// Destructive multiplication by a scalar. Not commutative                
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& operator *= (TME()& me, const T& s) noexcept {
      for (auto& it : me.mArray)
         it *= s;
      return me;
   }

   /// Destructive division by a scalar. Not commutative                      
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& operator /= (TME()& me, const T& s) noexcept {
      const auto inv_s = T(1) / s;
      for (auto& it : me.mArray)
         it *= inv_s;
      return me;
   }

   /// Multiply by a row vector                                               
   ///   @return a column vector result                                       
   template<TARGS(LHS), CT::ScalarBased T, Count C>
   constexpr TVector<T, C> operator * (const TMAT(LHS)& me, const TVector<T, C>& vec) noexcept requires (C <= LHSC and C > 1) {
      using LT = Lossless<T, LHST>;
      if constexpr (LHSC == LHSR and LHSC == 2) {
         // 2x2 matrix * row optimization                               
         return {
            me.mColumns[0][0] * vec[0] + me.mColumns[1][0] * vec[1],
            me.mColumns[0][1] * vec[0] + me.mColumns[1][1] * vec[1]
         };
      }
      else if constexpr (LHSC == LHSR and LHSC == 3) {
         // 3x3 matrix * row optimization                               
         return {
            me.mColumns[0][0] * vec[0] + me.mColumns[1][0] * vec[1] + me.mColumns[2][0] * vec[2],
            me.mColumns[0][1] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[2][1] * vec[2],
            me.mColumns[0][2] * vec[0] + me.mColumns[1][2] * vec[1] + me.mColumns[2][2] * vec[2]
         };
      }
      else if constexpr (LHSC == LHSR and LHSC == 4) {
         /* __m128 v0 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0));
      __m128 v1 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1));
      __m128 v2 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2));
      __m128 v3 = _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 3, 3, 3));
      __m128 m0 = _mm_mul_ps(m[0].data, v0);
      __m128 m1 = _mm_mul_ps(m[1].data, v1);
      __m128 a0 = _mm_add_ps(m0, m1);
      __m128 m2 = _mm_mul_ps(m[2].data, v2);
      __m128 m3 = _mm_mul_ps(m[3].data, v3);
      __m128 a1 = _mm_add_ps(m2, m3);
      __m128 a2 = _mm_add_ps(a0, a1);
      return typename mat<4, 4, T, Q>::col_type(a2);*/
         // 4x4 matrix * row optimization                               
         if constexpr (C > 3) {
            return {
               me.mColumns[0][0] * vec[0] + me.mColumns[1][0] * vec[1] + me.mColumns[2][0] * vec[2] + me.mColumns[3][0] * vec[3],
               me.mColumns[0][1] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[2][1] * vec[2] + me.mColumns[3][1] * vec[3],
               me.mColumns[0][2] * vec[0] + me.mColumns[1][2] * vec[1] + me.mColumns[2][2] * vec[2] + me.mColumns[3][2] * vec[3],
               me.mColumns[0][3] * vec[0] + me.mColumns[1][3] * vec[1] + me.mColumns[2][3] * vec[2] + me.mColumns[3][3] * vec[3]
            };
         }
         else {
            return {
               me.mColumns[0][0] * vec[0] + me.mColumns[1][0] * vec[1] + me.mColumns[2][0] * vec[2] + me.mColumns[3][0],
               me.mColumns[0][1] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[2][1] * vec[2] + me.mColumns[3][1],
               me.mColumns[0][2] * vec[0] + me.mColumns[1][2] * vec[1] + me.mColumns[2][2] * vec[2] + me.mColumns[3][2],
               me.mColumns[0][3] * vec[0] + me.mColumns[1][3] * vec[1] + me.mColumns[2][3] * vec[2] + me.mColumns[3][3]
            };
         }
      }
      else {
         // Generic matrix * row                                        
         LT r[C] = {};
         for (Offset vr = 0; vr < C; ++vr) {
            for (Offset mc = 0; mc < Math::Min(C, LHSC); ++mc)
               r[vr] += me.mColumns[mc][vr] * vec[mc];
         }
         return r;
      }
   }

   /// Multiply by a column vector                                            
   ///   @return a row vector result                                          
   template<TARGS(RHS), CT::ScalarBased T, Count C>
   constexpr TVector<T, C> operator * (const TVector<T, C>& vec, const TMAT(RHS)& me) noexcept requires (C <= RHSR and C > 1) {
      using LT = Lossless<T, RHST>;
      if constexpr (RHSC == RHSR and RHSC == 2) {
         // 2x2 column * matrix optimization                            
         return {
            me.mColumns[0][0] * vec[0] + me.mColumns[0][1] * vec[1],
            me.mColumns[1][0] * vec[0] + me.mColumns[1][1] * vec[1]
         };
      }
      else if constexpr (RHSC == RHSR and RHSC == 3) {
         // 3x3 column * matrix optimization                            
         return {
            me.mColumns[0][0] * vec[0] + me.mColumns[0][1] * vec[1] + me.mColumns[0][2] * vec[2],
            me.mColumns[1][0] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[1][2] * vec[2],
            me.mColumns[2][0] * vec[0] + me.mColumns[2][1] * vec[1] + me.mColumns[2][2] * vec[2]
         };
      }
      else if constexpr (RHSC == RHSR and RHSC == 4) {
         // 4x4 column * matrix optimization                            
         if constexpr (C > 3) {
            return {
               me.mColumns[0][0] * vec[0] + me.mColumns[0][1] * vec[1] + me.mColumns[0][2] * vec[2] + me.mColumns[0][3] * vec[3],
               me.mColumns[1][0] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[1][2] * vec[2] + me.mColumns[1][3] * vec[3],
               me.mColumns[2][0] * vec[0] + me.mColumns[2][1] * vec[1] + me.mColumns[2][2] * vec[2] + me.mColumns[2][3] * vec[3],
               me.mColumns[3][0] * vec[0] + me.mColumns[3][1] * vec[1] + me.mColumns[3][2] * vec[2] + me.mColumns[3][3] * vec[3]
            };
         }
         else {
            return {
               me.mColumns[0][0] * vec[0] + me.mColumns[0][1] * vec[1] + me.mColumns[0][2] * vec[2] + me.mColumns[0][3],
               me.mColumns[1][0] * vec[0] + me.mColumns[1][1] * vec[1] + me.mColumns[1][2] * vec[2] + me.mColumns[1][3],
               me.mColumns[2][0] * vec[0] + me.mColumns[2][1] * vec[1] + me.mColumns[2][2] * vec[2] + me.mColumns[2][3],
               me.mColumns[3][0] * vec[0] + me.mColumns[3][1] * vec[1] + me.mColumns[3][2] * vec[2] + me.mColumns[3][3]
            };
         }
      }
      else {
         // Generic column * matrix                                     
         LT r[C] = {};
         for (Offset vr = 0; vr < C; ++vr) {
            for (Offset mc = 0; mc < Math::Min(C, RHSR); ++mc)
               r[vr] += me.mColumns[vr][mc] * vec[mc];
         }
         return r;
      }
   }

   /// Destructive multiplication of a row vector                             
   template<TARGS(RHS), CT::ScalarBased T, Count C> LANGULUS(INLINED)
   constexpr TVector<T, C>& operator *= (TVector<T, C>& vec, const TMAT(RHS)& me) noexcept requires (C <= RHSC and C > 1) {
      return vec = vec * me;
   }


   ///                                                                        
   ///   COMPARISON                                                           
   ///                                                                        
   /// Compare with another matrix                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool operator == (const TME()& lhs, const TME()& rhs) noexcept {
      return 0 == memcmp(lhs.mArray, rhs.mArray, sizeof(lhs.mArray));
   }

   /// Compare with scalar                                                    
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool operator == (const TME()& lhs, const T& rhs) noexcept {
      for (auto& it : lhs.mArray)
         if (it != rhs)
            return false;
      return true;
   }


   ///                                                                        
   ///   ENCAPSULATION                                                        
   ///                                                                        
   /// Access 1D index                                                        
   ///   @param i - index [0; MemberCount)                                    
   ///   @return a reference to the element                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::ColumnType& TME()::operator [] (const Offset i) noexcept {
      return mColumns[i];
   }

   /// Access 1D index (const)                                                
   ///   @param i - index [0; COLS*ROWS)                                      
   ///   @return a reference to the element                                   
   TEMPLATE() LANGULUS(INLINED)
   constexpr const typename TME()::ColumnType& TME()::operator [] (const Offset i) const noexcept {
      return mColumns[i];
   }

   /// Access raw data                                                        
   ///   @return pointer to the first element                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr T* TME()::GetRaw() noexcept {
      return mArray;
   }

   /// Access raw data (const)                                                
   ///   @return pointer to the first element                                 
   TEMPLATE() LANGULUS(INLINED)
   constexpr const T* TME()::GetRaw() const noexcept {
      return mArray;
   }

   /// Get right axis                                                         
   TEMPLATE() LANGULUS(INLINED)
   constexpr TVector<T, 3> TME()::GetRight() const noexcept {
      if constexpr (IsSquare and Rows > 2)
         return {mColumns[0][0], mColumns[1][0], mColumns[2][0]};
      else LANGULUS_ERROR("Can't get right axis of this matrix");
   }

   /// Get up axis                                                            
   TEMPLATE() LANGULUS(INLINED)
   constexpr TVector<T, 3> TME()::GetUp() const noexcept {
      if constexpr (IsSquare and Rows > 2)
         return {mColumns[0][1], mColumns[1][1], mColumns[2][1]};
      else LANGULUS_ERROR("Can't get up axis of this matrix");
   }

   /// Get view axis                                                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr TVector<T, 3> TME()::GetView() const noexcept {
      if constexpr (IsSquare and Rows > 2)
         return {mColumns[0][2], mColumns[1][2], mColumns[2][2]};
      else LANGULUS_ERROR("Can't get view axis of this matrix");
   }

   /// Get translation                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TVector<T, 3> TME()::GetScale() const noexcept {
      if constexpr (IsSquare and Rows > 2)
         return {GetRight().Length(), GetUp().Length(), GetView().Length()};
      else LANGULUS_ERROR("Can't get translation of this matrix");
   }

   /// Get translation                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr const TVector<T, ROWS - 1>& TME()::GetPosition()
   const noexcept requires (ROWS > 2 and COLUMNS > 2) {
      return mColumns[Columns - 1];
   }

   /// Set translation                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME()& TME()::SetPosition(const CT::Vector auto& position)
   noexcept requires (ROWS > 2 and COLUMNS > 2) {
      using V = Deref<decltype(position)>;
      constexpr auto S = Math::Min(3u, CountOf<V>);
      static_assert (S <= Rows and S <= Columns,
         "Position out of matrix limits");
      auto& column = mColumns[Columns - 1];
      for (unsigned i = 0; i < S; ++i)
         column[i] = position[i];
      return *this;
   }

   /// Get a whole row                                                        
   ///   @param idx - row index                                               
   ///   @return a row                                                        
   TEMPLATE() LANGULUS(INLINED)
   typename TME()::RowType TME()::GetRow(Offset idx) const noexcept {
      T r[Columns];
      for (unsigned i = 0; i < Columns; ++i)
         r[i] = mColumns[i][idx];
      return r;
   }

   /// Get a whole column                                                     
   ///   @param idx - column index                                            
   ///   @return a column                                                     
   TEMPLATE() LANGULUS(INLINED)
   const typename TME()::ColumnType& TME()::GetColumn(Offset idx) const noexcept {
      return mColumns[idx];
   }

   /// Check if identity                                                      
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsIdentity() const noexcept {
      return *this == Identity();
   }

   /// Check if null                                                          
   TEMPLATE() LANGULUS(INLINED)
   constexpr bool TME()::IsNull() const noexcept {
      return *this == Null();
   }

   /// Inner static function for nested determinant calculation               
   TEMPLATE() template<Count SIZE, Count NEXT_SIZE>
   constexpr T TME()::InnerDeterminant(const T(&a)[SIZE * SIZE]) noexcept {
      if constexpr (SIZE == 0)
         return T(0);
      else if constexpr (SIZE == 1)
         return a[0];
      else if constexpr (SIZE == 2)
         return a[0] * a[3] - a[2] * a[1];
      else {
         Count p, h, k, i, j;
         T det = 0;
         T temp[NEXT_SIZE * NEXT_SIZE];
         for (p = 0; p < SIZE; p++) {
            h = 0;
            k = 0;
            for (i = 1; i < SIZE; i++) {
               for (j = 0; j < SIZE; j++) {
                  if (j == p)
                     continue;

                  temp[h + k * NEXT_SIZE] = a[i + j * SIZE];
                  k++;
                  if (k == SIZE - 1) {
                     h++;
                     k = 0;
                  }
               }
            }
            det += a[p * SIZE] * Pow(T(-1), T(p)) * InnerDeterminant<NEXT_SIZE>(temp);
         }

         return det;
      }
   }

   /// Calculate the determinant of the matrix                                
   ///   @return the determinant of the matrix                                
   TEMPLATE() LANGULUS(INLINED)
   constexpr T TME()::Determinant() const noexcept {
      static_assert(IsSquare, "Can't get determinant of a non-square matrix");
      return InnerDeterminant<Columns>(mArray);
   }

   /// Transpose the matrix                                                   
   ///   @return the transposed matrix                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr TME() TME()::Transpose() const noexcept {
      static_assert(IsSquare, "Can't transpose non-square matrix");
      TME() result = *this;
      for (int i = 0; i < Columns; ++i) {
         for (int j = 0; j < i; ++j) {
            ::std::swap(result.mColumns[i][j], result.mColumns[j][i]);
         }
      }
      return result;
   }

   /// Get cofactor                                                           
   ///   @return the given cofactor of the matrix                             
   TEMPLATE()
   constexpr TME() TME()::Cofactor(int p, int q, int n) const noexcept {
      TME() temp;
      int i = 0, j = 0;
      for (int row = 0; row < n; row++) {
         for (int col = 0; col < n; col++) {
            //  Copying into temporary matrix only those element        
            //  which are not in given row and column                   
            if (row != p and col != q) {
               temp.mColumns[j++][i] = mColumns[col][row];

               // Row is filled, so increase row index and              
               // reset col index                                       
               if (j == n - 1) {
                  j = 0;
                  i++;
               }
            }
         }
      }

      return temp;
   }

   /// Get determinant of specific dimension                                  
   ///   @return the determinant                                              
   TEMPLATE()
   constexpr T TME()::Determinant(int n) const noexcept {
      float D = 0;

      // Base case : if matrix contains single element                  
      if (n == 1)
         return mColumns[0][0];

      TME() temp;
      T sign = 1;
      for (int f = 0; f < n; f++) {
         // Getting Cofactor of A[0][f]                                 
         temp = Cofactor(0, f, n);
         D += sign * mColumns[f][0] * temp.Determinant(n - 1);

         // terms are to be added with alternate sign                   
         sign = -sign;
      }

      return D;
   }

   /// Function to get adjoint of A[N][N]                                     
   ///   @return the adjoint matrix                                           
   TEMPLATE()
   constexpr TME() TME()::Adjoint() const noexcept {
      static_assert(IsSquare, "Can't adjoint non-square matrix");
      float sign = 1;
      TME() temp, adj;
      for (int i = 0; i < Rows; i++) {
         for (int j = 0; j < Rows; j++) {
            // Get cofactor of A[i][j]                                  
            temp = Cofactor(i, j, Rows);

            // sign of adj[j][i] positive if sum of row and column      
            // indexes is even.                                         
            sign = ((i + j) % 2 == 0) ? T(1) : T(-1);

            // Interchanging rows and columns to get the transpose      
            // of the cofactor matrix                                   
            adj.mColumns[i][j] = sign * temp.Determinant(Rows - 1);
         }
      }
      return adj;
   }

   /// Invert a square matrix                                                 
   ///   @return the inverted matrix                                          
   TEMPLATE()
   TME() TME()::Invert() const {
      static_assert(IsSquare, "Can't invert non-square matrix");

      if constexpr (Columns == 2) {
         const auto det = mArray[0] * mArray[3] - mArray[1] * mArray[2];
         if (det == 0)
            throw Except::Arithmetic("Degenerate 2x2 matrix");

         const auto detInv = 1 / det;
         return {
             mArray[3] * detInv,
            -mArray[1] * detInv,
            -mArray[2] * detInv,
             mArray[0] * detInv
         };
      }
      else if constexpr (Columns == 3) {
         auto n11 = mArray[0], n21 = mArray[1], n31 = mArray[2],
              n12 = mArray[3], n22 = mArray[4], n32 = mArray[5],
              n13 = mArray[6], n23 = mArray[7], n33 = mArray[8];

         auto t11 = n33 * n22 - n32 * n23,
              t12 = n32 * n13 - n33 * n12,
              t13 = n23 * n12 - n22 * n13;

         const auto det = n11 * t11 + n21 * t12 + n31 * t13;
         if (det == 0)
            throw Except::DivisionByZero("Degenerate 3x3 matrix");

         const auto detInv = 1 / det;

         return {
            t11 * detInv,
            (n31 * n23 - n33 * n21) * detInv,
            (n32 * n21 - n31 * n22) * detInv,
            
            t12 * detInv,
            (n33 * n11 - n31 * n13) * detInv,
            (n31 * n12 - n32 * n11) * detInv,
            
            t13 * detInv,
            (n21 * n13 - n23 * n11) * detInv,
            (n22 * n11 - n21 * n12) * detInv
         };
      }
      else if constexpr (Columns == 4) {
         auto n11 = mArray[0], n21 = mArray[1], n31 = mArray[2], n41 = mArray[3];
         auto n12 = mArray[4], n22 = mArray[5], n32 = mArray[6], n42 = mArray[7];
         auto n13 = mArray[8], n23 = mArray[9], n33 = mArray[10], n43 = mArray[11];
         auto n14 = mArray[12], n24 = mArray[13], n34 = mArray[14], n44 = mArray[15];

         auto t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
         auto t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
         auto t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
         auto t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

         const auto det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;
         if (det == 0)
            throw Except::DivisionByZero("Degenerate 4x4 matrix");

         const auto detInv = 1 / det;

         return {
            t11 * detInv,
            (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44)* detInv,
            (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44)* detInv,
            (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43)* detInv,
                                                                                                                               
            t12 * detInv,                                                                                                      
            (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44)* detInv,
            (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44)* detInv,
            (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43)* detInv,
                                                                                                                               
            t13 * detInv,                                                                                                     
            (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44)* detInv,
            (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44)* detInv,
            (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43)* detInv,
                                                                                                                               
            t14 * detInv,                                                                                                      
            (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34)* detInv,
            (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34)* detInv,
            (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33)* detInv,
         };
      }
      else LANGULUS_ERROR("Matrix inversion code not implemented");
   }

   
   ///                                                                        
   ///   Iteration                                                            
   ///                                                                        
   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::ColumnType* TME()::begin() noexcept {
      return mColumns;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::ColumnType* TME()::end() noexcept {
      return mColumns + COLUMNS;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr typename TME()::ColumnType* TME()::last() noexcept {
      return mColumns + COLUMNS - 1;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const typename TME()::ColumnType* TME()::begin() const noexcept {
      return mColumns;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const typename TME()::ColumnType* TME()::end() const noexcept {
      return mColumns + COLUMNS;
   }

   TEMPLATE() LANGULUS(INLINED)
   constexpr const typename TME()::ColumnType* TME()::last() const noexcept {
      return mColumns + COLUMNS - 1;
   }

} // namespace Langulus::Math


namespace Langulus::A
{

   /// Perspective constructor - left-handed perspective projection matrix    
   ///   @param fieldOfView - an angle representing the horizontal field of   
   ///                        view                                            
   ///   @param aspect - the aspect ratio (width/height)                      
   ///   @param near - the distance to the near clipping plane                
   ///   @param far - the distance to the far clipping plane                  
   ///   @return the projection matrix                                        
   template<CT::ScalarBased T>
   constexpr Math::TMatrix<T, 4> A::Matrix::PerspectiveFOV(
      const CT::Angle auto& fieldOfView,
      const T& aspect,
      const T& near, const T& far
   ) {
      auto result = Math::TMatrix<T, 4>::Null();
      const auto fd = T {1} / ::std::tan(T {fieldOfView.GetRadians()} *T {0.5});
      const auto id = -T {1} / (far - near);

      result.mArray[0] = fd;
      result.mArray[5] = fd * aspect;
      result.mArray[10] = far * id;
      result.mArray[11] = T {-1};
      result.mArray[14] = far * near * id;
      return result;
   }

   /// Perspective constructor - left-handed perspective projection matrix    
   /// described by a region on the near clipping plane                       
   template<CT::ScalarBased T>
   constexpr Math::TMatrix<T, 4> A::Matrix::PerspectiveRegion(
      const T& left, const T& right,
      const T& top,  const T& bottom,
      const T& near, const T& far
   ) {
      auto result = Math::TMatrix<T, 4>::Null();
      const auto x = T {2} * near / (right - left);
      const auto y = T {2} * near / (top - bottom);

      const auto a = (right + left) / (right - left);
      const auto b = (top + bottom) / (top - bottom);
      const auto c = -(far + near) / (far - near);
      const auto d = T {-2} * far * near / (far - near);

      result[0] = x;
      result[8] = a;
      result[5] = y;
      result[9] = b;
      result[10] = c;
      result[14] = d;
      result[11] = -1;
      return result;
   }

   /// Orthographic constructor - LH orthographic projection matrix           
   template<CT::ScalarBased T>
   constexpr Math::TMatrix<T, 4> A::Matrix::Orthographic(
      const T& width, const T& height,
      const T& near,  const T& far
   ) {
      const auto range = far - near;
      if (range == 0 or width == 0 or height == 0)
         throw Except::DivisionByZero();

      auto result = Math::TMatrix<T, 4>::Null();
      result.mArray[ 0] = T { 2} / width;
      result.mArray[ 5] = T { 2} / height;
      result.mArray[10] = T {-2} / range;
      result.mArray[12] = T {-1};
      result.mArray[13] = T {-1};
      result.mArray[14] = -(far + near) / range;
      result.mArray[15] = T { 1};
      return result;
   }

} // namespace Langulus::A

#undef TARGS
#undef TMAT
#undef TEMPLATE
#undef TME
