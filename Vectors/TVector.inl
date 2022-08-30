namespace PCFW::Math
{

	/// Reflect the abstract vector of specific size									
	template<pcptr S>
	REFLECT_MANUALLY_IMPL(TSizedVector<S>) {
		static GASM name, info;
		if (name.IsEmpty()) {
			name += "Vec";
			name += MemberCount;
			name = name.StandardToken();
			info += "an abstract vector of a size ";
			info += MemberCount;
		}

		auto reflection = RTTI::ReflectData::From<ME>(name, info);
		reflection.mConcrete = DataID::Of<TVector<real, S>>;
		reflection.template SetBases<ME>(
			REFLECT_BASE(AVector));
		reflection.MakeAbstract();
		return reflection;
	}

	/// Reflect the abstract vector of specific type									
	template<Number T>
	REFLECT_MANUALLY_IMPL(TTypedVector<T>) {
		static GASM name, info;
		if (name.IsEmpty()) {
			name += "Vec";
			name.TypeSuffix<T>();
			name = name.StandardToken();
			info += "an abstract vector of type ";
			info += DataID::Reflect<T>()->GetToken();
		}

		auto reflection = RTTI::ReflectData::From<ME>(name, info);
		reflection.mConcrete = DataID::Of<TVector<T, 4>>;
		reflection.template SetBases<ME>(
			REFLECT_BASE(AVector));
		reflection.MakeAbstract();
		return reflection;
	}

	/// Reflect vectors																			
	TEMPLATE()
	RTTI::ReflectData TME()::RTTI_Reflect() {
		static_assert(pcIsPOD<ME>, "Must be POD");
		static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
		static_assert(sizeof(DenseT) * MemberCount == sizeof(DenseME), "Size mismatch");
		static GASM name, info;
		if (name.IsEmpty()) {
			name += "Vec";
			name += MemberCount;
			name.TypeSuffix<T>();
			name = name.StandardToken();
			info += "a vector with type ";
			info += DataID::Reflect<T>()->GetToken();
			info += " and size ";
			info += MemberCount;
		}

		auto reflection = RTTI::ReflectData::From<ME>(name, info);
		reflection.template SetBases<ME>(
			REFLECT_BASE(TSizedVector<S>),
			REFLECT_BASE(TTypedVector<pcDecay<T>>),
			REFLECT_BASE_MAP(pcDecay<T>, S)
		);

		using v2 = TVector<MemberType, 2>;
		using v3 = TVector<MemberType, 3>;
		using n2 = TNormal<v2>;
		using n3 = TNormal<v3>;

		if constexpr (MemberCount == 1) {
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM, MemberType));

			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], X));
		}
		else if constexpr (MemberCount == 2) {
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));

			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], X),
				REFLECT_MEMBER_TRAIT(mArray[1], Y));
		}
		else if constexpr (MemberCount == 3) {
			DataID::Reflect<n2>();
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM, v2, n2));

			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], X),
				REFLECT_MEMBER_TRAIT(mArray[1], Y),
				REFLECT_MEMBER_TRAIT(mArray[2], Z));
		}
		else if constexpr (MemberCount == 4) {
			DataID::Reflect<n2>();
			DataID::Reflect<n3>();
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM, v2, v3, n2, n3));

			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mArray[0], X),
				REFLECT_MEMBER_TRAIT(mArray[1], Y),
				REFLECT_MEMBER_TRAIT(mArray[2], Z),
				REFLECT_MEMBER_TRAIT(mArray[3], W));
		}
		else {
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));

			reflection.template SetMembers<ME>(
				REFLECT_MEMBER(mArray));
		}

		return reflection;
	}
	
	/// Copy (and convert) from same/bigger vectors of same/different types		
	/// Also acts as a copy-constructor														
	///	@param a - vector to copy															
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr TME()::TVector(const TVector<ALTT, ALTS>& a) noexcept {
		Initialize < ALTT, ALTS, ALTT {0} > (a);
	}

	/// Initialize vector from another, setting unavailable values to DEFAULT	
	TEMPLATE()
	template<Number ALTT, pcptr ALTS, ALTT DEFAULT>
	constexpr void TME()::Initialize(const TVector<ALTT, ALTS>& a) noexcept {
		if constexpr (DenseVector) {
			if constexpr (S == 1) {
				// No loop, just use first element									
				mArray[0] = Adapt(a[0]);
			}
			else if constexpr (ALTS == 1) {
				// Prepare the scalar and set all elements to it				
				const auto scalar = Adapt(a[0]);
				for (pcptr i = 0; i < S; ++i)
					mArray[i] = scalar;
			}
			else {
				// Convert element-by-element											
				constexpr auto count = pcMin(S, ALTS);
				for (pcptr i = 0; i < count; ++i)
					mArray[i] = Adapt(a[i]);

				if constexpr (ALTS < S) {
					for (pcptr i = count; i < S; ++i)
						mArray[i] = DEFAULT;
				}
			}
		}
		else {
			auto& mutableA = const_cast<TVector<ALTT, ALTS>&>(a);
			if constexpr (S == 1) {
				// No loop, just use first element									
				mArray[0] = pcPtr(mutableA.mArray[0]);
			}
			else if constexpr (ALTS == 1) {
				// Prepare the scalar and set all elements to it				
				for (pcptr i = 0; i < S; ++i)
					mArray[i] = pcPtr(mutableA.mArray[0]);
			}
			else {
				// Convert element-by-element											
				constexpr auto count = pcMin(S, ALTS);
				for (pcptr i = 0; i < count; ++i)
					mArray[i] = pcPtr(mutableA.mArray[i]);

				if constexpr (ALTS < S)
					LANGULUS_ASSERT("Can't create sparse vector by the use of a smaller vector");
			}
		}
	}

	/// Scalar/array construction																
	///	@param xx - scalar value to copy everywhere									
	TEMPLATE()
	template<class N>
	constexpr TME()::TVector(const N& a) noexcept requires Convertible<pcDecay<N>, pcDecay<T>> {
		if constexpr (DenseVector) {
			// Setup a dense vector														
			if constexpr (Dense<N>) {
				const auto scalar = Adapt(a);
				for (pcptr i = 0; i < S; ++i)
					mArray[i] = scalar;
			}
			else if constexpr (pcIsArray<N>) {
				if constexpr (pcExtentOf<N> < S)
					LANGULUS_ASSERT("This vector is too powerful for your array");

				for (pcptr i = 0; i < pcMin(S, pcExtentOf<N>); ++i)
					mArray[i] = Adapt(a[i]);
			}
			else for (pcptr i = 0; i < S; ++i) {
				mArray[i] = Adapt(a[i]);
			}
		}
		else {
			// Setup a sparse vector													
			if constexpr (Dense<N>) {
				for (pcptr i = 0; i < S; ++i)
					mArray[i] = const_cast<T>(&a);
			}
			else if constexpr (pcIsArray<N>) {
				if constexpr (pcExtentOf<N> < S)
					LANGULUS_ASSERT("This vector is too powerful for your array");

				for (pcptr i = 0; i < pcMin(S, pcExtentOf<N>); ++i)
					mArray[i] = const_cast<T>(a + i);
			}
			else for (pcptr i = 0; i < S; ++i) {
				mArray[i] = const_cast<T>(pcPtr(a[i]));
			}
		}
	}

	/// Manual construction via a variadic head-tail									
	/// This constructor is disabled for proxy vectors									
	TEMPLATE()
	template<class HEAD, class... TAIL>
	constexpr TME()::TVector(const HEAD& head, const TAIL&... tail) noexcept requires (S > 1 && sizeof...(TAIL) > 0) {
		if constexpr (DenseVector) {
			// Setup a dense vector														
			if constexpr (ComplexNumber<HEAD>) {
				if constexpr (HEAD::MemberCount < MemberCount) {
					for (pcptr i = 0; i < HEAD::MemberCount; ++i)
						mArray[i] = Adapt(head[i]);
					const TVector<T, MemberCount - HEAD::MemberCount> theRest{ tail... };
					for (pcptr i = HEAD::MemberCount; i < MemberCount; ++i)
						mArray[i] = theRest.mArray[i - HEAD::MemberCount];
				}
				else LANGULUS_ASSERT("More elements provided than required");
			}
			else if constexpr (Convertible<HEAD, T>) {
				mArray[0] = Adapt(head);
				const TVector<T, MemberCount - 1> theRest{ tail... };
				for (pcptr i = 1; i < MemberCount; ++i)
					mArray[i] = theRest.mArray[i - 1];
			}
			else LANGULUS_ASSERT("Bad element type in dense vector unfolding constructor - must be ComplexNumber or Number");
		}
		else {
			// Setup a sparse vector													
			if constexpr (ComplexNumber<HEAD>) {
				if constexpr (HEAD::MemberCount < MemberCount) {
					for (pcptr i = 0; i < HEAD::MemberCount; ++i)
						mArray[i] = const_cast<T>(pcPtr(head[i]));
					TVector<T, MemberCount - HEAD::MemberCount> theRest{ tail... };
					for (pcptr i = HEAD::MemberCount; i < MemberCount; ++i)
						mArray[i] = theRest.mArray[i - HEAD::MemberCount];
				}
				else LANGULUS_ASSERT("More elements provided than required");
			}
			else if constexpr (Convertible<HEAD, T>) {
				mArray[0] = const_cast<T>(pcPtr(head));
				TVector<T, MemberCount - 1> theRest{ tail... };
				for (pcptr i = 1; i < MemberCount; ++i)
					mArray[i] = theRest.mArray[i - 1];
			}
			else LANGULUS_ASSERT("Bad element type in sparse vector unfolding constructor - must be ComplexNumber or Number");
		}
	}

	/// Construct from component, if its index is smaller than SIZE				
	///	@param a - component to set														
	TEMPLATE()
	template<Number N, Dimension I>
	constexpr TME()::TVector(const TVectorComponent<N, I>& a) noexcept requires (pcptr(I) < S)
		: TVector {} {
		if constexpr (DenseVector)
			mArray[I] = Adapt(a.mValue);
		else
			mArray[I] = const_cast<T*>(pcPtr(a.mValue));
	}

	/// Write the body of the vector (reused in vector specializations)			
	///	@param result - [out] the resulting body										
	TEMPLATE()
	void TME()::WriteBody(GASM& result) const {
		if constexpr (S > 1)
			result += GASM::OpenScope;

		for (pcptr i = 0; i < S; ++i) {
			result += (*this)[i];
			if (i < S - 1)
				result += GASM::AndSeparator;
		}

		if constexpr (S > 1)
			result += GASM::CloseScope;
	}

	/// Convert from any vector to text														
	TEMPLATE()
	TME()::operator GASM() const {
		GASM result;
		if constexpr (S > 1)
			result += DataID::Of<ME>;
		WriteBody(result);
		return result;
	}

	/// Get the value of a specific component index										
	TEMPLATE()
	template<class N>
	constexpr decltype(auto) TME()::Adapt(const N& item) const noexcept requires Convertible<pcDecay<N>, pcDecay<T>> {
		if constexpr (!Same<N, T>)
			return static_cast<DenseT>(pcVal(item));
		else
			return pcVal(item);
	}


	///																								
	///	Access																					
	///																								
	/// Get the value of a specific component index										
	TEMPLATE()
	constexpr decltype(auto) TME()::Get(const pcptr i) const noexcept {
		return mArray[i];
	}

	/// Get the value of a specific component index (with static check)			
	TEMPLATE()
	template<pcptr I>
	constexpr decltype(auto) TME()::GetIdx() const noexcept requires (I < S) {
		return Get(I);
	}

	/// Get Nth vector element (mutable)													
	/// Make sure the index is smaller than SIZE											
	///	@param a - index of the element (0, 1, 2 correspond to X, Y, Z)		
	///	@returns a reference to the component											
	TEMPLATE()
	constexpr decltype(auto) TME()::operator [] (const pcptr a) noexcept {
		if constexpr (SparseVector)
			return *mArray[a];
		else
			return mArray[a];
	}

	/// Get Nth vector element																	
	/// Make sure the index is smaller than SIZE											
	///	@param a - index of the element (0, 1, 2 correspond to X, Y, Z)		
	///	@returns a reference to the component											
	TEMPLATE()
	constexpr decltype(auto) TME()::operator [] (const pcptr a) const noexcept {
		if constexpr (SparseVector)
			return *mArray[a];
		else
			return mArray[a];
	}

	TEMPLATE()
	constexpr auto TME()::GetRaw() const noexcept {
		return mArray;
	}

	TEMPLATE()
	constexpr auto TME()::GetRaw() noexcept {
		return mArray;
	}

	TEMPLATE()
	constexpr auto TME()::GetCount() const noexcept {
		return MemberCount;
	}

	TEMPLATE()
	constexpr auto TME()::GetCount() noexcept {
		return MemberCount;
	}

	/// Get the raw dense data of the vector (mutable)									
	/// This is disabled for proxy vectors													
	TEMPLATE()
	constexpr auto TME()::operator () () noexcept requires DenseVector {
		return mArray;
	}

	/// Get the raw dense data of the vector												
	/// This is disabled for proxy vectors													
	TEMPLATE()
	constexpr auto TME()::operator () () const noexcept requires DenseVector {
		return mArray;
	}

	/// Get the squared magnitute of the vector											
	TEMPLATE()
	constexpr auto TME()::LengthSquared() const noexcept {
		auto accum = (*this)[0] * (*this)[0];
		for (int i = 1; i < S; ++i)
			accum += (*this)[i] * (*this)[i];
		return accum;
	}

	/// Get the magnitute of the vector														
	TEMPLATE()
	constexpr auto TME()::Length() const noexcept {
		return pcSqrt(LengthSquared());
	}

	/// Check if vector is a degenerate, that is at least one element is	0		
	///	@returns true if vector is degenerate											
	TEMPLATE()
	constexpr bool TME()::IsDegenerate() const noexcept {
		for (int i = 0; i < S; ++i)
			if ((*this)[i] == DenseT(0))
				return true;
		return false;
	}

	/// Mutable swizzle																			
	/// Make sure provided indices are inside the vector								
	///	@returns the proxy vector with the selected components					
	TEMPLATE()
	template<pcptr... I>
	constexpr decltype(auto) TME()::Swz() noexcept {
		return TVector<DenseT*, sizeof...(I)>(pcPtr(mArray[I])...);
	}

	/// Immutable swizzle																		
	/// Make sure provided indices are inside the vector								
	///	@returns a simple vector with the selected copied components			
	TEMPLATE()
	template <pcptr... I>
	constexpr decltype(auto) TME()::Swz() const noexcept {
		return TVector<DenseT, sizeof...(I)>(mArray[I]...);
	}

	/// Copy same vector as real																
	/// If the vector is an integer vector, all elements will be normalized		
	/// by the maximum integer and returned as real number.							
	TEMPLATE()
	constexpr decltype(auto) TME()::Real() const noexcept {
		if constexpr (RealNumber<T>) {
			// The vector is already a floating point vector. Just copy		
			return *this;
		}
		else {
			// Normalize all elements by the numeric limits of the type		
			constexpr real factor = real(1) / real(std::numeric_limits<DenseT>::max());
			real result[S];
			for (int i = 0; i < S; ++i)
				result[i] = static_cast<real>((*this)[i]) * factor;
			return TVector<real, S>(result);
		}
	}

	/// Multiply all members																	
	TEMPLATE()
	constexpr auto TME()::Volume() const noexcept {
		DenseT product = 1;
		for (pcptr i = 0; i < S; ++i)
			product *= (*this)[i];
		return product;
	}

	/// Copy a scalar/array																		
	TEMPLATE()
	template<Number N>
	constexpr auto& TME()::operator = (const N& scalar) noexcept {
		if constexpr (!Same<N, T>) {
			const auto convertedScalar = Adapt(scalar);
			for (pcptr i = 0; i < S; ++i)
				(*this)[i] = convertedScalar;
		}
		else {
			for (pcptr i = 0; i < S; ++i)
				(*this)[i] = scalar;
		}
		return *this;
	}

	/// Copy vector																				
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto& TME()::operator = (const TVector<ALTT, ALTS>& vec) noexcept {
		for (pcptr i = 0; i < pcMin(S, ALTS); ++i)
			(*this)[i] = Adapt(vec[i]);
		return *this;
	}

	/// Copy only component of same type													
	TEMPLATE()
	template<Number N, Dimension IDX>
	constexpr auto& TME()::operator = (const TVectorComponent<N, IDX>& com) noexcept requires (pcptr(IDX) < S) {
		(*this)[pcptr(IDX)] = Adapt(com.mValue);
		return *this;
	}

	/// Dot product																				
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Dot(const TVector<ALTT, ALTS>& other) const noexcept {
		DenseT accum = (*this)[0] * Adapt(other[0]);
		for (pcptr i = 1; i < pcMin(S, ALTS); ++i)
			accum += (*this)[i] * Adapt(other[i]);
		return accum;
	}

	TEMPLATE()
	template<Number N>
	constexpr auto TME()::Dot(const N& other) const noexcept {
		return Dot(DenseME(other));
	}

	/// Cross																						
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Cross(const TVector<ALTT, ALTS>& other) const noexcept requires (S > 2 && ALTS > 2) {
		DenseME base;
		base[0] = (*this)[1] * other[2] - (*this)[2] * other[1];
		base[1] = (*this)[2] * other[0] - (*this)[0] * other[2];
		base[2] = (*this)[0] * other[1] - (*this)[1] * other[0];
		return base;
	}

	/// Normalize																					
	TEMPLATE()
	constexpr auto TME()::Normalize() const requires (S > 1) {
		const auto l = Length();
		if (l == DenseT(0))
			throw Except::Arithmetic("Degenerate vector");
		return *this * (DenseT(1) / l);
	}

	/// Clamp between a minimum and maximum												
	TEMPLATE()
	template<Number ALTT1, pcptr ALTS1, Number ALTT2, pcptr ALTS2>
	constexpr auto TME()::Clamp(const TVector<ALTT1, ALTS1>& min, const TVector<ALTT2, ALTS2>& max) const noexcept {
		DenseME result{ *this };
		for (pcptr i = 0; i < pcMin(S, ALTS1, ALTS2); ++i)
			result[i] = pcClamp(result[i], min[i], max[i]);
		return result;
	}

	/// Clamp outide a minimum and maximum													
	TEMPLATE()
	template<Number ALTT1, pcptr ALTS1, Number ALTT2, pcptr ALTS2>
	constexpr auto TME()::ClampRev(const TVector<ALTT1, ALTS1>& min, const TVector<ALTT2, ALTS2>& max) const noexcept {
		DenseME result{ *this };
		for (pcptr i = 0; i < pcMin(S, ALTS1, ALTS2); ++i)
			result[i] = pcClampRev(result[i], min[i], max[i]);
		return result;
	}

	/// Round each element of the vector													
	TEMPLATE()
	constexpr auto TME()::Round() const noexcept {
		if constexpr (RealNumber<T>) {
			DenseT result[S];
			SIMD::Store(SIMD::Round(mArray), result);
			return DenseME{ result };
		}
		else return *this;
	}

	/// Floor each element of the vector													
	TEMPLATE()
	constexpr auto TME()::Floor() const noexcept {
		if constexpr (RealNumber<T>) {
			DenseT result[S];
			SIMD::Store(SIMD::Floor(mArray), result);
			return DenseME{ result };
		}
		else return *this;
	}

	/// Ceil each element of the vector														
	TEMPLATE()
	constexpr auto TME()::Ceil() const noexcept {
		if constexpr (RealNumber<T>) {
			DenseT result[S];
			SIMD::Store(SIMD::Ceil(mArray), result);
			return DenseME{ result };
		}
		else return *this;
	}

	/// Invert negative elements of vector													
	TEMPLATE()
	constexpr auto TME()::Abs() const noexcept {
		if constexpr (Signed<T>) {
			DenseT result[S];
			SIMD::Store(SIMD::Abs(mArray), result);
			return DenseME{ result };
		}
		else return *this;
	}

	/// Get biggest possible vector of the type											
	TEMPLATE()
	constexpr TME() TME()::Max() noexcept {
		return {std::numeric_limits<DenseT>::max()};
	}

	/// Get scalar maximum of each element													
	TEMPLATE()
	constexpr auto TME()::Max(const DenseT& limit) const noexcept {
		return SIMD::MaxWrap<DenseME>(mArray, limit);
	}

	/// Get maximum of each element															
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Max(const TVector<ALTT, ALTS>& limits) const noexcept {
		return SIMD::MaxWrap<TVector<DenseT, pcMin(S, ALTS)>>(mArray, limits.mArray);
	}

	/// Horizontal max																			
	TEMPLATE()
	constexpr auto TME()::HMax() const noexcept {
		DenseT biggest = (*this)[0];
		for (pcptr i = 1; i < S; ++i)
			biggest = pcMax((*this)[i], biggest);
		return biggest;
	}

	/// Get smallest possible vector of the type											
	TEMPLATE()
	constexpr TME() TME()::Min() noexcept {
		if constexpr (RealNumber<T>)
			return {std::numeric_limits<DenseT>::lowest()};
		else
			return {std::numeric_limits<DenseT>::min()};
	}

	/// Get scalar minimum of each element													
	TEMPLATE()
	constexpr auto TME()::Min(const DenseT& limit) const noexcept {
		return SIMD::MinWrap<DenseME>(mArray, limit);
	}

	/// Get minimum of each element															
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Min(const TVector<ALTT, ALTS>& limits) const noexcept {
		return SIMD::MinWrap<TVector<DenseT, pcMin(S, ALTS)>>(mArray, limits.mArray);
	}

	/// Horizontal min																			
	TEMPLATE()
	constexpr auto TME()::HMin() const noexcept {
		DenseT smallest = (*this)[0];
		for (pcptr i = 1; i < S; ++i)
			smallest = pcMin((*this)[i], smallest);
		return smallest;
	}

	/// Horizontal sum																			
	TEMPLATE()
	constexpr auto TME()::HSum() const noexcept {
		DenseT sum {};
		for (pcptr i = 0; i < S; ++i)
			sum += (*this)[i];
		return sum;
	}

	/// Horizontal multiply																		
	TEMPLATE()
	constexpr auto TME()::HMul() const noexcept {
		DenseT product {1};
		for (pcptr i = 0; i < S; ++i)
			product *= (*this)[i];
		return product;
	}

	/// Sign																							
	TEMPLATE()
	constexpr auto TME()::Sign() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcSign((*this)[i]);
		return DenseME {result};
	}

	/// Modulate via a scalar																	
	TEMPLATE()
	constexpr auto TME()::Mod(const DenseT& period) const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcMod((*this)[i], period);
		return DenseME {result};
	}

	/// Modulate via a vector																	
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Mod(const TVector<ALTT, ALTS>& period) const noexcept {
		constexpr pcptr commonS = pcMin(S, ALTS);
		DenseT result[commonS];
		for (pcptr i = 0; i < commonS; ++i)
			result[i] = pcMod((*this)[i], period[i]);
		return TVector<DenseT, commonS>{ result };
	}

	/// Step via a scalar																		
	TEMPLATE()
	constexpr auto TME()::Step(const DenseT& edge) const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcStep(edge, (*this)[i]);
		return DenseME {result};
	}

	/// Step via a vector																		
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Step(const TVector<ALTT, ALTS>& edge) const noexcept {
		constexpr pcptr commonS = pcMin(S, ALTS);
		DenseT result[commonS];
		for (pcptr i = 0; i < commonS; ++i)
			result[i] = pcStep(edge[i], (*this)[i]);
		return TVector<DenseT, commonS>{ result };
	}

	/// Power via a scalar																		
	TEMPLATE()
	constexpr auto TME()::Pow(const DenseT& exponent) const noexcept {
		return SIMD::PowerWrap<DenseME>(mArray, exponent);
	}

	/// Power via a vector																		
	TEMPLATE()
	template<Number ALTT, pcptr ALTS>
	constexpr auto TME()::Pow(const TVector<ALTT, ALTS>& exponents) const noexcept {
		return SIMD::PowerWrap<DenseME>(mArray, exponents.mArray);
	}

	/// Fraction																					
	TEMPLATE()
	constexpr auto TME()::Frac() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcFrac((*this)[i]);
		return DenseME {result};
	}

	/// Square root																				
	TEMPLATE()
	constexpr auto TME()::Sqrt() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcSqrt((*this)[i]);
		return DenseME {result};
	}

	/// Exponent																					
	TEMPLATE()
	constexpr auto TME()::Exp() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcExp((*this)[i]);
		return DenseME {result};
	}

	/// Sine																							
	TEMPLATE()
	constexpr auto TME()::Sin() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcSin((*this)[i]);
		return DenseME {result};
	}

	/// Cosine																						
	TEMPLATE()
	constexpr auto TME()::Cos() const noexcept {
		DenseT result[S];
		for (pcptr i = 0; i < S; ++i)
			result[i] = pcCos((*this)[i]);
		return DenseME {result};
	}

	/// Quicksort																					
	TEMPLATE()
	auto& TME()::Sort() noexcept {
		const auto compare = [](const void* p1, const void* p2) noexcept {
			auto g1 = static_cast<const T*>(p1);
			auto g2 = static_cast<const T*>(p2);
			if constexpr (Sparse<T>) {
				if (**g1 < **g2)			return -1;
				else if (**g1 > **g2)	return  1;
				else							return  0;
			}
			else {
				if (*g1 < *g2)				return -1;
				else if (*g1 > *g2)		return  1;
				else							return  0;
			}
		};

		qsort(mArray, S, sizeof(T), compare);
		return *this;
	}

	/// Warp (used for periodic boundary conditions)									
	TEMPLATE()
	constexpr auto TME()::Warp(const DenseT& scalar) const noexcept {
		if constexpr (Signed<T>) {
			const auto absScale = pcAbs(scalar);
			const auto halfScale = absScale / DenseT(2);
			DenseT result[S];

			for (pcptr i = 0; i < S; ++i)
				result[i] = (*this)[i] > halfScale
				? (*this)[i] - absScale
				: (*this)[i] < -halfScale
					? (*this)[i] + absScale
					: (*this)[i];
			return DenseME{ result };
		}
		else {
			DenseT result[S];
			for (pcptr i = 0; i < S; ++i)
				result[i] = (*this)[i] > scalar ? (*this)[i] - scalar : (*this)[i];
			return DenseME{ result };
		}
	}

	/// Implicitly convert from proxy to standard vector								
	TEMPLATE()
	constexpr TME()::operator DenseME () const noexcept requires SparseVector {
		return { mArray };
	}

	/// Implicitly convert to a number if size is 1										
	TEMPLATE()
	constexpr TME()::operator const DenseT& () const noexcept requires (S == 1) {
		return (*this)[0];
	}

	TEMPLATE()
	constexpr TME()::operator DenseT& () noexcept requires (S == 1) {
		return (*this)[0];
	}

	TEMPLATE()
	template<Number N>
	constexpr TME()::operator N () const noexcept requires (S == 1) {
		return static_cast<N>((*this)[0]);
	}
	

	///																								
	///	Operations																				
	///																								
	/// Returns an inverted vector															
	template<TARGS(RHS)>
	auto operator - (const TVEC(RHS)& me) noexcept {
		return me * pcDecay<RHST>(-1);
	}

	/// Returns the sum of any two vectors													
	/// Only the intersecting elements are added and returned:						
	///	v[4] + v[2] = v[2]																	
	template<TARGS(LHS), TARGS(RHS)>
	auto operator + (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::AddWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector + Scalar																			
	template<TARGS(LHS), Number N>
	auto operator + (const TVEC(LHS)& me, const N& other) noexcept {
		if constexpr (LHSS == 1)
			return me[0] + other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::AddWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar + Vector																			
	template<TARGS(RHS), Number N>
	auto operator + (const N& other, const TVEC(RHS)& me) noexcept {
		if constexpr (RHSS == 1)
			return other + me[0];	// 1D vectors decay to a number			
		else
			return me + other;
	}

	/// Returns the difference of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	auto operator - (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::SubtractWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector - Scalar																			
	template<TARGS(LHS), Number N>
	auto operator - (const TVEC(LHS)& me, const N& other) noexcept {
		if constexpr (LHSS == 1)
			return me[0] - other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::SubtractWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar - Vector																			
	template<TARGS(RHS), Number N>
	auto operator - (const N& other, const TVEC(RHS)& me) noexcept {
		if constexpr (RHSS == 1)
			return other - me[0];	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<RHST, N>;
			return SIMD::SubtractWrap<TVector<TYPE, RHSS>>(other, me.mArray);
		}
	}

	/// Returns the product of two vectors													
	template<TARGS(LHS), TARGS(RHS)>
	auto operator * (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::MultiplyWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector * Scalar																			
	template<TARGS(LHS), Number N>
	auto operator * (const TVEC(LHS)& me, const N& other) noexcept {
		if constexpr (LHSS == 1)
			return me[0] * other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::MultiplyWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar * Vector																			
	template<TARGS(RHS), Number N>
	auto operator * (const N& other, const TVEC(RHS)& me) noexcept {
		if constexpr (RHSS == 1)
			return other * me[0];	// 1D vectors decay to a number			
		else 
			return me * other;
	}

	/// Returns the division of two vectors												
	template<TARGS(LHS), TARGS(RHS)>
	auto operator / (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::DivideWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector / Scalar																			
	template<TARGS(LHS), Number N>
	auto operator / (const TVEC(LHS)& me, const N& other) {
		if constexpr (LHSS == 1)
			return me[0] / other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::DivideWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar / Vector																			
	template<TARGS(RHS), Number N>
	auto operator / (const N& other, const TVEC(RHS)& me) {
		if constexpr (RHSS == 1)
			return other / me[0];	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<RHST, N>;
			return SIMD::DivideWrap<TVector<TYPE, RHSS>>(other, me.mArray);
		}
	}

	/// Returns the left-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	auto operator << (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires IntegerNumber<LHST, RHST> {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::ShiftLeftWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector << Scalar																			
	template<TARGS(LHS), IntegerNumber N>
	auto operator << (const TVEC(LHS)& me, const N& other) noexcept requires IntegerNumber<LHST> {
		if constexpr (LHSS == 1)
			return me[0] << other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::ShiftLeftWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar << Vector																			
	template<TARGS(RHS), IntegerNumber N>
	auto operator << (const N& other, const TVEC(RHS)& me) noexcept requires IntegerNumber<RHST> {
		if constexpr (RHSS == 1)
			return other << me[0];	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<RHST, N>;
			return SIMD::ShiftLeftWrap<TVector<TYPE, RHSS>>(other, me.mArray);
		}
	}

	/// Returns the right-shift of two integer vectors									
	template<TARGS(LHS), TARGS(RHS)>
	auto operator >> (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires IntegerNumber<LHST, RHST> {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::ShiftRightWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector >> Scalar																			
	template<TARGS(LHS), IntegerNumber N>
	auto operator >> (const TVEC(LHS)& me, const N& other) noexcept requires IntegerNumber<LHST> {
		if constexpr (LHSS == 1)
			return me[0] >> other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::ShiftRightWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar >> Vector																			
	template<TARGS(RHS), IntegerNumber N>
	auto operator >> (const N& other, const TVEC(RHS)& me) noexcept requires IntegerNumber<RHST> {
		if constexpr (RHSS == 1)
			return other >> me[0];	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<RHST, N>;
			return SIMD::ShiftRightWrap<TVector<TYPE, RHSS>>(other, me.mArray);
		}
	}

	/// Returns the xor of two integer vectors											
	template<TARGS(LHS), TARGS(RHS)>
	auto operator ^ (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires IntegerNumber<LHST, RHST> {
		using TYPE = TLossless<LHST, RHST>;
		return SIMD::XOrWrap<TVector<TYPE, pcMin(LHSS, RHSS)>>(me.mArray, other.mArray);
	}

	/// Vector ^ Scalar																			
	template<TARGS(LHS), IntegerNumber N>
	auto operator ^ (const TVEC(LHS)& me, const N& other) noexcept requires IntegerNumber<LHST> {
		if constexpr (LHSS == 1)
			return me[0] ^ other;	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<LHST, N>;
			return SIMD::XOrWrap<TVector<TYPE, LHSS>>(me.mArray, other);
		}
	}

	/// Scalar ^ Vector																			
	template<TARGS(RHS), IntegerNumber N>
	auto operator ^ (const N& other, const TVEC(RHS)& me) noexcept requires IntegerNumber<RHST> {
		if constexpr (RHSS == 1)
			return other ^ me[0];	// 1D vectors decay to a number			
		else {
			using TYPE = TLossless<RHST, N>;
			return SIMD::XOrWrap<TVector<TYPE, RHSS>>(other, me.mArray);
		}
	}


	///																								
	///	Mutators																					
	///																								
	/// Add vectors																				
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		SIMD::Add(me.mArray, other.mArray, me.mArray);
		return me;
	}

	/// Add a dense vector to a proxy vector												
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator += (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires Sparse<LHST> {
		return operator += (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Add vector and a scalar																
	template<TARGS(LHS), Number N>
	auto& operator += (TVEC(LHS)& me, const N& other) noexcept {
		SIMD::Add(me.mArray, other, me.mArray);
		return me;
	}

	/// Add a proxy vector and a scalar														
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), Number N>
	auto& operator += (const TVEC(LHS)& me, const N& other) noexcept requires Sparse<LHST> {
		return operator += (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Subtract vectors																			
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		SIMD::Subtract(me.mArray, other.mArray, me.mArray);
		return me;
	}

	/// Subtract a dense vector from a proxy vector										
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator -= (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires Sparse<LHST> {
		return operator -= (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Subtract vector and a scalar															
	template<TARGS(LHS), Number N>
	auto& operator -= (TVEC(LHS)& me, const N& other) noexcept {
		SIMD::Subtract(me.mArray, other, me.mArray);
		return me;
	}

	/// Subtract a scalar vector from a proxy vector									
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), Number N>
	auto& operator -= (const TVEC(LHS)& me, const N& other) noexcept requires Sparse<LHST> {
		return operator -= (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Multiply vectors																			
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (TVEC(LHS)& me, const TVEC(RHS)& other) noexcept {
		SIMD::Multiply(me.mArray, other.mArray, me.mArray);
		return me;
	}

	/// Multiply a dense vector to a proxy vector										
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator *= (const TVEC(LHS)& me, const TVEC(RHS)& other) noexcept requires Sparse<LHST> {
		return operator *= (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Multiply vector by a scalar															
	template<TARGS(LHS), Number N>
	auto& operator *= (TVEC(LHS)& me, const N& other) noexcept {
		SIMD::Multiply(me.mArray, other, me.mArray);
		return me;
	}

	/// Multiply a proxy vector by a scalar												
	/// Proxy vectors are often temporary, so a constant lhs is required			
	template<TARGS(LHS), Number N>
	auto& operator *= (const TVEC(LHS)& me, const N& other) noexcept requires Sparse<LHST> {
		return operator *= (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Divide dense vectors																	
	/// This function will throw on division by zero									
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (TVEC(LHS)& me, const TVEC(RHS)& other) {
		SIMD::Divide(me.mArray, other.mArray, me.mArray);
		return me;
	}

	/// Divide a proxy vector to a dense vector											
	/// Proxy vectors are often temporary, so a constant lhs is required			
	/// This function will throw on division by zero									
	template<TARGS(LHS), TARGS(RHS)>
	auto& operator /= (const TVEC(LHS)& me, const TVEC(RHS)& other) requires Sparse<LHST> {
		return operator /= (const_cast<TVEC(LHS)&>(me), other);
	}

	/// Divide dense vector and a scalar													
	/// This function will throw on division by zero									
	template<TARGS(LHS), Number N>
	auto& operator /= (TVEC(LHS)& me, const N& other) {
		SIMD::Divide(me.mArray, other, me.mArray);
		return me;
	}

	/// Divide a proxy vector by a scalar													
	/// Proxy vectors are often temporary, so a constant lhs is required			
	/// This function will throw on division by zero									
	template<TARGS(LHS), Number N>
	auto& operator /= (const TVEC(LHS)& me, const N& other) requires Sparse<LHST> {
		return operator /= (const_cast<TVEC(LHS)&>(me), other);
	}


	///																								
	///	Compare																					
	///																								
	template<TARGS(LHS), TARGS(RHS)>
	auto operator < (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return SIMD::Lesser(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator < (const TVEC(LHS)& me, const N& other) {
		return SIMD::Lesser(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator < (const N& other, const TVEC(RHS)& me) {
		return SIMD::Lesser(other, me.mArray);
	}

	template<TARGS(LHS), TARGS(RHS)>
	auto operator <= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return SIMD::EqualsOrLesser(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator <= (const TVEC(LHS)& me, const N& other) {
		return SIMD::EqualsOrLesser(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator <= (const N& other, const TVEC(RHS)& me) {
		return SIMD::EqualsOrLesser(other, me.mArray);
	}

	template<TARGS(LHS), TARGS(RHS)>
	auto operator > (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return SIMD::Greater(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator > (const TVEC(LHS)& me, const N& other) {
		return SIMD::Greater(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator > (const N& other, const TVEC(RHS)& me) {
		return SIMD::Greater(other, me.mArray);
	}

	template<TARGS(LHS), TARGS(RHS)>
	auto operator >= (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return SIMD::EqualsOrGreater(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator >= (const TVEC(LHS)& me, const N& other) {
		return SIMD::EqualsOrGreater(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator >= (const N& other, const TVEC(RHS)& me) {
		return SIMD::EqualsOrGreater(other, me.mArray);
	}

	template<TARGS(LHS), TARGS(RHS)>
	auto operator == (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return SIMD::Equals(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator == (const TVEC(LHS)& me, const N& other) {
		return SIMD::Equals(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator == (const N& other, const TVEC(RHS)& me) {
		return SIMD::Equals(other, me.mArray);
	}

	template<TARGS(LHS), TARGS(RHS)>
	auto operator != (const TVEC(LHS)& me, const TVEC(RHS)& other) {
		return !SIMD::Equals(me.mArray, other.mArray);
	}

	template<TARGS(LHS), Number N>
	auto operator != (const TVEC(LHS)& me, const N& other) {
		return !SIMD::Equals(me.mArray, other);
	}

	template<TARGS(RHS), Number N>
	auto operator != (const N& other, const TVEC(RHS)& me) {
		return !SIMD::Equals(other, me.mArray);
	}

} // namespace PCFW::Math

