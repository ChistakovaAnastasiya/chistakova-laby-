//Работа с типизированным файлом
//база данных "Солнечная панель"

//#include <conio.h>
#include <iostream>
//#include <windows.h>h
#include <stdlib.h>

using namespace std;

class ListItem {
private:
    int value;
    ListItem *next;
public:
    ListItem(int value, ListItem *next) {
        this->value = value;
        this->next = next;
    }

    int getValue() const {
        return value;
    }

    ListItem *getNext() {
        return next;
    }

    void setNext(ListItem *newNext) {
        this->next = newNext;
    }

    ~ListItem() {
        delete this;
    }
};


class Vector {
private:
    ListItem *root;
public:
    Vector(ListItem *next) {
        this->root = next;
    }

    ListItem *getRoot() {
        return root;
    }

    void addNext(ListItem *newElement) {
        newElement->setNext(root);
        root = newElement;
    }

    ~Vector() {
        delete this;
    }
};

Vector *randomList() {
    cout << "Введите Очередной Вектор \n";
    int size = 10;
    Vector *list = new Vector(NULL);
    for (int i = 0; i < size; i++) {
        int data = 0;
        cout << "Добавьте новый элемент \n";
        cin >> data;
        ListItem *item = new ListItem(data, NULL);
        list->addNext(item);
        cout << "Новый добавленный элемент со значением  " << item->getValue() << " и индексом " << i << "\n";
    }
    return list;

}

void checkList(Vector *vector) {
    ListItem *item = vector->getRoot();
    while (item != NULL) {
        cout << "Новый элемент Вектора- " << item->getValue() << "\n";
        item = item->getNext();
    }
}

bool areEqual(Vector *vector1, Vector *vector2) {
    ListItem *item1 = vector1->getRoot();
    ListItem *item2 = vector2->getRoot();
    while (item1 != NULL || item2 != NULL) {
        if (item1->getValue() != item2->getValue()) {
            return false;
        }
        item1 = item1->getNext();
        item2 = item2->getNext();
    }
    if (item1 != NULL ^ item2 != NULL) {
        return false;
    }
    return true;

}


//Начало программы

int main() {
//    setlocale(LC_ALL, "");
    cout << setlocale(LC_ALL, "") << endl;
    Vector *vector1 = randomList();
    checkList(vector1);
    Vector *vector2 = randomList();
    checkList(vector2);
    bool equal = areEqual(vector1, vector2);
    cout << "Вектора " << (equal ? "Одинаковы" : "Не одинаковы") << endl;
    return 0;
}
