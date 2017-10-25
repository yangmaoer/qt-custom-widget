#ifndef CCUSTOMINFOBOX_H_
#define CCUSTOMINFOBOX_H_

#include <QWidget>

class QLabel;

class CCustomInfoBox : public QWidget
{
public:
	enum EInfoBoxAnchor {
		ANCHOR_TOPLEFT,
		ANCHOR_TOPRIGHT,
		ANCHOR_BOTTOMLEFT,
		ANCHOR_BOTTOMRIGHT
	};

	struct InfoBoxOption {
		int		width;
		int		height;
		int		font_size;
		//TODO
	};

	//static
	static void Info(
		const QString&	content,
		QWidget*		parent,
		EInfoBoxAnchor	anchor = CCustomInfoBox::ANCHOR_BOTTOMRIGHT) {
		show_infobox(content, parent, anchor, EInfoBoxType::TYPE_INFO);
	}

	static void Success(
		const QString&	content,
		QWidget*		parent,
		EInfoBoxAnchor	anchor = CCustomInfoBox::ANCHOR_BOTTOMRIGHT) {
		show_infobox(content, parent, anchor, EInfoBoxType::TYPE_SUCCESS);
	}

	static void Error(
		const QString&	content,
		QWidget*		parent,
		EInfoBoxAnchor	anchor = CCustomInfoBox::ANCHOR_BOTTOMRIGHT) {
		show_infobox(content, parent, anchor, EInfoBoxType::TYPE_ERROR);
	}

	static void Warning(
		const QString&	content,
		QWidget*		parent,
		EInfoBoxAnchor	anchor = CCustomInfoBox::ANCHOR_BOTTOMRIGHT) {
		show_infobox(content, parent, anchor, EInfoBoxType::TYPE_WARNING);
	}

protected:
	enum EInfoBoxType {
		TYPE_INFO,
		TYPE_WARNING,
		TYPE_ERROR,
		TYPE_SUCCESS
	};
	explicit CCustomInfoBox(QWidget* parent = Q_NULLPTR);
	~CCustomInfoBox();

	static void show_infobox(const QString&	content, QWidget* parent,
		EInfoBoxAnchor anchor, EInfoBoxType type);

	void init();
	void set_parent(QWidget* parent);
	void set_content(const QString& content);
	void set_style(EInfoBoxType type, EInfoBoxAnchor anchor);

	QPoint get_anchor_point(EInfoBoxAnchor anchor, QRect rect);

	//implementation
	bool eventFilter(QObject *watched, QEvent *event);
	void paintEvent(QPaintEvent *event);
	void showEvent(QShowEvent *event);
	void mousePressEvent(QMouseEvent *event);

private:
	QLabel*			lb_content_;
	bool			b_auto_close_;
	bool			b_multi_line_;
	EInfoBoxAnchor	anchor_;
	EInfoBoxType	type_;
	InfoBoxOption	option_;
};

#endif //CCUSTOMINFOBOX_H_