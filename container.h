#ifndef CONTAINER_H
#define CONTAINER_H

#include "component.h"

class Container : public Component
{
private:
    std::vector<Component*> children;
public:
    Container(const QPoint &start);
    ~Container() override = default;

    Container(const Container&) = delete;
    Container& operator=(const Container&) = delete;

    void display(QPainter *painter) override;
    void update(const QPoint &p) override;
    Component* inside(const QPoint &p) override;
    void add(Component* c);

    Node* toNode() const override;

    void setColor(const QColor &col) override;
    QColor getColor() const override;
};

#endif // CONTAINER_H
