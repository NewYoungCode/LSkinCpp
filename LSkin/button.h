#pragma once
#include "control.h"
namespace LSkin {
	class export Button :
		public Control
	{
	protected:
		void onMouseActive(MouseEventArgs * e);
		void onPaint(PaintEventArgs *e) override;
		bool mouseIn = false;
	};
}
