#include "Painter.h"
Painter::Painter(HWND hwnd) {
	Init();
	hWnd = hwnd;
	RECT rc;
	// ��������
	GetClientRect(hWnd, &rc);
	d2d_factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),//����һ��Render target���ԣ�������Ⱦģʽ�����ظ�ʽ��DPI�ȣ�D2D�ṩ��һ������D2D1::RenderTargetProperties()��������������Ĭ�ϵ�����
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &render);
	render->BeginDraw();//��ʼ�滭
}
void Painter::ClearBackground(const ColorF&color) {
	render->Clear(color);
}
void Painter::DrawRectangle(const ColorF&color, const RectF&rectf, float penWidth = 1.0f) {
	//������ˢ 
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
	render->EndDraw();//�����滭
	CleanUp();
	SAFE_RELEASE(render);

}