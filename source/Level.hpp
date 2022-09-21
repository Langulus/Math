///																									
/// Langulus::Math																				
/// Copyright(C) 2014 Dimo Markov <langulusteam@gmail.com>							
///																									
/// Distributed under GNU General Public License v3+									
/// See LICENSE file, or https://www.gnu.org/licenses									
///																									
#pragma once
#include "Functions/Arithmetics.hpp"

LANGULUS_DECLARE_TRAIT(Level, "Level trait");

namespace Langulus::Math
{

	///																								
	///	Physical levels of simulation and instancing									
	///																								
	///	A level is a layer inside the world fractal. Zero level is the			
	/// human level. There are levels below, and levels above humans'.			
	/// The level number is the index of the layer in the fractal.					
	/// Each level represents a scale of 10^3 units.									
	/// Level of zero in 3D space can contain (10^3)^3 human units.				
	/// Level of seven in 3D space can contain (10^3)^3 galaxy units.				
	/// The absolute amount of units in a level is 10^(3*(o - omin))				
	/// An entity might exist in multiple levels at the same time.					
	/// For example, a planet in planetary level can also exist as terrain on	
	/// human level, or a dot on galaxy level.											
	/// Generally, stuff in higher levels is more likely to affect stuff in		
	/// lower levels.																				
	///																								
	///																								
	/// An example of 1D level subdivisions:												
	///	Planets	|							   |							   |				
	///				+-----------------------+-----------------------+				
	///	Humans	|           |           |           |           |				
	///				+-----------+-----------+-----------+-----------+				
	///	Atoms		|     |     |     |     |     |     |     |     |				
	///																								
	struct PC_API_MATH Level : public TNumber<real, Level> {
		REFLECT(Level);

		constexpr Level() noexcept
			: TNumber {Level::Default} {}

		constexpr Level(const Level& other) noexcept
			: TNumber {other.mValue} {}

		constexpr Level(const pci32 octave) noexcept {
			const auto ioct = static_cast<real>(octave);
			if (ioct < Level::Min || ioct > Level::Max)
				mValue = Level::OutOfBounds;
			mValue = ioct;
		}

		constexpr Level(const real octave) noexcept {
			if (octave < Level::Min || octave > Level::Max)
				mValue = Level::OutOfBounds;
			mValue = octave;
		}

		constexpr Level(const pcptr octave) noexcept {
			const auto ioct = static_cast<real>(octave) + Level::Min;
			if (ioct < Level::Min || ioct > Level::Max)
				mValue = Level::OutOfBounds;
			mValue = ioct;
		}

		static constexpr real Unit = 1000;
		static constexpr real Exponent = 3;
		static constexpr real OutOfBounds = -100;


		// Humans inhabit level 0 at scale of 1 meter							
		static constexpr real Human = 0;

		// Asteroids inhabit level 1 (10^3), at scale of 1 kilometer		
		// Ceres is, for example, 473 km. in radius								
		static constexpr real Asteroid = 1;

		// Planets inhabit level 2 (10^6), at scale of 1 megameter			
		// Earth for example is 3.1855 megameters	in radius					
		// Our sun also falls in this category, with 695.7 Mm radius		
		static constexpr real Planet = 2;

		// Planetary systems inhabit level 3 (scale of 10^9 meters)			
		// The solar system expands to 150 gigameters radius					
		// Some of the largest stars fall into this category					
		// Like UY Scuti - 139.14 gigameters										
		static constexpr real System = 3;

		// Galaxies inhabit level 7 (10^21), at scale of 1 zettameter		
		// The Milky Way's radius is 0.473 zettameters							
		// IC 1101's radius is 56.764 zettameters									
		static constexpr real Galaxy = 7;

		// Universes inhabit level 9 (10^27), at scale of 1... universe	
		// Our observable universe is 0.861 * (10^26) meters					
		static constexpr real Universe = 9;

		// Cells inhabit level -2 (10^-6), at scale of 1 micrometer			
		// The human egg is 65 micrometers in radius								
		static constexpr real Cell = -2;

		// Viruses inhabit level -3 (10^-9), at scale of 1 nanometer		
		// The HIV virus is 65 nanometers in radius								
		// There are ginormous virus-sized macromolecules						
		static constexpr real Virus = -3;

		// Atoms inhabit level -4 (10^-12), at scale of 1 picometer			
		// Atoms range from 50 pm to 250 pm	in radius							
		static constexpr real Atom = -4;

		// Neutrons inhabit level -5 (10^-15), at scale of 1 femtometer	
		// Radius of a neutron is 5 femtometers									
		// The radius of an electron is 0.5 femtometers							
		static constexpr real Neutron = -5;

		// Quarks inhabit level -6 (10^-18), at scale of 1 attometer		
		// An up quark is 5 attometers in radius									
		static constexpr real Quark = -6;

		// Neutrinos inhabit level -8 (10^-24), at scale of 1 yoctometer	
		// A neutrino is 5 yoctometers in radius									
		static constexpr real Neutrino = -8;
	
		// Planck length inhabits level -12 (10^-36)								
		// A Planck length is about 0.8 * (10^-35) meters in radius			
		static constexpr real Planck = -12;

		static constexpr real Max = Universe;
		static constexpr real Min = Planck;
		static constexpr real Range = Level::Max - Level::Min + 1;
		static constexpr pcptr RangeInt = static_cast<pcptr>(Level::Max - Level::Min + 1);

		// Human is the default level													
		static constexpr real Default = Human;

		/// Convert to text																		
		NOD() explicit inline operator GASM() const {
			return GASM(mValue);
		}

		/// Get a factor for scaling a relative level to this one					
		///	@param level - the level to factor against								
		///	@param return the invlog scale that maps this to other				
		inline real Factor(const ME& level) const noexcept {
			return pcPow(Unit, static_cast<real>(level - (*this)));
		}

		/// Get a reference point between two levels										
		///	@param level - the other level												
		///	@return a middle level between this and other							
		constexpr ME RefPoint(const ME& level) const noexcept {
			if (!*this || !level) {
				// Reference point can't exist										
				return Level::OutOfBounds;
			}
			else if (*this == level) {
				// Reference point is same												
				return *this;
			}
				
			// Reference point is middle												
			return (mValue + level.mValue) / 2;
		}

		/// Get a reference point between two levels										
		///	@param o1 - the first level													
		///	@param o2 - the second level													
		///	@return a middle level															
		constexpr static ME RefPoint(const ME& o1, const ME& o2) noexcept {
			return o1.RefPoint(o2);
		}

		/// Get a zero based offset from this level										
		///	@return the zero-based offset													
		constexpr real Offset() const noexcept {
			return mValue - Level::Min;
		}

		/// Get a zero based offset from this level (as integer)						
		///	@return the zero-based offset													
		constexpr pcptr OffsetInt() const noexcept {
			return static_cast<pcptr>(mValue - Level::Min);
		}

		/// Static casts to other numbers													
		/*template<DenseNumber T>
		NOD() explicit constexpr operator T () const noexcept { 
			return static_cast<T>(mValue);
		}*/
		/*NOD() constexpr operator const real& () const noexcept {
			return mValue;
		}
		NOD() constexpr operator real& () noexcept {
			return mValue;
		}*/

	};

} // namespace Langulus::Math
