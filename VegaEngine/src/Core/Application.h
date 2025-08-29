#pragma once
#include "Window.h"
#include "LayerStack.h"
#include <memory>
#include "Timer.h"
#include <variant>

namespace Vega {

	struct float4 {
		float x;
		float y;
		float z;
		float w;

		float* GetAdress() {
			return &x;
		}
	};

	struct int4 {
		int x;
		int y;
		int z;
		int w;

		int* GetAdress() {
			return &x;
		}
	};

	struct Transform {
		float4 position{};
		float4 scale{};
		float4 rotation{};
		//int4 parameters{};
	};

	struct Material {
		float4 color{};
	};

	struct Object2 {
		Transform transform{};
		Material material{};
		int type = 0;

		Object2() {
			transform = {
				{2,0,0,0},
				{1,1,1,0},
				{0,0,0,0}
			};

			material.color = { 1,1,1,0 };
		}
	};


	class Application
	{
	public:

		Application();
		virtual ~Application();

		void Init();
		void Run();
		void Shutdown();
		void PlanShutdown();

		static Application* Get();
		Window* GetWindow();

		virtual void Resize(GLuint width, GLuint height);

		void AttachLayer(Layer* layer);
		void DetachLayers(Layer* layer);
		void ClearLayers();

		Object2 sphere{};

	private:
		static inline Application* _instance = nullptr;
		static inline bool _initialised = false;
		
		bool _running = false;
		bool _shouldClose = false;
		LayerStack _layerStack;
		Window* _window = nullptr;
	};

	std::unique_ptr<Vega::Application> CreateApplication();
}

