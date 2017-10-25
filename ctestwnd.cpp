#include "ctestwnd.h"
#include "custom/CustomInfoBox.h"

CTestWnd::CTestWnd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btn_topleft, &QPushButton::clicked, this, [this]()->void {
		CCustomInfoBox::Info(
			" CCustomInfoBox Info MessageCCustomInfoBox Info MessageCCustomInfoBox Info Message", 
			this,
			CCustomInfoBox::ANCHOR_TOPLEFT);
	});

	connect(ui.btn_bottomleft, &QPushButton::clicked, this, [this]()->void {
		CCustomInfoBox::Warning(
			"CCustomInfoBox Warning Message", 
			this,
			CCustomInfoBox::ANCHOR_BOTTOMLEFT);
	});

	connect(ui.btn_topright, &QPushButton::clicked, this, [this]()->void {
		CCustomInfoBox::Success(
			"CCustomInfoBox Success Message", 
			this,
			CCustomInfoBox::ANCHOR_TOPRIGHT);
	});

	connect(ui.btn_bottomright, &QPushButton::clicked, this, [this]()->void {
		CCustomInfoBox::Error(
			"CCustomInfoBox Error Message", 
			this,
			CCustomInfoBox::ANCHOR_BOTTOMRIGHT);
	});
}
