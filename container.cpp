#include "container.h"

Container::Container(const QPoint &start)
    : Component(start) {
}

void Container::display(QPainter *painter) {
    painter->setPen(Qt::gray);
    painter->setBrush(color);

    QRect rect(start, end);
    painter->drawRect(rect.normalized());

    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i]) {
            children[i]->display(painter);
        }
    }

    painter->setBrush(Qt::NoBrush);
}

void Container::update(const QPoint &p) {
    end = p;
}

Component* Container::inside(const QPoint &p) {
    for (int i = children.size() - 1; i >= 0; --i) {
        Component* c = children[i]->inside(p);
        if (c != nullptr) return c;
    }

    QRect rect(start, end);
    if (rect.normalized().contains(p)) return this;

    return nullptr;
}

void Container::add(Component* c) {
    if (c == nullptr) {
        return;
    }

    children.push_back(c);

    QPoint childEnd = c->getEnd();
    QPoint myEnd = this->getEnd();

    if (childEnd.x() > myEnd.x() || childEnd.y() > myEnd.y()) {
        QPoint newEnd(
            std::max(myEnd.x(), childEnd.x()),
            std::max(myEnd.y(), childEnd.y())
            );
        this->update(newEnd);
    }
}

Node* Container::toNode() const {
    Node* node = new Node("Container");

    std::string startStr = std::to_string(start.x()) + "," + std::to_string(start.y());
    std::string endStr = std::to_string(end.x()) + "," + std::to_string(end.y());

    node->setAttribute("startPos", startStr);
    node->setAttribute("endPos", endStr);
    node->setAttribute("color", std::to_string(color.rgb()));

    for (int i = 0; i < children.size(); ++i) {
        node->addChild(children[i]->toNode());
    }

    return node;
}

void Container::setColor(const QColor &col) {
    this->color = col;
}

QColor Container::getColor() const {
    return color;
}
