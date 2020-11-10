#pragma once
#define GDIPLUS
#ifdef GDIPLUS //如果使用GDI+
#include <comdef.h>
#include <gdiplus.h>
//#include <gdiplusheaders.h>
#include <gdipluspath.h>
#pragma comment(lib, "gdiplus.lib")

#define OutPut
#define InPut

//定义已存在的类型
typedef Gdiplus::Color Color;
typedef Gdiplus::Rect Rect;
typedef Gdiplus::Bitmap Bitmap;
typedef Gdiplus::Point Point;
typedef Gdiplus::PointF PointF;
typedef Gdiplus::Image Image;
typedef Gdiplus::Size Size;
typedef Gdiplus::RectF RectF;
typedef Gdiplus::StringFormat StringFormat;
typedef Gdiplus::StringAlignment StringAlignment;

//自定义类申明
typedef class PaddingX {

public:
	int Left = 0;
	int Top = 0;
	int Right = 0;
	int Bottom = 0;
	PaddingX() {
	}
	inline PaddingX(int left, int top, int right, int bottom);
} Padding;
typedef class GraphicsX :public Gdiplus::Graphics
{
private:
	inline Gdiplus::GraphicsPath* getRoundPath(Rect &rect, int radius);
public:
	GraphicsX(HWND hWnd, int icm = 0) :Graphics(hWnd, icm) {
	}
	GraphicsX(HDC hdc) :Graphics(hdc) {
		Opt();
	};
	GraphicsX(Image *image) :Graphics(image) {
		Opt();
	};
	//这是动态分配的，一定要释放
	inline	Gdiplus::GraphicsPath*  BuildRectPath(Rect &rec, int radius);
	//画一个矩形 可以锐角
	inline void DrawRect(Rect &rect, Color &color, int radius = 0);
	//画一个矩形 可以锐角
	inline void FillRect(Rect &rect, Color &color, int radius = 0);
	//优化显示效果
	inline void Opt();
}Graphics;

//自定义类函数体
PaddingX::PaddingX(int left, int top, int right, int bottom) {
	Left = left;
	Top = top;
	Right = right;
	Bottom = bottom;
}
Gdiplus::GraphicsPath*  GraphicsX::getRoundPath(Rect &rect, int radius) {
	int diameter = radius;
	Rect arcRect(Point(rect.X, rect.Y), Size(diameter, diameter));

	Gdiplus::GraphicsPath *path = new Gdiplus::GraphicsPath;
	//左上角      
	path->AddArc(arcRect, 180, 90);
	//右上角      
	arcRect.X = rect.GetRight() - diameter;
	path->AddArc(arcRect, 270, 90);
	//右下角      
	arcRect.Y = rect.GetBottom() - diameter;
	path->AddArc(arcRect, 0, 90);
	//左下角      
	arcRect.X = rect.GetLeft();
	path->AddArc(arcRect, 90, 90);
	path->CloseAllFigures();
	return path;
};
Gdiplus::GraphicsPath*  GraphicsX::BuildRectPath(Rect &rec, int radius)
{
	int width = rec.Width;
	int height = rec.Height;
	if (width < height && radius > width) radius = width;
	if (height < width && radius > height) radius = height;
	int x = rec.X;
	int y = rec.Y;

	Gdiplus::GraphicsPath *gpp = new Gdiplus::GraphicsPath;
	if (radius <= 0)
	{
		gpp->AddRectangle(rec);
		gpp->CloseAllFigures();
		return gpp;
	}
	if (width == height && radius * 2 >= width)
	{
		gpp->AddEllipse(rec);
		gpp->CloseAllFigures();
		return gpp;
	}
	if (!(width == height) || (width == height && radius * 2 <= width))
	{
		delete gpp; //这里不会使用他;
		return  getRoundPath(rec, radius);
	}
	return gpp;
};
void GraphicsX::DrawRect(Rect &rect, Color &color, int radius) {
	Gdiplus::GraphicsPath *gp = BuildRectPath(rect, radius);
	Gdiplus::Pen pen(Color(color), 1);
	DrawPath(&pen, gp);
	delete gp;
};
void GraphicsX::FillRect(Rect &rect, Color &color, int radius) {
	Gdiplus::GraphicsPath *gp = BuildRectPath(rect, radius);
	Gdiplus::SolidBrush sb(color);
	FillPath(&sb, gp);
	delete gp;
};
void GraphicsX::Opt() {
	SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeHighQuality);
	SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHalf);
	SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintClearTypeGridFit);
	SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeHighQualityBicubic);
}
class PaintConnector
{
public:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput = 0;
	ULONG_PTR _m_gdiplusToken = 0;
	//初始化GDI+
	void Init(HWND hWnd = 0) {
		//初始化GDI+
		Gdiplus::GdiplusStartup(&_m_gdiplusToken, &gdiplusStartupInput, NULL);
	}
	//释放GDI+
	~PaintConnector() {
		if (_m_gdiplusToken) {
			Gdiplus::GdiplusShutdown(_m_gdiplusToken);
		}
	}
};
enum TextAlign
{
	MiddleCenter = 0x001,
	TopLeft = 0x002
};
namespace DrawTool {
	//矩形转换
	inline static RectF ConvertRectF(RectF rectf, Padding padd)
	{
		RectF recX = rectf;
		if (padd.Top != 0)
		{
			recX.Y -= padd.Top;
			recX.Height += padd.Top;
		}
		if (padd.Right != 0)
		{
			recX.Width += padd.Right;
		}
		if (padd.Bottom != 0)
		{
			recX.Height += padd.Bottom;
		}
		if (padd.Left != 0)
		{
			recX.X -= padd.Left;
			recX.Width += padd.Left;
		}
		return recX;
	};
	//矩形转换
	inline static Rect ConvertRect(Rect rectf, Padding padd)
	{
		Rect recX = rectf;
		if (padd.Top != 0)
		{
			recX.Y -= padd.Top;
			recX.Height += padd.Top;
		}
		if (padd.Right != 0)
		{
			recX.Width += padd.Right;
		}
		if (padd.Bottom != 0)
		{
			recX.Height += padd.Bottom;
		}
		if (padd.Left != 0)
		{
			recX.X -= padd.Left;
			recX.Width += padd.Left;
		}
		return recX;
	};
	//颜色转换变深或者变浅 
	inline static Color ConvertColor(Color color, float rate)
	{
		byte r = (color.GetR() * rate);
		byte g = (color.GetG() * rate);
		byte b = (color.GetB() * rate);
		byte a = color.GetA();
		if (rate > 1)
		{
			return Color(a < 255 ? a : 255, r > 255 ? 255 : r, g > 255 ? 255 : g, b > 255 ? 255 : b);
		}
		else
		{
			return Color(a < 255 ? a : 255, r < 0 ? 0 : r, g < 0 ? 0 : g, b < 0 ? 0 : b);
		}
	}

	//获取对齐方式 新的方式
	inline static  void  GetStringFormat(TextAlign align, OutPut StringFormat* sf) {
		//中间
		if (TextAlign::MiddleCenter == align) {
			sf->SetAlignment(StringAlignment::StringAlignmentCenter);
			sf->SetLineAlignment(StringAlignment::StringAlignmentCenter);
		}
		//左上
		if (TextAlign::TopLeft == align) {
			sf->SetAlignment(StringAlignment::StringAlignmentNear);
			sf->SetLineAlignment(StringAlignment::StringAlignmentNear);
		}
	};
};
#endif
