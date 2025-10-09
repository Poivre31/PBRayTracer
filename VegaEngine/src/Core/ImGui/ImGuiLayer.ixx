module;
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module Core:ImGuiLayer;
import :Window;
import :Layer;
import Gui;
import Utility;
import std;
import Io;

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
            Vega::Keys::SetIo(&ImGui::GetIO());

        }

        void OnDetach() final {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        void OnUpdate(double) final {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Vega::Keys::SetIo(&ImGui::GetIO());
            Vega::Keys::SetMouseWheel(ImGui::GetIO().MouseWheel);
            Vega::Keys::SetMouseDelta(ImGui::GetIO().MouseDelta.x, ImGui::GetIO().MouseDelta.y);
            Vega::Keys::KillMe(ImGui::GetIO().WantCaptureMouse);

            for (size_t i = 0; i < _canvasStack.size(); i++)
            {
                ImGui::Begin(_canvasNames[i].data());
                _canvasStack[i]->Draw();
                ImGui::End();
            }

            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        template <std::derived_from<GuiCanvas> T, typename ...Args>
        T* AttachCanvas(const char* name, Args... args) {
            auto* canvas = new T(args...);
            _canvasStack.push_back(canvas);
            _canvasNames.push_back(name);
            Log.debug("Attached canvas");
            return canvas;
        }

    private:
        ImGuiLayer() = delete;

        std::vector<GuiCanvas*> _canvasStack;
        std::vector<std::string> _canvasNames;
        Window* _window = nullptr;
    };

}