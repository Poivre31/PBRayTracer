#pragma once
#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include "Timer.h"

namespace Vega {

	struct float4 {
		float x;
		float y;
		float z;
		float w;
	};

	struct Transform {
		float4 position;
		float4 scale;
		float4 rotation;
	};

	struct Material {
		float4 color;
	};

	struct Object {
		Transform transform;
		Material material;
		int type;

		Object() {
			transform = {};
			transform.scale = { 1,1,1,0 };
			material = {};
			material.color = { 1,1,1,0 };
			type = 0;
		}
	};


	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		static Application* Get();
		Window* GetWindow();

		void Close();
		void Resize(UINT width, UINT height);

		void AttachLayer(Layer* layer);
		void DetachLayer(Layer* layer);
		void ClearLayers();

		Object sphere{};

	private:
		static inline Application* _instance = nullptr;
		LayerStack _layerStack;
		bool _running = false;
		std::unique_ptr<Window> _window;
	};

	std::unique_ptr <Vega::Application> CreateApplication();
}

