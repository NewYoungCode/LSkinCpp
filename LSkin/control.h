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
	
	//����
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
		//��ȡ�ؼ����뷽ʽ
		const AnchorStyle&	anchorStyle() const;
		//���ÿؼ����뷽ʽ
		void setAnchorStyle(const char & anchorStyle_right);
		//��ȡ����ͼƬ
		Bitmap *backgroundImage();
		//���ñ���ͼƬ
		void setBackgroundImage(Bitmap *bitmap);
		//��ȡǰ��ͼƬ
		Bitmap *foreImage();
		//����ǰ��ͼƬ
		void setForeImage(Bitmap *bitmap);
		//��ȡ����
		Gdiplus::Font* font();
		//��������
		void setFont(Gdiplus::Font *font);
		//��ȡ�Ƿ�����͸��
		bool transparent();
		//�����Ƿ�͸�� //�������û������
		void setTransparent(bool enable = true);
		//˫�����Ƿ���״̬
		bool doubleBuffered();
		//�����Ƿ���˫���� ���鿪������Ȼ��˸�ĺ�����
		void setDoubleBuffered(bool enable);
		//�������пؼ�����
		std::vector<Control*> controls();
		//��ӿؼ�
		virtual	void addControl(Control *control);
		//�Ƴ��ؼ�
		virtual	void removeControl(Control *control);
		//�����ӿؼ�
		void setChild(Control * parent);
		//���ø��ؼ�
		void setParent(Control * control);
		Control *parent();
		//���ô���&�ؼ��ı�����ɫ
		void setBackgroundColor(const Color &color);
		//�ػ洰��&�ؼ�
		void Invalidate();
		//��ȡ�ؼ�&���ڵı�����ɫ
		Color backgroundColor();
		//���������б�Ҫ������
		//��ȡ���ھ��
		HWND Hwnd();
		//�ô��ھ�����ʾ
		void setCenter();
		//ֱ����ʾ����
		virtual	void show(int ncmdShow = SW_SHOW);
		//���ش���
		virtual	void hide();
		//�رմ���
		void close();
		//����text
		virtual void setText(const std::string&str);
		//���ÿؼ�&��������
		void setLocation(const Point &point);
		void setLocation(int x, int y);
		//��ȡλ��
		Point location();
		//��ȡ����
		std::string text();
		//��ȡ��
		int width();
		//��ȡ��
		int height();
		//��ȡǰ��ɫ
		Color foreColor();
		//����ǰ��ɫ
		void setForeColor(const Color &color);
		Size size();
		//���ÿؼ�&���ڵĴ�С
		void setSize(const Size &size);
		void setSize(int width, int height);
		//��ȡ�ؼ��ľ�������
		virtual Rect rect();
		//���ÿؼ��ľ�������
		void setRect(const Rect&rect);
		//��ȡ���ֶ��뷽ʽ
		TextAlign textAlign();
		void setTextAlign(TextAlign  align);
		//��ȡ��Ǵ�С
		int radius();
		//������Ǵ�С
		void setRadius(int radius);
		//�¼���
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
		//Wndproc����ؼ�&���ڵ���Ϣ����
		virtual	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		HWND    hWnd = 0;
		bool _isForm = false;
	};
};
