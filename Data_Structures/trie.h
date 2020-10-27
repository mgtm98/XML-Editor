#ifndef TRIE_H
#define TRIE_H

#include <QStringList>
#include "trie_node.h"

template<typename T>
class Trie
{
public:
    Trie();
    void add(QString str, T value);
    bool contains(QString str);
    T& getValue(QString str);
    T& getValue(QString str, TrieNode<T> *node, int letterIndex);
    QStringList *getStrings();
    QStringList *stringsStartWith(QString theStartString);
    void stringsStartWith(QString theStartString, TrieNode<T> *node, int letterIndex);

private:
    TrieNode<T> *root;
    QStringList *getStringsResult;
    void add(QString str, T value, TrieNode<T> *node, int letterIndex);
    bool contains(QString str, TrieNode<T> *node, int letterIndex);
    void getStrings(TrieNode<T> *node, QString startString);

};

template<typename T>
Trie<T>::Trie() {
    root = new TrieNode<T>('\0');
    getStringsResult = nullptr;
}

template<typename T>
void Trie<T>::add(QString str, T value) {
    add(str, value, root, 0);
}

template<typename T>
void Trie<T>::add(QString str, T value, TrieNode<T> *node, int letterIndex){
    if (letterIndex == str.size() - 1) {
        if (node->contains(str[letterIndex])) {
            node->getNextNode(str[letterIndex])->setValue(value);
        } else {
            node->addNextNode(str[letterIndex], value);
        }
    } else {
        if (node->contains(str[letterIndex])) {
            add(str, value, node->getNextNode(str[letterIndex]), letterIndex + 1);
        } else {
            add(str, value, node->addNextNode(str[letterIndex]), letterIndex + 1);
        }
    }
}

template<typename T>
bool Trie<T>::contains(QString str) {
    return contains(str, root, 0);
}

template<typename T>
bool Trie<T>::contains(QString str, TrieNode<T> *node, int letterIndex) {
    bool result;
    if (letterIndex == str.size() - 1) {
        if (node->contains(str[letterIndex]) && node->getNextNode(str[letterIndex])->getHasValue()) {
            result = true;
        } else {
            result = false;
        }
    } else {
        if (node->contains(str[letterIndex])) {
            result = contains(str, node->getNextNode(str[letterIndex]), letterIndex + 1);
        } else {
            result = false;
        }
    }
    return result;
}

template<typename T>
T& Trie<T>::getValue(QString str) {
    return getValue(str, root, 0);
}

template<typename T>
T& Trie<T>::getValue(QString str, TrieNode<T> *node, int letterIndex) {
    T t;
    if (letterIndex == str.size() - 1) {
        if (node->contains(str[letterIndex]) && node->getNextNode(str[letterIndex])->getHasValue()) {
            return node->getNextNode(str[letterIndex])->getValue();
        } else {
            return t;
        }
    } else {
        if (node->contains(str[letterIndex])) {
            return getValue(str, node->getNextNode(str[letterIndex]), letterIndex + 1);
        } else {
            return t;
        }
    }
}

template<typename T>
QStringList *Trie<T>::stringsStartWith(QString theStartString) {
    getStringsResult = new QStringList();
    stringsStartWith(theStartString, root, 0);
    return getStringsResult;
}

template<typename T>
void Trie<T>::stringsStartWith(QString theStartString, TrieNode<T> *node, int letterIndex) {
    if (letterIndex == theStartString.size() - 1) {
        if (node->contains(theStartString[letterIndex])) {
            getStrings(node->getNextNode(theStartString[letterIndex]), theStartString);
        } else {
            return;
        }
    } else {
        if (node->contains(theStartString[letterIndex])) {
            stringsStartWith(theStartString, node->getNextNode(theStartString[letterIndex]), letterIndex + 1);
        } else {
            return;
        }
    }
}

template<typename T>
void Trie<T>::getStrings(TrieNode<T> *node, QString startString) {
    if (node->getLetter() != '\0' && node->getHasValue())getStringsResult->append(startString);
    vector<QChar> strings = node->getNextNodes();
    for (QChar character: strings) {
        getStrings(node->getNextNode(character), startString + character);
    }
}



#endif // TRIE_H
