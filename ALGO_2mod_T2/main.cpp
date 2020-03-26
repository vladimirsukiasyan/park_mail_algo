/*
 * Сукиасян Владимир, АПО-13
 *
 * Дано число N ≤ 10^4 и последовательность целых чисел из [-2^31..2^31] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 * то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * Выведите элементы в порядке in-order (слева направо).

Рекурсия запрещена.*/


#include <iostream>

template<class T>
struct StackNode {
    StackNode *next;
    T data;

    StackNode() {}

    StackNode(const T data) : data(data) {}

    ~StackNode() {}
};

template<class T>
class Stack {
    
    typedef StackNode<T> SNode;
    SNode *top;                //pointer to the end of the stack

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top) {
            pop();
        }
    }

    void push(const T data) {   //put element into stack
        SNode *newNode = new SNode(data);
        newNode->next = top;
        top = newNode;
    }

    T *peek() {     //gets top element
        return top->data;
    }

    T pop() {
        T data = top->data;
        SNode *tempPtr = top;
        top = top->next;
        delete tempPtr;
        return data;
    }

    bool empty() {
        return top == nullptr;
    }
};

struct Node {
    Node(int64_t key) :
            key(key),
            left(nullptr),
            right(nullptr),
            parent(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }


    int64_t key;
    Node *parent;
    Node *left;
    Node *right;
};

class BinarySearchTree {
public:

    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        delete root;
    }

    void Add(int64_t key) {
        if (!root) {
            root = new Node(key);

        } else {

            Node *node = root;
            while (node != nullptr) {
                if (key < node->key) {
                    if (node->left == nullptr) {
                        node->left = new Node(key);
                        node->left->parent = node;
                        break;
                    } else node = node->left;
                } else {
                    if (node->right == nullptr) {
                        node->right = new Node(key);
                        node->right->parent = node;
                        break;
                    } else node = node->right;
                }
            }
        }
    }

    bool Delete(int64_t key) {
        Node *node = root;
        while (node) {
            if (key == node->key) {
                DeleteNode(node);
            }
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    };

    bool Has(int64_t key) {
        Node *node = root;
        while (node) {
            if (key == node->key) {
                return true;
            }
            if (key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    void TraverseInOrderDFS() {
        Stack<Node *> stack;
        Node *node = root;

        while (!stack.empty() || node != nullptr) {
            if (node) {
                stack.push(node);
                node = node->left;
            } else {
                node = stack.pop();
                visit(node);
                node = node->right;
            }
        }
    }

private:
    Node *root;

    void DeleteNode(Node *&node) {
        if (!node->left && !node->right) {
            node = nullptr;
        } else if (!node->left) {
            Node *tmpRight = node->right;
            tmpRight->parent = node->parent;
            delete node;
            node = tmpRight;
        } else if (!node->right) {
            Node *tmpLeft = node->left;
            tmpLeft->parent = node->parent;
            delete node;
            node = tmpLeft;
        } else {
            Node *minParent = node;
            Node *min = node->right;
            while (min->left != NULL) {
                minParent = min;
                min = min->left;
            }
            node->key = min->key;
            (minParent->left == min ? minParent->right : minParent->left)
                    = min->right;
            min->right->parent = minParent;
            delete min;
        }
    }

    void visit(Node *node) {
        std::cout << node->key << " ";
    }
};


int main() {
    int n;
    int64_t key;
    std::cin >> n;

    BinarySearchTree tree;
    for (int i = 0; i < n; i++) {
        std::cin >> key;
        tree.Add(key);
    }
    tree.TraverseInOrderDFS();
    return 0;
}