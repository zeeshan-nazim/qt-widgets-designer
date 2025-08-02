#include "csvwriter.h"

CSVWriter::CSVWriter() {}

bool CSVWriter::write(const std::string& filename, const Node* root) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei " << filename << std::endl;
        return false;
    }

    // CSV Header
    out << "type,color,startPosX,startPosY,endPosX,endPosY\n";
    writeNode(out, root);
    out.close();
    return true;
}

void CSVWriter::writeNode(std::ofstream& out, const Node* node) {
    if (!node) return;

    std::string tag = node->getTagName();
    std::string color = node->getAttribute("color");
    std::string startPos = node->getAttribute("startPos");
    std::string endPos = node->getAttribute("endPos");

    int startX = 0, startY = 0;
    int endX = 0, endY = 0;

    if (!startPos.empty()) {
        sscanf(startPos.c_str(), "%d,%d", &startX, &startY);
    }
    if (!endPos.empty()) {
        sscanf(endPos.c_str(), "%d,%d", &endX, &endY);
    }

    out << tag << "," << color << ","
        << startX << "," << startY << ","
        << endX << "," << endY << "\n";

    std::vector<Node*> children = node->getChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        writeNode(out, children[i]);
    }
}
