#pragma once 
#include "string.h"

class BookCategory
{
    public:
        string CategoryName;
        string CategoryDescription = "none";

    public:
        BookCategory(const string& Name, const string& Description) : CategoryName(Name), CategoryDescription(Description) {}
        BookCategory(const string& Name) : CategoryName(Name) {}

    public:
        void AddDescription(const string& Description) { CategoryDescription = Description; }

    public:
        void operator=(const string& Name) { CategoryName = Name; }
        std::ostream& operator<<(std::ostream& flux) { flux<< CategoryName << " : " << CategoryDescription; return flux;  }
};

class book
{
    public:
        string BookName;
        BookCategory CatName;
        static int NumberOfBooks;
        int Stock;
        
    public:
        book(const string& Name, const string& Category, int stock) : BookName(Name), CatName(Category), Stock(stock) {  NumberOfBooks++; }
        
};

vector<book> BookList;
vector<BookCategory> Categorylist;
void InitialiseBookList();
void InitialiseCategoryList();



 


