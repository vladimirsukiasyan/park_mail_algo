/*
 *
 * Cукиасян Владимир, группа АПО-13
 *
 * Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
 * Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 * При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
 * Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
 * а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
 * Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
 * Равные ключи добавляйте в правое поддерево. Вычислить количество узлов
 * в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
 * Вывести их разницу. Разница может быть отрицательна.
*/


#include <iostream>
#include <queue>

struct TreapNode {
    int64_t key;
    int64_t priority;

    TreapNode *left;
    TreapNode *right;

    TreapNode(int64_t key, int64_t priority) :
            key(key),
            priority(priority),
            left(nullptr),
            right(nullptr) {}

    ~TreapNode() {
        delete left;
        delete right;
    }
};


class Treap {
public:
    TreapNode *root;

    Treap() {
        root = nullptr;
    }

    ~Treap() {
        delete root;
    }

    void Add(int64_t key, int64_t priority) {
        TreapNode *newNode = new TreapNode(key, priority);

        if (!root) {
            root = newNode;
            return;
        }

        TreapNode *currentNode = root;
        TreapNode *parentNode = root;
        while (currentNode && priority <= currentNode->priority) {
            parentNode = currentNode;
            if (key > currentNode->key) {
                currentNode = currentNode->right;
            } else currentNode = currentNode->left;
        }

        Split(currentNode, key, newNode->left, newNode->right);

        if (currentNode == root) {
            root = newNode;
        } else {
            if (key > parentNode->key)
                parentNode->right = newNode;
            else
                parentNode->left = newNode;
        }
    }

    int getMaxWidth() {
        int maxLayerWidth = 0;
        std::queue<TreapNode *> layerNodes;

        layerNodes.push(root);

        while (!layerNodes.empty()) {
            int currentSize = (int) (layerNodes.size());

            if (currentSize > maxLayerWidth) {
                maxLayerWidth = currentSize;
            }
            for (int i = 0; i < currentSize; i++) {
                TreapNode *node = layerNodes.front();
                layerNodes.pop();
                if (node->left) {
                    layerNodes.push(node->left);
                }
                if (node->right) {
                    layerNodes.push(node->right);
                }
            }
        }
        return maxLayerWidth;
    }

private:

    void Split(TreapNode *node, int64_t key, TreapNode *&left, TreapNode *&right) {
        if (node == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (key >= node->key) {
            Split(node->right, key, node->right, right);
            left = node;
        } else {
            Split(node->left, key, left, node->left);
            right = node;
        }
    }

    TreapNode *Merge(TreapNode *&left, TreapNode *&right) {
        if (left == nullptr || right == nullptr) {
            return left == nullptr ? right : left;
        }
        if (left->priority > right->priority) {
            left->right = Merge(left->right, right);
            return left;
        } else {
            right->left = Merge(left->left, left);
            return right;
        }
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

    int getMaxWidth() {
        int maxLayerWidth = 0;
        std::queue<Node *> layerNodes;

        layerNodes.push(root);

        while (!layerNodes.empty()) {
            int currentSize = (int) (layerNodes.size());

            if (currentSize > maxLayerWidth) {
                maxLayerWidth = currentSize;
            }
            for (int i = 0; i < currentSize; i++) {
                Node *node = layerNodes.front();
                if (node->left) {
                    layerNodes.push(node->left);
                }
                if (node->right) {
                    layerNodes.push(node->right);
                }
                layerNodes.pop();
            }
        }
        return maxLayerWidth;
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
            while (min->left != nullptr) {
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
};


int main() {
    int n;
    int64_t key, priority;
    std::cin >> n;

    BinarySearchTree tree;
    Treap treap;

    for (int i = 0; i < n; i++) {
        std::cin >> key >> priority;
        treap.Add(key, priority);
        tree.Add(key);
    }

    std::cout << treap.getMaxWidth()-tree.getMaxWidth();
    return 0;
}