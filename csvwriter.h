    #ifndef CSVWRITER_H
    #define CSVWRITER_H

    #include "writer.h"

    class CSVWriter : public Writer {
    public:
        CSVWriter();
        bool write(const std::string& filename, const Node* root) override;

    private:
        void writeNode(std::ofstream& out, const Node* node);
    };

    #endif // CSVWRITER_H
