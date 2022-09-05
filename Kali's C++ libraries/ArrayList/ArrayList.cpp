#include <iostream>

template <typename T> class ArrayList {
private:
    T          dato;
    ArrayList<T>*next;
    ArrayList<T>*head = NULL;
    
    bool isHere(T e){
        ArrayList<T>*current = head;
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

        ArrayList<T>*newNode = new ArrayList<T>;
        newNode->dato = x;
        newNode->next = NULL;

        if(head == NULL){
            head = newNode;
            return;
        }

        ArrayList<T>*current = head;
        while (current != NULL) {
            if (current->next == NULL) {
                current->next = newNode;
                return;
            }
            current = current->next;
        }
    }
    T    operator[](int index){
        if (!inBounds()) return T();
        ArrayList<T>*current = head;
        for(int i = 0;i < index; i++) current = current->next;
        return current->dato;
    }
    bool operator==(ArrayList e){
        
        if (!inBounds(e.size())) return false;

        ArrayList<T>*current = head;
        for (int i = 0; current != NULL; i++){
            if (current->dato != e[i]) return false;
            current = current->next;
        }
        return true;
    }
    int  size(){
        ArrayList<T>*current = head;
        int i = 0;
        for (; current != NULL; i++) current = current->next;
        return i;
    }
    void println(){
        ArrayList<T>*current = head;
        for(; current!=NULL; current = current->next){
            std::cout << current->dato << " ";
        }
        std::cout << std::endl;
    }
    void remove(int index){

        if (!inBounds(index)) return;

        ArrayList<T>*current = head;
        ArrayList<T>*before  = NULL;
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
