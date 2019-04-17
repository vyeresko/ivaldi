#include "Precompiled.h"
#include "GLMaterialSystem.h"

#define SHADER_SOURCE(src) #src

const char *vertex_shader_src = SHADER_SOURCE(
	#version 330 core \n

	layout(location = 0) in vec3 v_pos; \n

	uniform mat4 v_transform;

	void main() { \n
		gl_Position = v_transform * vec4(v_pos, 1.0); \n
	} \n
);

const char *pixel_shader_src = SHADER_SOURCE(
	#version 330 core \n

	out vec4 px_color; \n
	
	void main() { \n
		px_color = vec4(0.0, 0.0, 0.0, 1.0); \n
	} \n
);

namespace ivaldi {
	namespace gpu {
		std::string GLMaterialSystem::createVertexShaderSrc(VertexAttribute channels, const char* info) const
		{
			return vertex_shader_src;
		}


		std::string GLMaterialSystem::createPixelShaderSrc(VertexAttribute channels, const char* info) const
		{
			return pixel_shader_src;
		}
	}
}