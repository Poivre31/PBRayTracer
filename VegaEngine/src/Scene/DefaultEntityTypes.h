#pragma once
#include "Entity.h"

namespace Vega {

	class Camera : Entity {
	public:
		CCamera camera;
		CController controller;

		void Update(double timeStep, Keys controls) {

			controller.Rotate(controls);
			controller.Move(controls, camera.GetTransformationMatrix());

			controller.Update(timeStep);
			camera.ConstructCameraView(controller);
		}
	};

}