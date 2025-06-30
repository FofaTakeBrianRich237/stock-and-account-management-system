#include "account.h"
#include "book.h"
#include<fstream>

using std::cout;
using std::endl;
using std::cin;

int Costumer::NumberofCostumers = 0;
int User::NumUsers = 0;
int BorrowedBooksData::TotalBorrowed;
vector<string> Costumer::UnusedCId;
vector<string> User::UnusedUId;

int main()
{

    InitialiseUserList();
    // InitialiseCostumerList();
    // DisplayAllCostumer();
    DisplayAllUsers();
    // cout << "massa : " << CostumerList[0].WCAID << endl;
    // cout << GetName() << endl;
    return 0;
    
}