#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include "canvas.h"

Canvas::Canvas(QWidget *parent)
    : QFrame(parent)
{
	setFrameStyle(QFrame::Box);
	setMouseTracking(true);

	type = NONE;
    design = true;
    dragging = false;

    root = new Container(QPoint(0, 0));
    root->setColor(Qt::white);
    root->update(QPoint(width(), height()));
}

Canvas::~Canvas()
{
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::clearCanvas()
{
    delete root;
    root = new Container(QPoint(0, 0));
    root->setColor(Qt::white);
    root->update(QPoint(width(), height()));
    update();
}

void Canvas::setWidgetMode(int mode)
{
    type = (Canvas::WidgetMode)mode;

    if (type != NONE) {
        // TODO; if no "widget" root node is set, create one
    }
}

void Canvas::setInteractionMode(bool mode)
{
    design = mode;
}

void Canvas::setObjColor(const QColor &col)
{
    activeCol = col;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);

    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);

    if (root) {
        root->display(&painter);
    }

    if (design && current != nullptr) {
        current->display(&painter);
    }
}

void Canvas::resizeEvent(QResizeEvent *event) 
{
	QFrame::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint currPos = event->pos();
        dragging = true;
        lastPos = currPos;

        if (design) {
            if (type == BUTTON) {
                current = new Button(currPos);
            } else if (type == CONTAINER) {
                current = new Container(currPos);
            }

            if (current) {
                current->setColor(activeCol);
            }
        }

        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && dragging) {
        QPoint currPos = event->pos();

        if (design && current) {
            current->update(currPos);
        }
        lastPos = currPos;
		update();
	}
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging) {
        QPoint currPos = event->pos();
        dragging = false;

        if (design && current) {
            current->update(currPos);

            Component* target = nullptr;
            if (root) {
                target = root->inside(current->getStart());
            }

            Container* parent = dynamic_cast<Container*>(target);

            QPoint start = current->getStart();
            QPoint end = current->getEnd();
            int width = abs(end.x() - start.x());
            int height = abs(end.y() - start.y());

            if (width < 10 || height < 10) {
                delete current;
            }
            else if (parent) {
                parent->add(current);

                Button* btn = dynamic_cast<Button*>(current);
                if (btn) {
                    addEventListener(btn);
                }
            } else {
                delete current;
            }

            current = nullptr;
        }

        else if (!design) {
            Component* clicked = root->inside(currPos);
            Button* btn = dynamic_cast<Button*>(clicked);
            if (btn) {
                btn->notify();
            }
        }

        lastPos = currPos;
        update();
    }
}

Node* Canvas::buildNodeTree() const {
    if (root)
        return root->toNode();
    return nullptr;
}

void Canvas::loadFromNodeTree(const Node* node)
{
    if (!node) return;

    delete root;
    root = new Container(QPoint(0, 0));
    root->setColor(Qt::white);

    loadRecursively(root, node);

    root->update(QPoint(width(), height()));

    update();
}

void Canvas::loadRecursively(Container* parent, const Node* node)
{
    if (!parent || !node) return;

    std::vector<Node*> children = node->getChildren();

    for (size_t i = 0; i < children.size(); ++i) {
        const Node* childNode = children[i];

        QString tag = QString::fromStdString(childNode->getTagName());

        QPoint start(0, 0), end(0, 0);
        QColor color = Qt::lightGray;

        std::map<std::string, std::string> attrs = childNode->getAttributesMap();

        if (attrs.find("startPos") != attrs.end()) {
            sscanf(attrs["startPos"].c_str(), "%d,%d", &start.rx(), &start.ry());
        }
        if (attrs.find("endPos") != attrs.end()) {
            sscanf(attrs["endPos"].c_str(), "%d,%d", &end.rx(), &end.ry());
        }
        if (attrs.find("color") != attrs.end()) {
            bool ok;
            uint rgb = QString::fromStdString(attrs["color"]).toUInt(&ok);
            if (ok) color = QColor::fromRgb(rgb);
        }

        Component* c = nullptr;

        if (tag == "Button") {
            Button* btn = new Button(start);
            btn->setColor(color);
            btn->update(end);
            c = btn;
        } else if (tag == "Container") {
            Container* cont = new Container(start);
            cont->setColor(color);
            cont->update(end);
            loadRecursively(cont, childNode);
            c = cont;
        }

        if (c != nullptr) {
            parent->add(c);
        }
    }
}

void Canvas::addEventListener(Button *btn) {
    if (btn) {
        btn->attach([btn]() {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Information");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Ein Button wurde geklickt.");
            msgBox.exec();
        });
    }
}
