#pragma once

#include <iostream>


template <class T>
class Binary_Tree;


template <class T>
struct BTNode{

    friend class Binary_Tree<T>;

    BTNode(const typename Binary_Tree<T>::value_type value){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        this->value = value;
    }

    BTNode* parent;
    BTNode* left;
    BTNode* right;
    typename Binary_Tree<T>::value_type value;
};


template <class T>
class Binary_Tree{
public:
    typedef T value_type;
    typedef BTNode<T> Node;

    Binary_Tree();

    Node* insertdx(Node* , const value_type);
    void create();
    Node* insertsx(Node* , const value_type);
    Node* sx(Node*) const;
    Node* dx(Node*) const;
    Node* parent(Node*) const;
    bool isEmpty_sx(Node*) const;
    bool isEmpty_dx(Node*) const;
    bool isEmpty() const;
    value_type read(Node*) const;
    void write(Node*, value_type); 
    Node* insert_root(const value_type);
    Node* get_root() const;
    void print(std::ostream&, Node*, int, std::string, std::string space);
    void remove(Node*);
    

    template <class Z>
    friend std::ostream& operator<<(std::ostream&, Binary_Tree<Z>&);

private:
    Node* root;
    size_t size;

    void _erase(Node*);

    
};

template <class T>
void Binary_Tree<T>::create(){
    root = nullptr;
    size = 0;
}

template <class T>
void Binary_Tree<T>::write(Node* n, value_type value){
    if(n != nullptr){
        n->value = value;
    }else{
        throw "Nodo nullo";
    }
}

template <class T>
void Binary_Tree<T>::_erase(Node* n){

    if(n != nullptr){
        _erase(n->left);
        _erase(n->right);
        
        delete n;
        size--;
    }
}

template <class T>
void Binary_Tree<T>::remove(Node* n){

    if(n->parent != nullptr){
        if(n->parent->left == n){
            n->parent->left = nullptr;
        }else{
            n->parent->right = nullptr;
        }
    }

    _erase(n);
}

template <class T>
typename Binary_Tree<T>::value_type Binary_Tree<T>::read(Node* n) const{
    return n->value;
}

template <class T>
bool Binary_Tree<T>::isEmpty() const{
    return (root == nullptr);
}

template <class T>
bool Binary_Tree<T>::isEmpty_dx(Node* n) const{
    return (n->right == nullptr);
}

template <class T>
bool Binary_Tree<T>::isEmpty_sx(Node* n) const{
    return (n->left == nullptr);
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::parent(Node* n) const{
    return n->parent;
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::dx(Node* n) const{
    return n->right;
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::sx(Node* n) const{
    return n->left;
}

template <class T>
std::ostream& operator<<(std::ostream& os, Binary_Tree<T>& tree){
    tree.print(os, tree.get_root(), 0, "","");
    return os;
}


template <class T>
void Binary_Tree<T>::print(std::ostream& os, Node* n, int count, std::string chr, std::string space){

    if(space.length() > 0){
        if(space[space.size() - 1] != ' '){
            os << space.substr(0, space.size() - 3);
        }else{
            os << space.substr(0, space.size() - 1);
        }

    }else{
        os << space;
    }
   
    os << chr;
    os << n->value;
   
    if(n->right != nullptr){
        if(n->left != nullptr){
            chr =  "├";
        }else{
            chr =  "└";
        }
        
        os << std::endl;
        if(n->right != nullptr and n->left != nullptr and n->right->right != nullptr){
            print(os,n->right,count+1,chr, space + "\u2502");
        }else{
            print(os,n->right,count+1,chr, space + " ");
        }
    }

    if(n->left != nullptr){
        chr = "└";
        os << std::endl;
        print(os,n->left,count+1, chr, space + " ");
    }  
}


template <class T>
Binary_Tree<T>::Binary_Tree(){
    create();
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::insertdx(Node* n, value_type value){
    if(n->right == nullptr){
        n->right = new Node(value);
        n->right->parent = n;

        size++;

        return n->right;
    }else{
        throw "Nodo presente";
    }
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::insertsx(Node* n, value_type value){
    if(n->left == nullptr){
        n->left = new Node(value);
        n->left->parent = n;

        size++;

        return n->left;
    }else{
        throw "Nodo presente";
    }
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::insert_root(const value_type value){
    if(root == nullptr){
        root = new Node(value);
        size++;

        return root;
    }else{
        throw "Root gia presente";
    }
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::get_root() const{
    return root;
}