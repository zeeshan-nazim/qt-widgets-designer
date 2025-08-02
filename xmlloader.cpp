#include "xmlloader.h"
#include "Stack.h"
#include "InvalidOperationException.h"

XMLLoader::XMLLoader() : root(nullptr) {}

XMLLoader::~XMLLoader() {
    delete root;
}

bool XMLLoader::load(const std::string& filename) {
    std::cout << redMsg;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Fehler: Datei konnte nicht geöffnet werden." << colorEnd << std::endl;
        return false;
    }

    Stack stack;
    std::vector<Node*> nodeStack;

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        std::string tagNameString;
        std::map<std::string, std::string> attrs;
        TagType type = tagName(line, tagNameString, attrs);

        if (type == START_TAG) {
            Node* newNode = new Node(tagNameString);

            for (std::map<std::string, std::string>::iterator it = attrs.begin(); it != attrs.end(); ++it) {
                newNode->setAttribute(it->first, it->second);
            }

            if (nodeStack.empty()) {
                root = newNode;
            } else {
                nodeStack.back()->addChild(newNode);
            }

            nodeStack.push_back(newNode);
            stack.push(tagNameString);
        }
        else if (type == SELF_CLOSING) {
            Node* newNode = new Node(tagNameString);

            for (std::map<std::string, std::string>::iterator it = attrs.begin(); it != attrs.end(); ++it) {
                newNode->setAttribute(it->first, it->second);
            }

            if (nodeStack.empty()) {
                root = newNode;
            } else {
                nodeStack.back()->addChild(newNode);
            }

        }
        else if (type == END_TAG) {
            try {
                std::string top = stack.pop();
                if (top != tagNameString) {
                    std::cerr << "Fehler in Zeile " << lineNumber << ": "
                              << "End-Tag </" << tagNameString << "> passt nicht zu <" << top << ">" << colorEnd << std::endl;
                    delete root;  // Baum löschen
                    root = nullptr;
                    return false;
                }
            } catch (const InvalidOperationException& ex) {
                std::cerr << "Fehler in Zeile " << lineNumber << ": " << ex.what() << colorEnd << std::endl;
                delete root;
                root = nullptr;
                return false;
            }

            if (!nodeStack.empty()) {
                nodeStack.pop_back();
            } else {
                std::cerr << "Fehler: End-Tag ohne passenden Start-Tag." << colorEnd << std::endl;
                delete root;
                root = nullptr;
                return false;
            }
        }


    }

    if (!stack.empty()) {
        std::cerr << "Fehler: Es sind noch Tags offen!" << colorEnd << std::endl;
        delete root;
        root = nullptr;
        return false;
    }

    file.close();
    std::cout << colorEnd;
    if (root) {
        root->printNode(std::cout, 0, FILETYPE_XML, false);
    }
    return true;
}

TagType XMLLoader::tagName(const std::string& line, std::string& name, std::map<std::string, std::string> &attrs) {
    name = "";
    attrs.clear();

    size_t start = line.find('<');
    size_t end = line.find('>');
    if (start == std::string::npos || end == std::string::npos || start > end) return NONE;

    std::string tag = line.substr(start + 1, end - start - 1);
    if (tag.empty() || tag[0] == '?' || tag[0] == '!') return NONE;

    bool isEndTag = false;
    bool isSelfClosing = false;

    // Detect self-closing by trailing '/'
    if (!tag.empty() && tag.back() == '/') {
        isSelfClosing = true;
        tag = tag.substr(0, tag.size() - 1);
    }

    // Detect end tag
    if (tag[0] == '/') {
        isEndTag = true;
        tag = tag.substr(1);
    }

    // Extract name and attributes
    size_t space = tag.find(' ');
    if (space != std::string::npos) {
        name = tag.substr(0, space);
        std::string attrString = tag.substr(space + 1);

        size_t pos = 0;
        while (pos < attrString.length()) {
            while (pos < attrString.length() && isspace(attrString[pos])) ++pos;
            size_t equalPos = attrString.find('=', pos);
            if (equalPos == std::string::npos) break;

            std::string attrName = attrString.substr(pos, equalPos - pos);
            attrName.erase(attrName.find_last_not_of(" \t\n\r") + 1);

            pos = equalPos + 1;
            if (attrString[pos] == '\"') {
                ++pos;
                size_t quoteEnd = attrString.find('\"', pos);
                if (quoteEnd == std::string::npos) break;

                std::string attrValue = attrString.substr(pos, quoteEnd - pos);
                attrs[attrName] = attrValue;
                pos = quoteEnd + 1;
            } else break;
        }
    } else {
        name = tag;
    }

    if (isSelfClosing) return SELF_CLOSING;
    if (isEndTag) return END_TAG;
    return START_TAG;
}

const Node* XMLLoader::getRoot() const {
    return root;
}
