#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "writer.h"

class XMLWriter : public Writer
{
private:
    void writeNode(std::ofstream &out, const Node *node, int indent);
public:
    XMLWriter();
    bool write(const std::string &filename, const Node *root) override;
};

#endif // XMLWRITER_H
