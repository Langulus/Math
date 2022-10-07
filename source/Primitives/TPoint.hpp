///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Primitive.hpp"

namespace Langulus::Math
{

	template<CT::Vector> struct TPoint;

	using Point1 = TPoint<vec1>;
	using Point2 = TPoint<vec2>;
	using Point3 = TPoint<vec3>;

	using Point = Point3;

	namespace A
	{

		///																								
		///	An abstract point, also used as a topology type								
		///																								
		struct Point {
			LANGULUS(ABSTRACT) true;
			LANGULUS(CONCRETE) ::Langulus::Math::Point;
			LANGULUS_BASES(Topology);
		};

	} // namespace Langulus::Math::A


	///																								
	///	A concrete point																		
	///																								
	#pragma pack(push, 1)
	template<CT::Vector T>
	struct TPoint : public T {
		LANGULUS_BASES(A::Point, T);

		using PointType = T;
		using typename T::MemberType;
		using T::MemberCount;
		using T::T;

		/// Convert from any point to text													
		NOD() explicit operator Flow::Code() const {
			return Serialize<TPoint>();
		}

		/// Calculate signed distance															
		///	@param point - point to check distance from								
		///	@return the distance to the primitive										
		NOD() auto SignedDistance(const T& point) const {
			return (point - *this).Length();
		}
	};
	#pragma pack(pop)

} // namespace Langulus::Math
