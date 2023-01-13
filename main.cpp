#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;

class Person{

};

class Client
{
protected:
    int clientID;
    string clientName;
public:
    Client(int id,string name):clientID(id),clientName(name){}
    virtual void display_client_info()=0;
};

class PersonalClient : public Client
{
private:
    string personalPhoneNumber;
public:
    PersonalClient(int id,string name,string phone):Client(id,name),personalPhoneNumber(phone){}
    void display_client_info()
    {
        cout<<"ID: "<<clientID<<endl;
        cout<<"Name: "<<clientName<<endl;
        cout<<"Phone Number: "<<personalPhoneNumber<<endl;
    }
};

class BusinessClient : public Client
{
private:
    string businessPhoneNumber;
public:
    BusinessClient(int id,string name,string phone):Client(id,name),businessPhoneNumber(phone){}
    void display_client_info()
    {
        cout<<"ID: "<<clientID<<endl;
        cout<<"Name: "<<clientName<<endl;
        cout<<"Phone Number: "<<businessPhoneNumber<<endl;
    }
};


template <typename T>
class Account{
private:
    T accountNumber;
    T accountHolderName;
    T accountBalance;

public:
    Account(T accountNumber, T accountHolderName, T accountBalance)
    {
        this->accountNumber = accountNumber;
        this->accountHolderName = accountHolderName;
        this->accountBalance = accountBalance;
    }

    void deposit(T amount)
    {
        accountBalance += amount;
    }

    void withdraw(T amount)
    {
        if (amount > accountBalance)
        {
            cout << "Insufficient funds." << endl;
            return;
        }
        accountBalance -= amount;
    }

    T getAccountNumber()
    {
        return accountNumber;
    }

    T getAccountHolderName()
    {
        return accountHolderName;
    }

    T getAccountBalance()
    {
        return accountBalance;
    }
};

int main(){
    cout << "Hello World!";
}
