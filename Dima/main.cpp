#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <unordered_map>

typedef std::vector<std::string> Tokens;

// Definición de un mapa para almacenar las funciones definidas por el usuario
std::unordered_map<std::string, Tokens> userFunctions;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluate(Tokens& tokens, std::unordered_map<std::string, int>& variables) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (userFunctions.find(token) != userFunctions.end()) {
            // Token es una función definida por el usuario, evaluemos la función.
            Tokens functionTokens = userFunctions[token];
            evaluate(functionTokens, variables);
        } else if (token == "+") {
            if (stack.size() < 2) {
                std::cerr << "Error: Operador '+' necesita al menos 2 operandos en la pila." << std::endl;
                return 0;
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "*") {
            if (stack.size() < 2) {
                std::cerr << "Error: Operador '*' necesita al menos 2 operandos en la pila." << std::endl;
                return 0;
            }
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            stack.push(a * b);
        } else if (token == "def") {
            // Definición de una función por el usuario
            if (tokens.size() < 3) {
                std::cerr << "Error: Declaración de función incompleta." << std::endl;
                return 0;
            }
            std::string functionName = tokens.back();
            tokens.pop_back();
            std::string parameter1 = tokens.back();
            tokens.pop_back();
            std::string parameter2 = tokens.back();
            tokens.pop_back();

            // Almacenar la definición de la función en el mapa
            userFunctions[functionName] = tokens;
        } else if (variables.find(token) != variables.end()) {
            stack.push(variables[token]);
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    Tokens tokens = tokenize(input);
    std::unordered_map<std::string, int> variables;

    int result = evaluate(tokens, variables);
    std::cout << "Resultado: " << result << std::endl;
    return 0;
}
