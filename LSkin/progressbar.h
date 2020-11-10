#pragma once
#include "control.h"
namespace LSkin {
	class export Progressbar :public Control
	{
	private:
		int _value = 50;
		int _maxvalue =100;
	public:
		void onPaint(PaintEventArgs * e);
		void setValue(int value);
		int  value();
		void setMaxValue(int maxValue);
		int  maxValue();
	};
}

