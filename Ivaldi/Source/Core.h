#pragma once

#ifdef IVALDI_PLATFORM_WINDOWS
#ifdef IVALDI_EXPORTS
	#define IVALDI_API __declspec(dllexport)
#else
	#define IVALDI_API __declspec(dllimport)
#endif
#else
	#error Ivaldi only supports Windows!
#endif

#ifdef IVALDI_ENABLE_ASSERTS
	#define IVALDI_ASSERT(x, ...) { if(!(x)) {  __debugbreak(); } }
	#define IVALDI_ASSERT(x, ...) { if(!(x)) { __debugbreak(); } }
#else
	#define IVALDI_ASSERT(x, ...)
	#define IVALDI_ASSERT(x, ...)
#endif

namespace ivaldi {
	enum ShaderType {
		Vertex,
		Tessalation,
		Geometry,
		Pixel,
		Count
	};

	enum class VertexAttribute : char {
		None = 0,
		Position = 1 << 0, // 00001 == 1
		Normal = 1 << 1, // 00010 == 2
		Texture = 1 << 2, // 00100 == 4
		Color = 1 << 3, // 01000 == 8
		Tangent = 1 << 4, // 10000 == 16
		BiTangent = 1 << 5,
		Count
	};

	inline constexpr VertexAttribute operator|(VertexAttribute a, VertexAttribute b) {
		int i_a = static_cast<int>(a);
		int i_b = static_cast<int>(b);
		return a = static_cast<VertexAttribute> (i_a | i_b);
	}

	inline constexpr VertexAttribute operator&(VertexAttribute a, VertexAttribute b) {
		int i_a = static_cast<int>(a);
		int i_b = static_cast<int>(b);
		return a = static_cast<VertexAttribute> (i_a & i_b);
	}
}