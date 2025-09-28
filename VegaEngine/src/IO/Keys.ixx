module;
#include "imgui.h"
export module IO:Keys;
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
		Ctrl,
		Alt,
		Shift,
		MouseLeft,
		MouseRight,
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

		void SetKey(char& key, ImGuiKey imguiKey) {
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


		void Update() {
			for (size_t i = 0; i <= (int)Key::Z; i++)
			{
				SetKey(keys[i], (ImGuiKey)(ImGuiKey_A + i));
			}
			SetKey(keys[(int)Key::Ctrl], ImGuiKey_ModCtrl);
			SetKey(keys[(int)Key::Alt], ImGuiKey_ModAlt);
			SetKey(keys[(int)Key::Shift], ImGuiKey_ModShift);
			SetKey(keys[(int)Key::MouseLeft], ImGuiKey_MouseLeft);
			SetKey(keys[(int)Key::MouseRight], ImGuiKey_MouseRight);
		}


		bool KeyStatus(Key key, KeyEvent eventType) const {
			return keys[(int)key] & (int)eventType;
		}
		bool KeyStatus(Key key, KeyEvent eventType, KeyMod mod) const {
			return keys[(int)key] & (int)eventType && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		bool KeyPressed(Key key) const {
			return keys[(int)key] & (int)KeyEvent::Pressed;
		}
		bool KeyPressed(Key key, KeyMod mod) const {
			return keys[(int)key] & (int)KeyEvent::Pressed && ImGui::IsKeyDown((ImGuiKey)mod);
		}

		bool KeyDown(Key key) const {
			return keys[(int)key] & (int)KeyEvent::Down;
		}
		bool KeyDown(Key key, KeyMod mod) const {
			return keys[(int)key] & (int)KeyEvent::Down && ImGui::IsKeyDown((ImGuiKey)mod);
		}


	private:
		std::array<char, 32> keys;
	};

}