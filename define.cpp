#include "define.h"

int Environment::get(const std::string& var) {
    if (variables.find(var) != variables.end()) {
        return variables[var];
    } else {
        throw std::invalid_argument("Variable no definida");
    }
}

void Environment::set(const std::string& var, int value) {
    variables[var] = value;
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        throw std::invalid_argument("División por cero indefinida");
    }
}