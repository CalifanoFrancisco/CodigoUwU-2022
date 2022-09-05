#include <iostream>
#include "HashSet.hpp"

template <typename T>      HashSet<T>::HashSet(){
    this->head = NULL;
}

template <typename T> bool HashSet<T>::isHere(T e){
    HashSet<T>*current = head;
    while (current != NULL) {
        if (current->dato == e) return true;
        current = current->next;
    }
    return false;
}

template <typename T> bool HashSet<T>::inBounds(int index){
    return !(i < 0 || i > this->size());
}

template <typename T> void HashSet<T>::add(T x){
    if(isHere(x)) return;

    HashSet<T>*newNode = new HashSet<T>;
    newNode->dato = x;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return;
    }

    HashSet<T>*current = head;
    while (current != NULL) {
        if (current->next == NULL) {
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}

template <typename T> T    HashSet<T>::operator[](int index){
    if (index > size() || index < 0) return T();
    HashSet<T>*current = head;
    for(int i = 0;i < index; i++) current = current->next;
    return current->dato;
}

template <typename T> bool HashSet<T>::operator==(HashSet<T> e){
    if (!inBounds(e.size())) return false;

    HashSet<T>*current = head;
    for (int i = 0; current != NULL; i++){
        if (current->dato != e[i]) return false;
        current = current->next;
    }
    return true;
}

template <typename T> int  HashSet<T>::size(){
    HashSet<T>*current = head;
    int i = 0;
    for (; current != NULL; i++) current = current->next;
    return i;
}

template <typename T> void HashSet<T>::println(){
    HashSet<T>*current = head;
    for(; current!=NULL; current = current->next){
        std::cout << current->dato << " ";
    }
    std::cout << std::endl;
}

template <typename T> void HashSet<T>::remove(int index){
    
    if (!inBounds(index)) return;

    HashSet<T>*current = head;
    HashSet<T>*before  = NULL;
    for(int i = 0; current != NULL; i++){
        if (index == i){
            before->next = current->next;
            delete current;
            return;
        }
    before  = current;
    current = current->next;
    }
}

