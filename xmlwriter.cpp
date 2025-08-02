#include "xmlwriter.h"

XMLWriter::XMLWriter() {}

bool XMLWriter::write(const std::string &filename, const Node *root) {
    std::ofstream out(filename);
    if(!out.is_open()){
        std::cerr << "Fehler beim Öffnen der Datei " << filename << std::endl;
        return false;
    }

    writeNode(out, root, 0);
    out.close();
    return true;
}

void XMLWriter::writeNode(std::ofstream &out, const Node *node, int indent){
    std::string ind(indent, ' ');

    out << ind << "<" << node->getTagName();

    std::vector<std::pair<std::string, std::string>> attrs = node->getAttributes();
    for (size_t i = 0; i < attrs.size(); i++) {
        out << " " << attrs[i].first << "=\"" << attrs[i].second << "\"";
    }

    std::vector<Node*> children = node->getChildren();
    if (children.empty()) {
        out << " />\n";
    } else {
        out << ">\n";
        for (size_t i = 0; i < children.size(); i++) {
            writeNode(out, children[i], indent + 2);
        }
        out << ind << "</" << node->getTagName() << ">\n";
    }
}
