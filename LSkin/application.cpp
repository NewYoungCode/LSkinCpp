#include "application.h"
#include "control.h"
namespace LSkin {
	int runningTotal = 0;
	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
		LONG objPtr = GetWindowLongPtr(hwnd, GWL_USERDATA);
		if (objPtr) {
			LSkin::Control *ptr = (LSkin::Control*)objPtr;
			//����ʵ������ȥ�����������������
			return 	ptr->WndProc(hwnd, message, wParam, lParam);
		}
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	Application::Application()
	{  
		_paintConnector = new PaintConnector();
		_paintConnector->Init();
		if (!LSkin::regClass) {
			//��ƴ���
			HINSTANCE hInstance = GetModuleHandle(0);
			WNDCLASS     wc;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC | CS_SAVEBITS;
			wc.lpfnWndProc = WndProc;
			wc.cbClsExtra = NULL;
			wc.cbWndExtra = NULL;
			wc.hInstance = hInstance;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = LSkin::className.c_str();
			if (!RegisterClassA(&wc)) //ע�ᴰ��
			{
				MessageBoxA(NULL, ("This program requires Windows NT!"),
					wc.lpszClassName, MB_ICONERROR);
				return;
			}
			LSkin::regClass = true;
		}
	}
	Application::~Application()
	{
		if (_paintConnector) {
			delete _paintConnector;
		}
	}
	int Application::exec()
	{
		{
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0) != 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			return msg.wParam;
		}
	}
	void Application::exit()
	{
		PostQuitMessage(0);
	}
}