#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include "define.h"

typedef std::vector<std::string> Tokens;

Environment env;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    for (const auto& token : tokens) {
        if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(add(a, b));
        } else if (token == "*") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(multiply(a, b));
        } else {
            try {
                stack.push(std::stoi(token));
            } catch (const std::invalid_argument&) {
                stack.push(env.get(token));
            }
        }
    }

    return stack.top();
}

int main() {


    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    std::cout << evaluate(tokens) << std::endl;
    return 0;
}
