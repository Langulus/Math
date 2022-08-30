#pragma once
#include "Vectors/TVector.hpp"
#include "Vectors/TNormal.hpp"
#include "Vectors/TSampler.hpp"
#include "Vectors/TForce.hpp"
#include "Vectors/TSizer.hpp"

namespace PCFW::Math
{

	using vec1Grad = TGrad2<vec1>;
	using vec1fGrad = TGrad2<vec1f>;
	using vec1dGrad = TGrad2<vec1d>;
	using vec1iGrad = TGrad2<vec1i>;
	using vec1uGrad = TGrad2<vec1u>;

	using vec2Grad = TGrad2<vec2>;
	using vec2fGrad = TGrad2<vec2f>;
	using vec2dGrad = TGrad2<vec2d>;
	using vec2iGrad = TGrad2<vec2i>;
	using vec2uGrad = TGrad2<vec2u>;

	using vec3Grad = TGrad2<vec3>;
	using vec3fGrad = TGrad2<vec3f>;
	using vec3dGrad = TGrad2<vec3d>;
	using vec3iGrad = TGrad2<vec3i>;
	using vec3uGrad = TGrad2<vec3u>;

	using vec4Grad = TGrad2<vec4>;
	using vec4fGrad = TGrad2<vec4f>;
	using vec4dGrad = TGrad2<vec4d>;
	using vec4iGrad = TGrad2<vec4i>;
	using vec4uGrad = TGrad2<vec4u>;

	namespace Vectors
	{
		template<Number T>
		constexpr TVec<T, 4> Origin { 0, 0, 0, 0 };

		template<Number T>
		constexpr TVec<T, 4> Forward { 0, 0, 1, 0 };

		template<Number T>
		constexpr TVec<T, 4> Backward { 0, 0, -1, 0 };

		template<Number T>
		constexpr TVec<T, 4> Up { 0, 1, 0, 0 };

		template<Number T>
		constexpr TVec<T, 4> Down { 0, -1, 0, 0 };

		template<Number T>
		constexpr TVec<T, 4> Right { 1, 0, 0, 0 };

		template<Number T>
		constexpr TVec<T, 4> Left { -1, 0, 0, 0 };
	}

	/// Vector typelists																			
	template<pcptr SIZE>
	struct TVecTypeGenerator {
		template<Number... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TVec<T, SIZE>...>;
	};

	using TVec1Types = TTYPELIST_FROM(TVecTypeGenerator<1>, NumberTypes);
	using TVec2Types = TTYPELIST_FROM(TVecTypeGenerator<2>, NumberTypes);
	using TVec3Types = TTYPELIST_FROM(TVecTypeGenerator<3>, NumberTypes);
	using TVec4Types = TTYPELIST_FROM(TVecTypeGenerator<4>, NumberTypes);
	using TVecTypes = TTYPELIST_CAT4(TVec1Types, TVec2Types ,TVec3Types ,TVec4Types);

	/// Normal typelists																			
	struct TNormalTypeGenerator {
		template<ComplexNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TNormal<T>...>;
	};

	using TNormal2Types = TTYPELIST_FROM(TNormalTypeGenerator, TVec2Types);
	using TNormal3Types = TTYPELIST_FROM(TNormalTypeGenerator, TVec3Types);
	using TNormal4Types = TTYPELIST_FROM(TNormalTypeGenerator, TVec4Types);
	using TNormalTypes = TTYPELIST_CAT3(TNormal2Types, TNormal3Types, TNormal4Types);

	/// Force typelists																			
	struct TForceTypeGenerator {
		template<ComplexNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TForce<T>...>;
	};

	using TForce1Types = TTYPELIST_FROM(TForceTypeGenerator, TVec1Types);
	using TForce2Types = TTYPELIST_FROM(TForceTypeGenerator, TVec2Types);
	using TForce3Types = TTYPELIST_FROM(TForceTypeGenerator, TVec3Types);
	using TForce4Types = TTYPELIST_FROM(TForceTypeGenerator, TVec4Types);
	using TForceTypes = TTYPELIST_CAT4(TForce1Types, TForce2Types ,TForce3Types,TForce4Types);

	/// Sampler typelists																		
	struct TSamplerTypeGenerator {
		template<ComplexNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TSampler<T>...>;
	};

	using TSampler1Types = TTYPELIST_FROM(TSamplerTypeGenerator, TVec1Types);
	using TSampler2Types = TTYPELIST_FROM(TSamplerTypeGenerator, TVec2Types);
	using TSampler3Types = TTYPELIST_FROM(TSamplerTypeGenerator, TVec3Types);
	using TSampler4Types = TTYPELIST_FROM(TSamplerTypeGenerator, TVec4Types);
	using TSamplerTypes = TTYPELIST_CAT4(TSampler1Types, TSampler2Types, TSampler3Types, TSampler4Types);

	/// Sizer typelists																			
	struct TSizerTypeGenerator {
		template<ComplexNumber... T>
		static constexpr auto ForEach(TTypeList<T...>)
			-> TTypeList<TSizer<T>...>;
	};

	using TSizer1Types = TTYPELIST_FROM(TSizerTypeGenerator, TVec1Types);
	using TSizer2Types = TTYPELIST_FROM(TSizerTypeGenerator, TVec2Types);
	using TSizer3Types = TTYPELIST_FROM(TSizerTypeGenerator, TVec3Types);
	using TSizer4Types = TTYPELIST_FROM(TSizerTypeGenerator, TVec4Types);
	using TSizerTypes = TTYPELIST_CAT4(TSizer1Types, TSizer2Types, TSizer3Types, TSizer4Types);

} // namespace PCFW::Math

namespace PCFW::Constants
{
	namespace Vectors = Math::Vectors;
}

LANGULUS_DECLARE_CONSTANT(Origin, Vectors::Origin<real>, "Center of a coordinate system");
LANGULUS_DECLARE_CONSTANT(Forward, Vectors::Forward<real>, "Standard local forward vector");
LANGULUS_DECLARE_CONSTANT(Backward, Vectors::Backward<real>, "Standard local backward vector");
LANGULUS_DECLARE_CONSTANT(Up, Vectors::Up<real>, "Standard local up vector");
LANGULUS_DECLARE_CONSTANT(Down, Vectors::Down<real>, "Standard local down vector");
LANGULUS_DECLARE_CONSTANT(Right, Vectors::Right<real>, "Standard local right vector");
LANGULUS_DECLARE_CONSTANT(Left, Vectors::Left<real>, "Standard local left vector");
