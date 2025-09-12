module;

#include <glad/gl.h>
#include <GLFW/glfw3.h>

export module Core:Layer;
import std;
import :Log;

namespace Vega {

	export class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

//#ifdef DEBUG
//		const char* GetName() {
//			return _name;
//		}
//		void SetName(const char* name) {
//			if (!name) {
//				Log.error("Invalid layer name");
//				return;
//			}
//			_name = name;
//		}
//#endif

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnResize(GLuint width, GLuint height) {}
		virtual void OnUpdate() {}
		virtual void OnPhysicsUpdate(double timeStep) {}

//#ifdef DEBUG
//	private:
//		const char* _name = "default name";
//#endif
	};

}

