#include "ctestwnd.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CTestWnd w;
	w.show();
	return a.exec();
}
