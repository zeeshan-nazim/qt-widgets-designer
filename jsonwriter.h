#ifndef JSONWRITER_H
#define JSONWRITER_H

#include "writer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

class JSONWriter : public Writer {
public:
    JSONWriter();
    bool write(const std::string& filename, const Node* root) override;

private:
    QJsonObject writeNode(const Node* node);
};

#endif // JSONWRITER_H
