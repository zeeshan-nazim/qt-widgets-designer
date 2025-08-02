#ifndef CSVLOADER_H
#define CSVLOADER_H

#include "loader.h"
#include "node.h"

class CSVLoader : public Loader {
private:
    Node* root;

public:
    CSVLoader();
    ~CSVLoader();

    bool load(const std::string& filename) override;
    const Node* getRoot() const override;
};

#endif // CSVLOADER_H
