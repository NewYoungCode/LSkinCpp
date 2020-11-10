#pragma once
#include "../LSkin/application.h"
#include "../LSkin/form.h"
#include "../LSkin/button.h"
#include <thread>
#include <Gdiplus.hpp>
using namespace LSkin;
class DesktopBar :public Form
{
private:
	std::thread *timer_ = NULL;
	void timer();
	char value = 0;
public:
	DesktopBar();

protected:
	void onMouseActive(MouseEventArgs * e)override;
	void onPaint(PaintEventArgs*e) override;
};

