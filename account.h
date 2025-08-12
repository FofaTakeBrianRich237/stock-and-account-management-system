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
std::ostream& operator<<(std::ostream& flux, const Status& status);

struct Month_Data
{
    string Month_name; 
    string Num;
    int Num_Days;
    
    Month_Data(const string& Mname, const string& num, const int& Ndays) : Month_name(Mname), Num(num), Num_Days(Ndays) {} // constructor
};

static Month_Data Months[12] = 
{
    {"January","01",31},
    {"febuary","02",28},
    {"March","03",31},
    {"April","04",30},
    {"May","05",31},
    {"June","06",30},
    {"July","07",31},
    {"August","08",31},
    {"September","09",30}, 
    {"October","10",31},
    {"November","11",30},
    {"December","12",31}
};

struct Date
{
    int day,month,year;
    Date() {}
    Date(const int& d, const int& m, const int& y) : day(d), month(m), year(y) {}  
    friend std::ostream& operator << (std::ostream& flux,const Date& date) { flux << date.day << "/" << date.month << "/" << date.year; return flux; }
};
static Date Actual_Date(31,7,2025);


class Acount
{
    public:
        string Name;
        Date DateofBirth;
        int Age;
        string ID;
        string password;
        Status status;
        string WCAID; // id of the account that created this account
        Date RegistrationDate;
        vector<string> UnAccesedFunctionIDs;

    public:
        void modifyName(const string& name) { Name = name; }
        void modifyDB(const Date& date) { DateofBirth = date; }
        void modifyAge(const int& age) { Age = age; }

    public:
        Acount() {}
        Acount(const string& name, int age, const Date& DB,const string& wcaid,const Status& stat, const Date& RD,const string& PW)  : Name(name), Age(age), DateofBirth(DB), WCAID(wcaid), status(stat), RegistrationDate(RD)
        {
            if(PW == "none") GeneratePassword();
            else password = PW;
        } 

    protected:
        void copy(const Acount& other);        
        string DetYear(string&) const;
        int DetInt(string&) const;
        static void FreeID(const Acount& user,vector<string>& This) { This.add(user.ID); }
        static void IdGeneration(Acount& acc,const int& num,vector<string>& list,const Status& status)
        { 
            if(list.size != 0)
            {
                acc.ID = list[0];
                list.pop(0);
            }
            else
            {
                char * temp = (char*) malloc(sizeof(char) * 7);

                auto StatusFilling = [temp] (const string& status) { for(int i = 0; i < 4; i++) temp[i] = status.String[i]; };

                if( status == Status::Simp) StatusFilling("SIMP");
                else if(status == Status::Admin) StatusFilling("ADMI");
                else if(status == Status::Cos) StatusFilling("COST");
                
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
    public:
        void DisplayInfos();
        void GeneratePassword();
         
};

class Costumer : public Acount
{
    public:
        static vector<string> UnusedCId;
        static int NumberofCostumers;
        

    public:
        Costumer() { IncrementNum(); }
        Costumer(const string& name, const int& age, const Date& DB, const Date& RD,const string& wcaid ,const string& PW = "none",const string& Id = "none") : Acount(name,age,DB,wcaid,Status::Cos,RD,PW)
        {
            IncrementNum();
            if(Id == "none") Acount::IdGeneration(*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
            else ID = Id;
        }

    private:
        static void IncrementNum() {  Costumer::NumberofCostumers++; }

    public:
        void operator=(const Costumer&);
        void operator()(const string& name, const int& age, const Date& DB, const Date& RD,const string& wacid ,const string& PW,const string& Id = "none");

};

class User :  public Acount
{
    public:
        static int NumUsers; 

    public:
        User() { IncrementNum(); }
        User(const string& name, const Date& DB, const int& age, const string& wcaid ,const Status& stat,const string& Id,const string& PW,const Date& RD) : Acount(name,age,DB,wcaid,stat,RD,PW) { IncrementNum(); }
        
    private:
        static void IncrementNum() { NumUsers++; }
        void AgeCal(const int& DB, const int& RD) { Age = RD-DB; }

    public:
        void operator=(const User&);

    public:
        void PassWordReste();
        
};

class SimpleUser : public User
{
    public:
        static int NumSimpleUsers;
        static vector<string> UnusedSUID;

    public:
        SimpleUser(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW = "none", const string& Id = "none",const Status& stat = Status::Simp) : User(name,DB,age,wcaid,stat,Id,PW,RD)
        {
            IncrementSNum();
            if(Id == "none") Acount::IdGeneration(*this,SimpleUser::NumSimpleUsers,SimpleUser::UnusedSUID,this->status);
            else ID = Id;
        }
    
    private:
        static void IncrementSNum() { NumSimpleUsers++; }
    
    public:
        void operator()(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW = "none", const string& Id = "none",const Status& stat = Status::Simp);
};

class AdminUser : public User
{
    public:
        static int NumAdminUsers;
        static vector<string> UnusedAUID;

    public:
        AdminUser(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW = "none", const string& Id = "none",const Status& stat = Status::Admin) : User(name,DB,age,wcaid,stat,Id,PW,RD)
        {
            IncrementANum();
            if(Id == "none") Acount::IdGeneration(*this,AdminUser::NumAdminUsers,AdminUser::UnusedAUID,this->status);
            else ID = Id;
        }
    
    private:
        static void IncrementANum() { NumAdminUsers++; }
    
    public:
        void operator()(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW = "none", const string& Id = "none",const Status& stat = Status::Admin);
};


static vector<User> SimpleUserList;
static vector<User> AdminUserList;
static vector<Costumer> CostumerList;

//--------------Infos display function for Constumers/Users---------------
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

static void DisplayAllCostumers()
    {
        for(int i = 0; i < CostumerList.size; i++)
        {
            CostumerList[i].DisplayInfos();
            std::cout << std::endl << std::endl;
        }
    }
//------------------------------------------------------------------------

//---------------Initialising Costumers and USers(simple/admin) lists------------------
 //Initailise Simple User list from simple users file
static void InitialiseSimpleUserList()
{
    char name[20]; //name
    int DB[3]; // db
    int RD[3];
    char ID[20]; //rd
    char WACID[20]; 
    char password[20];
    int age; 
    // User user;
    // std::cout << 'in' << std::endl;
    std::ifstream fileU("User/Costumers_Data/simpleuser.txt");
    while (fileU >> name >> DB[0] >> DB[1] >> DB[2] >> age >> WACID >> RD[0] >> RD[1] >> RD[2] >> password >> ID) SimpleUserList.add(SimpleUser(name,{DB[0],DB[1],DB[2]},age,WACID,{RD[0],RD[1],RD[2]},password,ID));
    fileU.close();
    // std::cout << "list : " << wacid << std::endl;
}

 //Initailise Admin User list from Admin users file
static void InitialiseAdminUserList()
{
    char name[20]; //name
    int DB[3]; // db
    int RD[3];
    char ID[20]; 
    char WACID[20]; 
    char password[20];
    int age; 

    std::ifstream fileU("User/Costumers_Data/adminuser.txt");
    while (fileU >> name >> DB[0] >> DB[1] >> DB[2] >> age >> WACID  >> RD[0] >> RD[1] >> RD[2] >> password >> ID) AdminUserList.add(AdminUser(name,{DB[0],DB[1],DB[2]},age,WACID,{RD[0],RD[1],RD[2]},password,ID));
    fileU.close();
}

 //Initialise Costumer list from the Costumers file
static void InitialiseCostumerList()
{
    char name[20];
    int age;
    int DB[3];
    int RD[3];
    char ID[8];
    char w[20];
    char PW[20];

    std::ifstream fileC("User/Costumers_Data/costumer.txt");
    while (fileC >> name >> age >> DB[0] >> DB[1] >> DB[2] >> RD[0] >> RD[1] >> RD[2] >> w >> PW >>ID)
    CostumerList.add(Costumer(name, age, {DB[0], DB[1], DB[2]}, {RD[0], RD[1], RD[2]}, w, PW,ID));
    fileC.close();
}
//----------------------------------------------------------------------------------------

//------------Unused Users,Costumer IDs list fiiling------------------
std::istream& getline(std::istream& is, string& st); // overloading getline function tu work with our string class

 //Function fills the different stored IDs into their respective vector list
  //vec is the variable that represent the unused ID list which may be that for Uers(simple/admin) and Costumers
  // st is that string that stores the different IDs stored in the UnusedIDs file(txt file for know)
static void fill(vector<string>& vec,string& st)
{
    string temp(8);
    for(int i = 0,j = 0; i < st.length+1; i++,j++)
    { 
        // IDs seperation mechanism
        if(st[i] != ' ' && st[i] != '\0')  temp[j] = st.String[i]; 
        else { vec.add(temp); j = -1; }
        //-------------------------
    }
}

 //Function gets the Unused IDs from the Unused IDs file (txt file for know)
static void InitialiseUnusedIDs()
{
    string IDs; // used to store the IDs goten from file
    std::ifstream filec("User/Costumers_Data/Un");
    for(int i = 1; i < 4; i++)
    {
        //geting and filling the gotten IDs in their repsectif lists
        getline(filec,IDs);
        if(i == 1)fill(Costumer::UnusedCId,IDs);// filling costumers Unused IDs
        else if (i == 2) fill(AdminUser::UnusedAUID,IDs);// filling Admin users Unused IDs
        else fill(SimpleUser::UnusedSUID,IDs);// filling Simple users Unused IDs
        //----------------------------------------------------------
    }
    filec.close();
}
//----------------------------------------------------------------------


string GetName();
Date GetDb();
int GetAge();


//-----------Acount creation functions-----------
  //-----Costumer acount creation function
   //WCAID is the string containing the ID of the Acount that creat the Costumer Acount
   //Date_of_today stores the actual registration date of the costumer
static void CreateNewCostumer(const string& WCAID,const Date& Date_of_today)
{
    CostumerList.add(Costumer(GetName(),GetAge(),GetDb(),Date_of_today,WCAID));
}

  //------Simple user acount user creation fucntion
   //----WCAID is the string containing the ID of the Acount that creat the Simple user Acount
   //Date_of_today stores the actual registration date of Simple user
static void CreateNewSimpleUser(const string& WCAID,const Date& Date_of_today)
{
    SimpleUserList.add(SimpleUser(GetName(),GetDb(),GetAge(),WCAID,Date_of_today,WCAID));
}

 //------Admin user acount creation function
  //----WCAID is the string containing the ID of the Acount that creat the Admin user Acount
  //Date_of_today stores the actual registration date of the Admin user
static void CreateNewAdminUser(const string& WCAID,const Date& Date_of_today)
{
    AdminUserList.add(AdminUser(GetName(),GetDb(),GetAge(),WCAID,Date_of_today,WCAID));
}
//------------------------------------------------
