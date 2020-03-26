/*
 *
 * Сукиасян Владимир, группа АПО-13
 *
 * Дано число N и N строк.
 * Каждая строка содержащит команду добавления или удаления натуральных чисел,
 * а также запрос на получение k-ой порядковой статистики.
 * Команда добавления числа A задается положительным числом A,
 * команда удаления числа A задается отрицательным числом “-A”.
 * Запрос на получение k-ой порядковой статистики задается числом k.
 * Требуемая скорость выполнения запроса - O(log n).
*/


#include <iostream>
#include <random>

template<typename Key>
class AvlTree {
    struct Node {
        Node(const Key &key) : key(key), height(1), weight(1), left(nullptr), right(nullptr) {}

        Key key;
        size_t height;
        size_t weight;
        Node *left;
        Node *right;
    };

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        destroyTree(root);
    }

    bool Has(const Key &key) const {
        Node *tmp = root;
        while (tmp) {
            if (tmp->key == key) {
                return true;
            } else if (tmp->key < key) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return false;
    }

    void Add(const Key &key) {
        root = addInternal(root, key);
    }

    void Remove(const Key &key) {
        root = removeInternal(root, key);
    }

    template <typename T>
    T kth_statistic_element(int k){
        T result;

        if (k < getWeight(root)) {
            Node* node = root;
            size_t index =getWeight(root->left);

            while (index != k) {
                if (k > index) {
                    node = node->right;
                    index += 1 + getWeight(node->left);
                } else {
                    node = node->left;
                    index -= 1 + getWeight(node->right);
                }
            }
            result = node->key;
        }
        return result;
    }

private:

    size_t sizeOf(Node* node){
        return !node?0:node->weight;
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *addInternal(Node *node, const Key &key) {
        if (!node)
            return new Node(key);
        if (node->key <= key)
            node->right = addInternal(node->right, key);
        else
            node->left = addInternal(node->left, key);

        return doBalance(node);
    }

    Node *removeInternal(Node *node, const Key &key) {
        if (!node)
            return nullptr;
        if (node->key < key)
            node->right = removeInternal(node->right, key);
        else if (node->key > key)
            node->left = removeInternal(node->left, key);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (!right)
                return left;

            Node *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;

            return doBalance(min);
        }

        return doBalance(node);
    }

    Node *findMin(Node *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node *removeMin(Node *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node *doBalance(Node *node) {
        fixHeight(node);
        fixWeight(node);

        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }

    size_t getHeight(Node *node) {
        return node ? node->height : 0;
    }

    size_t getWeight(Node *node) {
        return node ? node->weight : 0;
    }

    void fixHeight(Node *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void fixWeight(Node *node) {
        node->weight = getWeight(node->left)+getWeight(node->right)+1;
    }

    int getBalance(Node *node) {
        if(node== nullptr){
            return 0;
        }
        return static_cast<int>(getHeight(node->right) - getHeight(node->left));
    }

    Node *rotateLeft(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fixHeight(node);
        fixWeight(node);
        fixHeight(tmp);
        fixWeight(tmp);

        return tmp;
    }

    Node *rotateRight(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fixHeight(node);
        fixWeight(node);
        fixHeight(tmp);
        fixWeight(tmp);

        return tmp;
    }

    Node *root;
};

int main(int argc, const char *argv[]) {
    int n;
    AvlTree<int> avlTree;

    std::cin >> n;

    int key, kth;
    for (int i = 0; i < n; i++) {
        std::cin >> key >> kth;
        if (key < 0) {
            avlTree.Remove(std::abs(key));
            std::cout <<avlTree.kth_statistic_element<int>(kth)<<std::endl;
        } else {
            avlTree.Add(key);
            std::cout <<avlTree.kth_statistic_element<int>(kth)<<std::endl;
        }
    }
    return 0;
}
