#pragma once

#include <QtWidgets/QWidget>
#include "ui_ctestwnd.h"

class CTestWnd : public QWidget
{
	Q_OBJECT

public:
	CTestWnd(QWidget *parent = Q_NULLPTR);

private:
	Ui::CTestWndClass ui;
};
