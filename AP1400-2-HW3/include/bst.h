#ifndef BST_H
#define BST_H

#include <iostream>
#include <ostream>
#include <functional>
#include <queue>
#include <map>
#include <vector>
#include <initializer_list>

class BST {
public:
    class Node {
    public:
        Node (int value, Node* left, Node* right);
        Node ();
        Node (const Node& node);
        
        bool operator< (const int num) const;
        bool operator> (const int num) const;
        bool operator<= (const int num) const;
        bool operator>= (const int num) const;
        bool operator== (const int num) const;
        friend std::ostream& operator<< (std::ostream& os, const Node& node);
        friend bool operator< (const int num, const Node& node);
        friend bool operator> (const int num, const Node& node);
        friend bool operator<= (const int num, const Node& node);
        friend bool operator>= (const int num, const Node& node);
        friend bool operator== (const int num, const Node& node);

        
        int value;
        Node* left;
        Node* right;
    };

    BST ();
    BST (BST& bst);
    BST (BST&& bst);
    BST (std::initializer_list<int> list);
    ~BST ();

    Node*& get_root ();
    void bfs (std::function<void(Node*& node)> func);
    size_t length ();
    bool add_node (int value);
    Node** find_node (int value);
    Node** find_parrent (int value);
    Node** find_successor (int value);
    bool delete_node (int value);

    friend std::ostream& operator<< (std::ostream& os, BST& bst);
    BST& operator++ ();
    BST operator++ (int);
    BST& operator= (BST& bst);
    BST& operator= (BST&& bst);

private:
    Node* root;
};

#endif //BST_H