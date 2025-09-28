module;
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module Core:ImGuiLayer;
import :Window;
import :Layer;
import :GuiCanvas;
import Utility;
import std;

export namespace Vega {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(Window* window) : _window(window) {
            if (!window) {
                Log.error("Invalid window passed to ImGuiLayer");
            }
        }
        //void SetWindow(Window* window) {
        //    if (!window) {
        //        Log.error("Invalid window passed to ImGuiLayer");
        //    }
        //    _window = window;
        //}

        void OnAttach() final {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(_window->GetGLFWWindow(), true);
            ImGui_ImplOpenGL3_Init("#version 460");

            Log.trace("Created ImGui layer");

        }

        void OnDetach() final {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void OnUpdate() final {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (GuiCanvas* window : _imguiCanvasStack)
            {
                window->Draw();
            }

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        template <std::derived_from<GuiCanvas> T>
        T* AttachCanvas() {
            auto* canvas = new T();
            _imguiCanvasStack.push_back(canvas);
            Log.debug("Attached canvas");
            return canvas;
        }

    private:
        ImGuiLayer() = delete;

        std::vector<GuiCanvas*> _imguiCanvasStack;
        Window* _window = nullptr;
    };

}