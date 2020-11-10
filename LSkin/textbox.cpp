#include "textbox.h"
namespace LSkin {
	TextBox::TextBox(Control *parent)
	{
		hWnd = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 0, 0, 120, 25,
			parent->Hwnd(), NULL, GetModuleHandle(0), NULL);
		SetFontWin32(Hwnd());
		setTransparent(false);
		parent->addControl(this);
	}
};