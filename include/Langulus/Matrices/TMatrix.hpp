///                                                                           
/// Langulus::Math                                                            
/// Copyright (c) 2014 Dimo Markov <team@langulus.com>                        
/// Part of the Langulus framework, see https://langulus.com                  
///                                                                           
/// SPDX-License-Identifier: GPL-3.0-or-later                                 
///                                                                           
#pragma once
#include "../Vectors/TVector.hpp"
#include "../Numbers/TAngle.hpp"
#include <Langulus/CT/Matrix.hpp>

#define TARGS(a)     CT::Scalar a##T, size_t a##C, size_t a##R
#define TMAT(a)      TMatrix<a##T, a##C, a##R>
#define TEMPLATE()   template<CT::Scalar T, size_t COLS, size_t ROWS>
#define TME()        TMatrix<T, COLS, ROWS>


namespace Langulus::Math
{
   template<CT::Scalar>
   struct TQuaternion;

   template<CT::Scalar, size_t COLS, size_t ROWS = COLS>
   struct TMatrix;

   using Mat2  = TMatrix<Real, 2>;
   using Mat3  = TMatrix<Real, 3>;
   using Mat4  = TMatrix<Real, 4>;

   using Mat2f = TMatrix<float, 2>;
   using Mat3f = TMatrix<float, 3>;
   using Mat4f = TMatrix<float, 4>;

   using Mat2d = TMatrix<double, 2>;
   using Mat3d = TMatrix<double, 3>;
   using Mat4d = TMatrix<double, 4>;

   using Mat2i = TMatrix<int, 2>;
   using Mat3i = TMatrix<int, 3>;
   using Mat4i = TMatrix<int, 4>;

   using Mat2u = TMatrix<unsigned, 2>;
   using Mat3u = TMatrix<unsigned, 3>;
   using Mat4u = TMatrix<unsigned, 4>;


   /// An abstract matrix that depends on context. Defaults to 4x4 reals      
   struct Matrix {
      using CTTI_Abstract = Yup;
      using CTTI_Concrete = Mat4;

      template<CT::CustomVector V> static constexpr auto
      From(const TQuaternion<TypeOf<V>>&, V const& = 0, V const& = 1) noexcept
         -> TMatrix<TypeOf<V>, V::MemberCount + 1>;

      template<CT::Angle A, CT::Scalar T> static constexpr auto
      PerspectiveFOV(A const&, T const& aspect, T const& near, T const& far)
         -> TMatrix<T, 4>;

      template<CT::Scalar T> static constexpr auto
      PerspectiveRegion(T const& left, T const& right, T const& top, T const& bottom, T const& near, T const& far)
         -> TMatrix<T, 4>;

      template<CT::Scalar T> static constexpr auto
      Orthographic(T const& width, T const& height, T const& near, T const& far)
         -> TMatrix<T, 4>;
   };

   /// An abstract matrix of specific column size, with rows and type that    
   /// depends on context. Defaults to a square real matrix.                  
   template<size_t C>
   struct MatrixOfColumns : Matrix {
      using CTTI_Concrete  = TMatrix<Real, C, C>;
      using CTTI_Bases     = Matrix;

      static constexpr size_t Cols = C;
      static_assert(C > 0, "Column count must be greater than zero");
   };

   /// An abstract matrix of specific row size, with type and column size that
   /// depends on context. Defaults to a square real matrix.                  
   template<size_t R>
   struct MatrixOfRows : Matrix {
      using CTTI_Concrete  = TMatrix<Real, R, R>;
      using CTTI_Bases     = Matrix;

      static constexpr size_t Rows = R;
      static_assert(R > 0, "Row count must be greater than zero");
   };

   /// An abstract matrix of specific size, with type that depends on context.
   /// Defaults to a real matrix.                                             
   template<size_t C, size_t R = C>
   struct MatrixOfSize : Matrix {
      using CTTI_Concrete  = Math::TMatrix<::Langulus::Real, C, R>;
      using CTTI_Bases     = Matrix;
      
      static constexpr size_t Cols = C;
      static constexpr size_t Rows = R;
      static_assert(C > 0, "Column count must be greater than zero");
      static_assert(R > 0, "Row count must be greater than zero");
   };

   /// An abstract matrix of specific type, with size that depends on context.
   /// Defaults to a 4x4 matrix.                                              
   template<CT::Scalar T>
   struct MatrixOfType : Matrix {
      using CTTI_Concrete  = TMatrix<T, 4, 4>;
      using CTTI_Typed     = T;
      using CTTI_Bases     = Matrix;
   };


   ///                                                                        
   /// MARK: TMatrix                                                          
   /// A templated matrix (column-major)                                      
   ///                                                                        
   #pragma pack(push, 1)
   TEMPLATE()
   struct TMatrix {
      static_assert(COLS > 0, "Column count must be greater than zero");
      static_assert(ROWS > 0, "Row count must be greater than zero");

      using ColType        = TVector<T, ROWS>;
      using RowType        = TVector<T, COLS>;
      using TransposeType  = TMatrix<T, ROWS, COLS>;

      static constexpr size_t Cols        = COLS;
      static constexpr size_t Rows        = ROWS;
      static constexpr size_t Diagonal    = Math::Min(Cols, Rows);
      static constexpr size_t MemberCount = Cols *  Rows;
      static constexpr bool   IsSquare    = Cols == Rows;

      union {
         ColType mColumns[Cols] {};
         T       mArray[MemberCount];
      };

   private:
      /// Custom name generator at compile-time for matrices                  
      static consteval auto GenerateToken() {
         constexpr auto defaultClassName = LastCppNameOf<TMatrix>();
         ::std::array<char, defaultClassName.size() + 1> name {};
         ::std::size_t offset {};

         if constexpr (COLS > 4 or ROWS > 4) {
            for (auto i : defaultClassName)
               name[offset++] = i;
            return name;
         }

         // Write prefix                                                
         constexpr Token prefix = "Matrix";
         for (auto i : prefix)
            name[offset++] = i;

         // Write columns and rows                                      
         if constexpr (COLS == ROWS) {
            name[offset++] = '0' + COLS;
         }
         else {
            name[offset++] = '0' + COLS;
            name[offset++] = 'x';
            name[offset++] = '0' + ROWS;
         }

         // Write suffix                                                
         for (auto i : SuffixOf<T>())
            name[offset++] = i;
         return name;
      }

   public:
      using CTTI_Typed     = T;
      using CTTI_Matrix    = Yup;
      using CTTI_Named     = Yes<GenerateToken()>;
      using CTTI_POD       = Maybe<CT::POD<T>>;
      using CTTI_Nullable  = No;
      using CTTI_Bases     = Types<
         MatrixOfSize<COLS, ROWS>, MatrixOfColumns<COLS>, MatrixOfRows<ROWS>,
         MatrixOfType<T>, 
         T
      >;

   public:
      ///                                                                     
      ///   Construction                                                      
      ///                                                                     
      constexpr TMatrix() noexcept;
      constexpr TMatrix(TMatrix const&) noexcept;
      constexpr TMatrix(TMatrix&&) noexcept;
      constexpr TMatrix(CT::Matrix auto const&) noexcept;
      constexpr TMatrix(CT::Vector auto const&) noexcept;
      constexpr TMatrix(CT::Scalar auto const&) noexcept;
      template<class T1>
      constexpr TMatrix(const T1*) noexcept;
      template<class T1, class T2, class...TN>
      constexpr TMatrix(const T1&, const T2&, const TN&...) noexcept;

      explicit TMatrix(Describe&&);

      static constexpr TMatrix LookAt(TVector<T, 3>, TVector<T, 3>)
      requires (ROWS >= 2 and COLS >= 2);

      static constexpr TMatrix Rotate(CT::Angle auto const&) noexcept
      requires (ROWS >= 2 and COLS >= 2);

      static constexpr TMatrix RotateAxis(const TVector<T, 3>&, CT::Angle auto const&) noexcept
      requires (ROWS >= 3 and COLS >= 3);

      static constexpr TMatrix Rotate(CT::Angle auto const& pitch, CT::Angle auto const& yaw) noexcept
      requires (ROWS >= 3 and COLS >= 3);

      static constexpr TMatrix Rotate(
         CT::Angle auto const& pitch,
         CT::Angle auto const& yaw,
         CT::Angle auto const& roll /*= Radians {0}*/ // causes clang-cl 16.0.5 to crash :( //TODO check if still relevant
      ) noexcept requires (ROWS >= 3 and COLS >= 3);

      static constexpr auto Translate(CT::Vector auto const&) noexcept -> TMatrix;
      static constexpr auto Scale(CT::Scalar auto const&) noexcept -> TMatrix;
      static constexpr auto Scale(CT::Vector auto const&) noexcept -> TMatrix;
      static constexpr auto Identity() noexcept -> TMatrix;
      static constexpr auto Null() noexcept -> TMatrix;

      ///                                                                     
      ///   Assignment                                                        
      ///                                                                     
      constexpr auto operator = (TMatrix const&) noexcept -> TMatrix&;
      constexpr auto operator = (TMatrix&&) noexcept -> TMatrix&;
      constexpr auto operator = (CT::Matrix auto const&) noexcept -> TMatrix&;
      constexpr auto operator = (CT::Vector auto const&) noexcept -> TMatrix&;
      constexpr auto operator = (CT::Scalar auto const&) noexcept -> TMatrix&;

      template<CT::Scalar N, CT::Dimension D>
      constexpr auto& operator = (const TVectorComponent<N, D>&) noexcept;

      ///                                                                     
      ///   Interpretation                                                    
      ///                                                                     
      static constexpr decltype(auto) Adapt(CT::Scalar auto const&) noexcept;

      ///                                                                     
      ///   Access                                                            
      ///                                                                     
      constexpr auto operator [] (size_t)       noexcept -> ColType&;
      constexpr auto operator [] (size_t) const noexcept -> ColType const&;
      constexpr auto GetRaw()       noexcept -> T*;
      constexpr auto GetRaw() const noexcept -> T const*;

      template<size_t>
      auto GetRow() const noexcept -> RowType;
      template<size_t>
      auto GetRow() noexcept;

   protected:
      template<size_t, size_t...C>
      auto GetRowInner(::std::integer_sequence<size_t, C...>&&) noexcept;

   public:
      template<size_t>
      auto GetColumn() const noexcept -> ColType const&;
      template<size_t>
      auto GetColumn()       noexcept -> ColType&;

      constexpr auto GetRight() const noexcept -> TVector<T, 3>;
      constexpr auto GetUp() const noexcept -> TVector<T, 3>;
      constexpr auto GetView() const noexcept -> TVector<T, 3>;
      constexpr auto GetScale() const noexcept -> TVector<T, 3>;

      constexpr auto GetPosition() const noexcept
      -> const TVector<T, ROWS - 1>& requires (ROWS > 2 and COLS > 2);

      constexpr auto SetPosition(const CT::Vector auto&) noexcept
      -> TMatrix& requires (ROWS > 2 and COLS > 2);

      constexpr bool IsIdentity() const noexcept;
      constexpr bool IsNull() const noexcept;

      constexpr auto Determinant() const noexcept -> T;
      constexpr auto Transpose() const noexcept -> TMatrix;
      constexpr auto Cofactor(int, int, int) const noexcept -> TMatrix;
      constexpr auto Determinant(int) const noexcept -> T;
      constexpr auto Adjoint() const noexcept -> TMatrix;
      auto Invert() const -> TMatrix;

      ///                                                                     
      ///   Iteration                                                         
      ///                                                                     
      constexpr auto begin()       noexcept -> ColType*;
      constexpr auto end()         noexcept -> ColType*;
      constexpr auto last()        noexcept -> ColType*;
      constexpr auto begin() const noexcept -> ColType const*;
      constexpr auto end()   const noexcept -> ColType const*;
      constexpr auto last()  const noexcept -> ColType const*;

   private:
      template<size_t SIZE, size_t NEXT_SIZE = SIZE - 1>
      constexpr static T InnerDeterminant(const T(&a)[SIZE * SIZE]) noexcept;
   };
   #pragma pack(pop)


   /// Generate a lossless matrix type from provided LHS and RHS matrices     
   ///   @tparam LHS left hand side, can be scalar/array/vector/matrix        
   ///   @tparam RHS right hand side, can be scalar/array/vector/matrix       
   template<class LHS, class RHS> requires CT::Matrix<Deref<LHS>, Deref<RHS>>
   using LosslessMatrix = TMatrix<
      Lossless<TypeOf<LHS>, TypeOf<RHS>>,
      Deref<LHS>::Cols < Deref<RHS>::Cols ? Deref<RHS>::Cols : Deref<LHS>::Cols,
      Deref<LHS>::Rows < Deref<RHS>::Rows ? Deref<RHS>::Rows : Deref<LHS>::Rows
   >;


   ///                                                                        
   ///   Operations                                                           
   ///                                                                        
   constexpr auto operator * (CT::Matrix auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator + (CT::Matrix auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator - (CT::Matrix auto const&, CT::Matrix auto const&) noexcept;

   constexpr auto operator * (CT::Vector auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator + (CT::Vector auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator - (CT::Vector auto const&, CT::Matrix auto const&) noexcept;

   constexpr auto operator * (CT::Matrix auto const&, CT::Vector auto const&) noexcept;
   constexpr auto operator + (CT::Matrix auto const&, CT::Vector auto const&) noexcept;
   constexpr auto operator - (CT::Matrix auto const&, CT::Vector auto const&) noexcept;

   constexpr auto operator * (CT::Scalar auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator + (CT::Scalar auto const&, CT::Matrix auto const&) noexcept;

   constexpr auto operator * (CT::Matrix auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator / (CT::Matrix auto const&, CT::Scalar auto const&);
   constexpr auto operator + (CT::Matrix auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator - (CT::Matrix auto const&, CT::Scalar auto const&) noexcept;


   ///                                                                        
   ///   Mutators                                                             
   ///                                                                        
   /// Add                                                                    
   constexpr auto& operator += (CT::Matrix auto&, CT::Matrix auto const&) noexcept;
   constexpr auto& operator += (CT::Matrix auto&, CT::Scalar auto const&) noexcept;
   constexpr auto& operator += (CT::Matrix auto&, CT::Vector auto const&) noexcept;

   /// Subtract                                                               
   constexpr auto& operator -= (CT::Matrix auto&, CT::Matrix auto const&) noexcept;
   constexpr auto& operator -= (CT::Matrix auto&, CT::Scalar auto const&) noexcept;
   constexpr auto& operator -= (CT::Matrix auto&, CT::Vector auto const&) noexcept;

   /// Multiply                                                               
   constexpr auto& operator *= (CT::Matrix auto&, CT::Matrix auto const&) noexcept;
   constexpr auto& operator *= (CT::Matrix auto&, CT::Scalar auto const&) noexcept;

   /// Divide                                                                 
   constexpr auto& operator /= (CT::Matrix auto&, CT::Scalar auto const&);


   ///                                                                        
   ///   Comparison                                                           
   ///                                                                        
   constexpr auto operator == (CT::Matrix auto const&, CT::Matrix auto const&) noexcept;
   constexpr auto operator == (CT::Matrix auto const&, CT::Scalar auto const&) noexcept;
   constexpr auto operator == (CT::Scalar auto const&, CT::Matrix auto const&) noexcept;
}

#include "TMatrix.inl"

#undef TARGS
#undef TMAT
#undef TEMPLATE
#undef TME