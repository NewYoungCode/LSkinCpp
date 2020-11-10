#pragma once
#include "control.h"
#include <vcruntime.h>
#include <exception>
namespace LSkin {


	Control::Control() {
		hWnd = CreateWindowA(className.c_str(), "Helo World", WS_POPUP,
			0, 0, 100, 30, 0, nullptr, 0, nullptr);
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)this);
		setBackgroundColor(_backgroundColor);
		Gdiplus::FontFamily ff(L"Microsoft YaHei");
		Gdiplus::Font *f = new Gdiplus::Font(&ff, 10);
		setFont(f);
	}
	Control::Control(const std::string& className)
	{
		hWnd = CreateWindowA(className.c_str(), "Helo World", WS_POPUP,
			0, 0, 100, 30, 0, nullptr, 0, nullptr);
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)this);
		setBackgroundColor(_backgroundColor);
		Gdiplus::FontFamily ff(L"Microsoft YaHei");
		Gdiplus::Font *f = new Gdiplus::Font(&ff, 10);
		setFont(f);
	}

	Control::Control(Control *parent)
	{
		parent->addControl(this);
	}
	Control::~Control() {

		Control *ct = parent();
		if (ct) {
			ct->removeControl(this);
		}
		if (_backImage) {
			delete _backImage;
			_backImage = 0;
		}
		if (_foreImage) {
			delete _foreImage;
			_foreImage = 0;
		}
		if (_font) {
			delete _font;
			_font = 0;
		}
		close();

	}
	int Control::x()
	{
		return rect().X;
	}
	int Control::y()
	{
		return rect().Y;
	}
	const AnchorStyle& Control::anchorStyle() const
	{
		return _anchorStle;
	}
	void Control::setAnchorStyle(const char & anchorStyle_right)
	{
		const AnchorStyle& anchorStyle = (AnchorStyle)anchorStyle_right;
		if (parent()) {
			Rect r = rect();
			Rect rp = parent()->rect();
			this->_anchorStle = anchorStyle;
			Rect 	parentRect = parent()->rect();
			bottom = parentRect.Height - this->y();
			right = parentRect.Width - this->x();
			marginRight = parentRect.Width - this->width();
			marginBottom = parentRect.Height - this->height();
		}
	}
	Bitmap * Control::backgroundImage()
	{
		return _backImage;
	}
	void Control::setBackgroundImage(Bitmap * bitmap)
	{
		_backImage = bitmap;
		Invalidate();
	}
	Bitmap * Control::foreImage()
	{
		return _foreImage;
	}
	void Control::setForeImage(Bitmap * bitmap)
	{
		_foreImage = bitmap;
		Invalidate();
	}
	Gdiplus::Font * Control::font()
	{
		return _font;
	}
	void Control::setFont(Gdiplus::Font * font)
	{
		_font = font;
		Invalidate();
	}
	bool Control::transparent()
	{
		return 	_transparent;
	}
	void Control::setTransparent(bool enable)
	{
		_transparent = enable;
		Invalidate();
	}
	bool Control::doubleBuffered()
	{
		return _doubleBuffered;
	}
	void Control::setDoubleBuffered(bool enable)
	{
		_doubleBuffered = enable;
	}
	std::vector<Control*> Control::controls()
	{
		return _controls;
	}
	void Control::addControl(Control *control)
	{
		if (control->Hwnd() == Hwnd()) {
			throw	std::exception("已经是顶级控件");
		}
		std::vector<Control*>::iterator it = find(_controls.begin(), _controls.end(), control);
		if (it == _controls.end()) { //先判断有没有这个元素 ==end()就是没有
			_controls.push_back(control);
			setChild(control);
			control->show();
		}
	}
	void Control::removeControl(Control  *control)
	{
		std::vector<Control*>::iterator item = find(_controls.begin(), _controls.end(), control);
		if (item != _controls.end()) {
			_controls.erase(item);
			control->close();
		}
	}
	Control* Control::parent() {
		return this->_parentControl;
	}
	void Control::setChild(Control *control) {
		//改变窗口风格 改为控件窗口
		SetWindowLong(control->Hwnd(), GWL_STYLE, WS_CHILD);
		::SetParent(control->Hwnd(), hWnd);
		control->setParent(this);
	}
	void Control::setParent(Control *parent) {
		::SetParent(hWnd, parent->Hwnd());
		_parentControl = parent;
	}
	void Control::setBackgroundColor(const Color &color) {
		//SetLayeredWindowAttributes(hWnd, color, bAlpha, LWA_ALPHA | LWA_COLORKEY);
		//GetClassLongW(hWnd, GCL_HBRBACKGROUND,)
		_backgroundColor = color;
		Invalidate();
	}
	void Control::Invalidate() {
		InvalidateRect(Hwnd(), NULL, true);
	}
	Color Control::backgroundColor()
	{
		return _backgroundColor;
	}
	HWND Control::Hwnd() {
		return hWnd;
	}
	void  Control::setCenter() {
		//RECT rect;
		if (_isForm) {
			Rect r = rect();
			//如果是窗口，获取屏幕宽高
			SIZE size = getScreenSize();
			int sw = size.cx;
			int sh = size.cy;
			setRect(Rect((sw - r.Width) / 2, (sh - r.Height) / 2, r.Width, r.Height));
		}
		else {
			Rect r = rect();
			//如果是窗口，获取屏幕宽高
			Rect pRect = parent()->rect();
			int sw = pRect.Width;
			int sh = pRect.Height;
			setRect(Rect((sw - r.Width) / 2, (sh - r.Height) / 2, r.Width, r.Height));
		}
	}
	void  Control::show(int ncmdShow) {
		UpdateWindow(hWnd);
		::ShowWindow(hWnd, ncmdShow);
	}
	void  Control::hide() {
		::ShowWindow(hWnd, SW_HIDE);
	}
	void Control::close()
	{
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	}

	void  Control::setText(const std::string &str) {
		::SetWindowTextA(hWnd, str.c_str());
		Invalidate();
	}
	void Control::setLocation(const Point & point)
	{
		setRect(Rect(point.X, point.Y, rect().Width, rect().Height));
	}
	void Control::setLocation(int x, int y) {
		setLocation({ x,y });
	}
	Point Control::location() {
		return { x(),y() };
	}

	std::string   Control::text() {
		CHAR buf[MAX_PATH];
		GetWindowTextA(hWnd, buf, MAX_PATH);
		return buf;
	}
	int Control::width()
	{
		return size().Width;
	}
	int Control::height()
	{
		return size().Height;
	}
	Color Control::foreColor()
	{
		return _foreColor;
	}
	void Control::setForeColor(const  Color & color)
	{
		_foreColor = color;
		Invalidate();
	}
	Size Control::size()
	{
		return { rect().Width,rect().Height };
	}
	void Control::setSize(const Size &size) {
		setRect(Rect(x(), y(), size.Width, size.Height));
	}
	void Control::setSize(int width, int height) {
		setSize({ width,height });
	}
	Rect Control::rect()
	{
		if (parent()) {
			RECT rect;
			GetWindowRect(Hwnd(), &rect);
			MapWindowPoints(NULL, parent()->Hwnd(), (LPPOINT)&rect, 2);
			return Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		}
		else {
			RECT rect;
			GetClientRect(Hwnd(), &rect);
			return Rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		}
	}
	void Control::setRect(const Rect &rect)
	{
		::MoveWindow(hWnd, rect.X, rect.Y, rect.Width, rect.Height, true);
	}
	void  Control::onPaint(PaintEventArgs *e) {
		int w = width();
		int h = height();
		Rect r(0, 0, w, h);
		e->graphics->FillRect(r, backgroundColor(), radius());
		if (backgroundImage()) {
			e->graphics->DrawImage(backgroundImage(), r);
		}
		if (foreImage()) {
			e->graphics->DrawImage(foreImage(), r);
		}
		std::string _text = text();
		if (!_text.empty()) {
			Gdiplus::SolidBrush sb(foreColor());
			StringFormat sf;
			sf.SetAlignment(GDIPLUS::StringAlignment::StringAlignmentCenter);
			sf.SetLineAlignment(GDIPLUS::StringAlignment::StringAlignmentCenter);
			std::wstring wtext = Text::ANSIToUniCode(_text);
			e->graphics->DrawString(wtext.c_str(), wtext.length(), font(), RectF(0, 0, w, h), &sf, &sb);
		}

		if (paint) {
			paint(this, e);
		}
	};
	TextAlign Control::textAlign() {
		return _align;
	}
	void Control::setTextAlign(TextAlign align) {
		_align = align;
		Invalidate();
	}
	int Control::radius()
	{
		return _radius;
	}
	void Control::setRadius(int radius)
	{
		_radius = radius;
		Invalidate();
	}
	void  Control::onWindowActiveEvent(WindowActiveEventArgs *e) {
		if (windowActiveEvent) {
			windowActiveEvent(this, e);
		}
	};
	void Control::parentWndProc(Control *p, UINT message, WPARAM wParam, LPARAM lParam) {
		if (message == WM_SIZE) {
			//左上保持 默认左上保持
			//下
			Rect pr = p->rect();
			Rect r = rect();
			if (anchorStyle() == AnchorStyle::Bottom) {
				this->setLocation(this->x(), p->height() - bottom);//保持下边距离
			}
			//上下
			if (anchorStyle() == (AnchorStyle::Top | AnchorStyle::Bottom)) {
				this->setSize(Size(width(), p->height() - marginBottom));//上下缩放
			}
			//右
			if (anchorStyle() == AnchorStyle::Right) {
				this->setLocation(p->width() - right, this->y());//保持右边距离
			}
			//左右
			if (anchorStyle() == (AnchorStyle::Left | AnchorStyle::Right)) {
				this->setSize(Size(p->width() - marginRight, height()));//左右缩放
			}
			//上下左右
			if (anchorStyle() == (AnchorStyle::Top | AnchorStyle::Bottom | AnchorStyle::Left | AnchorStyle::Right)) {
				this->setSize(Size(p->width() - marginRight, height()));//左右缩放
				this->setSize(Size(width(), p->height() - marginBottom));//上下缩放
			}
			//其他组合
			//右上
			if (anchorStyle() == (AnchorStyle::Top | AnchorStyle::Right)) {
				this->setLocation(p->width() - right, this->y());//保持右边距离
			}
			//右下
			if (anchorStyle() == (AnchorStyle::Bottom | AnchorStyle::Right)) {
				this->setLocation(p->width() - right, this->y());//保持右边距离
				this->setLocation(this->x(), p->height() - bottom);//保持下边距离
			}
			//左下
			if (anchorStyle() == (AnchorStyle::Bottom | AnchorStyle::Left)) {
				this->setLocation(this->x(), p->height() - bottom);//保持下边距离
			}
			//上下左
			if (anchorStyle() == (AnchorStyle::Top | AnchorStyle::Bottom | AnchorStyle::Left)) {
				this->setSize(Size(width(), p->height() - marginBottom));//上下缩放
			}
			//上下右
			if (anchorStyle() == (AnchorStyle::Top | AnchorStyle::Bottom | AnchorStyle::Left)) {
				this->setSize(Size(width(), p->height() - marginBottom));//上下缩放
				this->setLocation(p->width() - right, this->y());//保持右边距离
			}
			//左右上
			if (anchorStyle() == (AnchorStyle::Left | AnchorStyle::Right | AnchorStyle::Top)) {
				this->setSize(Size(p->width() - marginRight, height()));//左右缩放
			}
			//左右下
			if (anchorStyle() == (AnchorStyle::Left | AnchorStyle::Right | AnchorStyle::Bottom)) {
				this->setSize(Size(p->width() - marginRight, height()));//左右缩放
				this->setLocation(this->x(), p->height() - bottom);//保持下边距离
			}
		}
	}
	void  Control::onMouseActive(MouseEventArgs *e) {
		if (mouseActive) {
			mouseActive(this, e);
		}
	}
	void Control::onMouseClick(MouseEventArgs * e)
	{
		if (mouseClick) {
			mouseClick(this, e);
		}
	};
	void  Control::onKeyboardActive(KeyboardEventArgs *e) {
		if (keyboardActive) {
			keyboardActive(this, e);
		}
	};
	LRESULT CALLBACK Control::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

		std::vector<Control*> controls = this->controls();
		for (size_t i = 0; i < controls.size(); i++)
		{
			if (controls[i] != NULL && controls[i]->Hwnd() != 0) {
				controls[i]->parentWndProc(this, message, wParam, lParam);
			}
		}
		switch (message)
		{
			//销毁窗口前发
		case WM_CLOSE:
		{
			WindowActiveEventArgs args;
			args.msgCode = WM_CLOSE;
			onWindowActiveEvent(&args);
			if (args.Cancel) {
				return NULL;
			}
			DestroyWindow(hwnd);
			break;
		}
		//销毁窗口
		case WM_DESTROY:
		{
			//如果窗口销毁,就将子窗口全部销毁
			for (size_t i = 0; i < controls.size(); i++)
			{
				if (controls[i]->Hwnd()) {
					DestroyWindow(controls[i]->Hwnd());
				}
			}
			break;
		}
		//鼠标双击
		case WM_LBUTTONDBLCLK: {
			MouseEventArgs args;
			args.mouseType = MouseType::MouseDoubleClick;
			args.mouseButton = MouseButton::LeftButton;
			args.msgCode = WM_LBUTTONDOWN;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
			break;
		}

							   //左边按钮按下
		case WM_LBUTTONDOWN:
		{
			MouseEventArgs args;

			args.mouseType = MouseType::MouseDown;
			args.mouseButton = MouseButton::LeftButton;

			args.msgCode = WM_LBUTTONDOWN;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
			break;
		}


		//左边按钮放开
		case WM_LBUTTONUP:
		{
			MouseEventArgs args;
			args.mouseType = MouseType::MouveUp;
			args.mouseButton = MouseButton::LeftButton;
			args.msgCode = WM_LBUTTONUP;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
		}
		//右边按钮按下
		case WM_RBUTTONDOWN:
		{
			MouseEventArgs args;

			args.mouseType = MouseType::MouseDown;
			args.mouseButton = MouseButton::RightButton;

			args.msgCode = WM_RBUTTONDOWN;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
		}
		//右边按钮放开
		case WM_RBUTTONUP:
		{
			MouseEventArgs args;

			args.mouseType = MouseType::MouveUp;
			args.mouseButton = MouseButton::RightButton;

			args.msgCode = WM_RBUTTONUP;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
		}

		//鼠标点击
		case BM_CLICK: {
			MouseEventArgs args;

			args.mouseType = MouseType::MouseClick;
			args.mouseButton = MouseButton::LeftButton;

			args.msgCode = BM_CLICK;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseClick(&args);
			break;
		}
					   //鼠标移动
		case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			tme.hwndTrack = hWnd;
			TrackMouseEvent(&tme);

			MouseEventArgs args;

			args.mouseType = MouseType::MouseMove;
			args.mouseButton = MouseButton::None;
			args.msgCode = WM_MOUSEMOVE;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);

			if (_mouseIn == false) {
				_mouseIn = true;
				args.mouseType = MouseType::MouseEnter;


				onMouseActive(&args);
			}
			break;
		}

		//鼠标停留
		case WM_MOUSEHOVER:
		{
			MouseEventArgs args;

			args.mouseType = MouseType::MouseHover;
			args.mouseButton = MouseButton::None;

			args.msgCode = WM_MOUSEHOVER;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
			break;
		}

		//鼠标移出
		case WM_MOUSELEAVE:
		{
			_mouseIn = false;

			MouseEventArgs args;

			args.mouseType = MouseType::MouveLeave;
			args.mouseButton = MouseButton::None;

			args.msgCode = WM_MOUSELEAVE;
			args.point = Point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			onMouseActive(&args);
			break;
		}

		//鼠标滚轮
		case WM_MOUSEWHEEL:
		{
			MouseEventArgs args;

			args.mouseType = MouseType::None;
			args.mouseButton = MouseButton::None;

			args.msgCode = WM_MOUSEWHEEL;
			onMouseActive(&args);
			break;
		}
		case WM_ERASEBKGND: {
			//如果支持透明
			if (transparent()) {
				return true;
			}
		}
		case WM_PAINT:
		{
			PAINTSTRUCT pst;
			HDC hdc = BeginPaint(hwnd, &pst);
			//从dc画布中创建绘图类
			Graphics gp(hdc);
			if (doubleBuffered()) {
				//申请一块内存中的画布
				Bitmap temp(width(),height());
				//从内存画布中创建绘图类
				Graphics gptemp(&temp);
				//参数
				PaintEventArgs args;
				args.graphics = &gptemp;
				//交给虚函数去绘图
				onPaint(&args);
				//绘图完成之后将内存中的画布贴到DC上
				gp.DrawImage(&temp, Rect(0, 0, width(), height()));
				//结束绘图
				EndPaint(hwnd, &pst);
				break;
			}
			PaintEventArgs args;
			args.graphics = &gp;
			args.pst = pst;
			args.hdc = hdc;
			onPaint(&args);
			EndPaint(hwnd, &pst);
			break;
		}
		case WM_SIZE: {

			WindowActiveEventArgs args;
			args.msgCode = WM_SIZE;
			onWindowActiveEvent(&args);
			break;
		}
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
