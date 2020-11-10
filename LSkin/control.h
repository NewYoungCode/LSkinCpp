#pragma once
#include "common.hpp"
#pragma once
#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <vector>
#include <functional>
#include "paintconnector.h"
#include <iostream>
#include <stdio.h>
#include<Dwmapi.h>
#include "application.h"
#pragma comment(lib, "dwmapi")

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


namespace  LSkin {
	
	//基类
	class export Control{
	private:
		std::vector<Control*> _controls;
		MSG      _msg;
		Control *_parentControl = 0;
		Gdiplus::Font *_font = 0;
		Color _backgroundColor = Color(41, 44, 44);
		bool _doubleBuffered = true;
		Color	_foreColor = Color(254, 254, 254);
		TextAlign _align = TextAlign::MiddleCenter;
		int _radius = 0;
		bool _transparent = true;
		Bitmap *_backImage = 0;
		Bitmap *_foreImage = 0;
		AnchorStyle _anchorStle = (AnchorStyle)(AnchorStyle::Top | AnchorStyle::Left);
		int right = 0;
		int bottom = 0;
		int marginRight = 0;
		int marginBottom = 0;
		bool _mouseIn = false;
	public:
		void* Tag = 0;
		Control();
		Control(Control*parent);
		Control(const std::string& className);
		~Control();
		int x();
		int y();
		//获取控件对齐方式
		const AnchorStyle&	anchorStyle() const;
		//设置控件对齐方式
		void setAnchorStyle(const char & anchorStyle_right);
		//获取背景图片
		Bitmap *backgroundImage();
		//设置背景图片
		void setBackgroundImage(Bitmap *bitmap);
		//获取前景图片
		Bitmap *foreImage();
		//设置前景图片
		void setForeImage(Bitmap *bitmap);
		//获取字体
		Gdiplus::Font* font();
		//设置字体
		void setFont(Gdiplus::Font *font);
		//获取是否开启了透明
		bool transparent();
		//设置是否透明 //窗口设置会出问题
		void setTransparent(bool enable = true);
		//双缓冲是否开启状态
		bool doubleBuffered();
		//设置是否开启双缓冲 建议开启，不然闪烁的很厉害
		void setDoubleBuffered(bool enable);
		//返回所有控件集合
		std::vector<Control*> controls();
		//添加控件
		virtual	void addControl(Control *control);
		//移除控件
		virtual	void removeControl(Control *control);
		//设置子控件
		void setChild(Control * parent);
		//设置父控件
		void setParent(Control * control);
		Control *parent();
		//设置窗口&控件的背景颜色
		void setBackgroundColor(const Color &color);
		//重绘窗口&控件
		void Invalidate();
		//获取控件&窗口的背景颜色
		Color backgroundColor();
		//用来保存有必要的数据
		//获取窗口句柄
		HWND Hwnd();
		//让窗口居中显示
		void setCenter();
		//直接显示窗口
		virtual	void show(int ncmdShow = SW_SHOW);
		//隐藏窗口
		virtual	void hide();
		//关闭窗口
		void close();
		//设置text
		virtual void setText(const std::string&str);
		//设置控件&窗口坐标
		void setLocation(const Point &point);
		void setLocation(int x, int y);
		//获取位置
		Point location();
		//获取文字
		std::string text();
		//获取宽
		int width();
		//获取高
		int height();
		//获取前景色
		Color foreColor();
		//设置前景色
		void setForeColor(const Color &color);
		Size size();
		//设置控件&窗口的大小
		void setSize(const Size &size);
		void setSize(int width, int height);
		//获取控件的矩形区域
		virtual Rect rect();
		//设置控件的矩形区域
		void setRect(const Rect&rect);
		//获取文字对齐方式
		TextAlign textAlign();
		void setTextAlign(TextAlign  align);
		//获取锐角大小
		int radius();
		//设置锐角大小
		void setRadius(int radius);
		//事件绑定
		std::function<void(Control *sender, PaintEventArgs *e)> paint = NULL;
		std::function<void(Control *sender, WindowActiveEventArgs *e)> windowActiveEvent = NULL;
		std::function<void(Control *sender, MouseEventArgs *e)> mouseActive = NULL;
		std::function<void(Control *sender, MouseEventArgs *e)> mouseClick = NULL;
		std::function<void(Control *sender, KeyboardEventArgs *e)> keyboardActive = NULL;
		virtual	void onPaint(PaintEventArgs *e);
		virtual	void onWindowActiveEvent(WindowActiveEventArgs *e);
		void parentWndProc(Control * p, UINT message, WPARAM wParam, LPARAM lParam);
		virtual	void onMouseActive(MouseEventArgs *e);
		virtual	void onMouseClick(MouseEventArgs *e);
		virtual	void onKeyboardActive(KeyboardEventArgs *e);
		//Wndproc处理控件&窗口的消息函数
		virtual	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		HWND    hWnd = 0;
		bool _isForm = false;
	};
};
