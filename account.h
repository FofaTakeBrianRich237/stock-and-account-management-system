#pragma once 
#include "vector.h"
#include "string.h"
#include <thread>
#include <mutex>
#include<fstream>

// std::mutex usernum,cosnum;

enum class Status
{
    Admin = 0,
    Simp,
    Cos
};


struct BorrowedBooksData
{
    string Name;
    int quantity;
    static int TotalBorrowed;

    BorrowedBooksData(){};
    BorrowedBooksData(const string& name, const int& quant) : Name(name), quantity(quant) { TotalBorrowed++; }

    std::ostream& operator<<(std::ostream& flux);
};


class Account
{
    public:
        string Name;
        string DateofBirth;
        int Age;
        string ID;
        Status status;

    public:
        // virtual void IdGeneration() = 0;
        void modifyName(const string& name) { Name = name; }
        void modifyDB(const string& Date) { DateofBirth = Date; }
        void modifyAge(const int& age) { Age = age; }

    public:
        Account() {}
        Account(const string& name, int age, const string& DB)  : Name(name), Age(age), DateofBirth(DB) {}

    protected:
        void copy(const Account& other);        
        string DetYear(string&) const;
        int DetInt(string&) const;
        static void FreeID(const Account& user,vector<string>& This) { This.add(user.ID); }
        static void IdGeneration(Account& acc,const int& num,vector<string>& list,const Status& status)
        { 
            if(list.size != 0)
            {
                acc.ID = list[0];
                list.pop(0);
            }
            else
            {
                char * temp = (char*) malloc(sizeof(char) * 7);
                if( status == Status::Simp)
                {
                    temp[0] = 'S';
                    temp[1] = 'I';
                    temp[2] = 'M';
                    temp[3] = 'P';
                }
                else if(status == Status::Admin)
                {
                    temp[0] = 'A';
                    temp[1] = 'D';
                    temp[2] = 'M';
                    temp[3] = 'I';
                }
                else
                {
                    temp[0] = 'C';
                    temp[1] = 'O';
                    temp[2] = 'S';
                    temp[3] = 'T';
                }
                int val;
                auto lambda = [temp,&val] (const int& numZero,int tval)  
                {
                    for(int i = 4; i < 4+numZero; i++) temp[i] = 48;
                    for(int i = 4+numZero; i < 7; i++)
                    {
                        temp[i] = (tval/val) + 48;
                        tval -= ((tval/val)*val);
                        val = val/10;
                    }
                };

                if(num < 10)
                {
                    val = 1;
                    lambda(2,num);
                }
                else if(num < 100)
                {
                    val = 10;
                    lambda(1,num);
                }
                else
                {
                    val = 100;
                    lambda(0,num);
                }

                acc.ID = temp;

                free(temp);
            }
        }
        void ADisplayInfos();
         
};


class Costumer : public Account
{
    public:
        string RegistrationDate;
        static vector<string> UnusedCId;
        static int NumberofCostumers;
        vector<BorrowedBooksData> BorrowedBooksList;
        

    public:
        Costumer() { IncrementNum(); }
        Costumer(const string& name, const int& age, const string& DB, const string& RD, const string& Id = "none") : Account(name,age,DB), RegistrationDate(RD)
        {
            this->status = Status::Cos;
            int temp = Costumer::NumberofCostumers;
            IncrementNum();
            if(Id == "none") 
            {
                // std::thread GenerateCId(&Account::IdGeneration,*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
                Account::IdGeneration(*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
                // if(GenerateCId.joinable()) GenerateCId.detach();
            }
            else ID = Id;
        }


    private:
        static void IncrementNum() {  Costumer::NumberofCostumers++; }

    public:
        void operator=(const Costumer&);
        void operator()(const string& name, const int& age, const string& DB, const string& RD, const string& Id = "none");
        void DisplayInfos();

};


class User : public Account
{
    public:
        static int NumUsers;
        static vector<string> UnusedUId;

    public:
        User() { IncrementNum(); }
        User(const string& name, const string& DB, const int& age, const Status& stat = Status(1), const string& Id = "none") : Account(name,age,DB)
        {
            this->status = stat;
            IncrementNum();
            if(Id == "none") Account::IdGeneration(*this,User::NumUsers,User::UnusedUId,this->status);
            else ID = Id;
        }
        
    private:
        static void IncrementNum() { NumUsers++; }
        void AgeCal(const int& DB, const int& RD) { Age = RD-DB; }

    public:
        void operator=(const User&);
        void operator()(const string& name, const string& DB, const int& age, const Status& stat = Status(1), const string& Id = "none");

    public:
        void DisplayInfos();
        
};

std::ostream& operator<<(std::ostream& flux, const Status& status);

static vector<User> UserList;
static vector<Costumer> CostumerList;
void InitialiseUserList();
void InitialiseCostumerList();
static void some()
{
    UserList.add(User("ad","ad",1,Status(0),"d"));
}