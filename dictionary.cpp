#include <iostream>
#include <cstring>
using namespace std;

template <class P>
void echo(P* arr, int size){
    cout<<"["<<" "<<arr[0];
    for (int i = 1; i < size; i++){
        cout<<", "<<arr[i];
    }
    cout<<" ]"<<endl;
}


template <class T>
class Object{
    string *keys;
    T *values;
    public:
    int size;
        Object(string key, T value){
            this->size = 1;
            this->keys = new string[size];
            this->values = new T[size];
            this->keys[0] = key;
            this->values[0] = value;
        }

        Object(string *keys, int size){
            this->keys = new string[size];
            this->values = new T[size];
            this->size = size;
            for (int i = 0; i < size; i++){
                this->keys[i] = keys[i];
                this->values[i] = i; 
            }
        };

        void operator+=(string key){
            if (is_same<T, int>::value){
                string *keys = new string[this->size+1];
                T *values = new T[this->size+1];
                for (int i = 0; i < this->size; i++){
                    keys[i] = this->keys[i];
                    values[i] = this->values[i]; 
                }
                keys[size] = key;
                values[size] = size;
                delete[] this->keys;
                delete[] this->values;
                this->size += 1;
                this->keys = keys;
                this->values = values;
            }
        }

        Object(int size){
            this->size = size;
            this->keys = new string[size] ;
            this->values = new T[size];
            bool is_zero = true;
            if (is_same<T, string>::value || is_same<T, char>::value){
                is_zero = false;
            }
            for (int i = 0; i < this->size; i++){
                this->keys[i] = '\0';
                if (is_zero){
                    this->values[i] = 0;
                } else {
                    this->values[i] = '\0';
                }
                
            }
        };

        void set(string key, T value, int index){
            if (index >= this->size){ return; }
            this->values[index] = value;
            this->keys[index] = key;
        }

        void display(){
            cout<<"{"<<endl;
            for (int i = 0; i < this->size; i++){
                cout<<" "<<this->keys[i]<<" : "<<this->values[i]<<","<<endl;
            }
            cout<<"}"<<endl;
        }

        void push(string key, T value){
            string *keys = new string[this->size+1];
            T *values = new T[this->size+1];
            for (int i = 0; i < this->size; i++){
                keys[i] = this->keys[i];
                values[i] = this->values[i]; 
            }
            keys[size] = key;
            values[size] = value;
            delete[] this->keys;
            delete[] this->values;
            this->size += 1;
            this->keys = keys;
            this->values = values;
        }

        void pop(int index){
            if (index >= this->size){
                return;
            }
            string *keys = new string[this->size-1];
            T *values = new T[this->size-1]; 
            int iter = 0;
            for (int i = 0; i < size; i++){
                if (i != index){
                    keys[iter] = this->keys[i];
                    values[iter] = this->values[i]; 
                    iter++;
                }
            }
            delete[] this->keys;
            delete[] this->values;
            this->size -= 1;
            this->keys = keys;
            this->values = values;
        }

        void operator--(int){
            pop(this->size-1);
        }

        string* getKeys(){
            return this->keys;
        }

        T* getValues(){
            return this->values;
        }

        T getValue(string key){
            for (int i = 0; i < this->size; i++){
                if (key==this->keys[i]){
                    return this->values[i];
                }
            }
        }

        Object get(int index){
            Object<T>pair(1);
            pair.set(this->keys[index], this->values[index], 0);
            return pair;
        }

        Object slice(int start, int last){
            int size = last - start;
            Object<T>pairs(size);
            int iter = 0;
            for(int i = start; i < last; i++){
                pairs.set(this->keys[i], this->values[i], iter);
                iter++;
            }
            return pairs;
        }

        Object(const Object<T>&target){
            this->size = target.size;
            this->keys = new string[size];
            this->values = new T[size];
            for (int i = 0; i < this->size; i++){
                this->keys[i] = target.keys[i];
                this->values[i] = target.values[i];
            }
        }

        void operator+(Object<T>pairs){
            string *keys = new string[this->size+pairs.size];
            T *values = new T[this->size+pairs.size];
            for (int i = 0; i < this->size; i++){
                keys[i] = this->keys[i];
                values[i] = this->values[i]; 
            }
            for (int i = 0; i < pairs.size; i++){
                keys[this->size + i] = pairs.getKeys()[i];
                values[this->size + i] = pairs.getValues()[i];
            }
            delete[] this->keys;
            delete[] this->values;
            this->size += pairs.size;
            this->keys = keys;
            this->values = values;
        }

        void merge(Object<T>pairs){
            operator+(pairs);
        }

        T getSum(){
            T result = 0;
            if (is_same<T, int>::value || is_same<T, float>::value){
                for (int i = 0; i < this->size; i++){
                    result += this->values[i];
                }
                return result;
            }
        }
  
        void keySort(bool ascending = true){
            for (int  i = 0; i < this->size - 1; i++){
                for (int j = i + 1; j < this->size; j++){
                    if (ascending 
                        ? stricmp(this->keys[i].c_str(), this->keys[j].c_str()) > 0
                        : stricmp(this->keys[i].c_str(), this->keys[j].c_str()) < 0
                    ){
                        string temp = this->keys[i];
                        this->keys[i] = this->keys[j];
                        this->keys[j] = temp;

                        T tempVal = this->values[i];
                        this->values[i] = this->values[j];
                        this->values[j] = tempVal;
                    }
                }
            }
        }

        void valueSort(bool ascending = true){
            for (int i = 0; i < this->size - 1; i++){
                for (int j = i+1; j < this->size; j++){
                    if (ascending 
                        ? this->values[i]>this->values[j]
                        : this->values[i]<this->values[j]    
                    ){
                        string temp = this->keys[i];
                        this->keys[i] = this->keys[j];
                        this->keys[j] = temp;

                        T tempVal = this->values[i];
                        this->values[i] = this->values[j];
                        this->values[j] = tempVal;
                    }
                }
            }
        }
            
        int search(string key){
            for (int i = 0; i < this->size; i++){
                if (key == this->keys[i]){
                    return i;
                }
            }
            cout<<"Not found"<<endl;
        }

        int operator[](string key){
            return search(key);
        }

        Object operator()(int index){
            return get(index);
        }

        Object map(bool (fn)(string key, T value, int index)){
            Object<T>pairs(0);
            int iter = 0;
            for (int i = 0; i < this->size; i++){
                if (fn(this->keys[i], this->values[i], i)){
                    pairs.push(this->keys[i], this->values[i]);
                    iter++;
                }
            }
            return pairs;
        }

        Object insert(string key, T value, int index){
            Object<int>pairs(0);
            pairs.merge(slice(0, index));
            pairs.push(key, value);
            pairs.merge(slice(index, this->size));
            return pairs;
        }

        ~Object(){
            delete[] this->keys;
            delete[] this->values;
        }
};

//any function
bool searchByValue(string key, int value, int index){
    if (value>2000){
        return true;
    } else {
        return false;
    }
};


int main(){
    string keys[7]={
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };
    
    Object<int>week(keys, 7);
    // week.display();
    // cout<<week.getValue("Wednesday")<<endl;
    // Object<int>monday = week.get(0);
    // monday.display();
    // week = week.slice(0, 5);
    // week.display();
    // week = week.get(0);
    // week.display();
    // week = Object<int>(keys, 7);
    // week.display();

    Object<int>expenditures(4);
    expenditures.set("Household", 1500, 0);
    expenditures.set("Business", 2000, 1);
    expenditures.set("Leisure", 3000, 2);
    expenditures.set("Groceries", 500, 3);
    expenditures.display();
    echo(expenditures.getKeys(), expenditures.size);
    echo(expenditures.getValues(), expenditures.size);
    cout<<expenditures.getSum()<<endl;
    expenditures.push("electricity", 1000);
    expenditures.display();

    expenditures.keySort();
    expenditures.display();
    expenditures.valueSort();
    expenditures.display();
    expenditures--;
    expenditures.display();

    int index = expenditures.search("Household");
    expenditures.set(expenditures.getKeys()[index], expenditures.getValues()[index]+1000, index);
    // expenditures.set("Household", expenditures.getValue("Household")+1000, expenditures.search("Household"));
    expenditures.display();

    expenditures.pop(expenditures.search("Groceries"));
    expenditures.display();

    // expenditures.merge(expenditures.get(expenditures.search("electricity")));
    // expenditures.display();

    expenditures.merge(week.slice(0, week.search("Wednesday")));
    expenditures.merge(week.get(week.search("Sunday")));
    expenditures.display();

    expenditures = Object<int>(keys, 7);
    expenditures.display();
    cout<<expenditures.search("Monday")<<endl;
    expenditures.set("Monday", 1000, expenditures.search("Monday"));
    expenditures.set("Tuesday", 2000, expenditures.search("Tuesday"));
    expenditures.set("Wednesday", 3000, expenditures.search("Wednesday"));
    expenditures.set("Thurday", 4000, expenditures.search("Thursday"));
    expenditures.set("Friday", 5000, expenditures.search("Friday"));
    expenditures.set(keys[5], 1000, expenditures.search(keys[5]));
    expenditures.set(keys[6], 1000, expenditures.search(keys[6]));
    expenditures.display();

    cout<<expenditures["Monday"]<<endl;
    expenditures(0).display();

    Object<int>great = expenditures.map(searchByValue);
    great.display();

    expenditures.insert("new", 200, 2).display();

    
    
    // week.push("new", 7);
    // week.display();
    // week.pop(7);
    // week.display();
    // week+="New Day";
    // week.display();
    // week--;
    // week.display();
    // echo(week.getKeys(), week.size);
    // echo(week.getValues(), week.size);
    // Object<char>new_week(7);
    // for (int i = 0; i < 7; i++){
    //     new_week.set(keys[i], keys[i][0], i);
    // }
    // new_week.display();
    // week.merge(new_week);
    // week+Object<int>("New", 9);
    // week.display();

    // Object<char>("Aryan", 'A').display();

    return 0;
}
