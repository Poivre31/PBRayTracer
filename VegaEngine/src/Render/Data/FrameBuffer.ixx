module;
#include "OpenGL.h"
export module Render:FrameBuffer;
import :Shader;
import :Mesh2D;
import :Texture;
import Math;

export namespace Vega {
	class FrameBuffer {
	public:
		FrameBuffer() {
			_image = Texture({ 1, 1, Formats::RGBA16F });

			glGenFramebuffers(1, &_fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image.GetID(), 0);

			_screenQuad = Mesh2D::CreateScreenQuad();
		}

		FrameBuffer(Vec2<int> size) {
			_image = Texture({ size.x, size.y, Formats::RGBA16F });

			glGenFramebuffers(1, &_fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image.GetID(), 0);

			_screenQuad = Mesh2D::CreateScreenQuad();
		}

		void SetTexture(Texture& texture) {
			_image.Delete();
			_image = texture;
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image.GetID(), 0);
		}

		Texture* GetTexture() {
			return &_image;
		}

		void NewFrame(Vec2<int> size) {
			_image.Update(size.x, size.y);
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image.GetID(), 0);
			glViewport(0, 0, _image.Width(), _image.Height());
			glClearColor(.1f, .1f, .1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void RunShader(Shader* shader) {
			glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image.GetID(), 0);
			glViewport(0, 0, _image.Width(), _image.Height());
			if(shader)
				_screenQuad.Draw(shader);

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

	private:
		GLuint _fbo = 0;
		Texture _image;
		Mesh2D _screenQuad;
	};

}