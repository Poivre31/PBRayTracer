#pragma once
#include <vector>
#include "Log.h"

namespace Vega {

	class Layer
	{
	public:
		Layer();
		virtual ~Layer();

#ifdef DEBUG
		const char* GetName() {
			return _name;
		}
		void SetName(const char* name) {
			if (!name) {
				Log::error("Invalid layer name");
				return;
			}
			_name = name;
		}
#endif

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnResize(GLuint width, GLuint height);
		virtual void OnUpdate();
		virtual void OnPhysicsUpdate(double timeStep);

	private:
		const char* _name = "default name";
	};

}

