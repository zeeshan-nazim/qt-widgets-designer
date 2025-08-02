#include "csvloader.h"
#include <fstream>
#include <iostream>
#include <sstream>

CSVLoader::CSVLoader() : root(nullptr) {}

CSVLoader::~CSVLoader() {
    delete root;
}

bool CSVLoader::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << redMsg << "Fehler beim Öffnen der Datei: " << filename << colorEnd << std::endl;
        return false;
    }

    delete root;
    root = new Node("Container");

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false; // Skip header
            continue;
        }

        std::stringstream ss(line);
        std::string type, color, startX, startY, endX, endY;

        std::getline(ss, type, ',');
        std::getline(ss, color, ',');
        std::getline(ss, startX, ',');
        std::getline(ss, startY, ',');
        std::getline(ss, endX, ',');
        std::getline(ss, endY, ',');

        Node* child = new Node(type);
        child->setAttribute("color", color);
        child->setAttribute("startPos", startX + "," + startY);
        child->setAttribute("endPos", endX + "," + endY);

        root->addChild(child);
    }

    file.close();
    if (root) {
        std::cout << "[DEBUG] Geladene Struktur:\n";
        root->printNode(std::cout, 0, FILETYPE_XML, false);
    }
    return true;
}

const Node* CSVLoader::getRoot() const {
    return root;
}
