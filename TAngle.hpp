#pragma once
#include "Vectors.hpp"
#include "Dimensions.hpp"

namespace PCFW::Math
{

	template<class T, Dimension AXIS, bool RAD>
	struct TAngle;

	template<class T, bool RAD> 
	using TYaw = TAngle<T, Dimension::Y, RAD>;
	template<class T>	
	using DYaw = TYaw<T, false>;
	template<class T> 
	using RYaw = TYaw<T, true>;

	template<class T, bool RAD> 
	using TPitch = TAngle<T, Dimension::X, RAD>;
	template<class T> 
	using DPitch = TPitch<T, false>;
	template<class T> 
	using RPitch = TPitch<T, true>;

	template<class T, bool RAD> 
	using TRoll = TAngle<T, Dimension::Z, RAD>;
	template<class T> 
	using DRoll = TRoll<T, false>;
	template<class T> 
	using RRoll = TRoll<T, true>;

	using dyawf = DYaw<pcr32>;
	using dyawd = DYaw<pcr64>;
	using ryawf = RYaw<pcr32>;
	using ryawd = RYaw<pcr64>;

	using dpitchf = DPitch<pcr32>;
	using dpitchd = DPitch<pcr64>;
	using rpitchf = RPitch<pcr32>;
	using rpitchd = RPitch<pcr64>;

	using drollf = DRoll<pcr32>;
	using drolld = DRoll<pcr64>;
	using rrollf = RRoll<pcr32>;
	using rrolld = RRoll<pcr64>;

	using dyaw = DYaw<real>;
	using ryaw = RYaw<real>;
	using dpitch = DPitch<real>;
	using rpitch = RPitch<real>;
	using droll = DRoll<real>;
	using rroll = RRoll<real>;


	///																								
	///	Abstract angle																			
	///																								
	PC_DECLARE_ABSTRACT_DATA(Angle);


	///																								
	/// Angle oriented around a specific axis												
	///																								
	template<Dimension AXIS>
	struct EMPTY_BASE() TAngleOriented {
		using Concrete = TAngle<real, AXIS, false>;

		REFLECT_MANUALLY(TAngleOriented) {
			static GASM name, info;
			if (name.IsEmpty()) {
				if constexpr (AXIS == Dimension::X) {
					name += "Pitch";
					info += "pitch";
				}
				else if constexpr (AXIS == Dimension::Y) {
					name += "Yaw";
					info += "yaw";
				}
				else if constexpr (AXIS == Dimension::Z) {
					name += "Roll";
					info += "roll";
				}
				else LANGULUS_ASSERT("Unsupported axis");
				name = name.StandardToken();
				info = " abstract " + info + " angle";
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mConcrete = DataID::Of<Concrete>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(AAngle));
			reflection.MakeAbstract();
			return reflection;
		}
	};


	///																								
	/// Angle that is explicitly either in radians or degrees						
	///																								
	template<bool RAD>
	struct EMPTY_BASE() TAngleTyped {
		REFLECT_MANUALLY(TAngleTyped) {
			static GASM name, info;
			if (name.IsEmpty()) {
				if constexpr (RAD) {
					name += "Radians";
					info += "radians";
				}
				else {
					name += "Degrees";
					info += "degrees";
				}
				name = name.StandardToken();
				info = "abstract angle in " + info;
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.mConcrete = DataID::Of<real>;
			reflection.template SetBases<ME>(
				REFLECT_BASE(AAngle));
			reflection.MakeAbstract();
			return reflection;
		}
	};


	///																								
	///	Templated angle																		
	///																								
	template<class T, Dimension AXIS, bool RAD>
	struct EMPTY_BASE() TAngle 
		: public TAngleOriented<AXIS>
		, public TAngleTyped<RAD>
		, public TNumber<T, TAngle<T, AXIS, RAD>> {

		using NUMBER_BASE = TNumber<T, TAngle<T, AXIS, RAD>>;

		REFLECT_MANUALLY(TAngle) {
			static_assert(pcIsPOD<ME>, "Must be POD");
			static_assert(pcIsNullifiable<ME>, "Must be NULLIFIABLE");
			static_assert(sizeof(T) == sizeof(ME), "Size mismatch");
			static GASM name, info;
			if (name.IsEmpty()) {
				name += Text(DataID::Reflect<TAngleTyped<RAD>>()->GetToken(), 1);
				name += DataID::Reflect<TAngleOriented<AXIS>>()->GetToken();
				name.TypeSuffix<T>();
				name = name.StandardToken();

				if constexpr (AXIS == Dimension::X)
					info += "pitch";
				else if constexpr (AXIS == Dimension::Y)
					info += "yaw";
				else if constexpr (AXIS == Dimension::Z)
					info += "roll";
				else LANGULUS_ASSERT("Unsupported axis");

				info += " angle in ";
				if constexpr (RAD)
					info += "radians";
				else
					info += "degrees";

				info += " of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetBases<ME>(
				REFLECT_BASE(TAngleOriented<AXIS>), 
				REFLECT_BASE(TAngleTyped<RAD>));
			reflection.template SetAbilities<ME>(
				REFLECT_CONVERSIONS(GASM));
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER(mValue));
			return reflection;
		}

	public:
		using NUMBER_BASE::TNumber;

		template<bool ANYRAD>
		using SIMILAR = TAngle<T, AXIS, ANYRAD>;

		template<bool ANYRAD>
		NOD() friend constexpr ME operator + (const ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			if constexpr (ANYRAD == RAD)
				return lhs.mValue + rhs.mValue;
			else if constexpr (ANYRAD)
				return lhs.mValue + pcR2D(rhs.mValue);
			else 
				return lhs.mValue + pcD2R(rhs.mValue);
		}

		template<bool ANYRAD>
		NOD() friend constexpr ME operator - (const ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			if constexpr (ANYRAD == RAD)
				return lhs.mValue - rhs.mValue;
			else if constexpr (ANYRAD)
				return lhs.mValue - pcR2D(rhs.mValue);
			else
				return lhs.mValue - pcD2R(rhs.mValue);
		}

		template<bool ANYRAD>
		NOD() friend constexpr ME operator * (const ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			if constexpr (ANYRAD == RAD)
				return lhs.mValue * rhs.mValue;
			else if constexpr (ANYRAD)
				return lhs.mValue * pcR2D(rhs.mValue);
			else
				return lhs.mValue * pcD2R(rhs.mValue);
		}

		template<bool ANYRAD>
		NOD() friend constexpr ME operator / (const ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			if constexpr (ANYRAD == RAD)
				return lhs.mValue / rhs.mValue;
			else if constexpr (ANYRAD)
				return lhs.mValue / pcR2D(rhs.mValue);
			else
				return lhs.mValue / pcD2R(rhs.mValue);
		}

		template<bool ANYRAD>
		friend constexpr ME& operator += (ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			lhs = lhs + rhs;
			return lhs;
		}

		template<bool ANYRAD>
		friend constexpr ME& operator -= (ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			lhs = lhs - rhs;
			return lhs;
		}

		template<bool ANYRAD>
		friend constexpr ME& operator *= (ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			lhs = lhs * rhs;
			return lhs;
		}

		template<bool ANYRAD>
		friend constexpr ME& operator /= (ME& lhs, const SIMILAR<ANYRAD>& rhs) noexcept {
			lhs = lhs / rhs;
			return lhs;
		}

		/// Implicitly convert among angles of same type								
		template<class ANYT = T>
		NOD() constexpr operator TAngle<ANYT, AXIS, !RAD>() const noexcept {
			if constexpr(RAD)
				return { ANYT(pcR2D(NUMBER_BASE::mValue)) };
			else 
				return { ANYT(pcD2R(NUMBER_BASE::mValue)) };
		}

		NOD() constexpr T GetRadians() const noexcept {
			if constexpr (RAD)
				return NUMBER_BASE::mValue;
			else
				return pcD2R(NUMBER_BASE::mValue);
		}

		NOD() constexpr T GetDegrees() const noexcept {
			if constexpr (!RAD)
				return NUMBER_BASE::mValue;
			else
				return pcR2D(NUMBER_BASE::mValue);
		}

		/// Convert from any angle to text													
		NOD() explicit operator GASM() const {
			GASM result;
			result += DataID::Of<ME>;
			result += GASM::OpenScope;
				result += NUMBER_BASE::mValue;
			result += GASM::CloseScope;
			return result;
		}
	};


	/// Calculate cosine																			
	template<class T, Dimension AXIS, bool RAD>
	T pcCos(const TAngle<T, AXIS, RAD>& a) noexcept {
		if constexpr (RAD)
			return pcCos(a);
		else
			return pcCosDeg(a);
	}

	/// Calculate sine																			
	template<class T, Dimension AXIS, bool RAD>
	T pcSin(const TAngle<T, AXIS, RAD>& a) noexcept {
		if constexpr (RAD)
			return pcSin(a);
		else
			return pcSinDeg(a);
	}

	/// Angle typelists																			
	template<Dimension AXIS, bool RAD>
	struct TAngleTypeGenerator {
		template<class... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TAngle<T, AXIS, RAD>...>;
	};

	using TAnglePitchDegreeTypes = decltype(TAngleTypeGenerator<Dimension::X, false>::ForEach(std::declval<NumberTypes>()));
	using TAngleYawDegreeTypes = decltype(TAngleTypeGenerator<Dimension::Y, false>::ForEach(std::declval<NumberTypes>()));
	using TAngleRollDegreeTypes = decltype(TAngleTypeGenerator<Dimension::Z, false>::ForEach(std::declval<NumberTypes>()));
	using TAnglePitchRadianTypes = decltype(TAngleTypeGenerator<Dimension::X, true>::ForEach(std::declval<NumberTypes>()));
	using TAngleYawRadianTypes = decltype(TAngleTypeGenerator<Dimension::Y, true>::ForEach(std::declval<NumberTypes>()));
	using TAngleRollRadianTypes = decltype(TAngleTypeGenerator<Dimension::Z, true>::ForEach(std::declval<NumberTypes>()));

	using TAngleDegreeTypes = TTYPELIST_CAT3(TAnglePitchDegreeTypes, TAngleYawDegreeTypes, TAngleRollDegreeTypes);
	using TAngleRadianTypes = TTYPELIST_CAT3(TAnglePitchRadianTypes, TAngleYawRadianTypes, TAngleRollRadianTypes);
	using TAngleTypes = TTYPELIST_CAT2(TAngleDegreeTypes, TAngleRadianTypes);

	PC_DEFINE_ABSTRACT_DATA(Angle, "An abstract angle", void, REFLECT_BASE(ANumber));

} // namespace PCFW::Math