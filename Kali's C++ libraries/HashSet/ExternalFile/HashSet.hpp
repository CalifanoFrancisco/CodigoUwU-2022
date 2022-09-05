#ifndef HASHSET_HPP
#define HASHSET_HPP

template <typename T> class HashSet {
private:
    T          dato;
    HashSet<T>*next;
    HashSet<T>*head = NULL;
    bool isHere(T e);
    bool inBounds(int i);
public:
    HashSet();
    void add(T x);
    void remove(int index);
    int  size();

    void println();
    
    T    operator[](int index);
    bool operator==(HashSet e);
};

#endif
