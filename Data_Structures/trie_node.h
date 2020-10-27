#ifndef TRIENODE_H
#define TRIENODE_H

#include <QChar>
#include "map_vector.h"

template <typename T>
class TrieNode{
private:
    QChar letter;
    T value;
    bool hasValue;
    Map<QChar, TrieNode*> *nextNodes;

public:
    TrieNode(QChar letter);
    TrieNode(QChar letter, T value);
    QChar getLetter();
    void setLetter(QChar letter);
    T& getValue();
    void setValue(T value);
    bool getHasValue();
    bool contains(QChar letter);
    TrieNode* addNextNode(QChar letter);
    TrieNode* addNextNode(QChar letter, T value);
    TrieNode* getNextNode(QChar letter);
    vector<QChar> getNextNodes();
    ~TrieNode();
};

template <typename T>
TrieNode<T>::TrieNode(QChar letter): letter{letter}, hasValue{false} {
    nextNodes = new Map<QChar, TrieNode*>();
}

template <typename T>
TrieNode<T>::TrieNode(QChar letter, T value): letter{letter}, value{value}, hasValue{true} {
    nextNodes = new Map<QChar, TrieNode*>();
}

template <typename T>
QChar TrieNode<T>::getLetter() {
    return letter;
}

template <typename T>
void TrieNode<T>::setLetter(QChar letter) {
    this->letter = letter;
}

template <typename T>
T& TrieNode<T>::getValue() {
    return value;
}

template <typename T>
void TrieNode<T>::setValue(T value) {
    this->value = value;
    hasValue = true;
}

template <typename T>
bool TrieNode<T>::getHasValue() {
    return hasValue;
}

template <typename T>
bool TrieNode<T>::contains(QChar letter) {
    return nextNodes->contains(letter);
}

template <typename T>
TrieNode<T>* TrieNode<T>::addNextNode(QChar letter) {
    if (nextNodes->contains(letter)) throw "The character already exists";
    TrieNode<T>* result = new TrieNode<T>(letter);
    nextNodes->insert(letter, result);
    return result;
}

template <typename T>
TrieNode<T>* TrieNode<T>::addNextNode(QChar letter, T value) {
    if (nextNodes->contains(letter)) throw "The character already exists";
    TrieNode<T>* result = new TrieNode<T>(letter, value);
    nextNodes->insert(letter, result);
    return result;
}

template <typename T>
TrieNode<T>* TrieNode<T>::getNextNode(QChar letter) {
    if (!nextNodes->contains(letter)) throw "Letter doesn't exist";
    return nextNodes->value(letter);
}

template <typename T>
vector<QChar> TrieNode<T>::getNextNodes() {
    return nextNodes->keys();
}

template <typename T>
TrieNode<T>::~TrieNode() {
    delete nextNodes;
}

#endif // TRIENODE_H
