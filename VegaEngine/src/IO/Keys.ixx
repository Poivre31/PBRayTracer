module;
#include "imgui.h"
export module Core:Keys;

export namespace Vega {

	class Keys {
	public:
		Keys() = default;
		Keys(char keyCodes) : _keysCode(keyCodes) {}

		void SetKeyZ(bool pressed) {
			SetBit(0, pressed);
		}
		void SetKeyS(bool pressed) {
			SetBit(1, pressed);
		}
		void SetKeyQ(bool pressed) {
			SetBit(2, pressed);
		}
		void SetKeyD(bool pressed) {
			SetBit(3, pressed);
		}
		void SetKeyA(bool pressed) {
			SetBit(4, pressed);
		}
		void SetKeyE(bool pressed) {
			SetBit(5, pressed);
		}
		void SetMouseLeft(bool pressed) {
			SetBit(6, pressed);
		}
		void SetMouseRight(bool pressed) {
			SetBit(7, pressed);
		}

		void SetKeysFromInput() {
			SetKeyZ(ImGui::IsKeyDown(ImGuiKey_Z));
			SetKeyS(ImGui::IsKeyDown(ImGuiKey_S));
			SetKeyQ(ImGui::IsKeyDown(ImGuiKey_Q));
			SetKeyD(ImGui::IsKeyDown(ImGuiKey_D));
			SetKeyA(ImGui::IsKeyDown(ImGuiKey_A));
			SetKeyE(ImGui::IsKeyDown(ImGuiKey_E));
			SetMouseLeft(ImGui::IsKeyDown(ImGuiKey_MouseLeft));
			SetMouseRight(ImGui::IsKeyDown(ImGuiKey_MouseRight));
		}

		bool GetKeyZ() {
			return GetBit(0);
		}
		bool GetKeyS() {
			return GetBit(1);
		}
		bool GetKeyQ() {
			return GetBit(2);
		}
		bool GetKeyD() {
			return GetBit(3);
		}
		bool GetKeyA() {
			return GetBit(4);
		}
		bool GetKeyE() {
			return GetBit(5);
		}
		bool GetMouseLeft() {
			return GetBit(6);
		}
		bool GetMouseRight() {
			return GetBit(7);
		}

	private:
		void SetBit(int n, bool value) {
			if (value) {
				_keysCode |= (1 << n);
			}
			else {
				_keysCode &= ~(1 << n);
			}
		}

		bool GetBit(int n) const {
			return _keysCode & (1 << n);
		}

		char _keysCode = 0;
	};

}