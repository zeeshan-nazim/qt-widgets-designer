#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>

class Stack {
private:
    std::vector<std::string> elements;

public:
    void push(const std::string& element);
    std::string pop();
    bool empty() const;
};

#endif // STACK_H

