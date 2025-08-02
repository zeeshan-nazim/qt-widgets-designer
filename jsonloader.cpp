#include "jsonloader.h"
#include <QColor>

JSONLoader::JSONLoader() : root(nullptr) {}

JSONLoader::~JSONLoader() {
    delete root;
}

bool JSONLoader::load(const std::string& filename) {
    std::cout << redMsg;

    QFile file(QString::fromStdString(filename));
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << colorEnd << std::endl;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Fehler beim Parsen: " << parseError.errorString().toStdString() << colorEnd << std::endl;
        return false;
    }

    if (!doc.isObject()) {
        std::cerr << "Ungültiges JSON-Format." << colorEnd << std::endl;
        return false;
    }

    delete root;
    root = parseNode(doc.object());

    std::cout << colorEnd;
    if (root) {
        root->printNode(std::cout, 0, FILETYPE_JSON, false);
    }

    return root != nullptr;
}

Node* JSONLoader::parseNode(const QJsonObject& obj) {
    if (!obj.contains("type")) return nullptr;

    QString type = obj["type"].toString();
    Node* node = new Node(type.toStdString());

    // Farbwert sicher casten (QColor::fromRgb erwartet uint)
    if (obj.contains("color")) {
        int signedRgb = obj["color"].toInt();
        QColor c = QColor::fromRgb(static_cast<uint>(signedRgb));
        node->setAttribute("color", QString::number(c.rgb()).toStdString());
    }

    if (obj.contains("startPos")) {
        QJsonObject pos = obj["startPos"].toObject();
        int x = pos["x"].toInt();
        int y = pos["y"].toInt();
        node->setAttribute("startPos", QString("%1,%2").arg(x).arg(y).toStdString());
    }

    if (obj.contains("endPos")) {
        QJsonObject pos = obj["endPos"].toObject();
        int x = pos["x"].toInt();
        int y = pos["y"].toInt();
        node->setAttribute("endPos", QString("%1,%2").arg(x).arg(y).toStdString());
    }

    if (obj.contains("children")) {
        QJsonArray arr = obj["children"].toArray();
        for (int i = 0; i < arr.size(); ++i) {
            QJsonObject childObj = arr[i].toObject();
            Node* child = parseNode(childObj);
            if (child) {
                node->addChild(child);
            }
        }
    }

    return node;
}

const Node* JSONLoader::getRoot() const {
    return root;
}
