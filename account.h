#pragma once 
#include "vector.h"
#include "string.h"
#include <thread>
#include <mutex>
#include<fstream>

static std::mutex usernum,cosnum;

enum class Status
{
    Admin,
    Simp,
    Cos,
    Proprio
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
        string WCAID; // id of the account that created this account

    public:
        // virtual void IdGeneration() = 0;
        void modifyName(const string& name) { Name = name; }
        void modifyDB(const string& Date) { DateofBirth = Date; }
        void modifyAge(const int& age) { Age = age; }

    public:
        Account() {}
        Account(const string& name, int age, const string& DB,const string& wcaid,const Status& stat)  : Name(name), Age(age), DateofBirth(DB), WCAID(wcaid), status(stat) {} 

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
                else if(status == Status::Cos)
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
        Costumer(const string& name, const int& age, const string& DB, const string& RD,const string& wcaid ,const string& Id = "none") : Account(name,age,DB,wcaid,Status::Cos), RegistrationDate(RD)
        {
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
        void operator()(const string& name, const int& age, const string& DB, const string& RD,const string& wacid ,const string& Id = "none");
        void DisplayInfos();

};


class User : public Account
{
    public:
        static int NumUsers;

    public:
        User() { IncrementNum(); }
        User(const string& name, const string& DB, const int& age, const string& wcaid ,const Status& stat,const string& Id) : Account(name,age,DB,wcaid,stat)
        {
            IncrementNum();
        }
        
    private:
        static void IncrementNum() { NumUsers++; }
        void AgeCal(const int& DB, const int& RD) { Age = RD-DB; }

    public:
        void operator=(const User&);
        // void operator()(const string& name, const string& DB, const int& age, const string& wcaid,const Status& stat, const string& Id= "none");

    public:
        void DisplayInfos();
        
};

class SimpleUser : public User
{
    public:
        static int NumSimpleUsers;
        static vector<string> UnusedSUID;

    public:
        SimpleUser(const string& name, const string& DB, const int& age, const string& wcaid ,const string& Id = "none",const Status& stat = Status::Simp) : User(name,DB,age,wcaid,stat,Id)
        {
            IncrementSNum();
            if(Id == "none") Account::IdGeneration(*this,SimpleUser::NumSimpleUsers,SimpleUser::UnusedSUID,this->status);
            else ID = Id;
        }
    
    private:
        static void IncrementSNum() { NumSimpleUsers++; }
    
    public:
        void operator()(const string& name, const string& DB, const int& age, const string& wcaid ,const string& Id = "none",const Status& stat = Status::Simp);
};

class AdminUser : public User
{
    public:
        static int NumAdminUsers;
        static vector<string> UnusedAUID;

    public:
        AdminUser(const string& name, const string& DB, const int& age, const string& wcaid ,const string& Id = "none",const Status& stat = Status::Admin) : User(name,DB,age,wcaid,stat,Id)
        {
            IncrementANum();
            if(Id == "none") Account::IdGeneration(*this,AdminUser::NumAdminUsers,AdminUser::UnusedAUID,this->status);
            else ID = Id;
        }
    
    private:
        static void IncrementANum() { NumAdminUsers++; }
    
    public:
        void operator()(const string& name, const string& DB, const int& age, const string& wcaid ,const string& Id = "none",const Status& stat = Status::Admin);
};

std::ostream& operator<<(std::ostream& flux, const Status& status);

static vector<User> SimpleUserList;
static vector<User> AdminUserList;
static vector<Costumer> CostumerList;

static void DisplayAllSimpleUsers()
{
    for(int i = 0; i < SimpleUserList.size; i++)
    {
        SimpleUserList[i].DisplayInfos();
        std::cout << std::endl << std::endl;
    }
}

static void DisplayAllAdminUsers()
{
    for(int i = 0; i < AdminUserList.size; i++)
    {
        AdminUserList[i].DisplayInfos();
        std::cout << std::endl << std::endl;
    }
}

static void InitialiseSimpleUserList()
{
    char name[20]; //name
    char DB[20]; // db
    char ID[20]; //rd
    char WACID[20]; 
    int age; 
    // User user;
    // std::cout << 'in' << std::endl;
    std::ifstream fileU("files/simpleuser.txt");
    while (fileU >> name >> DB >> age >> WACID >> ID) SimpleUserList.add(SimpleUser(name,DB,age,WACID,ID));
    fileU.close();
    // std::cout << "list : " << wacid << std::endl;
}

static void InitialiseAdminUserList()
{
    char name[20]; //name
    char DB[20]; // db
    char ID[20]; //rd
    char WACID[20]; 
    int age; 
    // User user;
    // std::cout << 'in' << std::endl;
    std::ifstream fileU("files/adminuser.txt");
    while (fileU >> name >> DB >> age >> WACID >> ID) AdminUserList.add(AdminUser(name,DB,age,WACID,ID));
    fileU.close();
    // std::cout << "list : " << wacid << std::endl;
}

static void InitialiseCostumerList()
{
    char name[20];
    int age;
    char DB[20];
    char RD[20];
    char ID[8];
    char w[20];

    std::ifstream fileC("files/costumer.txt");
    while(fileC >> name >> age >> DB >> RD >> w >>ID) CostumerList.add(Costumer(name,age,DB,RD,w,ID));
    fileC.close();
}

static void DisplayAllCostumer()
{
    for(int i = 0; i < CostumerList.size; i++)
    {
        CostumerList[i].DisplayInfos();
        std::cout << std::endl << std::endl;
    }
}

string GetName();

// static void CreateNewAccount(Const)
// {

// }