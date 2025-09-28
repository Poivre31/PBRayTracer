export module Core:GuiCanvas;

export namespace Vega {

	class GuiCanvas
	{
	public:
		GuiCanvas() = default;
		virtual ~GuiCanvas() = default;

		virtual void Draw() = 0;
	};

}

