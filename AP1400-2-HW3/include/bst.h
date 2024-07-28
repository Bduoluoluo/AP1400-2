#ifndef BST_H
#define BST_H

#include <iostream>
#include <ostream>

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
};

#endif //BST_H