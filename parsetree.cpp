#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
    Node(const string& v, Node* l = nullptr, Node* r = nullptr)
        : value(v), left(l), right(r) {}
};

vector<string> tokenize(const string& expr) {
    vector<string> tokens;
    string current;
    for (char c : expr) {
        if (isspace(c)) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else if (isdigit(c)) {
            current += c;
        } else {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
            tokens.push_back(string(1, c));
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }
    return tokens;
}

class Parser {
    vector<string> tokens;
    size_t pos;

public:
    Parser(const vector<string>& t) : tokens(t), pos(0) {}

    Node* parse() {
        return E();
    }

private:
    string peek() {
        return (pos < tokens.size()) ? tokens[pos] : "";
    }

    void consume() {
        if (pos < tokens.size()) pos++;
    }

    Node* E() {
        Node* left = T();
        return E_prime(left);
    }

    Node* E_prime(Node* left) {
        string op = peek();
        if (op == "+" || op == "-") {
            consume();
            Node* right = T();
            Node* new_node = new Node(op, left, right);
            return E_prime(new_node);
        }
        return left;
    }

    Node* T() {
        Node* left = F();
        return T_prime(left);
    }

    Node* T_prime(Node* left) {
        string op = peek();
        if (op == "*" || op == "/") {
            consume();
            Node* right = F();
            Node* new_node = new Node(op, left, right);
            return T_prime(new_node);
        }
        return left;
    }

    Node* F() {
        string tok = peek();
        if (tok == "(") {
            consume();
            Node* expr = E();
            if (peek() != ")") {
                cerr << "Error: Expected ')'\n";
                exit(1);
            }
            consume();
            return expr;
        } else if (!tok.empty() && isdigit(tok[0])) {
            consume();
            return new Node(tok);
        } else {
            cerr << "Error: Unexpected token '" << tok << "'\n";
            exit(1);
        }
    }
};

void printUprightTree(Node* root, int space = 0, int indent = 5) {
    if (root == nullptr) return;

    space += indent;

    // print right child first (on top)
    printUprightTree(root->right, space);

    // print current node after spaces
    cout << setw(space) << root->value << endl;

    // then print left child
    printUprightTree(root->left, space);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);

    vector<string> tokens = tokenize(expr);
    Parser parser(tokens);
    Node* root = nullptr;

    try {
        root = parser.parse();
    } catch (...) {
        cerr << "Parsing failed due to syntax errors.\n";
        return 1;
    }

    cout << "\nSyntax Tree (Upright):\n";
    printUprightTree(root);

    deleteTree(root);
    return 0;
}
