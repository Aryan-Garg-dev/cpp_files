#include <iostream>
#include <cstdlib>
#include <initializer_list>
using namespace std;

template <class T>
class Set{
    T* arr;
    protected:
    void sort(){
        for (int i = 0; i < this->size-1; i++){
            for (int j = 1+i; j < this->size; j++){
                if (arr[i]>arr[j]){
                    T temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    
    void copyInto(T* target){
        for (int i = 0; i < this->size; i++){
            target[i] = this->arr[i];
        }
    }

    void copyFrom(Set<T>&target){
        for (int i = 0; i < target.size; i++){
            this->arr[i] = target[i];
        }
    }

    void removeDuplicates(){
        T *uniqArr = (T*)malloc(sizeof(T)); 
        int iter = 0;
        for (int i = 0; i < this->size; i++){
            bool isUniq = true;
            for (int j = i+1; j < this->size; j++){
                if (this->arr[i]==this->arr[j]){
                    isUniq = false;
                    break;
                }
            }
            if (isUniq){
                uniqArr[iter] = this->arr[i];
                iter++;
                uniqArr = (T*)realloc(uniqArr, sizeof(T)*(iter+1));
            }
        }
        delete[] this->arr;
        this->size = iter;
        this->arr = uniqArr;
    }
    
    public:
    int size;
    Set(int size){
        arr = new T[size];
        this->size = size;
    }
    Set(initializer_list<T>list){
        this->arr = new T[list.size()];
        auto it = list.begin();
        for (int i = 0; it != list.end();++it, i++){
            this->arr[i] = *it;
        } 
        this->size = list.size();
        sort();
        removeDuplicates();
    }
    Set(T* arr, int size){
        this->arr = new T[size];
        for (int i = 0; i < size; i++){
            this->arr[i] = arr[i];
        }
        this->size = size;
        sort();
        removeDuplicates();
    }

    void display(){
        cout<<"("<<" ";
        this->size > 0 ? cout<<this->arr[0] : cout<<"!";
        for (int i = 1; i < this->size; i++){
            cout<<", "<<this->arr[i];
        }
        cout<<" )"<<endl;
    }

    void push(T value){
        for (int i = 0; i < this->size, this->size > 0; i++){
            if (this->arr[i]==value){
                return;
            }
        }
        T* arr = new T[this->size+1];
        copyInto(arr);
        arr[size] = value;
        delete[] this->arr;
        this->arr = arr;
        this->size += 1;
        sort();
    }

    T operator[](int index){
        return this->arr[index];
    }

    bool includes(T value){
        for (int i = 0; i < this->size; i++){
            if (value==this->arr[i]){
                return true;
            }
        }
        return false;
    }

    Set& operator=(Set<T>&target){
        this->size = target.size;
        delete[] this->arr;
        this->arr = new T[this->size];
        copyFrom(target);
    }

    int index(T value){
        if (!includes(value)) return -1;
        for (int i = 0; i < this->size; i++){
            if (this->arr[i] == value){
                return i;
            }
        }
    }

    Set slice(int start, int end){
        int size = end - start;
        Set<T>set(0);
        for (int i = start; i < end; i++){
            set.push(this->arr[i]);
        }
        return set;
    }

    void pop(T value){
        T *newArr = new T[this->size - 1];
        if (!includes(value)){
            return;
        }
        for (int i = 0, iter = 0; i < this->size; i++){
            if (this->arr[i]!=value){
                newArr[iter] = this->arr[i];
                iter++;
            }
        }
        delete[] this->arr;
        this->size -= 1;
        this->arr = newArr;
    }

    //UNION
    void operator&&(Set<T>&target){
        for (int i = 0; i < target.size; i++){
            push(target[i]);
        }
    }
    //INTERSECTION
    void operator||(Set<T>&target){
        T *newArr = (T*)malloc(sizeof(T));
        int iter = 0;
        for (int i = 0; i < this->size; i++){
            if (target.includes(this->arr[i])){
                newArr[iter] = this->arr[i];
                iter++;
                newArr = (T*)realloc(newArr, (iter+1)*sizeof(T));
            }
        }
        for (int i = 0; i < target.size; i++){
            if (includes(target[i])){
                newArr[iter] = target[i];
                iter++;
                newArr = (T*)realloc(newArr, (iter+1)*sizeof(T));
            }
        }
        delete[] this->arr;
        this->size = iter;
        this->arr = newArr;
        removeDuplicates();
    }
    //DIFFERENCE
    void operator-(Set<T>&target){
        for (int i = 0; i < target.size; i++){
            pop(target[i]);
        }
    }
    //SYMMETRIC DIFFERENCE
    void operator^(Set<T>&target){
        T *newArr = (T*) malloc(sizeof(T));
        int iter = 0;
        for (int i = 0; i < this->size; i++){
            if (!target.includes(this->arr[i])){
                newArr[iter] = this->arr[i];
                iter++;
                newArr = (T*) realloc(newArr, (iter+1)*sizeof(T));
            }
        }
        for (int i = 0; i < target.size; i++){
            if (!includes(target[i])){
                newArr[iter] = target[i];
                iter++;
                newArr = (T*) realloc(newArr, (iter+1)*sizeof(T));       
            }
        }
        delete[] this->arr;
        this->size = iter;
        this->arr = newArr;
    }

    void clear(){
        T *newArr;
        delete[] this->arr;
        this->arr = newArr;
        this->size = 0;
    }

    ~Set(){
        delete[] arr;
    }
};

int main(){
    int arr[]={1, 2, 3, 3};
    Set<int>set(arr, 3);
    // set.display();
    Set<int>dummy({1, 2, 3, 3, 5, 6, 7});
    Set<int>newSet = {9, 10, 12}; 
    dummy.display();
    set.clear();
    set.push(5);
    set.display();
    // set.push(4);
    // set.display();
    // set-dummy;
    // set.display();
    // set-dummy;
    // set.display();
    // set.pop(4);
    // set.display();
    // set.clear();
    // set.display();
    // set||dummy;
    // set.display();
    // set&&dummy;
    // set.display();
    // Set<int>new_set = set.slice(0, 2);
    // new_set.display();
    // set.push(5);
    // new_set = set;
    // new_set.display();
    // new_set.push(5);
    // new_set.display();
    return 0;
} 
