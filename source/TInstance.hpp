///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Level.hpp"
#include "Ranges.hpp"
#include "Vectors.hpp"
#include "Quaternions/TQuaternion.hpp"
#include "Primitives.hpp"
#include "TAngle.hpp"
#include "Ranges.hpp"

#define PC_TINSTANCE_VERBOSE(a) // pcLogSelfVerbose << a

LANGULUS_DECLARE_TRAIT(ModelTransform, "Model transformation matrix trait");
LANGULUS_DECLARE_TRAIT(Solid, "Solidity state");
LANGULUS_DECLARE_TRAIT(Pickable, "Pickability state (true to be able to select with mouse)");
LANGULUS_DECLARE_TRAIT(Signed, "Signed state (inverts domains/geometry; flips faces; negates numbers)");
LANGULUS_DECLARE_TRAIT(Bilateral, "Bilateral state (doublesidedness)");
LANGULUS_DECLARE_TRAIT(Static, "Static state");
LANGULUS_DECLARE_TRAIT(Boundness, "Boundness state (shifts control from simulation to user and vice-versa)");
LANGULUS_DECLARE_TRAIT(Relative, "Relativity trait");

PC_DECLARE_VERB(Move, Move, "Move and rotate instances");

namespace Langulus::Math
{

	using LevelRange = TRange<Level>;

	///																								
	///	SPATIAL INSTANCE																		
	///																								
	/// Provides higher level functionality regarding rotation, translation,	
	/// scaling, primitive collisions, etc.												
	///																								
	template<ComplexNumber T>
	class TInstance {
	public:
		using PointType = T;
		using MemberType = typename PointType::MemberType;
		static_assert(RealNumber<MemberType>, "Instance must be made of real numbers");
		static constexpr pcptr MemberCount = PointType::MemberCount;
		using MatrixType = TMat<MemberType, MemberCount + 1, MemberCount + 1>;
		using RangeType = TRange<MemberType, MemberCount>;
		using QuatType = TQuat<MemberType>;
		using SizeType = TSizer<PointType>;

		REFLECT_MANUALLY(TInstance) {
			static GASM name, info;
			if (name.IsEmpty()) {
				name += "TInstance";
				name += MemberCount;
				if (!Same<MemberType, real>)
					name.TypeSuffix<MemberType>();
				name = name.StandardToken();
				info += "a physical instance of type ";
				info += DataID::Reflect<T>()->GetToken();
			}

			auto reflection = RTTI::ReflectData::From<ME>(name, info);
			reflection.template SetMembers<ME>(
				REFLECT_MEMBER_TRAIT(mPosition, Position),
				REFLECT_MEMBER_TRAIT(mVelocity, Velocity),
				REFLECT_MEMBER_TRAIT(mAcceleration, Acceleration),
				REFLECT_MEMBER_TRAIT(mAim, Aim),
				REFLECT_MEMBER_TRAIT(mScale, Scale),
				REFLECT_MEMBER_TRAIT(mSimBoundness, Boundness),
				REFLECT_MEMBER_TRAIT(mUseBoundness, Boundness),
				REFLECT_MEMBER_TRAIT(mSolid, Solid),
				REFLECT_MEMBER_TRAIT(mPickable, Pickable),
				REFLECT_MEMBER_TRAIT(mSigned, Signed),
				REFLECT_MEMBER_TRAIT(mBilateral, Bilateral),
				REFLECT_MEMBER_TRAIT(mStatic, Static),
				REFLECT_MEMBER_TRAIT(mLevel, Level)
			);
			reflection.template SetAbilities<ME>(
				REFLECT_ABILITY(Move)
			);

			return reflection;
		}

	public:
		TInstance() noexcept = default;

		NOD() RangeType GetRange(Level) const;
		NOD() RangeType GetRangeRotated(Level) const;

		NOD() PointType GetPositionNext(const MemberType&) const noexcept;
		NOD() PointType GetPositionPrev(const MemberType&) const noexcept;
		NOD() PointType GetVelocityNext(const MemberType&) const noexcept;
		NOD() PointType GetVelocityPrev(const MemberType&) const noexcept;

		NOD() PointType GetRight() const noexcept;
		NOD() PointType GetUp() const noexcept;
		NOD() PointType GetForward() const noexcept;
		NOD() SizeType GetScale(Level) const;
		NOD() SizeType GetScale() const noexcept;
		NOD() QuatType GetAim() const noexcept;
		NOD() PointType GetPosition(Level) const;
		NOD() PointType GetPosition() const noexcept;
		NOD() Level GetLevel() const noexcept;

		NOD() MatrixType GetModelTransform(Level) const;
		NOD() MatrixType GetModelTransform() const;

		NOD() MatrixType GetViewTransform(Level) const;
		NOD() MatrixType GetViewTransform() const;

		void ConstrainPosition(const TInstance<T>&, const RangeType&);

		template<bool RELATIVE = false>
		void SetScale(const SizeType&);
		template<bool RELATIVE = false>
		void SetPosition(const PointType&);

		NOD() PointType RandomPosition(PCMRNG&, const RangeType&) const;

		template<Dimension AXIS, bool RAD>
		void Rotate(MemberType, const TAngle<MemberType, AXIS, RAD>&, bool relative = false);

		template<class K>
		void Move(MemberType, const TNormal<K>&, bool relative = false);

		template<class K>
		void Move(MemberType, const TSizer<K>&, bool relative = false);

		template<class K>
		void Move(MemberType, const TPoint<K>&, bool relative = false);

		template<class K>
		void Move(MemberType, const TForce<K>&, bool relative = false);

		PC_VERB(Move);

		void ChangeLevel(MemberType, const Level&, bool relative = false);

		bool operator == (const TInstance&) const noexcept;
		bool operator != (const TInstance&) const noexcept;

	public:
		// Optional parent for inheriting transformations						
		Ptr<TInstance<T>> mParent;

		// Position in space																
		PointType mPosition;

		// Velocity incurred by simulation											
		PointType mSimVelocity;
		// Velocity incurred by user interaction									
		PointType mUseVelocity;
		// Total velocity 																
		PointType mVelocity;

		// Acceleration																	
		PointType mAcceleration;
		// The current orientation														
		QuatType mAim;
		// The current scale																
		SizeType mScale;

		// User-boundness of the instance											
		// Instances with zero sim-boundness, but high use-boundness are	
		// only explicitly moved and manipulated.									
		// They are not slaves of the simulation and 							
		// will not move without user input - useful for explicit control 
		// on characters and so on. This might cause really unexpected		
		// results in worlds that are the size of an universe.				
		// Instances with sim-boundness of one are dependent on				
		// the simulation. You can use any ratio in order to blend			
		// between user and sim input, but only simulation-boundness is	
		// capped. Use-boundness might exceed 1, and even be reversed.		
		// Excessive use-boundness essentially directs energy to the 		
		// physical system, so care must be taken to balance it out			
		// against the rest of energy applied from simulation. It's best	
		// to design a controller that relies on 1 SB, and 0 UB, so that	
		// physical movement is completely dependent on the simulation		
		// energy transfer. However, sometimes that is not an option, and 
		// involves quite elaborate tweeking and testing to behave well.	
		MemberType mSimBoundness = 1;
		MemberType mUseBoundness = 1;

		// Instance solidity. Solid instances are colliders.					
		// Nonsolid instances are never tested for collision.					
		// Volumes of water/air/etc. have partial solidity, causing drag	
		MemberType mSolid = 0;

		// Pickable instances are selectable by mouse ray						
		bool mPickable = true;

		// Instance hollowness. Hollow instances are inverted. (ie rooms)	
		// This way we can reuse geometry like cube, to make an empty box	
		// It also changes the face winding if not doublesided				
		bool mSigned = false;

		// Doublesidedness																
		bool mBilateral = false;

		// Static instances are never updated. Used as optimization			
		bool mStatic = false;

		// Octave change incurred by simulation									
		Level mSimLevelChange = 0;
		// Octave change incurred by user interaction							
		Level mUseLevelChange = 0;
		// Octave for scaling, position, acceleration and velocity			
		Level mLevel = 0;
	};

} // namespace Langulus::Math

#include "TInstance.inl"