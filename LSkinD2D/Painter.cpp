#include "Painter.h"
Painter::Painter(HWND hwnd) {
	Init();
	hWnd = hwnd;
	RECT rc;
	// 创建画家
	GetClientRect(hWnd, &rc);
	d2d_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),//参数一是Render target属性，包括渲染模式，象素格式，DPI等，D2D提供了一个函数D2D1::RenderTargetProperties()，可以用来生成默认的属性
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &render);
	render->BeginDraw();//开始绘画
}
void Painter::ClearBackground(const ColorF&color) {
	render->Clear(color);
}
void Painter::DrawRectangle(const ColorF&color, const RectF&rectf, float penWidth = 1.0f) {
	//创建画刷 
	ID2D1SolidColorBrush* brush = NULL;
	render->CreateSolidColorBrush(color, &brush);
	render->DrawRectangle(rectf, brush, penWidth);
	SAFE_RELEASE(brush);
}
void Painter::DrawString(const std::string&text, const std::string&fontFamilyName, const RectF &rectf, const ColorF&color, float fontSize) {
	IDWriteTextFormat *pTextFormat_ = NULL;
	d2d_writeFactory->CreateTextFormat(
		Text::ANSIToUniCode(fontFamilyName).c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"zh-cn",
		&pTextFormat_
	);
	ID2D1SolidColorBrush* brush = NULL;
	render->CreateSolidColorBrush(color, &brush);

	std::wstring wstr = Text::ANSIToUniCode(text);
	render->DrawText(wstr.c_str(), wstr.size(), pTextFormat_, rectf, brush);
	SAFE_RELEASE(pTextFormat_);
}
Painter::~Painter() {
	render->EndDraw();//结束绘画
	CleanUp();
	SAFE_RELEASE(render);

}