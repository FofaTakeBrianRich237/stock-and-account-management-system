#include "account.h"
using std::cout;
using std::endl;
using std::cin;


void Acount::copy(const Acount& other)
{
    this->Age = other.Age;
    this->DateofBirth = other.DateofBirth;
    this->Name = other.Name;
    this->ID = other.ID;
    this->status = other.status;
    this->WCAID = other.WCAID;
    this->RegistrationDate = other.RegistrationDate;
    this->password = other.password;
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

string Acount::DetYear(string& st) const
{
    int len;
    char temp[4];

    for(len = 0; st[len] != '\0'; len++);
    for(int i = len-1,j = 0; i > len-5; i--,j++) temp[j] = st[i];

    return string(temp);
}

int Acount::DetInt(string& st) const
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

void Costumer::operator()(const string& name, const int& age, const Date& DB, const Date& RD, const string& wacid ,const string& PW,const string& Id)
{
    this->status = Status::Cos;
    this->Name = name;
    this->Age = age;
    this->DateofBirth = DB;
    this->RegistrationDate = RD;
    this->WCAID = wacid;
    this->password = PW;
    if(Id == "none") Acount::IdGeneration(*this,Costumer::NumberofCostumers,Costumer::UnusedCId,this->status);
    else ID = Id;
}

void SimpleUser::operator()(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW, const string& Id,const Status& stat)
{
    this->status = stat;
    this->Age = age;
    this->DateofBirth = DB;
    this->Name = name;
    this->WCAID = wcaid;
    this->RegistrationDate = RD;
    if(Id == "none") Acount::IdGeneration(*this,SimpleUser::NumSimpleUsers,SimpleUser::UnusedSUID,this->status);
    else ID = Id;
    if(PW == "none") GeneratePassword();
    else password = PW;
}

void AdminUser::operator()(const string& name, const Date& DB, const int& age, const string& wcaid , const Date& RD, const string& PW, const string& Id,const Status& stat)
{
    this->status = stat;
    this->Age = age;
    this->DateofBirth = DB;
    this->Name = name;
    this->WCAID = wcaid;
    this->RegistrationDate = RD;
    if(Id == "none") Acount::IdGeneration(*this,AdminUser::NumAdminUsers,AdminUser::UnusedAUID,this->status);
    else ID = Id;
    if(PW == "none") GeneratePassword();
    else password = PW;
}

void Acount::DisplayInfos()
{
    cout << "Name : " << this->Name << endl;
    cout << "Age : " << this->Age << endl;
    cout << "Date of birth : " << this->DateofBirth << endl;
    cout << "Id : " << this->ID << endl;
    cout << "Status : " << this->status << endl;
    cout << "Account created by : "  << this->WCAID << endl;
    cout << "Rigstration date : " << this->RegistrationDate << endl;
}

void Acount::GeneratePassword()
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

    for(string temp; !StrongPassword(temp); );
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
    return name;
}

Date GetDb()
{
    Date Date_of_Birth;
    int day,month,year;

    // bool valid  = false;
    // auto lambda = [&day,&month,&year](){};
    // auto SizeCheck = [](const int& parameter, const int& end) { return ( parameter > 0 && parameter <= end) ? true : false;};
    // auto Month_Limit = [](const int& month_num) {};

    cout << "Date of birth" << endl;    
    cout << "Enter the year" << endl;
    cin >> year;
    cout << "Enter the month" << endl;
    cin >> month;
    cout << "Enter the day" << endl;
    cin >> day;

    Date_of_Birth = {day,month,year};\
    return Date_of_Birth;
}

int GetAge()
{
    int age;
    cout << "Enter Age please"  << endl;
    cin >> age;
    return age;
}

std::istream& getline(std::istream& file, string& st)
{
    char ch;
    st.length = 0;
    while(file.get(ch) && ch != '\n') {st.push_back(ch);}
    if(file.eof() && st.length > 0) file.clear();
    return file;
}

