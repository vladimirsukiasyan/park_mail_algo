/*
 * Сукиасян Владимир, АПО-13
 * ya.vova_1999-99
 *
Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми.
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.

1_2. Для разрешения коллизий используйте двойное хеширование.
Формат входных данных
Каждая строка входных данных задает одну операцию над множеством.
Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция.
Тип операции  – один из трех символов:
    +  означает добавление данной строки в множество;
    -  означает удаление  строки из множества;
    ?  означает проверку принадлежности данной строки множеству.
При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат выходных данных
Программа должна вывести для каждой операции одну из двух строк OK или FAIL,
в зависимости от того, встречается ли данное слово в нашем множестве.

 */

#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;
const size_t RESIZE_FACTOR = 2;
const float MAX_ALPHA = 0.75;
const size_t COEFF1 = 11;
const size_t COEFF2 = 17;

struct HashNode {
    HashNode() {}

    HashNode(std::string key)
            : key(std::move(key)) {}

    std::string key;
};

size_t HornerHash(const std::string &s, size_t size, int coeff) {
    size_t hash = 0;
    for (char chr : s) {
        hash = hash * coeff + chr;
    }
    return hash % size;
}

size_t Hash1(const std::string &s, size_t size) {
    return HornerHash(s, size, COEFF1) % size;
}

size_t Hash2(const std::string &s, size_t size) {
    return (HornerHash(s, size, COEFF2) * 2 + 1) % size;
}

class HashTable {
public:
    HashTable(size_t size = DEFAULT_SIZE) :
            table(size, nullptr),
            size(0) {}

    ~HashTable() {
        for (auto &node : table) {
            delete node;
        }
    }

    bool Add(const std::string &key) {
        if ((float) size > MAX_ALPHA * (float) table.size())
            grow();

        size_t hash1 = Hash1(key, table.size());
        size_t hash2 = Hash2(key, table.size());

        if (Has(key)) {
            return false;
        }

        for (int i = 0; i < table.size(); i++) {
            if (table[hash1] == nullptr || table[hash1]->key == "DELETED") {
                table[hash1] = new HashNode(key);
                size++;
                return true;
            }
            hash1 = (hash1 + i * hash2) % table.size();
        }

        return false;
    }

    bool Delete(const std::string &key) {
        size_t hash1 = Hash1(key, table.size());
        size_t hash2 = Hash2(key, table.size());

        for (int i = 0; i < table.size(); i++) {
            if (table[hash1] != nullptr) {
                if (table[hash1]->key == key) {
                    table[hash1]->key = "DELETED";
                    size--;
                    return true;
                } else {
                    hash1 = (hash1 + i * hash2) % table.size();
                }
            } else {
                return false;
            }
        }
        return false;
    }

    bool Has(const std::string &key) {
        size_t hash1 = Hash1(key, table.size());
        size_t hash2 = Hash2(key, table.size());
        for (int i = 0; i < table.size(); i++) {
            if (table[hash1] == nullptr) {
                return false;
            }
            if (table[hash1]->key == key) {
                return true;
            }
            hash1 = (hash1 + i * hash2) % table.size();
        }
        return false;
    }

private:
    std::vector<HashNode *> table;
    size_t size;

    void grow() {
        HashNode *node;
        std::vector<HashNode *> newTable(table.size() * RESIZE_FACTOR, nullptr);
        for (int i = 0; i < table.size(); i++) {
            node = table[i];
            if (node && node->key != "DELETED") {
                size_t hash1 = Hash1(node->key, newTable.size());
                size_t hash2 = Hash2(node->key, newTable.size());

                for (int j = 0; j < newTable.size(); j++) {
                    if (newTable[hash1] == nullptr) {
                        newTable[hash1] = node;
                        break;
                    }
                    hash1 = (hash1 + j * hash2) % newTable.size();
                }
            } else {
                delete table[i];
            }
        }
        table = newTable;
    }
};

int main(int argc, const char *argv[]) {
    HashTable h;

    char op;
    std::string command;
    std::string key;

    while (std::cin >> op >> key) {
        if (op == '+') {

            std::cout << (h.Add(key) ? "OK" : "FAIL") << std::endl;
        } else if (op == '-') {
            std::cout << (h.Delete(key) ? "OK" : "FAIL") << std::endl;
        } else if (op == '?') {
            std::cout << (h.Has(key) ? "OK" : "FAIL") << std::endl;
        } else break;
    }

    return 0;
}


