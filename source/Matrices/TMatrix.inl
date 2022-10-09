///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TMatrix.hpp"

namespace Langulus::Math
{

	///																								
	///	CONSTRUCTION																			
	///																								
	/// Default constructor (identity)														
	TEMPLATE()
	constexpr TME()::TMatrix() noexcept {
		*this = Identity();
	}

	/// Construct from similar matrix														
	///	@param a - differently sized matrix												
	TEMPLATE()
	template<TARGS(ALT)>
	constexpr TME()::TMatrix(const TMAT(ALT)& a) noexcept {
		if constexpr (ALTC != COLUMNS || ALTR != ROWS) {
			if constexpr (ALTC < COLUMNS || ALTR < ROWS) {
				// If copied region is smaller, make sure to reset				
				*this = Identity();
			}

			for (Offset col = 0; col < Math::Min(COLUMNS, ALTC); ++col) {
				for (Offset row = 0; row < Math::Min(ROWS, ALTR); ++row) {
					if constexpr (CT::Same<ALTT, T>) {
						// Direct copy														
						Get(col, row) = a.Get(col, row);
					}
					else {
						// Conversion														
						Get(col, row) = static_cast<T>(a.Get(col, row));
					}
				}
			}
		}
		else if constexpr (!CT::Same<ALTT, T>) {
			for (int i = 0; i < MemberCount; ++i) {
				// Convert all elements													
				mArray[i] = static_cast<T>(a.mArray[i]);
			}
		}
		else {
			// Direct memory copy (fastest)											
			memcpy(mArray, a.mArray, sizeof(T) * MemberCount);
		}
	}

	/// Manual initialization with variadic head-tail									
	TEMPLATE()
	template<class HEAD, class... TAIL>
	constexpr TME()::TMatrix(const HEAD& head, const TAIL&... tail) noexcept requires (sizeof...(TAIL) > 0) {
		if constexpr (CT::Vector<HEAD>) {
			if constexpr (HEAD::MemberCount < MemberCount) {
				for (Offset i = 0; i < HEAD::MemberCount; ++i)
					(*this)[i] = static_cast<T>(head[i]);
				const TVector<T, MemberCount - HEAD::MemberCount> theRest {tail...};
				for (Offset i = HEAD::MemberCount; i < MemberCount; ++i)
					(*this)[i] = theRest[i - HEAD::MemberCount];
			}
			else LANGULUS_ERROR("More elements provided than required");
		}
		else if constexpr (IsCompatible<HEAD>) {
			(*this)[0] = static_cast<T>(head);
			const TVector<T, MemberCount - 1> theRest {tail...};
			for (Offset i = 1; i < MemberCount; ++i)
				(*this)[i] = theRest[i - 1];
		}
		else LANGULUS_ERROR(
			"Bad element type in matrix unfolding constructor"
			" - must be numbers and/or vectors");
	}

	/// Scalar constructor - sets all diagonal components								
	///	@param x - scalar value to spread across the matrix diagonals			
	TEMPLATE()
	template<CT::DenseNumber N>
	constexpr TME()::TMatrix(const N& x) noexcept requires IsCompatible<N> {
		const auto e = Adapt(x);
		for (Offset c = 0; c < Columns; ++c)
			for (Offset r = 0; r < Rows; ++r)
				Get(c, r) = (c == r) ? e : T {0};
	}

	/// Construct from an unbounded array													
	///	@attention very unsafe																
	///	@param a - pointer to first element in an unbounded array				
	TEMPLATE()
	template<CT::DenseNumber N>
	constexpr TME()::TMatrix(const N* a) noexcept requires IsCompatible<N> {
		for (auto& v : mArray)
			v = Adapt(*(a++));
	}

	/// Construct from bounded array															
	///	@param a - bounded array															
	TEMPLATE()
	template<CT::Array N>
	constexpr TME()::TMatrix(const N& a) noexcept requires IsCompatible<Decay<N>> {
		static_assert(ExtentOf<N> >= MemberCount,
			"This matrix is too powerful for your array");

		const Decay<N>* source = a;
		for (auto& v : mArray)
			v = Adapt(*(source++));
	}

	/// Adapt a component to the matrix's internal type								
	TEMPLATE()
	template<CT::DenseNumber N>
	constexpr decltype(auto) TME()::Adapt(const N& item) const noexcept requires IsCompatible<N> {
		if constexpr (!CT::Same<N, T>)
			return static_cast<T>(item);
		else
			return item;
	}

	///																								
	///	ARITHMETICS																				
	///																								
	/// Multiply two matrices - not commutative											
	TEMPLATE()
	constexpr TME() operator * (const TME()& me, const TME()& other) noexcept {
		auto result = TME()::Null();
		for (Offset i = 0; i < me.Columns; ++i) {
			for (Offset j = 0; j < me.Rows; ++j) {
				auto& rij = result.Get(i, j);
				for (Offset f = 0; f < me.Columns; ++f)
					rij += me.Get(f, j) * other.Get(i, f);
			}
		}
		return result;
	}

	/// Add two matrices																			
	TEMPLATE()
	constexpr TME() operator + (const TME()& me, const TME()& other) noexcept {
		TME() result(me);
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			result[idx] += other.mArray[idx];
		return result;
	}

	/// Subtract two matrices																	
	TEMPLATE()
	constexpr TME() operator - (const TME()& me, const TME()& other) noexcept {
		TME() result(me);
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			result[idx] -= other.mArray[idx];
		return result;
	}

	/// Multiply matrix by a scalar															
	TEMPLATE()
	constexpr TME() operator * (const TME()& me, const T& s) noexcept {
		TME() result(me);
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			result[idx] *= s;
		return result;
	}

	/// Multiply scalar by a matrix															
	TEMPLATE()
	constexpr TME() operator * (const T& s, const TME()& me) noexcept {
		return me * s;
	}

	/// Divide the matrix by a scalar - not commutative								
	TEMPLATE()
	constexpr TME() operator / (const TME()& me, const T& s) noexcept {
		const auto inv_s = T(1) / s;
		TME() result(me);
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			result[idx] *= inv_s;
		return result;
	}

	/// Divide the scalar by a matrix - not commutative								
	TEMPLATE()
	constexpr TME() operator / (const T& s, const TME()& me) noexcept {
		TME() result(me);
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			result[idx] = s / result[idx];
		return result;
	}

	/// Destructive multiplication of two matrices (not commutative)				
	TEMPLATE()
	constexpr void operator *= (TME()& me, const TME()& other) noexcept {
		me = me * other;
	}

	/// Destructive addition of two matrices. Not commutative						
	TEMPLATE()
	constexpr void operator += (TME()& me, const TME()& other) noexcept {
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			me.mArray[idx] += other.mArray[idx];
	}

	/// Destructive subtraction of two matrices. Not commutative					
	TEMPLATE()
		constexpr void operator -= (TME()& me, const TME()& other) noexcept {
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			me.mArray[idx] -= other.mArray[idx];
	}

	/// Destructive multiplication by a scalar. Not commutative						
	TEMPLATE()
		constexpr void operator *= (TME()& me, const T& s) noexcept {
		for (auto& it : me.mArray)
			it *= s;
	}

	/// Destructive division by a scalar. Not commutative								
	TEMPLATE()
		constexpr void operator /= (TME()& me, const T& s) noexcept {
		const auto inv_s = T(1) / s;
		for (auto& it : me.mArray)
			it *= inv_s;
	}

	/// Multiply by a column vector															
	///	@returns a row vector result														
	template<TARGS(LHS), CT::DenseNumber T, Count C>
	constexpr auto operator * (const TMAT(LHS)& me, const TVector<T, C>& vec) noexcept requires (C <= LHSR && C > 1) {
		using LT = Lossless<T, LHST>;
		LT r[C] = {};
		for (Offset vr = 0; vr < C; ++vr) {
			for (Offset mc = 0; mc < Math::Min(C, LHSC); ++mc)
				r[vr] += me.Get(vr, mc) * vec[mc];
		}
		return TVector<LT, C> {r};
	}

	/// Multiply by a row vector																
	///	@returns a column vector result													
	template<TARGS(RHS), CT::DenseNumber T, Count C>
	constexpr auto operator * (const TVector<T, C>& vec, const TMAT(RHS)& me) noexcept requires (C <= RHSC && C > 1) {
		using LT = Lossless<T, RHST>;
		LT r[C] = {};
		for (Offset vr = 0; vr < C; ++vr) {
			for (Offset mc = 0; mc < Math::Min(C, RHSR); ++mc)
				r[vr] += me.Get(mc, vr) * vec[mc];
		}
		return TVector<LT, C> {r};
	}

	/// Destructive multiplication of a row vector										
	template<TARGS(RHS), CT::DenseNumber T, Count C>
	constexpr void operator *= (TVector<T, C>& vec, const TMAT(RHS)& me) noexcept requires (C <= RHSC && C > 1) {
		T r[C] = {};
		for (Offset vr = 0; vr < C; ++vr) {
			for (Offset mc = 0; mc < Math::Min(C, RHSR); ++mc)
				r[vr] += me.Get(mc, vr) * vec[mc];
		}
		return TVector<T, C> {r};
	}


	///																								
	///	COMPARISON																				
	///																								
	/// Compare with another matrix															
	TEMPLATE()
	constexpr bool operator == (const TME()& me, const TME()& other) noexcept {
		for (Offset idx = 0; idx < me.MemberCount; ++idx)
			if (me[idx] != other[idx])
				return false;
		return true;
	}

	/// Compare with scalar																		
	TEMPLATE()
	constexpr bool operator == (const TME()& me, const T& a) noexcept {
		for (auto& it : me.mArray)
			if (!it != a)
				return false;
		return true;
	}


	///																								
	///	ENCAPSULATION																			
	///																								
	/// Access 1D index																			
	///	@param i - index [0; MemberCount)												
	///	@return a reference to the element												
	TEMPLATE()
	constexpr T& TME()::operator [] (const Offset i) noexcept {
		return mArray[i];
	}

	/// Access 1D index (const)																
	///	@param i - index [0; COLS*ROWS)													
	///	@return a reference to the element												
	TEMPLATE()
	constexpr const T& TME()::operator [] (const Offset i) const noexcept {
		return mArray[i];
	}

	/// Access raw data																			
	///	@return pointer to the first element											
	TEMPLATE()
	constexpr T* TME()::GetRaw() noexcept {
		return mArray;
	}

	/// Access raw data (const)																
	///	@return pointer to the first element											
	TEMPLATE()
	constexpr const T* TME()::GetRaw() const noexcept {
		return mArray;
	}

	/// Get a 2D cell from the matrix														
	///	@param col - column index [0; COLS)												
	///	@param row - row index [0; ROWS)													
	///	@return a reference to the element												
	TEMPLATE()
	constexpr T& TME()::Get(const Offset col, const Offset row) noexcept {
		return mArray[col + row * Columns];
	}

	/// Get a 2D cell from the matrix (const)												
	///	@param col - column index [0; COLS)												
	///	@param row - row index [0; ROWS)													
	///	@return a constant reference to the element									
	TEMPLATE()
	constexpr const T& TME()::Get(const Offset col, const Offset row) const noexcept {
		return mArray[col + row * Columns];
	}

	/// Get right axis																			
	TEMPLATE()
	constexpr TVector<T, 3> TME()::GetRight() const noexcept {
		if constexpr (IsSquare && Rows > 2)
			return {Get(0, 0), Get(1, 0), Get(2, 0)};
		else LANGULUS_ERROR("Can't get right axis of this matrix");
	}

	/// Get up axis																				
	TEMPLATE()
	constexpr TVector<T, 3> TME()::GetUp() const noexcept {
		if constexpr (IsSquare && Rows > 2)
			return {Get(0, 1), Get(1, 1), Get(2, 1)};
		else LANGULUS_ERROR("Can't get up axis of this matrix");
	}

	/// Get view axis																				
	TEMPLATE()
	constexpr TVector<T, 3> TME()::GetView() const noexcept {
		if constexpr (IsSquare && Rows > 2)
			return {Get(0, 2), Get(1, 2), Get(2, 2)};
		else LANGULUS_ERROR("Can't get view axis of this matrix");
	}

	/// Get translation 																			
	TEMPLATE()
	constexpr TVector<T, 3> TME()::GetScale() const noexcept {
		if constexpr (IsSquare && Rows > 2)
			return {GetRight().Length(), GetUp().Length(), GetView().Length()};
		else LANGULUS_ERROR("Can't get translation of this matrix");
	}

	/// Get translation 																			
	TEMPLATE()
	constexpr TVector<T, 3> TME()::GetPosition() const noexcept {
		if constexpr (IsSquare && Rows > 3)
			return {Get(0, 3), Get(1, 3), Get(2, 3)};
		else LANGULUS_ERROR("Can't get translation of this matrix");
	}

	/// Set translation 																			
	TEMPLATE()
	constexpr TME()& TME()::SetPosition(const TVector<T, 3>& position) noexcept {
		if constexpr (IsSquare && Rows > 3) {
			Get(0, 3) = position[0];
			Get(1, 3) = position[1];
			Get(2, 3) = position[2];
		}
		else LANGULUS_ERROR("Can't set translation to this matrix");
		return *this;
	}

	/// Get a whole row																			
	///	@param idx - row index																
	///	@return a row																			
	TEMPLATE()
	TVector<T, COLUMNS> TME()::Row(Offset idx) const noexcept {
		return mArray + idx * Columns;
	}

	/// Get a whole column																		
	///	@param idx - column index															
	///	@return a column																		
	TEMPLATE()
	TVector<T, ROWS> TME()::Column(Offset idx) const noexcept {
		T ar[Rows];
		for (Offset i = 0; i < Rows; ++i)
			ar[i] = mArray[idx + i * Columns];
		return ar;
	}

	/// Convert to text																			
	TEMPLATE()
	TME()::operator Flow::Code() const {
		Flow::Code result;
		result += MetaOf<TMatrix>();
		result += Flow::Code::OpenScope;
		for (Offset i = 0; i < MemberCount; ++i) {
			result += (*this)[i];
			if (i < MemberCount - 1)
				result += ", ";
		}
		result += Flow::Code::CloseScope;
		return result;
	}

	///																								
	///	CREATION																					
	///																								
	/// Perspective constructor - LH perspective projection matrix					
	TEMPLATE()
	constexpr TME() TME()::PerspectiveFOV(const T& fieldOfView, const T& aspect, const T& near, const T& far) {
		static_assert(IsSquare && Rows == 4,
			"Can't make a perspective matrix from this one");

		TME() result = Null();
		const auto fd = T(1) / std::tan(fieldOfView / T(2));
		const auto id = -T(1) / (far - near);
		result.mArray[0] = fd;
		result.mArray[5] = fd * aspect;
		result.mArray[10] = far * id;
		result.mArray[11] = T(-1);
		result.mArray[14] = far * near * id;
		return result;
	}

	/// Perspective constructor - LH perspective projection matrix					
	TEMPLATE()
	constexpr TME() TME()::PerspectiveRegion(const T& left, const T& right, const T& top, const T& bottom, const T& near, const T& far) {
		static_assert(IsSquare && Rows == 4,
			"Can't make a perspective matrix from this one");

		TME() result = Null();
		const auto x = T(2) * near / (right - left);
		const auto y = T(2) * near / (top - bottom);

		const auto a = (right + left) / (right - left);
		const auto b = (top + bottom) / (top - bottom);
		const auto c = -(far + near) / (far - near);
		const auto d = T(-2) * far * near / (far - near);

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
	TEMPLATE()
	constexpr TME() TME()::Orthographic(const T& width, const T& height, const T& near, const T& far) {
		static_assert(IsSquare && Rows == 4,
			"Can't make an orthogonal matrix from this one");
		const auto range = far - near;
		if (range == 0 || width == 0 || height == 0)
			throw Except::DivisionByZero();

		TME() result = Null();
		result.mArray[0] = T(2) / width;
		result.mArray[5] = T(2) / height;
		result.mArray[10] = T(-2) / range;
		result.mArray[12] = T(-1);
		result.mArray[13] = T(-1);
		result.mArray[14] = -(far + near) / range;
		result.mArray[15] = T(1);
		return result;
	}

	/// Look at constructor - LH lookat matrix											
	TEMPLATE()
	constexpr TME() TME()::LookAt(TVector<T, 3> forward, TVector<T, 3> up) {
		static_assert(IsSquare && Rows > 2,
			"Can't make a look-at matrix from this one");

		forward = forward.Normalize();
		up = up.Normalize();
		if (forward.Abs() == up.Abs())
			throw Except::Arithmetic("Degenerate LookAt matrix - forward and up are the same");

		const auto right = up.Cross(forward).Normalize();
		up = forward.Cross(right);

		TME() result = Identity();
		result.Get(0, 0) = right[0];
		result.Get(1, 0) = right[1];
		result.Get(2, 0) = right[2];
		result.Get(0, 1) = up[0];
		result.Get(1, 1) = up[1];
		result.Get(2, 1) = up[2];
		result.Get(0, 2) = forward[0];
		result.Get(1, 2) = forward[1];
		result.Get(2, 2) = forward[2];
		return result;
	}

	/// Create a rotational matrix (for 2x2 matrix, only around z)					
	TEMPLATE()
	constexpr TME() TME()::Rotation(const T& roll) noexcept {
		static_assert(IsSquare && Rows == 2,
			"Can't make a rotation matrix from this one");

		auto cosR = Math::Cos(roll);
		auto sinR = Math::Sin(roll);

		TME() result;
		result.Get(0, 0) = cosR;
		result.Get(1, 0) = -sinR;
		result.Get(0, 1) = sinR;
		result.Get(1, 1) = cosR;
		return result;
	}

	/// Create a rotational matrix based on axis and angle							
	TEMPLATE()
	constexpr TME() TME()::RotationAxis(const TVector<T, 3>& axis, const T& angle) noexcept {
		static_assert(IsSquare && Rows > 2,
			"Can't make a rotation matrix from this one");

		return static_cast<TME()>(TQuaternion<T>::FromAxisAngle(axis, angle));
	}

	/// Rotational constructor in euler radians (for 3x3 matrix)					
	TEMPLATE()
	constexpr TME() TME()::Rotation(const T& pitch, const T& yaw, const T& roll) noexcept {
		static_assert(IsSquare && Rows > 2,
			"Can't make a rotation matrix from this one");

		const auto a = Math::Cos(pitch);
		const auto b = Math::Sin(pitch);
		const auto c = Math::Cos(yaw);
		const auto d = Math::Sin(yaw);
		const auto e = Math::Cos(roll);
		const auto f = Math::Sin(roll);
		const auto ae = a * e;
		const auto af = a * f;
		const auto be = b * e;
		const auto bf = b * f;

		TME() result;
		result.Get(0, 0) = c * e;
		result.Get(1, 0) = -c * f;
		result.Get(2, 0) = d;
		result.Get(0, 1) = af + be * d;
		result.Get(1, 1) = ae - bf * d;
		result.Get(2, 1) = -b * c;
		result.Get(0, 2) = bf - ae * d;
		result.Get(1, 2) = be + af * d;
		result.Get(2, 2) = a * c;
		return result;
	}

	/// Translational constructor																
	TEMPLATE()
	constexpr TME() TME()::Translation(const TVector<T, 4>& position) noexcept {
		TME() temp = Identity();
		return temp.SetPosition(position);
	}

	/// Scalar constructor (uniform)															
	TEMPLATE()
	constexpr TME() TME()::Scalar(const T& xx) noexcept {
		TME() temp = Null();
		for (Count col = 0; col < Columns; ++col)
			temp.Get(col, col) = xx;
		return temp;
	}

	/// Scalar constructor (non-uniform)													
	TEMPLATE()
	template<Count SIZE>
	constexpr TME() TME()::Scalar(const TVector<T, SIZE>& xx) noexcept {
		TME() temp = Null();
		Count col;
		for (col = 0; col < Min(SIZE, Columns); ++col)
			temp.Get(col, col) = xx[col];
		for (col = SIZE; col < Columns; ++col)
			temp.Get(col, col) = T(1);
		return temp;
	}

	/// Set to identity																			
	TEMPLATE()
	constexpr TME() TME()::Identity() noexcept {
		return Scalar(T(1));
	}

	/// Check if identity																		
	TEMPLATE()
	constexpr bool TME()::IsIdentity() const noexcept {
		return *this == Identity();
	}

	/// Set to null																				
	TEMPLATE()
	constexpr TME() TME()::Null() noexcept {
		T temp[MemberCount] = {};
		return temp;
	}

	/// Check if null																				
	TEMPLATE()
	constexpr bool TME()::IsNull() const noexcept {
		return *this == Null();
	}

	/// Inner static function for nested determinant calculation					
	TEMPLATE()
	template<Count SIZE, Count NEXT_SIZE>
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
	///	@return the determinant of the matrix											
	TEMPLATE()
	constexpr T TME()::Determinant() const noexcept {
		static_assert(IsSquare, "Can't get determinant of a non-square matrix");
		return InnerDeterminant<Columns>(mArray);
	}

	/// Transpose the matrix																	
	///	@return the transposed matrix														
	TEMPLATE()
	constexpr TME() TME()::Transpose() const noexcept {
		static_assert(IsSquare, "Can't transpose non-square matrix");
		TME() result = *this;
		for (int i = 0; i < Columns; ++i) {
			for (int j = 0; j < i; ++j) {
				pcSwap(result.Get(i, j), result.Get(j, i));
			}
		}
		return result;
	}

	/// Get cofactor																				
	///	@return the given cofactor of the matrix										
	TEMPLATE()
	constexpr TME() TME()::Cofactor(int p, int q, int n) const noexcept {
		TME() temp;
		int i = 0, j = 0;
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				//  Copying into temporary matrix only those element			
				//  which are not in given row and column							
				if (row != p && col != q) {
					temp.Get(j++, i) = Get(col, row);

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
	///	@return the determinant																
	TEMPLATE()
	constexpr T TME()::Determinant(int n) const noexcept {
		float D = 0;

		// Base case : if matrix contains single element						
		if (n == 1)
			return Get(0, 0);

		TME() temp;
		T sign = 1;
		for (int f = 0; f < n; f++) {
			// Getting Cofactor of A[0][f]											
			temp = Cofactor(0, f, n);
			D += sign * Get(f, 0) * temp.Determinant(n - 1);

			// terms are to be added with alternate sign							
			sign = -sign;
		}

		return D;
	}

	/// Function to get adjoint of A[N][N]													
	///	@return the adjoint matrix															
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
				adj.Get(i, j) = sign * temp.Determinant(Rows - 1);
			}
		}
		return adj;
	}

	/// Invert a square matrix																	
	///	@return the inverted matrix														
	TEMPLATE()
	TME() TME()::Invert() const {
		static_assert(IsSquare, "Can't invert non-square matrix");

		if constexpr (Columns == 2) {
			const auto det = mArray[0] * mArray[3] - mArray[1] * mArray[2];
			if (det == 0)
				throw Except::Arithmetic("Degenerate 2x2 matrix");

			const auto detInv = 1 / det;
			return ME(
				mArray[3] * detInv, -mArray[1] * detInv,
				-mArray[2] * detInv, mArray[0] * detInv
			);
		}
		else if constexpr (Columns == 3) {
			auto	n11 = mArray[0], n21 = mArray[1], n31 = mArray[2],
				n12 = mArray[3], n22 = mArray[4], n32 = mArray[5],
				n13 = mArray[6], n23 = mArray[7], n33 = mArray[8];

			auto	t11 = n33 * n22 - n32 * n23,
				t12 = n32 * n13 - n33 * n12,
				t13 = n23 * n12 - n22 * n13;

			const auto det = n11 * t11 + n21 * t12 + n31 * t13;
			if (det == 0)
				throw Except::DivisionByZero("Degenerate 3x3 matrix");

			const auto detInv = 1 / det;

			T result[9];
			result[0] = t11 * detInv;
			result[1] = (n31 * n23 - n33 * n21) * detInv;
			result[2] = (n32 * n21 - n31 * n22) * detInv;

			result[3] = t12 * detInv;
			result[4] = (n33 * n11 - n31 * n13) * detInv;
			result[5] = (n31 * n12 - n32 * n11) * detInv;

			result[6] = t13 * detInv;
			result[7] = (n21 * n13 - n23 * n11) * detInv;
			result[8] = (n22 * n11 - n21 * n12) * detInv;
			return result;
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

			T result[16];
			result[0] = t11 * detInv;
			result[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
			result[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
			result[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * detInv;

			result[4] = t12 * detInv;
			result[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
			result[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
			result[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * detInv;

			result[8] = t13 * detInv;
			result[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
			result[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
			result[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;

			result[12] = t14 * detInv;
			result[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
			result[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
			result[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;
			return result;
		}
		else LANGULUS_ERROR("Matrix inversion code not implemented");
	}

} // namespace Langulus::Math
