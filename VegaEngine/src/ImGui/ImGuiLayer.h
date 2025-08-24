#pragma once
#include "Core/Layer.h"
#include "ImGuiInterface.h"
#include <vector>

namespace Vega {

    class ImGuiLayer : public Layer {
    public:
        void OnAttach() final;
        void OnDetach() final;
        void OnUpdate() final;

        inline void AttachWindow(ImGuiInterface* window) {
            _imguiWindowStack.push_back(window);
        }

    private:
        std::vector<ImGuiInterface*> _imguiWindowStack;
    };

}

