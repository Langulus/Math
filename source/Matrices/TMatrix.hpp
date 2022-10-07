///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "../Vectors.hpp"

namespace Langulus::Math
{

	template<CT::DenseNumber T>
	class TQuaternion;

	template<CT::DenseNumber T, Count COLUMNS, Count ROWS = COLUMNS>
	class TMatrix;

	using Matrix2 = TMatrix<Real, 2>;
	using Matrix3 = TMatrix<Real, 3>;
	using Matrix4 = TMatrix<Real, 4>;

	using Matrix2f = TMatrix<RealSP, 2>;
	using Matrix3f = TMatrix<RealSP, 3>;
	using Matrix4f = TMatrix<RealSP, 4>;

	using Matrix2d = TMatrix<RealDP, 2>;
	using Matrix3d = TMatrix<RealDP, 3>;
	using Matrix4d = TMatrix<RealDP, 4>;

	using Matrix2i = TMatrix<int, 2>;
	using Matrix3i = TMatrix<int, 3>;
	using Matrix4i = TMatrix<int, 4>;

	using Matrix2u = TMatrix<unsigned, 2>;
	using Matrix3u = TMatrix<unsigned, 3>;
	using Matrix4u = TMatrix<unsigned, 4>;

	using Matrix = Matrix4;

	namespace A
	{

		/// Used as an imposed base for any type that can be interpretable as a	
		/// matrix																					
		struct Matrix {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Matrix;
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// matrix of the same column count													
		template<Count COLUMNS>
		struct MatrixOfColumns : public Matrix {
			LANGULUS(CONCRETE) TMatrix<Real, COLUMNS, COLUMNS>;
			LANGULUS_BASES(Matrix);
			static constexpr Count Columns {COLUMNS};
			static_assert(COLUMNS > 0, "Column count must be greater than zero");
		};
		
		/// Used as an imposed base for any type that can be interpretable as a	
		/// matrix of the same rows count													
		template<Count ROWS>
		struct MatrixOfRows : public Matrix {
			LANGULUS(CONCRETE) TMatrix<Real, ROWS, ROWS>;
			LANGULUS_BASES(Matrix);
			static constexpr Count Rows {ROWS};
			static_assert(ROWS > 0, "Row count must be greater than zero");
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// matrix of the same column and row count										
		template<Count COLUMNS, Count ROWS>
		struct MatrixOfSize : public Matrix {
			LANGULUS(CONCRETE) TMatrix<Real, COLUMNS, ROWS>;
			LANGULUS_BASES(Matrix);
			static constexpr Count Columns {COLUMNS};
			static constexpr Count Rows {ROWS};
			static_assert(COLUMNS > 0, "Column count must be greater than zero");
			static_assert(ROWS > 0, "Row count must be greater than zero");
		};

		/// Used as an imposed base for any type that can be interpretable as a	
		/// matrix of the same type															
		template<CT::DenseNumber T>
		struct MatrixOfType : public Matrix {
			LANGULUS(CONCRETE) TMatrix<T, 4, 4>;
			LANGULUS_BASES(Matrix);
			using MemberType = T;
		};

	} // namespace Langulus::Math::A


	///																								
	///	A templated matrix (column-major)												
	///																								
	template<CT::DenseNumber T, Count COLUMNS, Count ROWS>
	struct TMatrix {
		using MemberType = T;
		using ColumnType = TVector<T, ROWS>;
		using RowType = TVector<T, COLUMNS>;

		static constexpr Count Columns = COLUMNS;
		static constexpr Count Rows = ROWS;
		static constexpr Count MemberCount = Columns * Rows;
		static constexpr bool IsSquare = Columns == Rows;

		T mArray[MemberCount] = {};

	public:
		constexpr TMatrix() noexcept;

		template<CT::DenseNumber ALTT = T, Count ALTC = COLUMNS, Count ALTR = ROWS>
		constexpr TMatrix(const TMatrix<ALTT, ALTC, ALTR>&) noexcept;

		template<CT::DenseNumber K>
		constexpr TMatrix(K) noexcept;

		template<class HEAD, class... TAIL>
		constexpr TMatrix(const HEAD&, const TAIL&...) noexcept requires (sizeof...(TAIL) > 0);

		NOD() static constexpr TMatrix PerspectiveFOV(const T&, const T&, const T&, const T&);
		NOD() static constexpr TMatrix PerspectiveRegion(const T&, const T&, const T&, const T&, const T&, const T&);
		NOD() static constexpr TMatrix Orthographic(const T&, const T&, const T&, const T&);
		NOD() static constexpr TMatrix LookAt(TVector<T, 3>, TVector<T, 3>);
		NOD() static constexpr TMatrix Rotation(const T&) noexcept;
		NOD() static constexpr TMatrix RotationAxis(const TVector<T, 3>&, const T&) noexcept;
		NOD() static constexpr TMatrix Rotation(const T&, const T&, const T&) noexcept;
		NOD() static constexpr TMatrix Translation(const TVector<T, 4>&) noexcept;
		NOD() static constexpr TMatrix Scalar(const T&) noexcept;
		template<Count SIZE>
		NOD() static constexpr TMatrix Scalar(const TVector<T, SIZE>&) noexcept;
		NOD() static constexpr TMatrix Identity() noexcept;
		NOD() static constexpr TMatrix Null() noexcept;


		///																							
		///	Access																				
		///																							
		NOD() constexpr T& operator [] (Offset) noexcept;
		NOD() constexpr const T& operator [] (Offset) const noexcept;
		NOD() constexpr T* GetRaw() noexcept;
		NOD() constexpr const T* GetRaw() const noexcept;
		NOD() constexpr T& Get(Offset, Offset) noexcept;
		NOD() constexpr const T& Get(Offset, Offset) const noexcept;
		NOD() TVector<T, COLUMNS> Row(Offset) const noexcept;
		NOD() TVector<T, ROWS> Column(Offset) const noexcept;

		NOD() constexpr TVector<T, 3> GetRight() const noexcept;
		NOD() constexpr TVector<T, 3> GetUp() const noexcept;
		NOD() constexpr TVector<T, 3> GetView() const noexcept;
		NOD() constexpr TVector<T, 3> GetScale() const noexcept;

		NOD() constexpr TVector<T, 3> GetPosition() const noexcept;
		constexpr TMatrix& SetPosition(const TVector<T, 3>&) noexcept;

		NOD() constexpr bool IsIdentity() const noexcept;
		NOD() constexpr bool IsNull() const noexcept;


		///																							
		///	Conversion																			
		///																							
		NOD() explicit operator Flow::Code() const;

	public:
		NOD() constexpr T Determinant() const noexcept;
		NOD() constexpr TMatrix Transpose() const noexcept;
		NOD() constexpr TMatrix Cofactor(int, int, int) const noexcept;
		NOD() constexpr T Determinant(int) const noexcept;
		NOD() constexpr TMatrix Adjoint() const noexcept;
		NOD() TMatrix Invert() const;

	private:
		template<Count SIZE, Count NEXT_SIZE = SIZE - 1>
		constexpr static T InnerDeterminant(const T(&a)[SIZE * SIZE]) noexcept;
	};


	///																								
	///	Arithmetic																				
	///																								
	#define TEMPLATE() template<CT::DenseNumber T, Count COLS, Count ROWS>
	#define TME() TMatrix<T, COLS, ROWS>

	TEMPLATE()
	NOD() constexpr TME() operator * (const TME()&, const TME()&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator + (const TME()&, const TME()&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator - (const TME()&, const TME()&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator * (const TME()&, const T&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator * (const T&, TME()&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator / (const TME()&, const T&) noexcept;

	TEMPLATE()
	NOD() constexpr TME() operator / (const T&, const TME()&) noexcept;

	TEMPLATE()
	constexpr void operator *= (TME()&, const TME()&) noexcept;

	TEMPLATE()
	constexpr void operator += (TME()&, const TME()&) noexcept;

	TEMPLATE()
	constexpr void operator -= (TME()&, const TME()&) noexcept;

	TEMPLATE()
	constexpr void operator *= (TME()&, const T&) noexcept;

	TEMPLATE()
	constexpr void operator /= (TME()&, const T&) noexcept;

	template<CT::DenseNumber T, Count COLS, Count ROWS, CT::DenseNumber K, Count C>
	NOD() constexpr auto operator * (const TME()&, const TVector<K, C>&) noexcept requires (C <= ROWS);

	template<CT::DenseNumber T, Count COLS, Count ROWS, CT::DenseNumber K, Count C>
	NOD() constexpr auto operator * (const TVector<K, C>&, const TME()&) noexcept requires (C <= COLS);

	template<CT::DenseNumber T, Count COLS, Count ROWS, CT::DenseNumber K, Count C>
	constexpr void operator *= (TVector<K, C>&, const TME()&) noexcept requires (C <= COLS);

	template<CT::DenseNumber T, Count COLS, Count ROWS, CT::DenseNumber K, Count C>
	constexpr void operator *= (const TVector<K, C>&, const TME()&) noexcept requires (C <= COLS);


	///																								
	///	Comparison																				
	///																								
	TEMPLATE() NOD() constexpr bool operator == (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr bool operator == (const TME()&, const T&) noexcept;
	TEMPLATE() NOD() constexpr bool operator != (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr bool operator != (const TME()&, const T&) noexcept;

} // namespace Langulus::Math

#include "TMatrix.inl"

#undef TEMPLATE
#undef TME
