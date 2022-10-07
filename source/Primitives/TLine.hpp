///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "TPoint.hpp"

namespace Langulus::Math
{

	template<CT::Vector> struct TLine;
	template<CT::Vector> struct TLineLoop;
	template<CT::Vector> struct TLineStrip;

	using Line2 = TLine<Point2>;
	using Line3 = TLine<Point3>;
	using LineLoop2 = TLineLoop<Point2>;
	using LineLoop3 = TLineLoop<Point3>;
	using LineStrip2 = TLineStrip<Point2>;
	using LineStrip3 = TLineStrip<Point3>;

	using Line = Line3;
	using LineLoop = LineLoop3;
	using LineStrip = LineStrip3;

	namespace A
	{

		///																							
		///	An abstract line, also used as a topology type							
		///																							
		struct Line {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Line;
			LANGULUS_BASES(Topology);
		};

		///																							
		///	An abstract line loop, also used as a topology type					
		///																							
		struct LineLoop {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::LineLoop;
			LANGULUS_BASES(Topology);
		};

		///																							
		///	An abstract line strip, also used as a topology type					
		///																							
		struct LineStrip {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::LineStrip;
			LANGULUS_BASES(Topology);
		};

	} // namespace Langulus::Math::A


	///																								
	///	Templated line segment																
	///																								
	#pragma pack(push, 1)
	template<CT::Vector T>
	struct TLine {
		LANGULUS(POD) CT::POD<T>;
		LANGULUS(NULLIFIABLE) CT::Nullifiable<T>;
		LANGULUS_BASES(A::Line);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Lines don't exist below two dimensions");

		T mAB[2] {};

	public:
		/// Default construction (along x)													
		constexpr TLine() noexcept {
			mAB[1][0] = MemberType {0};
		}

		/// Manual construction from two points of any type							
		///	@param p1 - first point															
		///	@param p2 - second point														
		template<CT::Vector ALT_T = T>
		constexpr TLine(const ALT_T& p1, const ALT_T& p2) noexcept
			: mAB {p1, p2} {}

		/// Manual construction from two points of any type (unsafe)				
		///	@param points - pointer to the two points									
		template<CT::Vector ALT_T = T>
		constexpr TLine(const ALT_T* points) noexcept
			: mAB {points[0], points[1]} {}

		/// Manual construction from two points of any type, indexed				
		///	@param points - pointer to the two points									
		///	@param indices - indices for the points array							
		template<CT::Vector ALT_T = T, CT::Integer IDX>
		constexpr TLine(const ALT_T* points, const IDX(&indices)[2]) noexcept
			: mAB {points[indices[0]], points[indices[1]]} {}

		/// Check if line is degenerate														
		///	@param radius - the line radius used for tolerance						
		///	@return true if line has no radius or no length							
		NOD() bool IsDegenerate() const noexcept {
			return (mAB[0] - mAB[1]).Length() == MemberType {0};
		}

		/// Subdivide line																		
		///	@return the two new lines														
		NOD() ::std::array<TLine, 2> Subdivide() const noexcept {
			const T midpoint = mAB[0] + (mAB[1] - mAB[0]) / MemberType {2};
			return {{mAB[0], midpoint}, {midpoint, mAB[1]}};
		}

		/// Calculate signed distance															
		///	@param point - the point from which distance is calculated			
		///	@return the distance																
		NOD() auto SignedDistance(const PointType& point) const {
			const auto pa = point - mAB[0];
			const auto ba = mAB[1] - mAB[0];
			const auto h = Clamp01(Dot(pa, ba) / Dot2(ba));
			return Length(pa - ba * h);
		}

		/// Access points																			
		NOD() auto& operator [] (Offset index) const noexcept {
			return mAB[index];
		}
		NOD() auto& operator [] (Offset index) noexcept {
			return mAB[index];
		}

		/// Convert to other kinds of lines													
		template<CT::Vector ALT>
		NOD() explicit operator TLine<ALT>() const noexcept {
			return {static_cast<ALT>(mAB[0]), static_cast<ALT>(mAB[1])};
		}
	};
	#pragma pack(pop)


	///																								
	///	Templated line loop																	
	/// Essentially a list of points, where each next point forms a line with	
	/// the previous, and the last point forms a line with the first one			
	///																								
	template<CT::Vector T>
	struct TLineLoop : public Anyness::TAny<T> {
		LANGULUS(DEEP) false;
		LANGULUS_BASES(A::LineLoop);

		using Base = Anyness::TAny<T>;
		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Lines don't exist below two dimensions");

		NOD() TLineLoop Clone() const {
			TLineLoop cloned;
			static_cast<Base&>(cloned) = Base::Clone();
			return cloned;
		}
	};


	///																								
	///	Templated line strip																	
	/// Essentially a list of points, where each next point forms a line with	
	/// the previous																				
	///																								
	template<CT::Vector T>
	struct TLineStrip : public Anyness::TAny<T> {
		LANGULUS(DEEP) false;
		LANGULUS_BASES(A::LineStrip);

		using Base = Anyness::TAny<T>;
		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		static_assert(MemberCount > 1, "Lines don't exist below two dimensions");

		NOD() TLineStrip Clone() const {
			TLineStrip cloned;
			static_cast<Base&>(cloned) = Base::Clone();
			return cloned;
		}
	};

} // namespace Langulus::Math

