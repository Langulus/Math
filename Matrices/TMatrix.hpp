#pragma once
#include "../Vectors.hpp"

namespace PCFW::Math
{

	template<RealNumber T>
	class TQuaternion;

	template<RealNumber T>
	using TQuat = TQuaternion<T>;

	template<DenseNumber T, pcptr COLS, pcptr ROWS = COLS>
	class TMatrix;

	template<DenseNumber T, pcptr COLS, pcptr ROWS = COLS>
	using TMat = TMatrix<T, COLS, ROWS>;

	using mat2 = TMat<real, 2>;
	using mat3 = TMat<real, 3>;
	using mat4 = TMat<real, 4>;

	using mat2f = TMat<pcr32, 2>;
	using mat3f = TMat<pcr32, 3>;
	using mat4f = TMat<pcr32, 4>;

	using mat2d = TMat<pcr64, 2>;
	using mat3d = TMat<pcr64, 3>;
	using mat4d = TMat<pcr64, 4>;

	using mat2i = TMat<int, 2>;
	using mat3i = TMat<int, 3>;
	using mat4i = TMat<int, 4>;

	using mat2u = TMat<unsigned, 2>;
	using mat3u = TMat<unsigned, 3>;
	using mat4u = TMat<unsigned, 4>;


	///																								
	///	Abstract matrix																		
	///																								
	PC_DECLARE_ABSTRACT_DATA(Matrix);


	///																								
	///	An abstract sized matrix															
	///																								
	template<pcptr COLS, pcptr ROWS = COLS>
	class TSizedMatrix : POD {
		static_assert(COLS != 0, "Columns must be more than 0");
		static_assert(ROWS != 0, "Rows must be more than 0");
	public:
		static constexpr pcptr RowCount = ROWS;
		static constexpr pcptr ColumnCount = COLS;
		static constexpr pcptr MemberCount = ColumnCount * RowCount;
		static constexpr bool IsSquare = (RowCount == ColumnCount);
		using Concrete = TMatrix<real, COLS, ROWS>;

		REFLECT_MANUALLY(TSizedMatrix) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "Mat";
				if constexpr (IsSquare) {
					name += RowCount;
				}
				else {
					name += ColumnCount;
					name += "x";
					name += RowCount;
				}
				name = name.StandardToken();
				info += "an abstract matrix with ";
				info += ColumnCount;
				info += " columns and ";
				info += RowCount;
				info += " rows";
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mConcrete = DataID::Of<Concrete>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(AMatrix));
			reflection.MakeAbstract();
			return reflection;
		}
	};


	///																								
	///	A templated matrix (column-major)												
	///																								
	template<DenseNumber T, pcptr COLS, pcptr ROWS>
	class TMatrix : public TSizedMatrix<COLS, ROWS> {
		using BASE = TSizedMatrix<COLS, ROWS>;
	public:
		static_assert(Dense<T>, "TMatrix elements must always be dense");

		using MemberType = T;
		using ColumnType = TVec<T, ROWS>;
		using RowType = TVec<T, COLS>;

		static constexpr pcptr ColumnCount = COLS;
		static constexpr pcptr RowCount = ROWS;
		static constexpr pcptr MemberCount = ColumnCount * RowCount;
		static constexpr bool IsSquare = (ColumnCount == RowCount);

		REFLECT_MANUALLY(TMatrix) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(sizeof(T) * MemberCount == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += DataID::Reflect<BASE>()->GetToken();
				name.TypeSuffix<T>();
				name = name.StandardToken();
				info += "a matrix of type ";
				info += DataID::Reflect<T>()->GetToken();
				info += " with ";
				info += ColumnCount;
				info += " columns and ";
				info += RowCount;
				info += " rows";
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(BASE));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER(mArray));
			return reflection;
		}

	public:
		///																							
		///	Construction																		
		///																							
		constexpr TMatrix() noexcept;

		template<DenseNumber ALTT = T, pcptr ALTC = COLS, pcptr ALTR = ROWS>
		constexpr TMatrix(const TMatrix<ALTT, ALTC, ALTR>&) noexcept;

		template<Number K>
		constexpr TMatrix(K) noexcept;

		template<class HEAD, class... TAIL>
		constexpr TMatrix(const HEAD&, const TAIL&...) noexcept requires (sizeof...(TAIL) > 0);

		NOD() static constexpr ME PerspectiveFOV(const T&, const T&, const T&, const T&);
		NOD() static constexpr ME PerspectiveRegion(const T&, const T&, const T&, const T&, const T&, const T&);
		NOD() static constexpr ME Orthographic(const T&, const T&, const T&, const T&);
		NOD() static constexpr ME LookAt(TVec<T, 3>, TVec<T, 3>);
		NOD() static constexpr ME Rotation(const T&) noexcept;
		NOD() static constexpr ME RotationAxis(const TVec<T, 3>&, const T&) noexcept;
		NOD() static constexpr ME Rotation(const T&, const T&, const T&) noexcept;
		NOD() static constexpr ME Translation(const TVec<T, 4>&) noexcept;
		NOD() static constexpr ME Scalar(const T&) noexcept;
		template<pcptr SIZE>
		NOD() static constexpr ME Scalar(const TVec<T, SIZE>&) noexcept;
		NOD() static constexpr ME Identity() noexcept;
		NOD() static constexpr ME Null() noexcept;

		///																							
		///	Access																				
		///																							
		NOD() constexpr T& operator [] (pcptr) noexcept;
		NOD() constexpr const T& operator [] (pcptr) const noexcept;
		NOD() constexpr T* GetRaw() noexcept;
		NOD() constexpr const T* GetRaw() const noexcept;
		NOD() constexpr T& Get(pcptr, pcptr) noexcept;
		NOD() constexpr const T& Get(pcptr, pcptr) const noexcept;
		NOD() TVec<T, COLS> Row(pcptr) const noexcept;
		NOD() TVec<T, ROWS> Column(pcptr) const noexcept;

		/// Integrate with range-based for loops											
		PC_RANGED_FOR_INTEGRATION(T, GetRaw(), MemberCount);

		NOD() constexpr TVec<T, 3> GetRight() const noexcept;
		NOD() constexpr TVec<T, 3> GetUp() const noexcept;
		NOD() constexpr TVec<T, 3> GetView() const noexcept;
		NOD() constexpr TVec<T, 3> GetScale() const noexcept;

		NOD() constexpr TVec<T, 3> GetPosition() const noexcept;
		constexpr ME& SetPosition(const TVec<T, 3>&) noexcept;

		NOD() constexpr bool IsIdentity() const noexcept;
		NOD() constexpr bool IsNull() const noexcept;


		///																							
		///	CONVERSION																			
		///																							
		NOD() explicit operator GASM() const;

	public:
		NOD() constexpr T Determinant() const noexcept;
		NOD() constexpr ME Transpose() const noexcept;
		NOD() constexpr ME Cofactor(int, int, int) const noexcept;
		NOD() constexpr T Determinant(int) const noexcept;
		NOD() constexpr ME Adjoint() const noexcept;
		NOD() ME Invert() const;

	private:
		template<pcptr SIZE, pcptr NEXT_SIZE = SIZE - 1>
		constexpr static T InnerDeterminant(const T(&a)[SIZE * SIZE]) noexcept;

	public:
		// 1D representation																
		T mArray[MemberCount] = {};
	};

	PC_DEFINE_ABSTRACT_DATA(Matrix, "An abstract matrix", void);


	///																								
	///	ARITHMETICS																				
	///																								
	#define TEMPLATE() template<DenseNumber T, pcptr COLS, pcptr ROWS>
	#define TME() TMatrix<T, COLS, ROWS>

	TEMPLATE()	NOD() constexpr TME() operator * (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator + (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator - (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator * (const TME()&, const T&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator * (const T&, TME()&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator / (const TME()&, const T&) noexcept;
	TEMPLATE() NOD() constexpr TME() operator / (const T&, const TME()&) noexcept;

	TEMPLATE() constexpr void operator *= (TME()&, const TME()&) noexcept;
	TEMPLATE() constexpr void operator += (TME()&, const TME()&) noexcept;
	TEMPLATE() constexpr void operator -= (TME()&, const TME()&) noexcept;
	TEMPLATE() constexpr void operator *= (TME()&, const T&) noexcept;
	TEMPLATE() constexpr void operator /= (TME()&, const T&) noexcept;

	template<DenseNumber T, pcptr COLS, pcptr ROWS, Number K, pcptr C>
	NOD() constexpr auto operator * (const TME()&, const TVec<K, C>&) noexcept requires (C <= ROWS);

	template<DenseNumber T, pcptr COLS, pcptr ROWS, Number K, pcptr C>
	NOD() constexpr auto operator * (const TVec<K, C>&, const TME()&) noexcept requires (C <= COLS);

	template<DenseNumber T, pcptr COLS, pcptr ROWS, Number K, pcptr C>
	constexpr void operator *= (TVec<K, C>&, const TME()&) noexcept requires (C <= COLS);

	template<DenseNumber T, pcptr COLS, pcptr ROWS, Number K, pcptr C>
	constexpr void operator *= (const TVec<K, C>&, const TME()&) noexcept requires (C <= COLS);


	///																								
	///	COMPARISON																				
	///																								
	TEMPLATE() NOD() constexpr bool operator == (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr bool operator == (const TME()&, const T&) noexcept;
	TEMPLATE() NOD() constexpr bool operator != (const TME()&, const TME()&) noexcept;
	TEMPLATE() NOD() constexpr bool operator != (const TME()&, const T&) noexcept;


	/// Matrix typelists																			
	template<pcptr SIZE>
	struct TMatrixTypeGenerator {
		template<DenseNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TMatrix<T, SIZE, SIZE>...>;
	};

	using TMatrix2Types = TTYPELIST_FROM(TMatrixTypeGenerator<2>, NumberTypes);
	using TMatrix3Types = TTYPELIST_FROM(TMatrixTypeGenerator<3>, NumberTypes);
	using TMatrix4Types = TTYPELIST_FROM(TMatrixTypeGenerator<4>, NumberTypes);
	using TMatrixTypes = TTYPELIST_CAT3(TMatrix2Types, TMatrix3Types, TMatrix4Types);

} // namespace PCFW::Math

#include "TMatrix.inl"

#undef TEMPLATE
#undef TME
