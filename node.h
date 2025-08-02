#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

enum FileType { FILETYPE_NONE, FILETYPE_XML, FILETYPE_JSON, FILETYPE_CSV };

class Node {
private:
    std::string tagName;
    std::vector<Node*> children;
    std::map<std::string, std::string> attributes;

public:
    Node(const std::string& name);
    ~Node();

    void addChild(Node* child);
    void removeChild(Node* child);
    void printNode(std::ostream& out, int level, FileType type, bool skipKey) const;

    void setAttribute(const std::string &name, const std::string& value);
    void removeAttribute(const std::string &name);
    bool hasAttribute(const std::string &name) const;
    std::string getAttribute(const std::string &name) const;

    void printAttributes(std::ostream& out, int level = 0) const;

    std::string getTagName() const;
    std::vector<Node*> getChildren() const;
    std::vector<std::pair<std::string, std::string>> getAttributes() const;

    void setTagName(const std::string &name);

    std::map<std::string, std::string> getAttributesMap() const;
};

#endif // NODE_H
