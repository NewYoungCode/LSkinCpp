#include "DesktopBar.h"


void DesktopBar::timer()
{
	/*for (;;) {
		Sleep(500);
		Invalidate();
		MEMORYSTATUS ms;
		::GlobalMemoryStatus(&ms);
		value = (char)ms.dwMemoryLoad;
	}*/
}

DesktopBar::DesktopBar() :Form()
{
	//this->setFormBorderStyle(FormBorderStyle::NoneBorder);
	setSize(500, 500);

	//std::string filename = Path::StartPath() + "\\test.bmp";
	//Gdiplus::Bitmap test(75, 75);
	//Gdiplus::Graphics gpp(&test);
	//gpp.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
	//gpp.SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHalf);
	//gpp.SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintClearTypeGridFit);
	//gpp.SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeHighQualityBicubic);

	//Gdiplus::SolidBrush sb(Color(0,0,0));
	//gpp.FillRectangle(&sb, Rect(0,0,75,75));
	//Gdiplus::SolidBrush sb2(Color(255,255,255));
	//gpp.FillEllipse(&sb2, Rect(1, 1, 75-2, 75-2));
	//gpp.Save();
	//ImageX::SaveAs(&test, filename, Bmp);

	//HBITMAP  bitmap = (HBITMAP) ::LoadImageA(GetModuleHandle(0), filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//HRGN hRGN = BitmapToRegion(bitmap, RGB(0,0,0), RGB(0,0,0));
	//SetWindowRgn(Hwnd(), hRGN, TRUE);//将创建的区域设定为窗口区域

	this->timer_ = new std::thread(&DesktopBar::timer, this);
}

void DesktopBar::onMouseActive(MouseEventArgs*e) {

	Form::onMouseActive(e);
	if (e->mouseType == MouseType::MouseDoubleClick) {
		msgBox("", "双击666");
	}

}
void DesktopBar::onPaint(PaintEventArgs * e)
{
	e->graphics->Opt();
	Form::onPaint(e);

	////背景圈
	//e->graphics->FillRect(Rect(0, 0, width(), height()), Color(200, 111, 175, 229));

	////内圈
	//Gdiplus::SolidBrush sb2(Color(255, 61, 153, 228));
	//e->graphics->FillEllipse(&sb2, Rect(4, 4, width() - 4 * 2, height() - 4 * 2));

	//////内圈边框
	////Gdiplus::Pen pen(Color(0, 0, 0));
	////e->graphics->DrawEllipse(&pen, Rect(0, 0, width(), height()));

	////画文字的
	//Gdiplus::FontFamily ff(L"Microsoft YaHei");
	//Gdiplus::Font f(&ff, 15);
	//Gdiplus::SolidBrush sbf(Color(255, 255, 200));
	//StringFormat sf;
	//sf.SetAlignment(GDIPLUS::StringAlignment::StringAlignmentCenter);
	//sf.SetLineAlignment(GDIPLUS::StringAlignment::StringAlignmentCenter);
	//std::wstring wtext = Text::ANSIToUniCode(std::to_string(value) + "%");
	//e->graphics->DrawString(wtext.c_str(), wtext.length(), &f, RectF(0, 1, width(), height()), &sf, &sbf);

}
