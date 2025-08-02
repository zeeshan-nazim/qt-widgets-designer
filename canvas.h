#ifndef CANVAS_H
#define CANVAS_H
#include <QFrame>
#include <QPoint>
#include <QColor>

#include "component.h"
#include "container.h"
#include "button.h"

class Canvas : public QFrame
{
	Q_OBJECT

public:
    enum WidgetMode { NONE, BUTTON, CONTAINER };

	Canvas(QWidget *parent = 0);
	~Canvas();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void clearCanvas(void);
    void setWidgetMode(int mode);
    void setInteractionMode(bool mode);
    void setObjColor(const QColor &col);

    Node* buildNodeTree() const;

    void loadFromNodeTree(const Node* node);
    void loadRecursively(Container* parent, const Node* node);

    void addEventListener(Button *btn);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);



private:
    bool dragging;
    QPoint lastPos;
    QColor activeCol;
    bool design;
    WidgetMode type;

    Component* current = nullptr;
    Container* root = nullptr;
};

#endif // CANVAS_H
