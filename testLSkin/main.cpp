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

	//��Ϣѭ������
	Application app;
	//������
	DesktopBar mainForm;
	//��ť
	Button btn;
	btn.setText("��ť");
	btn.mouseClick = [](Control *sender, MouseEventArgs *e)->void {
		msgBox("���", "�����ma��");
	};
	mainForm.addControl(&btn);

	//��ť2
	Button btn2;
	btn2.setRect({ 300,300,100,80 });
	btn2.setRadius(80);//���
	btn2.setBackgroundColor(Color(255,100,255));
	mainForm.addControl(&btn2);
	btn2.setAnchorStyle(AnchorStyle::Right);//�Զ����ұ߶���

	//������
	Progressbar pb;
	pb.setRect({ 10,50,300,30 });
	pb.setMaxValue(100);
	pb.setValue(30);
	mainForm.addControl(&pb);
	//�ı������
	TextBox tb(&mainForm);
	tb.setRect({ 100,100,100,30 });
	tb.setText("���ڴ�����");


	mainForm.show();
	return app.exec();
}
