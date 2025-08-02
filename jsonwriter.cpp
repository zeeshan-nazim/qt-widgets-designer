#include "jsonwriter.h"

JSONWriter::JSONWriter() {}

bool JSONWriter::write(const std::string& filename, const Node* root) {
    if (!root) return false;

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "\033[31mFehler beim Öffnen der Datei " << filename << "\033[0m" << std::endl;
        return false;
    }

    QJsonObject jsonRoot = writeNode(root);
    QJsonDocument doc(jsonRoot);

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

QJsonObject JSONWriter::writeNode(const Node* node) {
    QJsonObject json;

    json["type"] = QString::fromStdString(node->getTagName());

    auto attrs = node->getAttributesMap();

    if (attrs.find("color") != attrs.end()) {
        json["color"] = static_cast<int>(QString::fromStdString(attrs["color"]).toUInt());
    }

    if (attrs.find("startPos") != attrs.end()) {
        int x = 0, y = 0;
        sscanf(attrs["startPos"].c_str(), "%d,%d", &x, &y);
        QJsonObject startPos;
        startPos["x"] = x;
        startPos["y"] = y;
        json["startPos"] = startPos;
    }

    if (attrs.find("endPos") != attrs.end()) {
        int x = 0, y = 0;
        sscanf(attrs["endPos"].c_str(), "%d,%d", &x, &y);
        QJsonObject endPos;
        endPos["x"] = x;
        endPos["y"] = y;
        json["endPos"] = endPos;
    }

    std::vector<Node*> children = node->getChildren();
    if (!children.empty()) {
        QJsonArray jsonChildren;
        for (size_t i = 0; i < children.size(); ++i) {
            jsonChildren.append(writeNode(children[i]));
        }
        json["children"] = jsonChildren;
    }

    return json;
}
