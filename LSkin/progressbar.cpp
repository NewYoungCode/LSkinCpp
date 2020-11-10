#include "progressbar.h"
namespace LSkin {

	void Progressbar::onPaint(PaintEventArgs *e) {
		if (maxValue() > 0 && value() > 0) {
			Rect rect = Rect(0, 0, width(), height());
			e->graphics->FillRect(rect, Color(255, 255, 255));

			rect = Rect(1, 1, width() - 2, height() - 2);
			e->graphics->FillRect(rect, Color(0, 0, 0));
		
			float rate = width()*1.0f/ maxValue() ;

			rect.Width = value()*rate;
			e->graphics->FillRect(rect, Color(255, 255, 255));

			rect.X +=1;
			rect.Y += 1;
			rect.Width -= 2;
			rect.Height -= 2;

			e->graphics->DrawRect(Rect(0,0,width(),height()), Color( 0, 0, 0));

			int x = 0;
		}
	}
	void Progressbar::setValue(int value)
	{
		_value = value;
		Invalidate();
	}
	int Progressbar::value()
	{
		return _value;
	}
	void Progressbar::setMaxValue(int maxValue)
	{
		_maxvalue = maxValue;
		Invalidate();
	}
	int Progressbar::maxValue()
	{
		return _maxvalue;
	}
}