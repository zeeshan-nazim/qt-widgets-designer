#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <fstream>
#include "node.h"

class Writer {
public:
    virtual ~Writer() {}
    virtual bool write(const std::string& filename, const Node* root) = 0;
};

#endif // WRITER_H
