#pragma once
#include <string>
#include <Windows.h>
#include <comdef.h>
#include <D2D1.h>
#include <dwrite.h>
#include <Unknwnbase.h>
#pragma comment(lib,"D2D1.lib")
#pragma comment(lib,"Dwrite.lib")
typedef  D2D1_RECT_F RectF;
typedef D2D1::ColorF ColorF;
#include <Text.hpp>
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
class  Painter
{
public:
	ID2D1Factory*d2d_factory = NULL;
	IDWriteFactory*d2d_writeFactory = NULL;
	ID2D1Factory* CreateFactory() {
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);//参数1.单线程 、第二个参数用来接收创建的工厂
		return d2d_factory;
	}
	IDWriteFactory* CreateDWriteFactory() {
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&d2d_writeFactory)
		);
		return d2d_writeFactory;
	}
	void Init() {
		CreateFactory();
		CreateDWriteFactory();
	}
	void CleanUp() {
		SAFE_RELEASE(d2d_factory);
		SAFE_RELEASE(d2d_writeFactory);
	}
private:
	HWND hWnd = 0;
	ID2D1HwndRenderTarget* render = NULL;
public:

	Painter(HWND hwnd);

	void ClearBackground(const ColorF & color);

	void DrawRectangle(const ColorF & color, const RectF & rectf, float penWidth);

	void DrawString(const std::string & text, const std::string & fontFamilyName, const RectF & rectf, const ColorF & color, float fontSize);

	~Painter();

};
