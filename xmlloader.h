#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "loader.h"
#include "node.h"

enum TagType { NONE, START_TAG, END_TAG, SELF_CLOSING };

class XMLLoader : public Loader {
private:
    Node* root;

public:
    XMLLoader();
    ~XMLLoader();

    bool load(const std::string& filename) override;
    TagType tagName(const std::string& line, std::string& name, std::map<std::string, std::string>& attrs);

    const Node* getRoot() const override;
};

#endif // XMLLOADER_H
