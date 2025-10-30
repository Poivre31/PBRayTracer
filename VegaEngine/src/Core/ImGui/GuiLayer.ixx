module;
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module Core:GuiLayer;
import :Window;
import :Layer;
import Gui;
import Utility;
import std;
import Io;
import Render;
import Math;



export namespace Vega {

    enum class DrawMode {
        Fit,
        FitWidth,
        FitHeight,
        Stretch
    };

    class GuiLayer : public Layer {
    public:
        GuiLayer(Window* window) : _window(window) {
            if (!window) {
                Log.error("Invalid window passed to GuiLayer");
            }
        }

        Viewport* GetViewport() {
            return &_viewport;
        }

        void OnAttach() final {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
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

        void SetScreenShader(Shader* screen) {
            _screenShader = screen;
        }

        Vec2<int> ViewportSize() {
            return _screenSize;
        }

        void OnUpdate(double) final {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
#ifdef DIST
            dockspace_flags |= ImGuiDockNodeFlags_NoUndocking;
#endif // DIST
            ImGui::DockSpaceOverViewport(0, ImGui::GetWindowViewport(), dockspace_flags);
            ImGui::GetIO().ConfigDockingWithShift = true;

            Keys::SetIo(&ImGui::GetIO());
            Keys::SetMouseWheel(ImGui::GetIO().MouseWheel);
            Keys::SetMouseDelta((int)ImGui::GetIO().MouseDelta.x, (int)ImGui::GetIO().MouseDelta.y);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Viewport");

            auto width = ImGui::GetContentRegionAvail().x;
            auto height = ImGui::GetContentRegionAvail().y;
            _screenSize = { (int)width,(int)height };

            auto pos = ImGui::GetMousePos();
            auto off = ImGui::GetCursorScreenPos();
            Keys::SetMousePosViewport({ (int)(pos.x - off.x),(int)(height - (pos.y - off.y)) });

            
            Keys::KillMe(ImGui::IsWindowHovered());

            //if (_screenShader) {
            //    _frame.RunShader(_screenSize, _screenShader);
            //    ImGui::Image(_frame.GetTexture()->GetID(), ImVec2((float)width, (float)height));
            //}
            _viewport.Update(_screenSize);
            ImGui::End();
            ImGui::PopStyleVar();

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
        GuiLayer() = delete;
        Shader* _screenShader = nullptr;
        Texture* _screen;
        Vec2<int> _screenSize;
        FrameBuffer _frame;
        DrawMode _drawMode;
        std::vector<GuiCanvas*> _canvasStack;
        std::vector<std::string> _canvasNames;
        Window* _window = nullptr;
        Viewport _viewport;
    };

}

//GLuint _texID = _frame.GetTexture()->GetID();
//float R = (float)_screen->Width() / _screen->Height();
//switch (_drawMode) {
//case(DrawMode::Fit): {
//    float R2 = (float)width / height;
//    if(R2>R)
//        ImGui::Image(_texID, ImVec2((float)height * R, (float)height));
//    else
//        ImGui::Image(_texID, ImVec2((float)width, (float)width/R));
//    break;
//}
//case(DrawMode::FitHeight): {
//    ImGui::Image(_texID, ImVec2((float)height * R, (float)height));
//    break;
//}
//case(DrawMode::FitWidth): {
//    ImGui::Image(_texID, ImVec2((float)width, (float)width / R));
//    break;
//}
//case(DrawMode::Stretch): {
//    ImGui::Image(_texID, ImVec2((float)width, (float)height));
//    break;
//}
//}