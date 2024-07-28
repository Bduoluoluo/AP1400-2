#include "bst.h"

using Node = BST::Node;

Node::Node (int value, Node* left, Node* right) : value(value), left(left), right(right) {}

Node::Node () : value(0), left(nullptr), right(nullptr) {}

Node::Node (const Node& node) : value(node.value), left(node.left), right(node.right) {}

std::ostream& operator<< (std::ostream& os, const Node& node) {
    os << &node << "    =>    value:" << node.value << "    left:" << node.left << "    right:" << node.right;
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

BST::BST () : root(nullptr) {}

Node*& BST::get_root () {
    return this->root;
}

void BST::bfs (std::function<void(Node*& node)> func) {
    std::queue<Node*> que;
    que.push(this->root);

    while (!que.empty()) {
        Node* node = que.front();
        que.pop();
        if (node == nullptr) continue;

        func(node);
        if (node->left != nullptr) que.push(node->left);
        if (node->right != nullptr) que.push(node->right);
    }
}

size_t BST::length () {
    size_t size = 0;
    auto func = [&size] (Node*& node) {
        size ++;
    };
    bfs(func);
    return size;
}

bool BST::add_node (int value) {
    Node* newNode = new Node(value, nullptr, nullptr);
    Node* node = this->root;
    if (node == nullptr) {
        this->root = newNode;
        return true;
    }

    while (true) {
        if (value == node->value) {
            delete newNode;
            return false;
        } else if (value < node->value) {
            if (node->left == nullptr) {
                node->left = newNode;
                break;
            } else node = node->left;
        } else {
            if (node->right == nullptr) {
                node->right = newNode;
                break;
            } else node = node->right;
        }
    }
    return true;
}

Node** BST::find_node (int value) {
    if (this->root == nullptr) return nullptr;
    if (value == this->root->value) return &(this->root);

    Node* node = this->root;
    while (true) {
        if (node == nullptr) return nullptr;
        if (value < node->value) {
            if (node->left != nullptr && value == node->left->value)
                return &(node->left);
            node = node->left;
        } else {
            if (node->right != nullptr && value == node->right->value)
                return &(node->right);
            node = node->right;
        }
    }
}

Node** BST::find_parrent (int value) {
    if (this->root == nullptr || value == this->root->value) return nullptr;

    Node* node = this->root;
    while (true) {
        if (node == nullptr) return nullptr;
        if (value < node->value) {
            if (node->left != nullptr && value == node->left->value)
                return find_node(node->value);
            node = node->left;
        } else {
            if (node->right != nullptr && value == node->right->value)
                return find_node(node->value);
            node = node->right;
        }
    }
}

Node** BST::find_successor (int value) {
    Node* node = *find_node(value);
    if (node == nullptr) return nullptr;

    int findValue = INT32_MIN;
    while (true) {
        if (node == nullptr) break;
        if (value > node->value) findValue = std::max(findValue, node->value);
        if (value <= node->value) node = node->left;
        else node = node->right;
    }
    if (findValue == INT32_MIN) return nullptr;
    return find_node(findValue);
}

bool BST::delete_node (int value) {
    Node** node = find_node(value);
    if (node == nullptr) return false;

    if ((*node)->left == nullptr && (*node)->right == nullptr) {
        delete *node;
        *node = nullptr;
    } else if ((*node)->left == nullptr) {
        Node* right = (*node)->right;
        delete *node;
        *node = right;
    } else if ((*node)->right == nullptr) {
        Node* left = (*node)->left;
        delete *node;
        *node = left;
    } else {
        Node** sucNode = find_successor(value);
        int reValue = (*sucNode)->value;
        delete_node(reValue);
        (*node)->value = reValue;
    }
    return true;
}

std::ostream& operator<< (std::ostream& os, BST& bst) {
    auto func = [] (Node*& node) {
        std::cout << *node << std::endl;
    };

    std::cout << std::string(80, '*') << std::endl;
    bst.bfs(func);
    std::cout << "binary search tree size: " << bst.length() << std::endl;
    std::cout << std::string(80, '*') << std::endl;
    return os;
}