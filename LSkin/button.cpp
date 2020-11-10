#include "button.h"

#include <iostream>
#include <stdio.h>
namespace LSkin {
	void Button::onMouseActive(MouseEventArgs *e) {
		Control::onMouseActive(e);
		if (e->mouseType == MouseType::MouseEnter) {
			mouseIn = true;
			Invalidate();
		}
		if (e->mouseType == MouseType::MouveLeave) {
			mouseIn = false;
			Invalidate();
		}
	}
	void Button::onPaint( PaintEventArgs * e)
	{
		if (mouseIn) {
			Control::onPaint(e);
			Rect r(0, 0, width(), height());
			Gdiplus::SolidBrush sb(Color(129, 192, 255));
			Gdiplus::Pen p(&sb, 1);
			e->graphics->FillRect(r, Color(50, 201, 222, 245));
			e->graphics->DrawRectangle(&p, r);
		}
		else {
			Control::onPaint(e);
			Rect r(0, 0, width(), height());
			Gdiplus::SolidBrush sb(Color(204, 206, 219));
			Gdiplus::Pen p(&sb, 1);
			e->graphics->DrawRectangle(&p, r);
		}
	}
}