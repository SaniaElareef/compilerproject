#include <iostream>
#include <string>
#include <sstream>

// Node types for the Abstract Syntax Tree (AST)
enum class NodeType {
    BINARY_OP,
    NUMBER
};

// Node structure for the AST
struct Node {
    NodeType type;
    std::string value;
    Node* left;
    Node* right;
};

class CodeGenerator {
public:
    static std::string generateCode(Node* node) {
        if (node->type == NodeType::NUMBER) {
            return node->value;
        } else if (node->type == NodeType::BINARY_OP) {
            std::stringstream code;
            code << "(" << generateCode(node->left) << " " << node->value << " " << generateCode(node->right) << ")";
            return code.str();
        } else {
            std::cerr << "Error: Invalid node encountered!" << std::endl;
            exit(1);
        }
    }
};

int main() {
    // Construct an abstract syntax tree (AST) representing the expression: 3 + 5 * 2 - 10 / 2
    Node* three = new Node{ NodeType::NUMBER, "3", nullptr, nullptr };
    Node* five = new Node{ NodeType::NUMBER, "5", nullptr, nullptr };
    Node* two = new Node{ NodeType::NUMBER, "2", nullptr, nullptr };
    Node* ten = new Node{ NodeType::NUMBER, "10", nullptr, nullptr };

    Node* multiply = new Node{ NodeType::BINARY_OP, "*", nullptr, nullptr };
    multiply->left = five;
    multiply->right = two;

    Node* divide = new Node{ NodeType::BINARY_OP, "/", nullptr, nullptr };
    divide->left = ten;
    divide->right = new Node{ NodeType::NUMBER, "2", nullptr, nullptr };

    Node* add = new Node{ NodeType::BINARY_OP, "+", nullptr, nullptr };
    add->left = three;
    add->right = multiply;

    Node* subtract = new Node{ NodeType::BINARY_OP, "-", nullptr, nullptr };
    subtract->left = add;
    subtract->right = divide;

    // Generate code from the AST
    std::string generatedCode = CodeGenerator::generateCode(subtract);
    std::cout << "Generated code: " << generatedCode << std::endl;

    // Clean up memory (not shown in full)
    // Add your own code to properly deallocate the dynamically allocated nodes

    return 0;
}
