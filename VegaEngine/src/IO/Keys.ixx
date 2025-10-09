module;
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
export module Io:Keys;
import std;
import Utility;

export namespace Vega {

	enum class KeyMod : int {
		ModCtrl = ImGuiKey_ModCtrl,
		ModShift = ImGuiKey_ModShift,
		ModAlt = ImGuiKey_ModAlt,
	};

	enum class Key : int {
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		Space,
		Ctrl,
		Alt,
		Shift,
		MouseLeft,
		MouseRight,
		Esc,
		KeyNumber,
	};

	enum class KeyEvent : char {
		None = 0b0,
		Released = 0b10,
		Pressed = 0b100,
		Repeat = 0b1000,
		Down = 0b10000,
	};

	class Keys {
	public:
		Keys() = default;

		static void SetIo(ImGuiIO* io) {
			_io = io;
		}

		static void SetKey(char& key, ImGuiKey imguiKey) {
			key = (char)KeyEvent::None;
			if (ImGui::IsKeyReleased(imguiKey)) {
				key |= (char)KeyEvent::Released;
			}
			if (ImGui::IsKeyPressed(imguiKey, false)) {
				key |= (char)KeyEvent::Pressed;
			}
			if (ImGui::IsKeyPressed(imguiKey, true)) {
				key |= (char)KeyEvent::Repeat;
			}
			if (ImGui::IsKeyDown(imguiKey)) {
				key |= (char)KeyEvent::Down;
			}
		}


		static void Update() {
			for (size_t i = 0; i <= (int)Key::Z; i++)
			{
				SetKey(keys[i], (ImGuiKey)(ImGuiKey_A + i));
			}
			SetKey(keys[(int)Key::Space], ImGuiKey_Space);
			SetKey(keys[(int)Key::Ctrl], ImGuiKey_ModCtrl);
			SetKey(keys[(int)Key::Alt], ImGuiKey_ModAlt);
			SetKey(keys[(int)Key::Shift], ImGuiKey_ModShift);
			SetKey(keys[(int)Key::MouseLeft], ImGuiKey_MouseLeft);
			SetKey(keys[(int)Key::MouseRight], ImGuiKey_MouseRight);
			SetKey(keys[(int)Key::Esc], ImGuiKey_Escape);
		}


		static bool KeyStatus(Key key, KeyEvent eventType) {
			return keys[(int)key] & (int)eventType;
		}
		static bool KeyStatus(Key key, KeyEvent eventType, KeyMod mod) {
			return keys[(int)key] & (int)eventType && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		static bool KeyPressed(Key key) {
			return keys[(int)key] & (int)KeyEvent::Pressed;
		}
		static bool KeyPressed(Key key, KeyMod mod) {
			return keys[(int)key] & (int)KeyEvent::Pressed && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		static bool KeyReleased(Key key) {
			return keys[(int)key] & (int)KeyEvent::Released;
		}
		static bool KeyReleased(Key key, KeyMod mod) {
			return keys[(int)key] & (int)KeyEvent::Released && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		static bool KeyDown(Key key) {
			return keys[(int)key] & (int)KeyEvent::Down;
		}
		static bool KeyDown(Key key, KeyMod mod) {
			return keys[(int)key] & (int)KeyEvent::Down && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		static std::tuple<int, int> MousePos() {
			auto pos = ImGui::GetMousePos();
			return { (int)pos.x,(int)pos.y };
		}

		static void SetMouseWheel(float value) {
			_mouseWheel = value;
		}

		static void SetMouseDelta(int dx, int dy) {
			_dx = dx;
			_dy = dy;
		}

		static float MouseWheel() {
			// TO FUCKING FIX THIS IS HORRIBLE
			return _mouseWheel;
		}

		static bool MouseDoubleClicked() {
			return ImGui::IsMouseDoubleClicked(0);
		}

		static std::tuple<int, int> MouseDelta() {
			return { _dx, _dy };
		}

		static void KillMe(bool schrodinger) {
			killMe = schrodinger;
		}

		static bool HoveringWindow() {
			return killMe;
		}


	private:
		static inline std::array<char, 64> keys;
		static inline ImGuiIO* _io;
		static inline float _mouseWheel = 0.;
		static inline int _dx = 0;
		static inline int _dy = 0;
		static inline bool killMe = false;
	};

}