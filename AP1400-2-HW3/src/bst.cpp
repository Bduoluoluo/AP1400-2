#include "bst.h"

using Node = BST::Node;

Node::Node (int value, Node* left, Node* right) : value(value), left(left), right(right) {}

Node::Node () : value(0), left(nullptr), right(nullptr) {}

Node::Node (const Node& node) : value(node.value), left(node.left), right(node.right) {}

std::ostream& operator<< (std::ostream& os, const Node& node) {
    os << &node << "    =>    value:" << node.value << "    left:" << node.left << "    right:" << node.right << std::endl;
    return os;
}

bool Node::operator< (const int num) const {
    return this->value < num;
}

bool Node::operator> (const int num) const {
    return this->value > num;
}

bool Node::operator<= (const int num) const {
    return this->value <= num;
}

bool Node::operator>= (const int num) const {
    return this->value >= num;
}

bool Node::operator== (const int num) const {
    return this->value == num;
}

bool operator< (const int num, const Node& node) {
    return num < node.value;
}

bool operator> (const int num, const Node& node) {
    return num > node.value;
}

bool operator<= (const int num, const Node& node) {
    return num <= node.value;
}

bool operator>= (const int num, const Node& node) {
    return num >= node.value;
}

bool operator== (const int num, const Node& node) {
    return num == node.value;
}