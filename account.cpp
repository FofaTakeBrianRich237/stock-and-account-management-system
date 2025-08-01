#include "account.h"
using std::cout;
using std::endl;
using std::cin;

std::ostream& BorrowedBooksData::operator<<(std::ostream& flux)
{
    flux << "{" << this->Name << ", " << this->quantity << "}";
    return flux;
}

// void InitialiseUserList()
// {
//     // UserList.add(User("Bigis","18/11/1999",));
// }

void Account::copy(const Account& other)
{
    this->Age = other.Age;
    this->DateofBirth = other.DateofBirth;
    this->Name = other.Name;
    this->ID = other.ID;
    this->status = other.status;
    this->WCAID = other.WCAID;
}

void Costumer::operator=(const Costumer& other)
{
    this->copy(other);
    this->RegistrationDate = other.RegistrationDate;
}

void User::operator=(const User& other)
{
    this->copy(other);
}

string Account::DetYear(string& st) const
{
    int len;
    char temp[4];

    for(len = 0; st[len] != '\0'; len++);
    for(int i = len-1,j = 0; i > len-5; i--,j++) temp[j] = st[i];

    return string(temp);
}

int Account::DetInt(string& st) const
{
    int val = 0;
    for(int i = 0,mul = 1000; i < 4; i++,(mul = mul/10))
    {
        if(mul != 0) val += (int(st[i])-48) * mul;
        else val += (int(st[i]-48));
    }
    return val;
}

std::ostream& operator<<(std::ostream& flux, const Status& status)
{
    if(status == Status::Admin) flux << "ADMIN USER";
    else if(status == Status::Simp) flux << "SIMPLE USER";
    else if(status == Status::Cos) flux << "COSTUMER";
    else flux << "PROPRIETOR";

    return flux;
}

void Costumer::operator()(const string& name, const int& age, const string& DB, const string& RD, const string& wacid ,const string& Id)
{
    this->status = Status::Cos;
    this->Name = name;
    this->Age = age;
    this->DateofBirth = DB;
    this->RegistrationDate = RD;
    this->WCAID = wacid;
    if(Id == "none") 
    {
        // std::thread GenerateCId(&Account::IdGeneration,*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
        Account::IdGeneration(*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
        // if(GenerateCId.joinable()) GenerateCId.detach();
    }
    else ID = Id;
}

// void User::operator()(const string& name, const string& DB, const int& age, const string& wcaid,const Status& stat, const string& Id)
// {
//     this->status = stat;
//     this->Age = age;
//     this->DateofBirth = DB;
//     this->Name = name;
//     this->WCAID = wcaid;
//     if(Id == "none") Account::IdGeneration(*this,User::NumUsers,User::UnusedUId,this->status);
//     else ID = Id;
// }

void SimpleUser::operator()(const string& name, const string& DB, const int& age, const string& wcaid , const string& PW, const string& Id,const Status& stat)
{
    this->status = stat;
    this->Age = age;
    this->DateofBirth = DB;
    this->Name = name;
    this->WCAID = wcaid;
    if(Id == "none") Account::IdGeneration(*this,SimpleUser::NumSimpleUsers,SimpleUser::UnusedSUID,this->status);
    else ID = Id;
    if(PW == "none") GeneratePassword();
    else password = PW;
}

void AdminUser::operator()(const string& name, const string& DB, const int& age, const string& wcaid , const string& PW, const string& Id,const Status& stat)
{
    this->status = stat;
    this->Age = age;
    this->DateofBirth = DB;
    this->Name = name;
    this->WCAID = wcaid;
    if(Id == "none") Account::IdGeneration(*this,AdminUser::NumAdminUsers,AdminUser::UnusedAUID,this->status);
    else ID = Id;
    if(PW == "none") GeneratePassword();
    else password = PW;
}

void Account::ADisplayInfos()
{
    cout << "Name : " << this->Name << endl;
    cout << "Age : " << this->Age << endl;
    cout << "Date of birth : " << this->DateofBirth << endl;
    cout << "Id : " << this->ID << endl;
    cout << "Status : " << this->status << endl;
    cout << "Account created by : "  << this->WCAID << endl;
}

void Costumer::DisplayInfos()
{
    this->ADisplayInfos();
    cout << "Registration date : " << this->RegistrationDate << endl;
}

void User::DisplayInfos()
{
    // cout << "merde" << endl;
    this->ADisplayInfos();
}

void User::GeneratePassword()
{
    auto StrongPassword = [this](string& PW)
    {
        bool LowerCaseFound = false;
        bool UpperCaseFound = false;
        bool NumbersFound = false;
        
        cout << "Enter password" << endl;
        cin >> PW;

        for(int i = 0; PW[i] != '\0'; i++) 
        {
            if(PW[i] >= 'a' && PW[i] <= 'z') LowerCaseFound = true;
            else if(PW[i] >= 'A' && PW[i] <= 'Z') UpperCaseFound = true; 
            else if(PW[i] >= '0' && PW[i] <= '9') NumbersFound = true;
            // else { cout << "special charaters not aloud" << endl; return false;}
            if(LowerCaseFound && UpperCaseFound && NumbersFound) { password = PW; return true;}
        }

        if(!LowerCaseFound) cout << "Need at least one lower case letter" << endl;
        else if(!UpperCaseFound) cout << "Need at least one upper case letter" << endl; 
        else cout << "Need at least one digit number" << endl;

        return false;
    };

    for(string temp; !StrongPassword(temp) ; );
}

void User::PassWordReste()
{
    string temp;
    bool found;
    do 
    {
        cout << "Enter current password" << endl;
        cin >> temp;
        if(temp == "exit") {found = false; break;}
        cout << temp.length << endl;
    }
    while (password != temp);
    found = true;
    cout << "------------Password Rest------------" << endl;
    if(found) GeneratePassword();
}


string GetName()
{
    string name;
    std::cout << "Enter name " << std::endl;
    std::cin >> name;
    return string(name);
}


// string GetDb()
// {
//     int day,month,year;
//     cout << "Date of birth" << endl;
//     cout << "Enter the day" << endl;
//     day 
// }