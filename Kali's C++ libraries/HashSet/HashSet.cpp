#include <iostream>
#include <vector>

template <typename T> class HashSet {
    private:
        std::vector<T> data;
    public:
        //Constructors
        HashSet(){/*@*/};
        HashSet(std::vector<T> x) {
            for (int i = 0; i < x.size(); i++) this->data.add(x[i]);
        }
  
        //Methods
        void add   (T x) {
            if (!isHere(x)) this->data.push_back(x);
        }
        void remove(int i) {
            if(i <= this->data.size()) this->data.erase(this->data.begin()+i);
        }
        T    get   (int i) {
            if (i <= this->data.size()) return this->data[i];
        }
        int  find  (T x) {
            if (!isHere(x)) return NULL;
            for (int i = 0; i < this->data.size(); i++){
                if (this->data[i] == x) return i;
            }
        }
        bool isHere(T x) {
            for (int i = 0; i < this->data.size(); i++){
                if (this->data[i] == x) return true;
            }
            return false;
        }
        void sayAll() {
            for (int i = 0; i < this->data.size();i++) std::cout << this->data[i] << " ";
            std::cout << std::endl;
        }
        int  size  () {
            return this->data.size();
        };
        std::vector<T> getData(){
            return this->data;
        };
};
