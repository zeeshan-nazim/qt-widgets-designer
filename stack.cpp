#include "stack.h"
#include "InvalidOperationException.h"

void Stack::push(const std::string& element) {
    elements.push_back(element);
}

std::string Stack::pop() {
    if (elements.empty()) {
        throw InvalidOperationException("Stack ist leer – pop() nicht möglich!");
    }
    std::string top = elements.back();
    elements.pop_back();
    return top;
}

bool Stack::empty() const {
    return elements.empty();
}
