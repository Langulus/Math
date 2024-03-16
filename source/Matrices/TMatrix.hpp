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
#include "../Numbers/TAngle.hpp"


namespace Langulus
{
   namespace Math
   {

      template<CT::ScalarBased T>
      struct TQuaternion;

      template<CT::ScalarBased T, Count COLUMNS, Count ROWS = COLUMNS>
      struct TMatrix;

      using Mat2 = TMatrix<Real, 2>;
      using Mat3 = TMatrix<Real, 3>;
      using Mat4 = TMatrix<Real, 4>;

      using Mat2f = TMatrix<Float, 2>;
      using Mat3f = TMatrix<Float, 3>;
      using Mat4f = TMatrix<Float, 4>;

      using Mat2d = TMatrix<Double, 2>;
      using Mat3d = TMatrix<Double, 3>;
      using Mat4d = TMatrix<Double, 4>;

      using Mat2i = TMatrix<int, 2>;
      using Mat3i = TMatrix<int, 3>;
      using Mat4i = TMatrix<int, 4>;

      using Mat2u = TMatrix<unsigned, 2>;
      using Mat3u = TMatrix<unsigned, 3>;
      using Mat4u = TMatrix<unsigned, 4>;

      using Matrix = Mat4;
      using Mat = Matrix;

   } // namespace Langulus::Math

   #define TARGS(a) CT::ScalarBased a##T, Count a##C, Count a##R
   #define TMAT(a) TMatrix<a##T, a##C, a##R>
   #define TEMPLATE() template<CT::ScalarBased T, Count COLUMNS, Count ROWS>
   #define TME() TMatrix<T, COLUMNS, ROWS>

   namespace A
   {

      /// Used as an imposed base for any type that can be interpretable as a 
      /// matrix                                                              
      struct Matrix {
         LANGULUS(ABSTRACT) true;
         LANGULUS(CONCRETE) Math::Matrix;

         template<CT::VectorBased V>
         NOD() static constexpr Math::TMatrix<TypeOf<V>, V::MemberCount + 1>
         From(const Math::TQuaternion<TypeOf<V>>&, const V& = 0, const V& = 1) noexcept;

         template<CT::ScalarBased T>
         NOD() static constexpr Math::TMatrix<T, 4>
         PerspectiveFOV(const CT::Angle auto&, const T&, const T&, const T&);

         template<CT::ScalarBased T>
         NOD() static constexpr Math::TMatrix<T, 4>
         PerspectiveRegion(const T&, const T&, const T&, const T&, const T&, const T&);

         template<CT::ScalarBased T>
         NOD() static constexpr Math::TMatrix<T, 4>
         Orthographic(const T&, const T&, const T&, const T&);
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// matrix of the same column count                                     
      template<Count COLUMNS>
      struct MatrixOfColumns : Matrix {
         LANGULUS(CONCRETE) Math::TMatrix<::Langulus::Real, COLUMNS, COLUMNS>;
         LANGULUS_BASES(Matrix);
         static constexpr Count Columns {COLUMNS};
         static_assert(COLUMNS > 0, "Column count must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// matrix of the same rows count                                       
      template<Count ROWS>
      struct MatrixOfRows : Matrix {
         LANGULUS(CONCRETE) Math::TMatrix<::Langulus::Real, ROWS, ROWS>;
         LANGULUS_BASES(Matrix);
         static constexpr Count Rows {ROWS};
         static_assert(ROWS > 0, "Row count must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// matrix of the same column and row count                             
      template<Count COLUMNS, Count ROWS = COLUMNS>
      struct MatrixOfSize : Matrix {
         LANGULUS(CONCRETE) Math::TMatrix<::Langulus::Real, COLUMNS, ROWS>;
         LANGULUS_BASES(Matrix);
         static constexpr Count Columns {COLUMNS};
         static constexpr Count Rows {ROWS};
         static_assert(COLUMNS > 0, "Column count must be greater than zero");
         static_assert(ROWS > 0, "Row count must be greater than zero");
      };

      /// Used as an imposed base for any type that can be interpretable as a 
      /// matrix of the same type                                             
      template<CT::ScalarBased T>
      struct MatrixOfType : Matrix {
         LANGULUS(CONCRETE) Math::TMatrix<T, 4, 4>;
         LANGULUS(TYPED) T;
         LANGULUS_BASES(Matrix);
      };

   } // namespace Langulus::A


   /// Custom name generator at compile-time for matrices                     
   TEMPLATE()
   consteval auto CustomName(Of<Math::TME()>&&) noexcept {
      constexpr auto defaultClassName = RTTI::LastCppNameOf<Math::TME()>();
      ::std::array<char, defaultClassName.size() + 1> name {};
      ::std::size_t offset {};

      if constexpr (COLUMNS > 4 or ROWS > 4) {
         for (auto i : defaultClassName)
            name[offset++] = i;
         return name;
      }

      // Write prefix                                                   
      constexpr Token prefix = "Matrix";
      for (auto i : prefix)
         name[offset++] = i;

      // Write columns and rows                                         
      if constexpr (COLUMNS == ROWS) {
         name[offset++] = '0' + COLUMNS;
      }
      else {
         name[offset++] = '0' + COLUMNS;
         name[offset++] = 'x';
         name[offset++] = '0' + ROWS;
      }

      // Write suffix                                                   
      for (auto i : SuffixOf<T>())
         name[offset++] = i;
      return name;
   }


   namespace Math
   {

      ///                                                                     
      ///   A templated matrix (column-major)                                 
      ///                                                                     
      #pragma pack(push, 1)
      TEMPLATE()
      struct TMatrix {
         using ColumnType = TVector<T, ROWS>;
         using RowType = TVector<T, COLUMNS>;
         using TransposeType = TMatrix<T, ROWS, COLUMNS>;

         static constexpr Count Columns = COLUMNS;
         static constexpr Count Rows = ROWS;
         static constexpr Count Diagonal = Math::Min(Columns, Rows);
         static constexpr Count MemberCount = Columns * Rows;
         static constexpr bool IsSquare = Columns == Rows;

         // Make TMatrix match the CT::MatrixBased concept              
         static constexpr bool CTTI_MatrixTrait = true;

         union {
            ColumnType mColumns[Columns] {};
            T mArray[MemberCount];
         };

      public:
         LANGULUS(NAME) CustomNameOf<TMatrix>::Generate();
         LANGULUS(POD) CT::POD<T>;
         LANGULUS(NULLIFIABLE) false;
         LANGULUS(TYPED) T;
         LANGULUS_BASES(
            A::MatrixOfSize<COLUMNS, ROWS>, 
            A::MatrixOfColumns<COLUMNS>,
            A::MatrixOfRows<ROWS>,
            A::MatrixOfType<T>, 
            T
         );
         LANGULUS_CONVERTS_TO(Anyness::Text, Flow::Code);

      public:
         ///                                                                  
         ///   Construction                                                   
         ///                                                                  
         constexpr TMatrix() noexcept;
         constexpr TMatrix(const TMatrix&) noexcept;
         constexpr TMatrix(TMatrix&&) noexcept;
         constexpr TMatrix(const CT::MatrixBased auto&) noexcept;
         constexpr TMatrix(const CT::VectorBased auto&) noexcept;
         constexpr TMatrix(const CT::ScalarBased auto&) noexcept;
         template<class T1, class T2, class...TN>
         constexpr TMatrix(const T1&, const T2&, const TN&...) noexcept;

         TMatrix(Describe&&);

         NOD() static constexpr TMatrix LookAt(
            TVector<T, 3>,
            TVector<T, 3>
         ) requires (ROWS >= 2 and COLUMNS >= 2);

         NOD() static constexpr TMatrix Rotate(
            const CT::Angle auto&
         ) noexcept requires (ROWS >= 2 and COLUMNS >= 2);

         NOD() static constexpr TMatrix RotateAxis(
            const TVector<T, 3>&,
            const CT::Angle auto&
         ) noexcept requires (ROWS >= 3 and COLUMNS >= 3);

         NOD() static constexpr TMatrix Rotate(
            const CT::Angle auto& pitch,
            const CT::Angle auto& yaw
         ) noexcept requires (ROWS >= 3 and COLUMNS >= 3);

         NOD() static constexpr TMatrix Rotate(
            const CT::Angle auto& pitch,
            const CT::Angle auto& yaw,
            const CT::Angle auto& roll /*= Radians {0}*/ // causes clang-cl 16.0.5 to crash :(
         ) noexcept requires (ROWS >= 3 and COLUMNS >= 3);

         NOD() static constexpr TMatrix Translate(const CT::VectorBased auto&) noexcept;
         NOD() static constexpr TMatrix Scale(const CT::ScalarBased auto&) noexcept;
         NOD() static constexpr TMatrix Scale(const CT::VectorBased auto&) noexcept;
         NOD() static constexpr TMatrix Identity() noexcept;
         NOD() static constexpr TMatrix Null() noexcept;

         ///                                                                  
         ///   Assignment                                                     
         ///                                                                  
         constexpr TMatrix& operator = (const TMatrix&) noexcept;
         constexpr TMatrix& operator = (TMatrix&&) noexcept;
         constexpr TMatrix& operator = (const CT::MatrixBased auto&) noexcept;
         constexpr TMatrix& operator = (const CT::VectorBased auto&) noexcept;
         constexpr TMatrix& operator = (const CT::ScalarBased auto&) noexcept;

         template<CT::ScalarBased N, CT::Dimension D>
         constexpr auto& operator = (const TVectorComponent<N, D>&) noexcept;

         ///                                                                     
         ///   Interpretation                                                    
         ///                                                                     
         template<class TOKEN>
         Flow::Code Serialize() const;

         NOD() explicit operator Anyness::Text() const;
         NOD() explicit operator Flow::Code() const;

         NOD() static constexpr decltype(auto) Adapt(const CT::ScalarBased auto&) noexcept;

         ///                                                                  
         ///   Access                                                         
         ///                                                                  
         NOD() constexpr       ColumnType& operator [] (Offset) noexcept;
         NOD() constexpr const ColumnType& operator [] (Offset) const noexcept;
         NOD() constexpr       T* GetRaw() noexcept;
         NOD() constexpr const T* GetRaw() const noexcept;
         NOD() RowType GetRow(Offset) const noexcept;
         NOD() const ColumnType& GetColumn(Offset) const noexcept;

         NOD() constexpr TVector<T, 3> GetRight() const noexcept;
         NOD() constexpr TVector<T, 3> GetUp() const noexcept;
         NOD() constexpr TVector<T, 3> GetView() const noexcept;
         NOD() constexpr TVector<T, 3> GetScale() const noexcept;

         NOD() constexpr const TVector<T, ROWS-1>& GetPosition()
         const noexcept requires (ROWS > 2 and COLUMNS > 2);

         constexpr TMatrix& SetPosition(const CT::Vector auto&)
         noexcept requires (ROWS > 2 and COLUMNS > 2);

         NOD() constexpr bool IsIdentity() const noexcept;
         NOD() constexpr bool IsNull() const noexcept;

         NOD() constexpr T Determinant() const noexcept;
         NOD() constexpr TMatrix Transpose() const noexcept;
         NOD() constexpr TMatrix Cofactor(int, int, int) const noexcept;
         NOD() constexpr T Determinant(int) const noexcept;
         NOD() constexpr TMatrix Adjoint() const noexcept;
         NOD() TMatrix Invert() const;

         ///                                                                  
         ///   Iteration                                                      
         ///                                                                  
         NOD() constexpr ColumnType* begin() noexcept;
         NOD() constexpr ColumnType* end() noexcept;
         NOD() constexpr ColumnType* last() noexcept;
         NOD() constexpr const ColumnType* begin() const noexcept;
         NOD() constexpr const ColumnType* end() const noexcept;
         NOD() constexpr const ColumnType* last() const noexcept;

      private:
         template<Count SIZE, Count NEXT_SIZE = SIZE - 1>
         constexpr static T InnerDeterminant(const T(&a)[SIZE * SIZE]) noexcept;
      };
      #pragma pack(pop)


      ///                                                                     
      ///   Arithmetic                                                        
      ///                                                                     
      TEMPLATE() NOD()
      constexpr TME() operator * (const TME()&, const TME()&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator + (const TME()&, const TME()&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator - (const TME()&, const TME()&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator * (const TME()&, const T&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator * (const T&, TME()&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator / (const TME()&, const T&) noexcept;

      TEMPLATE() NOD()
      constexpr TME() operator / (const T&, const TME()&) noexcept;

      TEMPLATE()
      constexpr TME()& operator *= (TME()&, const TME()&) noexcept;

      TEMPLATE()
      constexpr TME()& operator += (TME()&, const TME()&) noexcept;

      TEMPLATE()
      constexpr TME()& operator -= (TME()&, const TME()&) noexcept;

      TEMPLATE()
      constexpr TME()& operator *= (TME()&, const T&) noexcept;

      TEMPLATE()
      constexpr TME()& operator /= (TME()&, const T&) noexcept;

      template<TARGS(LHS), CT::ScalarBased K, Count C>
      NOD() constexpr TVector<K, C> operator * (const TMAT(LHS)&, const TVector<K, C>&)
      noexcept requires (C <= LHSC and C > 1);

      template<TARGS(RHS), CT::ScalarBased K, Count C>
      NOD() constexpr TVector<K, C> operator * (const TVector<K, C>&, const TMAT(RHS)&)
      noexcept requires (C <= RHSR and C > 1);

      template<TARGS(RHS), CT::ScalarBased K, Count C>
      constexpr TVector<K, C>& operator *= (TVector<K, C>&, const TMAT(RHS)&)
      noexcept requires (C <= RHSC and C > 1);


      ///                                                                     
      ///   Comparison                                                        
      ///                                                                     
      TEMPLATE() NOD()
      constexpr bool operator == (const TME()&, const TME()&) noexcept;
      TEMPLATE() NOD()
      constexpr bool operator == (const TME()&, const T&) noexcept;

   } // namespace Langulus::Math

} // namespace Langulus

#undef TARGS
#undef TMAT
#undef TEMPLATE
#undef TME