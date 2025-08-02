#ifndef BUTTON_H
#define BUTTON_H

#include "component.h"

class Button : public Component
{
private:
    QString text;
public:
    Button(const QPoint &start);
    ~Button() override = default;

    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    void display(QPainter *painter) override;
    void update(const QPoint &p) override;
    Component* inside(const QPoint &p) override;

    Node* toNode() const override;

    void setColor(const QColor &col) override;
    QColor getColor() const override;

    void setText(const QString &t);
    QString getText() const;
};

#endif // BUTTON_H
