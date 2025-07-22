#pragma once 
#include <iostream>

class string
{
    public:
        char * String;    
        int length;

    public:
        string(){};
        string(const char* word) { copy(word); }
        ~string()
        {
            String = nullptr;
        }
    
    public:
        friend std::ostream& operator<<(std::ostream& flux,const string& st);
        friend std::istream& operator>>(std::istream& flux, string& st);
        void operator=(const string& st) { copy(st.String); }
        void operator=(const char* st) { copy(st); }
        char& operator[](const int& pos) { return String[pos]; }
        

    private:
        void copy(const char* st);
};

bool operator==(const string&, const string&);
bool operator==(const string&, const char*);
bool operator!=(const string&, const string&);
bool operator!=(const string&, const char*);
// char operator[](const string& String,const int& pos) { return String.String[pos]; }

