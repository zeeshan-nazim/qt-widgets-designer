#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "loader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class JSONLoader : public Loader {
private:
    Node* root;
    Node* parseNode(const QJsonObject& obj);

public:
    JSONLoader();
    ~JSONLoader();
    bool load(const std::string& filename) override;
    const Node* getRoot() const override;
};

#endif // JSONLOADER_H
