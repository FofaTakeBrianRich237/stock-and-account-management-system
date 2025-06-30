#include "account.h"
#include "book.h"
#include<fstream>

using std::cout;
using std::endl;
using std::cin;

int Costumer::NumberofCostumers = 0;
int User::NumUsers = 0;
int SimpleUser::NumSimpleUsers = 0;
int AdminUser::NumAdminUsers = 0;

int BorrowedBooksData::TotalBorrowed;
vector<string> Costumer::UnusedCId;
vector<string> SimpleUser::UnusedSUID;
vector<string> AdminUser::UnusedAUID;
// vector<string> User::UnusedUId;

int main()
{

    InitialiseAdminUserList();
    InitialiseSimpleUserList();
    // InitialiseCostumerList();
    // DisplayAllCostumer();
    DisplayAllSimpleUsers();
    cout << "----------------------------" << endl;
    DisplayAllAdminUsers();
    // cout << SimpleUserList.size << endl;
    return 0;
    
}