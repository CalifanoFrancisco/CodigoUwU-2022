#include <iostream>
template <typename T> class HashSet {
private:
    T         dato;
    HashSet<T>*next;
    HashSet<T>*head = NULL;
    bool isHere(T e){
        HashSet<T>*current = head;
        while (current != NULL) {
            if (current->dato == e) return true;
            current = current->next;
        }
        return false;
    }
    bool inBounds(int i){
        if (i < 0 || i > this->size()) return false;
        return true;
    }
public:
    void add(T x){
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
    T    operator[](int index){
        if (index > size() || index < 0) return T();
        HashSet<T>*current = head;
        for(int i = 0;i < index; i++) current = current->next;
        return current->dato;
    }
    bool operator==(HashSet e){
        
        if (!inBounds(e.size())) return false;

        HashSet<T>*current = head;
        for (int i = 0; current != NULL; i++){
            if (current->dato != e[i]) return false;
            current = current->next;
        }
        return true;
    }
    int  size(){
        HashSet<T>*current = head;
        int i = 0;
        for (; current != NULL; i++) current = current->next;
        return i;
    }
    void println(){
        HashSet<T>*current = head;
        for(; current!=NULL; current = current->next){
            std::cout << current->dato << " ";
        }
        std::cout << std::endl;
    }
    void remove(int index){

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
};
