#pragma once 
#include <iostream>

class string
{
    public:
        char * String = nullptr;    
        int length = 0;

    public:
        string(){};
        string(const int& size) : length(size) { String = (char*)malloc(sizeof(char) * length); }
        string(const char* word) { copy(word); }
        ~string()
        {
            String = nullptr;
        }
    
    public:
        friend std::ostream& operator<<(std::ostream& flux,const string& st);
        friend std::istream& operator>>(std::istream& flux, string& st);
        friend string operator+(const string& one , const string& two); // to be donne
        void operator=(const string& st) { copy(st.String); }
        void operator=(const char* st) { copy(st); }
        char& operator[](const int& pos) { return String[pos]; }
        void operator+=(const string& other);
        

    private:
        void copy(const char* st);
    
    public:
        void push_back(const char&);
};

bool operator==(const string&, const string&);
bool operator==(const string&, const char*);
bool operator!=(const string&, const string&);
bool operator!=(const string&, const char*);
// char operator[](const string& String,const int& pos) { return String.String[pos]; }

