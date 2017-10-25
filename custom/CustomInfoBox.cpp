#include "CustomInfoBox.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>

#define BOX_X_MARGIN	30
#define BOX_Y_MARGIN	30
#define DEFAULT_PADDING	6
#define BTN_HEIGHT		32
#define BTN_WIDTH		32

CCustomInfoBox::CCustomInfoBox(QWidget* parent)
	: QWidget(parent)
	, lb_content_(new QLabel)
	, b_auto_close_(false)
	, b_multi_line_(false)
{
	//option
	option_.width = 320;
	option_.height = 32;

	//init
	init();
}

CCustomInfoBox::~CCustomInfoBox()
{

}

void CCustomInfoBox::show_infobox(const QString& content, QWidget* parent,
	EInfoBoxAnchor anchor, EInfoBoxType type)
{
	if (parent == Q_NULLPTR) return;

	CCustomInfoBox* box = new CCustomInfoBox;
	box->set_parent(parent);
	box->set_content(content);
	box->set_style(type, anchor);
	box->show();
}

void CCustomInfoBox::init()
{
	lb_content_->setScaledContents(true);
	lb_content_->setAttribute(Qt::WA_TransparentForMouseEvents, true);
	lb_content_->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(lb_content_);
	this->setLayout(layout);
	this->setFixedSize(option_.width, option_.height);
	this->setObjectName("box");
}

void CCustomInfoBox::set_parent(QWidget* parent)
{
	this->setParent(parent);
	parent->installEventFilter(this);
}

void CCustomInfoBox::set_content(const QString& content)
{
	QString str = content;
	QFont font = lb_content_->font();
	QFontMetrics metrics(font);
	int fontSize = metrics.width(content);

	if (fontSize > option_.width - DEFAULT_PADDING)
	{
		str = metrics.elidedText(
			content, Qt::ElideRight, option_.width - DEFAULT_PADDING * 2);
	}

	lb_content_->setText(str);
	lb_content_->setToolTip(content);
}

void CCustomInfoBox::set_style(EInfoBoxType type, EInfoBoxAnchor anchor)
{
	anchor_ = anchor;
	type_ = type;

	QString style = "\
		QLabel{ \
			color: black; \
			padding-left: 6px; \
			padding-right: 6px; \
		}";

	switch (type)
	{
	case EInfoBoxType::TYPE_ERROR:
		style += 
			"QWidget#box{background-color: #d9534f;border-color: #d43f3a;}";
		break;
	case EInfoBoxType::TYPE_INFO:
		style +=
			"QWidget#box{background-color: #5bc0de;border-color: #46b8da;}";
		break;
	case EInfoBoxType::TYPE_SUCCESS:
		style +=
			"QWidget#box{background-color: #5cb85c;border-color: #4cae4c;}";
		break;
	case EInfoBoxType::TYPE_WARNING:
		style +=
			"QWidget#box{background-color: #f0ad4e;border-color: #eea236;}";
		break;
		style +=
			"QWidget#box{background-color: #337ab7;border-color: #2e6da4;}";
		break;
	}
	this->setStyleSheet(style);
}

QPoint CCustomInfoBox::get_anchor_point(EInfoBoxAnchor anchor, QRect rect)
{
	QPoint pt;
	switch (anchor)
	{
	case EInfoBoxAnchor::ANCHOR_TOPLEFT:
		pt = QPoint(
			rect.topLeft().x() + BOX_X_MARGIN,
			rect.topLeft().y() + BOX_Y_MARGIN);
		break;
	case EInfoBoxAnchor::ANCHOR_TOPRIGHT:
		pt = QPoint(
			rect.topRight().x() - BOX_X_MARGIN - option_.width,
			rect.topRight().y() + BOX_Y_MARGIN);
		break;
	case EInfoBoxAnchor::ANCHOR_BOTTOMRIGHT:
		pt = QPoint(
			rect.bottomRight().x() - BOX_X_MARGIN - option_.width,
			rect.bottomRight().y() - BOX_Y_MARGIN - option_.height);
		break;
	case EInfoBoxAnchor::ANCHOR_BOTTOMLEFT:
		pt = QPoint(
			rect.bottomLeft().x() + BOX_X_MARGIN,
			rect.bottomLeft().y() - BOX_Y_MARGIN - option_.height);
		break;
	default:
		break;
	}

	return pt;
}

void CCustomInfoBox::paintEvent(QPaintEvent *event)
{
	return QWidget::paintEvent(event);
}

bool CCustomInfoBox::eventFilter(QObject *watched, QEvent *event)
{
	QWidget* obj = qobject_cast<QWidget*>(watched);
	if (obj == Q_NULLPTR || obj != parent())
	{
		return false;
	}

	if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
	{
		QPoint anchor_pt = get_anchor_point(anchor_, obj->rect());
		this->move(anchor_pt);
		return false;
	}

	return QWidget::eventFilter(watched, event);
}

void CCustomInfoBox::showEvent(QShowEvent *event)
{
	QWidget* parent = qobject_cast<QWidget*>(this->parent());
	if (parent == Q_NULLPTR)
		return;
	QPoint anchor_pt = get_anchor_point(anchor_, parent->rect());
	this->move(anchor_pt);
}

void CCustomInfoBox::mousePressEvent(QMouseEvent *event)
{
	if (event->type() == QMouseEvent::MouseButtonPress
		&& event->button() == Qt::LeftButton)
	{
		this->close();
		this->setParent(Q_NULLPTR);
		this->deleteLater();
	}
}