#include <Windows.h>
#include "DesktopBar.h"
#include "../LSkin/button.h"
#include "../LSkin/progressbar.h"
#include "../LSkin/textbox.h"
int _stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	using namespace LSkin;

	//消息循环对象
	Application app;
	//主窗口
	DesktopBar mainForm;
	//按钮
	Button btn;
	btn.setText("按钮");
	btn.mouseClick = [](Control *sender, MouseEventArgs *e)->void {
		msgBox("点击", "你点你ma呢");
	};
	mainForm.addControl(&btn);

	//按钮2
	Button btn2;
	btn2.setRect({ 300,300,100,80 });
	btn2.setRadius(80);//锐角
	btn2.setBackgroundColor(Color(255,100,255));
	mainForm.addControl(&btn2);
	btn2.setAnchorStyle(AnchorStyle::Right);//自动向右边对齐

	//进度条
	Progressbar pb;
	pb.setRect({ 10,50,300,30 });
	pb.setMaxValue(100);
	pb.setValue(30);
	mainForm.addControl(&pb);
	//文本输入框
	TextBox tb(&mainForm);
	tb.setRect({ 100,100,100,30 });
	tb.setText("请在此输入");


	mainForm.show();
	return app.exec();
}
