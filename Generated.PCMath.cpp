#include "include/PCFW.Math.hpp"
#include "Functions/MathVerbs.hpp"

PC_MONOPOLIZE_MEMORY(0)

//TODO automatically generate this file

namespace PCFW::Math
{

	REFLECT_BEGIN(Level)
		REFLECT_INFO("An octave")
		REFLECT_BEGIN_BASES
			REFLECT_BASE_MAP(decltype(mValue), 1)
		REFLECT_END_BASES
		REFLECT_BEGIN_MEMBERS
			REFLECT_MEMBER(mValue)
		REFLECT_END_MEMBERS
	REFLECT_END

	REFLECT_BEGIN(PCTime)
		REFLECT_INFO("High precision time")
		REFLECT_BEGIN_BASES
			REFLECT_BASE(ATime)
		REFLECT_END_BASES
		REFLECT_BEGIN_MEMBERS
			REFLECT_MEMBER(mValue)
		REFLECT_END_MEMBERS
	REFLECT_END

	REFLECT_BEGIN(PCTimeStamp)
		REFLECT_INFO("High range time")
		REFLECT_BEGIN_BASES
			REFLECT_BASE(ATime)
		REFLECT_END_BASES
		REFLECT_BEGIN_MEMBERS
			REFLECT_MEMBER(mData.mRaw)
		REFLECT_END_MEMBERS
	REFLECT_END

	/// Initialize all meta data required by the math library						
	bool pcInitPCMath() {
		static bool guard = false;
		if (guard)
			return true;
		guard = true;

		using namespace ::PCFW::RTTI;

		MetaData::REGISTER_LIST(TVecTypes{});
		MetaData::REGISTER_LIST(TMatrixTypes{});
		MetaData::REGISTER_LIST(TQuatTypes{});
		MetaData::REGISTER_LIST(TFractionTypes{});
		MetaData::REGISTER_LIST(TAngleTypes{});
		MetaData::REGISTER_LIST(TColorTypes{});
		MetaData::REGISTER_LIST(TSamplerTypes{});
		MetaData::REGISTER_LIST(TForceTypes{});
		MetaData::REGISTER_LIST(TNormalTypes{});
		MetaData::REGISTER_LIST(TSizerTypes{});

		MetaData::REGISTER<red8, red32>();
		MetaData::REGISTER<green8, green32>();
		MetaData::REGISTER<blue8, blue32>();
		MetaData::REGISTER<alpha8, alpha32>();
		MetaData::REGISTER<depth16, depth32>();

		//DataID::Reflect<pcu8>()->AddAbility()

		// Register the standard types												
		// We should reflect them manually, since they're built in			
		// These definitions are unlikely to change, ever						

		/*{
			// PCU8																			
			auto reflected = ReflectData::From<pcu8>(
				"U8,U8Ptr,U8ConstPtr", 
				"unsigned 8bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pcu8>(
				Base::From<pcu8, AUnsignedInt>());
			reflected.SetAbilities<pcu8>(
				ALL_PCMATH_ABILITIES(pcu8),
				REFLECT_CONVERSIONS_EXT(pcu8, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcu8>(reflected);
		}

		{
			// PCU16																			
			auto reflected = ReflectData::From<pcu16>(
				"U16,U16Ptr,U16ConstPtr",
				"unsigned 16bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pcu16>(
				Base::From<pcu16, AUnsignedInt>());
			reflected.SetAbilities<pcu16>(
				ALL_PCMATH_ABILITIES(pcu16),
				REFLECT_CONVERSIONS_EXT(pcu16, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcu16>(reflected);
		}

		{
			// PCU32																			
			auto reflected = ReflectData::From<pcu32>(
				"U32,U32Ptr,U32ConstPtr", 
				"unsigned 32bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pcu32>(
				Base::From<pcu32, AUnsignedInt>());
			reflected.SetAbilities<pcu32>(
				ALL_PCMATH_ABILITIES(pcu32),
				REFLECT_CONVERSIONS_EXT(pcu32, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcu32>(reflected);
		}

		{
			// PCU64																			
			auto reflected = ReflectData::From<pcu64>(
				"U64,U64Ptr,U64ConstPtr", 
				"unsigned 64bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pcu64>(
				Base::From<pcu64, AUnsignedInt>());
			reflected.SetAbilities<pcu64>(
				ALL_PCMATH_ABILITIES(pcu64),
				REFLECT_CONVERSIONS_EXT(pcu64, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcu64>(reflected);
		}

		{
			// PCI8																			
			auto reflected = ReflectData::From<pci8>(
				"I8,I8Ptr,I8ConstPtr",
				"signed 8bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pci8>(
				Base::From<pci8, ASignedInt>());
			reflected.SetAbilities<pci8>(
				ALL_PCMATH_ABILITIES(pci8),
				REFLECT_CONVERSIONS_EXT(pci8, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pci8>(reflected);
		}

		{
			// PCI16																			
			auto reflected = ReflectData::From<pci16>(
				"I16,I16Ptr,I16ConstPtr",
				"signed 16bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pci16>(
				Base::From<pci16, ASignedInt>());
			reflected.SetAbilities<pci16>(
				ALL_PCMATH_ABILITIES(pci16),
				REFLECT_CONVERSIONS_EXT(pci16, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pci16>(reflected);
		}

		{
			// PCI32																			
			auto reflected = ReflectData::From<pci32>(
				"I32,I32Ptr,I32ConstPtr", 
				"signed 32bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pci32>(
				Base::From<pci32, ASignedInt>());
			reflected.SetAbilities<pci32>(
				ALL_PCMATH_ABILITIES(pci32),
				REFLECT_CONVERSIONS_EXT(pci32, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pci32>(reflected);
		}

		{
			// PCI64																			
			auto reflected = ReflectData::From<pci64>(
				"I64,I64Ptr,I64ConstPtr", 
				"signed 64bit integer");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			reflected.SetBases<pci64>(
				Base::From<pci64, ASignedInt>());
			reflected.SetAbilities<pci64>(
				ALL_PCMATH_ABILITIES(pci64),
				REFLECT_CONVERSIONS_EXT(pci64, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pci64>(reflected);
		}

		{
			// PCR32																			
			auto reflected = ReflectData::From<pcr32>(
				"R32,R32Ptr,R32ConstPtr", 
				"signed 32bit floating point number");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			if constexpr (Same<real, pcr32>)
				reflected.mIsNamed = true;
			reflected.SetBases<pcr32>(
				Base::From<pcr32, AReal>());
			reflected.SetAbilities<pcr32>(
				ALL_PCMATH_ABILITIES(pcr32),
				REFLECT_CONVERSIONS_EXT(pcr32, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcr32>(reflected);
		}

		{
			// PCR64																			
			auto reflected = ReflectData::From<pcr64>(
				"R64,R64Ptr,R64ConstPtr", 
				"signed 64bit floating point number");
			reflected.mPOD = true;
			reflected.mNullifiable = true;
			if constexpr (Same<real, pcr64>)
				reflected.mIsNamed = true;
			reflected.SetBases<pcr64>(
				Base::From<pcr64, AReal>());
			reflected.SetAbilities<pcr64>(
				ALL_PCMATH_ABILITIES(pcr64),
				REFLECT_CONVERSIONS_EXT(pcr64, ALL_PCMATH_TYPES));
			MetaData::REGISTER<pcr64>(reflected);
		}*/

		MetaData::REGISTER<PCTime>();
		MetaData::REGISTER<PCTimeStamp>();

		MetaData::REGISTER<AGradient>();
		MetaData::REGISTER<Level>();

		// Register ranges																
		MetaData::REGISTER<range1>();
		MetaData::REGISTER<range2>();
		MetaData::REGISTER<range3>();
		MetaData::REGISTER<range4>();

		// Register lines																	
		MetaData::REGISTER<Line2>();
		MetaData::REGISTER<Line3>();

		MetaData::REGISTER<LineLoop2>();
		MetaData::REGISTER<LineLoop3>();

		MetaData::REGISTER<LineStrip2>();
		MetaData::REGISTER<LineStrip3>();

		// Register triangles															
		MetaData::REGISTER<Triangle2>();
		MetaData::REGISTER<Triangle3>();

		MetaData::REGISTER<TriangleStrip2>();
		MetaData::REGISTER<TriangleStrip3>();

		MetaData::REGISTER<TriangleFan2>();
		MetaData::REGISTER<TriangleFan3>();

		// Register points																
		MetaData::REGISTER<Point2>();
		MetaData::REGISTER<Point3>();

		// Register verbs																	
		MetaVerb::REGISTER<Verbs::Move>();

		// Register traits																
		MetaTrait::REGISTER<Traits::ModelTransform>();
		MetaTrait::REGISTER<Traits::Position>();
		MetaTrait::REGISTER<Traits::Velocity>();
		MetaTrait::REGISTER<Traits::Aim>();
		MetaTrait::REGISTER<Traits::Sampler>();
		MetaTrait::REGISTER<Traits::Scale>();
		MetaTrait::REGISTER<Traits::Acceleration>();
		MetaTrait::REGISTER<Traits::Solid>();
		MetaTrait::REGISTER<Traits::Pickable>();
		MetaTrait::REGISTER<Traits::Signed>();
		MetaTrait::REGISTER<Traits::Bilateral>();
		MetaTrait::REGISTER<Traits::Static>();
		MetaTrait::REGISTER<Traits::Boundness>();
		MetaTrait::REGISTER<Traits::Level>();
		MetaTrait::REGISTER<Traits::Relative>();

		MetaTrait::REGISTER<Traits::X>();
		MetaTrait::REGISTER<Traits::Y>();
		MetaTrait::REGISTER<Traits::Z>();
		MetaTrait::REGISTER<Traits::W>();

		MetaTrait::REGISTER<Traits::R>();
		MetaTrait::REGISTER<Traits::G>();
		MetaTrait::REGISTER<Traits::B>();
		MetaTrait::REGISTER<Traits::A>();

		// Register vector constants													
		MetaConst::REGISTER<Constants::Origin>();
		MetaConst::REGISTER<Constants::Forward>();
		MetaConst::REGISTER<Constants::Backward>();
		MetaConst::REGISTER<Constants::Up>();
		MetaConst::REGISTER<Constants::Down>();
		MetaConst::REGISTER<Constants::Right>();
		MetaConst::REGISTER<Constants::Left>();

		// Register color constants													
		MetaConst::REGISTER<Constants::White>();
		MetaConst::REGISTER<Constants::Black>();
		MetaConst::REGISTER<Constants::Grey>();
		MetaConst::REGISTER<Constants::Red>();
		MetaConst::REGISTER<Constants::Green>();
		MetaConst::REGISTER<Constants::DarkGreen>();
		MetaConst::REGISTER<Constants::Blue>();
		MetaConst::REGISTER<Constants::DarkBlue>();
		MetaConst::REGISTER<Constants::Cyan>();
		MetaConst::REGISTER<Constants::DarkCyan>();
		MetaConst::REGISTER<Constants::Orange>();
		MetaConst::REGISTER<Constants::Yellow>();
		MetaConst::REGISTER<Constants::Purple>();
		MetaConst::REGISTER<Constants::DarkPurple>();

		pcLogVerbose << ccGreen << "PCFW::Math initialized";
		return true;
	}

} // namespace PCFW::Math
