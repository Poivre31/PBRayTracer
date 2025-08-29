#pragma once
#include "Core/Layer.h"
#include "ImGuiCanvas.h"
#include <vector>
#include "Core/Window.h"

namespace Vega {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(Window* window);

        void SetWindow(Window* window);

        void OnAttach() final;
        void OnDetach() final;
        void OnUpdate() final;

        void AttachCanvas(ImGuiCanvas* window);

    private:
        ImGuiLayer() = delete;

        std::vector<ImGuiCanvas*> _imguiCanvasStack;
        Window* _window = nullptr;
    };

}

