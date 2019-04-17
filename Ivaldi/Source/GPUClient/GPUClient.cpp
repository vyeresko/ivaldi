#include "Precompiled.h"

#include "GPUClient/GPUClient.h"

#include "Math/Matrix4x4.h"

namespace ivaldi {
	namespace gpu {
		void GPUClient::resetBuffers()
		{
			m_active_varray = nullptr;
		}

		void GPUClient::resetTextures()
		{
			m_active_textures.clear();
		}

		void GPUClient::resetProgram()
		{
			m_active_program = nullptr;
		}

		void GPUClient::draw()
		{
			m_active_program->bind();
			m_active_varray->bind();

			//for (int i = 0; i < m_active_textures.size(); ++i)
				//m_active_textures[i]->bind(i); // assume textures ordred by units
			

			// setup uniform temp

			ivaldi::math::Matrix4x4 transform = ivaldi::math::Matrix4x4::identity;
			
			transform[0].x = 0.02f;
			transform[1].y = 0.02f;
			transform[2].z = 0.02f;

			transform[3].y = -0.5f;

			transform.transpose();
			auto ptr = transform.getPtr();
			m_active_program->setVSUniformBuffer((const char*)ptr, 64);

			// call draw
			drawImp(m_active_varray->getIndexBuffer().getSize());
			
			/*for (auto &texture : m_active_textures)
				texture->unbind();*/
			
			m_active_varray->unbind();
			m_active_program->unbind();
		}	
	}
}