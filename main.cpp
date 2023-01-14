#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <conio.h>

using namespace std;

class Account
{
protected:
    int accountNumber;
    string accountHolderName;
    double accountBalance;

public:
    Account(int accountNumber, string accountHolderName, double accountBalance) :
            accountNumber(accountNumber), accountHolderName(accountHolderName), accountBalance(accountBalance) {}

    virtual void deposit(double amount)
    {
        accountBalance += amount;
    }

    virtual void withdraw(double amount)
    {
        if (amount > accountBalance)
        {
            cout << "Insufficient funds." << endl;
            return;
        }
        accountBalance -= amount;
    }

    friend istream& operator>>(istream& in, Account& a)
    {
        cout << endl;
        cout << "NAME: ";
        in >> a.accountHolderName;
        cout << "\n INITIAL DEPOSIT: "
        in >> a.accountBalance;
    };

    friend ostream& operator<< (ostream& out, Account& a)
    {
        out << endl;
        out << " ACCOUNT #id: " << a.accountNumber << endl;
        out << " NAME: " << a.accountHolderName << endl;
        out << " BALANCE: " << a.accountBalance << "$\n";
        return out;
    }
};

class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount(int accountNumber, string accountHolderName, double accountBalance, double interestRate) :
            Account(accountNumber, accountHolderName, accountBalance), interestRate(interestRate) {}

    void deposit(double amount)
    {
        accountBalance += amount + amount*interestRate;
    }
};

class CheckingAccount : public Account
{
private:
    double overdraftFee;

public:
    CheckingAccount(int accountNumber, string accountHolderName, double accountBalance, double overdraftFee) :
            Account(accountNumber, accountHolderName, accountBalance), overdraftFee(overdraftFee) {}

    void withdraw(double amount)
    {
        if (amount > accountBalance)
        {
            accountBalance -= overdraftFee;
            cout << "Overdraft fee applied. New balance: " << accountBalance << endl;
        }
        else
        {
            accountBalance -= amount;
        }
    }
};

template <typename T>
class Person
{
protected:
    T firstName;
    T lastName;
    T age;
public:
    Person(T firstName, T lastName, T age)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->age = age;
    }
    virtual void display()
    {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Age: " << age << endl;
    }
};

class Client : public Person<string>
{
private:
    int clientID;
public:
    Client(int id,string firstName,string lastName,int age):Person(firstName,lastName,age),clientID(id){}
    void display()
    {
        Person::display();
        cout<<"ID: "<<clientID<<endl;
    }
};

int main(){

}
