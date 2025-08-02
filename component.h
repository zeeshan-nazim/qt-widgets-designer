#ifndef COMPONENT_H
#define COMPONENT_H

#include <QPoint>
#include <QColor>
#include <QPainter>
#include <QDebug>

#include <vector>
#include <functional>
#include "node.h"

typedef std::function<void()> Observer;

class Component
{
protected:
    QPoint start;
    QPoint end;
    QColor color;

    std::vector<Observer> observers;
public:
    Component(const QPoint &start)
        : start(start), end(start), color(Qt::black) {}
    virtual ~Component() = default;

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    virtual void display(QPainter *painter) = 0;
    virtual void update(const QPoint &p) = 0;
    virtual Component* inside(const QPoint &p) = 0;

    virtual Node* toNode() const = 0;

    QPoint getEnd() const { return end; }
    QPoint getStart() const { return start; }

    virtual void setColor(const QColor &col) = 0;
    virtual QColor getColor() const = 0;

    void attach(const Observer &obs) {
        observers.push_back(obs);
    }

    void notify() {
        for (size_t i = 0; i < observers.size(); ++i)
            observers[i]();
    }
};

#endif // COMPONENT_H
