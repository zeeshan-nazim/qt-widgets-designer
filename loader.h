#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "node.h"

class Loader {
public:
    virtual ~Loader() = default;
    virtual bool load(const std::string& filename) = 0;
    virtual const Node* getRoot() const { return nullptr; }

protected:
    std::string redMsg = "\033[31m";
    std::string colorEnd = "\033[0m";
};

#endif // LOADER_H
