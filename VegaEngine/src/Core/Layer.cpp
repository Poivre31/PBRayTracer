#include "Layer.h"

namespace Vega {

	extern void OnLayerDestruction(Layer* layer);

	Layer::Layer() = default;

	Layer::~Layer() {
		OnLayerDestruction(this);
	}

	void Layer::OnAttach() {

	}
	void Layer::OnDetach() {

	}
	void Layer::OnResize(GLuint width, GLuint height) {

	}
	void Layer::OnUpdate() {

	}
	void Layer::OnPhysicsUpdate(double timeStep) {

	}
}