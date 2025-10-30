export module Gui:Widgets;
import :Primitives;
import :Grid;
import Entities;
import std;
import Math;
import Io;
import Utility;

bool linked = true;

export namespace Vega {

	enum class Status {
		Idle,
		Hovering,
		Moving,
		Deleting,
	};

	enum class Axis {
		None,
		X,
		Y,
		Z
	};

	Vec2<float> MosPos(Vec2<int> size) {
		auto [mosX, mosY] = Keys::MousePosViewport();
		Vec2 mosPos = { (float)mosX,(float)mosY };
		mosPos.x -= size.x / 2.f;
		mosPos.y -= size.y / 2.f;
		return mosPos;
	}

	class Widget {
	public:
		Vec2<float> MoveWidget(bool hovering, Vec2<int> size, Grid* grid) {
			auto mosPos = MosPos(size);

			Vec2<float> screenPos = grid->ToScreen(_position.xy());

			Vec2<float> targetPos = { 0.f,0.f };
			if (hovering and _status != Status::Moving and Keys::MouseDoubleClicked()) {
				_status = Status::Deleting;
				return screenPos;
			}


			if (_status != Status::Moving or
				Keys::Pressed(Key::Esc) or
				Keys::Released(Key::MouseLeft) and Timer::TimeS() - Keys::LastClickTimeS() > .1
				) {
				_status = Status::Idle;
			}

			if (Keys::Pressed(Key::MouseLeft) and _status == Status::Moving and Keys::HoveringViewport()) {
				_status = Status::Idle;
			}
			else if (hovering && _status != Status::Moving && Keys::HoveringViewport()) {
				if (Keys::Pressed(Key::MouseLeft)) {
					_selectionOffset = screenPos - mosPos;
					_selectionPosition = screenPos;
					_status = Status::Moving;
				}
				else {
					_status = Status::Hovering;
				}
			}

			if (Keys::Pressed(Key::X)) {
				if (_axis == Axis::X)
					_axis = Axis::None;
				else
					_axis = Axis::X;
			}
			if (Keys::Pressed(Key::Y)) {
				if (_axis == Axis::Y)
					_axis = Axis::None;
				else
					_axis = Axis::Y;
			}
			if (_status == Status::Idle)
				_axis = Axis::None;

			if (_status == Status::Moving) {
				targetPos = grid->ToWorld(_selectionOffset + mosPos);
				if (Keys::Down(Key::Ctrl)) {
					float gridSizeWS = float(grid->Settings()->gridSize * grid->Settings()->scale);
					targetPos = (targetPos / gridSizeWS).Round() * gridSizeWS;
				}
				screenPos = grid->ToScreen(targetPos);
				if (_axis == Axis::X) {
					screenPos.y = _selectionPosition.y;
				}
				else if (_axis == Axis::Y) {
					screenPos.x = _selectionPosition.x;
				}
			}

			return screenPos;
		}

		virtual Status Update(std::vector<Primitive>* vec, Vec2<int> size, Grid* grid, bool lock = false) = 0;

		Vec3<float> Position() {
			return _position;
		}

		Status GetStatus() {
			return _status;
		}

		void SetStatus(Status s, Vec2<float> clickPosition = {0.f,0.f}) {
			_selectionOffset = { 0.f,0.f };
			_selectionPosition = clickPosition;
			_status = s;
		}

	protected:
		Vec3<float> _position{ 0.f,0.f,0.f };
		Vec2<float> _selectionOffset{ 0.f,0.f };
		Vec2<float> _selectionPosition { 0.f,0.f };
		Status _status = Status::Idle;
		Axis _axis = Axis::None;
	};

	class DonutHandle : public Widget {
	public:
		DonutHandle() = default;

		DonutHandle(Vec2<int> position) {
			_position = Vec3((float)position.x, (float)position.y, 0.f);
		}

		Status Update(std::vector<Primitive>* vec, Vec2<int> size, Grid* grid, bool lock = false) override {
			auto mosPos = MosPos(size);
			Vec2<float> screenPos = grid->ToScreen(_position.xy());
			auto d = (screenPos - mosPos).Norm();

			if(!lock)
				screenPos = MoveWidget(d < 10.f * _size, size, grid);
			_position = grid->ToWorld(screenPos);

			if (_status == Status::Deleting)
				return _status;

			_mainDonut.position = screenPos;
			_innerOutline.position = screenPos;
			_outerOutline.position = screenPos;

			Vec3 color = _innerColor;
			if (_status == Status::Hovering && !lock)
				color = _hoverColor;
			if (_status == Status::Moving && !lock)
				color = _highlightColor;


			Primitive p;
			p.SetDonut(_innerOutline, _outlineColor, alpha);
			vec->push_back(p);
			p.SetDonut(_outerOutline, _outlineColor, alpha);
			vec->push_back(p);
			p.SetDonut(_mainDonut, color, alpha);
			vec->push_back(p);

			return _status;
		}

		float alpha = .8f;
	private:
		float _size = 1.5f;
		Vec3<float> _outlineColor = { .05f,.05f,.05f };
		Vec3<float> _innerColor = { .95f,.95f,.95f };
		Vec3<float> _highlightColor = { .95f,.6f,.4f };
		Vec3<float> _hoverColor = { .95f,.85f,.7f };

		// FIX SHADY SMOOTHING BETWEEN INNER DONUTS
		Donut _innerOutline{ _position,2.f * _size,3.5f * _size };
		Donut _outerOutline{ _position,8.5f * _size,10.f * _size };
		Donut _mainDonut{ _position,4.f * _size,8.f * _size };
	};

}