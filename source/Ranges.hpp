///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Ranges/TRange.hpp"
#include "Vectors.hpp"

namespace Langulus::Math
{

	/// Real number ranges																		
	using range1f = TRange<pcr32, 1>;
	using range1d = TRange<pcr64, 1>;

	using range2f = TRange<pcr32, 2>;
	using range2d = TRange<pcr64, 2>;
	using range3f = TRange<pcr32, 3>;
	using range3d = TRange<pcr64, 3>;
	using range4f = TRange<pcr32, 4>;
	using range4d = TRange<pcr64, 4>;

	using range1 = TRange<real, 1>;
	using range2 = TRange<real, 2>;
	using range3 = TRange<real, 3>;
	using range4 = TRange<real, 4>;

	/// Iteger ranges																				
	using range1u8 = TRange<pcu8, 1>;
	using range1u16 = TRange<pcu16, 1>;
	using range1u32 = TRange<pcu32, 1>;
	using range1u64 = TRange<pcu64, 1>;
	using range1i8 = TRange<pci8, 1>;
	using range1i16 = TRange<pci16, 1>;
	using range1i32 = TRange<pci32, 1>;
	using range1i64 = TRange<pci64, 1>;
	using range1pcptr = TRange<pcptr, 1>;

	using range2u8 = TRange<pcu8, 2>;
	using range2u16 = TRange<pcu16, 2>;
	using range2u32 = TRange<pcu32, 2>;
	using range2u64 = TRange<pcu64, 2>;
	using range2i8 = TRange<pci8, 2>;
	using range2i16 = TRange<pci16, 2>;
	using range2i32 = TRange<pci32, 2>;
	using range2i64 = TRange<pci64, 2>;
	using range2pcptr = TRange<pcptr, 2>;

	using range3u8 = TRange<pcu8, 3>;
	using range3u16 = TRange<pcu16, 3>;
	using range3u32 = TRange<pcu32, 3>;
	using range3u64 = TRange<pcu64, 3>;
	using range3i8 = TRange<pci8, 3>;
	using range3i16 = TRange<pci16, 3>;
	using range3i32 = TRange<pci32, 3>;
	using range3i64 = TRange<pci64, 3>;
	using range3pcptr = TRange<pcptr, 3>;

	using range4u8 = TRange<pcu8, 4>;
	using range4u16 = TRange<pcu16, 4>;
	using range4u32 = TRange<pcu32, 4>;
	using range4u64 = TRange<pcu64, 4>;
	using range4i8 = TRange<pci8, 4>;
	using range4i16 = TRange<pci16, 4>;
	using range4i32 = TRange<pci32, 4>;
	using range4i64 = TRange<pci64, 4>;
	using range4pcptr = TRange<pcptr, 4>;

} // namespace Langulus::Math
