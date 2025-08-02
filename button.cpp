#include "button.h"

Button::Button(const QPoint &start)
    : Component(start) {
    text = "Button";
}

void Button::display(QPainter *painter) {
    painter->setPen(color);
    QRect rect(start, end);
    painter->drawRect(rect.normalized());

    painter->drawText(rect, Qt::AlignCenter, "Button");
}

void Button::update(const QPoint &p) {
    end = p;
}

Component* Button::inside(const QPoint &p) {
    QRect rect(start, end);
    if (rect.normalized().contains(p)) return this;
    return nullptr;
}

Node* Button::toNode() const {
    Node* node = new Node("Button");

    std::string startStr = std::to_string(start.x()) + "," + std::to_string(start.y());
    std::string endStr = std::to_string(end.x()) + "," + std::to_string(end.y());

    node->setAttribute("startPos", startStr);
    node->setAttribute("endPos", endStr);
    node->setAttribute("color", std::to_string(color.rgb()));

    return node;
}

void Button::setColor(const QColor &col) {
    this->color = col;
}

QColor Button::getColor() const {
    return color;
}

void Button::setText(const QString &t) {
    text = t;
}

QString Button::getText() const {
    return text;
}
