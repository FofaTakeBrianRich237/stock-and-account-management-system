#pragma once 
#include <iostream>

template<typename type>
class vector
{
    public:
    type * array = nullptr;
    int size = 0;

    public :
    vector() {}
    ~vector() {free(array);}

    public :
    type& At(const int& pos)
    {
        if(pos >= 0 && pos < this->size) return this->array[pos];
        else 
        {
            std::cout << "invalid position" << std::endl;
            return array[this->size];
        }
    }

    type& Front() { return array[0]; }

    type& Back() { return array[size - 1]; }

    void Fill(const type& Value) { if( this->size > 0 ) for(int i = 0; i < this->size; i++) this->array[i] = Value; }

    void Swap(vector<type>& other)
    { 
        type temp;

        auto lambda = [&temp,&other](vector<type>* val,int limit)
        {
            for(int i = 0; i < limit;i++)
            {
                temp = val->array[i];
                val->array[i] = other.array[i];
                other.array[i] = temp;
            }
        };

        if(other.size == this->size || other.size < this->size) lambda(this,this->size);
        else lambda(this,other.size);
    }

    constexpr int Size() const { return this->size; }

    void add(const type& NewVal) 
    {
        if( this->array != nullptr) 
        {
            auto lambda = [this](type* init,const type* final)
            {
                for(int i = 0; i < this->size; i++) init[i] = final[i];
            };
            
            type * temp = (type*) malloc(sizeof(type) * size);
            lambda(temp,array);

            free(array);
            array = (type*) malloc(sizeof(type) * (size+1)); 
            lambda(array,temp);
            size++;
            array[size - 1] = NewVal;

            free(temp);
        }
        else 
        {
            array = (type*) malloc(sizeof(type) * ++size);
            array[0] = NewVal;
        }
    }

    void pop(const int& pos = -1)
    {
        if(size != 0)
        {
            auto lambda = [this](const int& p)
            {
                type * temp = (type*) malloc(sizeof(type) * (size-1));
                for(int i = 0,j = 0; i < size; i++) { if(i != p) temp[j++] = array[i]; }
                array = nullptr;
                array = (type*) malloc(sizeof(type) * --size);
                for(int i = 0; i < size; i++) array[i] = temp[i];
                free(temp);
            };

            if(pos < -1 || pos > size) std::cout << "invalid position" << std::endl;
            else if(pos != -1) lambda(pos);
            else lambda(size-1);
        }
        else std::cout << "no element to pop" << std::endl;
    }

    class Iterator
    {
        public:
        type * it;

        public:
        Iterator(){};
        Iterator(type* val) {it = val;}
        // Iterator(const Iterator& other) { this->it = other.it; }

        public:
        type& operator*() { return *it; }
        Iterator& operator++(int) { it++; return *this; }
        Iterator& operator++() { ++it; return *this; }
        Iterator& operator--(int) { it--; return *this; }
        Iterator operator+(const int& val) 
        { 
            Iterator temp(*this);
            temp.it = temp.it + 1;
            return temp;
        }

        Iterator operator-(const int& val) 
        { 
            Iterator temp(*this);
            temp.it = temp.it - 1;
            return temp;
        }
        const bool operator!=(const Iterator& other) { if(this->it != other.it) return true; else return false;}
        const bool operator==(const Iterator& other) { if(this->it == other.it) return true; else return false; }
    };

    // Iterator begin() { Iterator a(array); return a; }
    // Iterator end() { Iterator a(array + (size)); return a; }

    Iterator begin() { return Iterator(this->array); }
    Iterator end() { return Iterator(array - size); }

    public :
    type& operator[](const int& pos)
    {
        if(pos >= 0 && pos < this->size) return this->array[pos];
        else 
        {
            std::cout << "invalid position" << std::endl;
            return array[this->size];
        }
    }

};

template<typename type>
std::ostream& operator<<(std::ostream& flux,const vector<type>& a)
{
    if(a.size != 0) 
    {
        for(int i = 0; i < a.size; i++) 
        {
            flux << a.array[i]; 
            if(i < a.size-1) flux << ",";
        }
    }
    else flux << "empty list" << std::endl;

    return flux;
}

