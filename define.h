#ifndef DEFINE_H
#define DEFINE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

class Environment {
    std::unordered_map<std::string, int> variables;

public:
    int get(const std::string& var);
    void set(const std::string& var, int value);
};

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

#endif