#include "node.h"
#include <iostream>

Node::Node(const std::string& name) : tagName(name) {}

Node::~Node() {
    for (size_t i = 0; i < children.size(); ++i) {
        delete children[i];
    }
}

void Node::addChild(Node* child) {
    children.push_back(child);
}

void Node::removeChild(Node *child) {
    for (int i = 0; i < children.size(); ++i) {
        if(children[i] == child){
            delete children[i];
            children.erase(children.begin() + 1);
            }
    }
}

void Node::printNode(std::ostream& out, int level, FileType type, bool skipKey) const {
    std::string indent(level, ' ');

    if (type == FILETYPE_XML || type == FILETYPE_NONE) {
        out << indent << "<" << tagName;
        printAttributes(out, level);

        if (children.empty()) {
            out << " />" << std::endl;
        } else {
            out << ">" << std::endl;
            for (size_t i = 0; i < children.size(); ++i) {
                children[i]->printNode(out, level + 1, type, false);
            }
            out << indent << "</" << tagName << ">" << std::endl;
        }
        return;
    }

    // ✅ JSON bleibt unverändert:
    if (type == FILETYPE_JSON) {
        if (!skipKey) {
            out << indent << "\"" << tagName << "\": ";
        }

        bool hasAttributes = !attributes.empty();
        bool hasChildren = !children.empty();

        if (!hasAttributes && !hasChildren) {
            out << "{}";
            return;
        }

        out << "{\n";

        // 1. Attribute
        size_t attrCount = 0;
        for (auto it = attributes.begin(); it != attributes.end(); ++it) {
            out << indent << "  \"" << it->first << "\": \"" << it->second << "\"";
            if (++attrCount < attributes.size() || hasChildren) out << ",";
            out << "\n";
        }

        // 2. Kinder gruppieren
        std::map<std::string, std::vector<Node*>> grouped;
        for (size_t i = 0; i < children.size(); ++i) {
            grouped[children[i]->tagName].push_back(children[i]);
        }

        size_t groupCount = 0;
        for (auto it = grouped.begin(); it != grouped.end(); ++it) {
            const std::string& groupTag = it->first;
            const std::vector<Node*>& groupNodes = it->second;

            out << indent << "  \"" << groupTag << "\": ";

            if (groupNodes.size() > 1) {
                out << "[\n";
                for (size_t i = 0; i < groupNodes.size(); ++i) {
                    groupNodes[i]->printNode(out, level + 6, type, true);
                    if (i < groupNodes.size() - 1) out << ",";
                    out << "\n";
                }
                out << indent << "  ]";
            } else {
                groupNodes[0]->printNode(out, level + 4, type, true);
            }

            if (++groupCount < grouped.size()) out << ",";
            out << "\n";
        }

        out << indent << "}";
    }
}


void Node::setAttribute(const std::string& name, const std::string& value) {
    attributes[name] = value;   //Bsp. <person id="42"> wird so gespeichert attributes[id] = "42";
}


void Node::removeAttribute(const std::string& name) {
    attributes.erase(name);
}


bool Node::hasAttribute(const std::string& name) const{
    return attributes.find(name) != attributes.end();
}

std::string Node::getAttribute(const std::string &name) const {
    auto it = attributes.find(name);
    if (it != attributes.end()) {
        return it->second;
    }
    return "";
}

void Node::printAttributes(std::ostream& out, int level) const {
    std::map<std::string, std::string>::const_iterator it;
    for (it = attributes.begin(); it != attributes.end(); ++it) {
        out << " " << it->first << "=\"" << it->second << "\"";
    }
}

std::string Node::getTagName() const {
    return tagName;
}

std::vector<Node*> Node::getChildren() const {
    return children;
}

std::vector<std::pair<std::string, std::string>> Node::getAttributes() const {
    std::vector<std::pair<std::string, std::string>> result;
    for (std::map<std::string, std::string>::const_iterator it = attributes.begin(); it != attributes.end(); ++it) {
        result.push_back(std::make_pair(it->first, it->second));
    }
    return result;
}

void Node::setTagName(const std::string &name) {
    tagName = name;
}

std::map<std::string, std::string> Node::getAttributesMap() const {
    return attributes;
}