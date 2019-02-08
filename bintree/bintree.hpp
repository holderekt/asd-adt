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
    ~Binary_Tree();
    Binary_Tree(const Binary_Tree<T>&);

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
    size_t size() const;
    bool leaf(Node*) const;

    void preOrder();
    void postOrder();
    void inOrder();

    void traversalPreOrder(Node*);
    void traversalPostOrder(Node*);
    void traversalInOrder(Node*);

    template <class Z>
    friend std::ostream& operator<<(std::ostream&, Binary_Tree<Z>&);
    void operator=(const Binary_Tree<T>&);

private:
    Node* root;
    size_t dsize;

    void _erase(Node*);
    Node* _copy(Node*, Node*);

    
};


template<class T>
void Binary_Tree<T>::preOrder(){
    traversalPreOrder(root);
}

template <class T>
void Binary_Tree<T>::traversalPreOrder(Node* node){
    if(node != nullptr){
        std::cout << node->value;
        traversalPreOrder(node->left);
        traversalPreOrder(node->right);
    }
}

template<class T>
void Binary_Tree<T>::inOrder(){
    traversalInOrder(root);
}

template <class T>
void Binary_Tree<T>::traversalInOrder(Node* node){
    if(node != nullptr){
        traversalInOrder(node->left);
        std::cout << node->value;
        traversalInOrder(node->right);
    }
}

template<class T>
void Binary_Tree<T>::postOrder(){
    traversalPostOrder(root);
}

template <class T>
void Binary_Tree<T>::traversalPostOrder(Node* node){
    if(node != nullptr){
        traversalPostOrder(node->left);
        traversalPostOrder(node->right);
        std::cout << node->value;
    }
}

template<class T>
size_t Binary_Tree<T>::size() const{
    return this->dsize;
}

template <class T>
Binary_Tree<T>::Binary_Tree(const Binary_Tree<T>& tree){
    create();
    root = _copy(nullptr, tree.get_root());

}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::_copy(Node* parent_node, Node* node){

    if(node != nullptr){
        Node* new_node = new Node(node->value);
        new_node->parent = parent_node;
        new_node->left = _copy(new_node, node->left);
        new_node->right = _copy(new_node, node->right);

        dsize++;

        return new_node;

    }else{
        return nullptr;
    }
}

template <class T>
void Binary_Tree<T>::create(){
    root = nullptr;
    dsize = 0;
}

template <class T>
void Binary_Tree<T>::operator=(const Binary_Tree<T>& tree){
    _erase(root);
    create();
    root = _copy(nullptr, tree.get_root());
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
Binary_Tree<T>::~Binary_Tree(){
    _erase(root);
}

template <class T>
void Binary_Tree<T>::_erase(Node* n){

    if(n != nullptr){
        _erase(n->left);
        _erase(n->right);
        
        delete n;
        dsize--;
    }
}

template <class T>
void Binary_Tree<T>::remove(Node* n){

    bool isRoot = false;
    if(n->parent != nullptr){
        if(n->parent->left == n){
            n->parent->left = nullptr;
        }else{
            n->parent->right = nullptr;
        }
    }else{
        if(n == root){
            isRoot = true;
        }
    }

    _erase(n);

    if(isRoot){
        create();
    }
    
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
    if(tree.get_root() != nullptr){
        tree.print(os, tree.get_root(), 0, "","");
    }
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

        dsize++;

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

        dsize++;

        return n->left;
    }else{
        throw "Nodo presente";
    }
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::insert_root(const value_type value){
    if(root == nullptr){
        root = new Node(value);
        dsize++;

        return root;
    }else{
        throw "Root gia presente";
    }
}

template <class T>
typename Binary_Tree<T>::Node* Binary_Tree<T>::get_root() const{
    return root;
}

template <class T>
bool Binary_Tree<T>::leaf(Node* n) const{
    return (isEmpty_sx(n) and isEmpty_dx(n));
}