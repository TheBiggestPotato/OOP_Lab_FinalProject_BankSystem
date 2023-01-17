#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <string>
#include <conio.h>

using namespace std;

/*
1
2.CREATE NEW ACCOUNT -> use map
3.MAKE A DEPOSIT
4.CONVERT ACCOUNT
5.MAKE A WITHDRAWAL
6.DELETE AN ACCOUNT
7.TRANSFER MONEY TO ANOTHER ACCOUNT
8.SHOW TRANSACTIONS
9.GENERATE BANK STATEMENT(optional)
10.SHOW YOUR DETAILS(optional)
11.UPDATE YOUR DETAILS(optional)
0.EXIT
*/

class Account
{
protected:
    string accountName;
    string iban;
    string accountHolderName;
    double accountBalance;

public:
    Account(string accountName, string iban, string accountHolderName, double accountBalance) :
            accountName(accountName), iban(iban), accountHolderName(accountHolderName), accountBalance(accountBalance) {}
    Account() : accountName("GHOST ACCOUNT"), iban("BNK0CURR0000"), accountHolderName("GHOST"), accountBalance(0.0) {}
    Account(const Account& a)
    {
        accountName = a.accountName;
        iban = a.iban;
        accountHolderName = a.accountHolderName;
        accountBalance = a.accountBalance;
    }
    ~Account() {}


    virtual void deposit(double amount)
    {
        this->accountBalance += amount;
    }

    virtual void withdraw(double amount)
    {
        if (amount > this->accountBalance)
        {
            throw runtime_error("Insufficient funds.");
            return;
        }
        this->accountBalance -= amount;
    }

    string getAccountName() {
        return this->accountName;
    }

    friend istream& operator>> (istream& in, Account& a)
    {
        cout << " ACCOUNT'S NAME: ";
        in >> a.accountName;
        a.accountBalance = 0.0;
        a.iban = "BNK0ACC" + to_string((long)rand() + 10000000);

        return in;
    }

    friend ostream& operator<< (ostream& out, Account& a)
    {
        out << "\nACCOUNT NAME: " << a.accountName;
        out << "\nIBAN: " << a.iban;
        out << "\nACCOUNT BALLANCE: " << a.accountBalance;

        return out;
    }

    Account& operator=(const Account& a)
    {
        if (this != &a)
        {
            this->accountName = a.accountName;
            this->iban = a.iban;
            this->accountHolderName = a.accountHolderName;
            this->accountBalance = a.accountBalance;
        }

        return *this;
    }

};

class SavingsAccount : public Account
{
    //Copy constructor
    //= overloading
private:
    double interestRate;
protected:
    static string accountType;

public:
    SavingsAccount(string accountName, string iban, string accountHolderName, double accountBalance, double interestRate) :
            Account(accountName, iban, accountHolderName, accountBalance), interestRate(interestRate) {}
    SavingsAccount() : Account(), interestRate(0.0) {}
    ~SavingsAccount() { Account::~Account(); }

    void deposit(double amount)
    {
        this->accountBalance += amount + amount * this->interestRate;
    }

    friend istream& operator>> (istream& in, SavingsAccount& a)
    {
        cout << " ACCOUNT'S NAME: ";
        in >> a.accountName;
        a.accountBalance = 0.0;
        a.iban = "BNK0ACC0SV" + to_string((long)rand() + 1000000000);
        a.interestRate = 0.03;

        return in;
    }

    friend ostream& operator<< (ostream& out, SavingsAccount& a)
    {
        out << "\nACCOUNT NAME: " << a.accountName;
        out << "\nIBAN: " << a.iban;
        out << "\nACCOUNT BALLANCE: " << a.accountBalance;
        out << "\nACCOUNT TYPE: " << a.accountType;
        out << "\nINTEREST RATE: " << a.interestRate;

        return out;
    }
};
string SavingsAccount::accountType = "Savings Account";

class CheckingAccount : public SavingsAccount
{
    //Copy constructor
    //= overloading
private:
    double overdraftFee;
protected:
    static string accountType;

public:
    CheckingAccount(string accountName, string iban, string accountHolderName, double accountBalance, double overdraftFee, double interestRate) :
            SavingsAccount(accountName, iban, accountHolderName, accountBalance, interestRate), overdraftFee(overdraftFee) {}
    CheckingAccount() : SavingsAccount(), overdraftFee(0.0) {}
    ~CheckingAccount() { SavingsAccount::~SavingsAccount(); }

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

    friend istream& operator>> (istream& in, CheckingAccount& a)
    {
        cout << " ACCOUNT'S NAME: ";
        in >> a.accountName;
        a.accountBalance = 0;
        a.iban = "BNK0ACC0CH" + to_string((long)rand() + 100000);
        a.overdraftFee = 0.05;

        return in;
    }

    friend ostream& operator<< (ostream& out, CheckingAccount& a)
    {
        out << "\nACCOUNT NAME: " << a.accountName;
        out << "\nIBAN: " << a.iban;
        out << "\nACCOUNT BALLANCE: " << a.accountBalance;
        out << "\nACCOUNT TYPE: " << a.accountType;
        out << "\nOVERDRAFT FEE %: " << a.overdraftFee;

        return out;
    }
};
string CheckingAccount::accountType = "Checking Account";

class Client
{
    // Copy Constructor
    // = overload
private:
    int clientID;
    string name;
    string bday;
    string socialSecurityNo;

    string email;
    string password;

    vector<Account> accounts;
protected:
    static int nextClientID;
public:

    Client() : clientID(0), name("GHOST"), bday("N/A"), socialSecurityNo("0000") {}
    Client(int clientID, string name, string bday, string socialSecurityNo) {
        this->clientID = ++nextClientID;
        this->name = name;
        this->bday = bday;
        this->socialSecurityNo = socialSecurityNo;
    }
    ~Client() {}

    void displayAccounts()
    {
        if (accounts.size() == 0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "NO ACCOUNT HAVE BEEN FOUND!";
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            return;
        }

        for (int i = 0; i < accounts.size(); i++)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << accounts.at(i) << "\n";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        }
    }

    void depositAmount(double amount, int i)
    {
        accounts.at(i).deposit(amount);
    }

    void withdrawAmount(double amount, int i)
    {
        try
        {
            accounts.at(i).withdraw(amount);
        }
        catch (const runtime_error& e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    void createSavingsAccount(const SavingsAccount& a)
    {
        this->accounts.push_back(a);
    }

    void createCheckingAccount(const CheckingAccount& a)
    {
        this->accounts.push_back(a);
    }

    int getNumberOfAccounts()
    {
        return accounts.size();
    }

    vector<Account> getAccounts() const {
        return this->accounts;
    }

    string get_email() {
        return this->email;
    }

    string get_password() {
        return this->password;
    }

    friend ostream& operator<< (ostream& out, Client& c)
    {
        out << "NAME: " << c.name;
        out << "DATE OF BIRTH: " << c.bday;
        out << "SOCIAL SECURITY NUMBER: " << c.socialSecurityNo;
        out << "EMAIL: " << c.email;
    }
    friend istream& operator>> (istream& in, Client& c)
    {
        string name;
        cout << " NAME: ";
        in >> name;
        c.name = name;
        cout << endl << " SOCIAL SECURITY NUMBER: ";
        string socialSecurityNo;
        in >> socialSecurityNo;
        c.socialSecurityNo = socialSecurityNo;
        cout << endl << " EMAIL: ";
        string email;
        in >> email;
        c.email = email;
        cout << endl << " DATE OF BIRTH: ";
        string bday;
        in >> bday;
        c.bday = bday;
        cout << endl << " PASSWORD: ";
        char pass[100], ch;
        for (int i = 0;;)
        {
            ch = _getch();
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
            {
                pass[i] = ch;
                ++i;
                cout << '*';
            }
            if (ch == '\b' && i >= 1)
            {
                cout << "\b \b";
                --i;
            }
            if (ch == '\r')
            {
                pass[i] = '\0';
                break;
            }
        }
        cout << endl;
        c.password = pass;
        cout << endl;


        return in;
    };
};
int Client::nextClientID = 0;

template <typename T>
class Transaction
{
private:
    string ibanFrom;
    string ibanTo;
    T amount;

public:
    Transaction(string ibanFrom, string ibanTo, T amount) :
            ibanFrom(ibanFrom), ibanTo(ibanTo), amount(amount) {}

    void display()
    {
        cout << "Sender:" << endl;
        cout << "Receiver: " << accountNumber << endl;
        cout << "Amount: " << amount << endl;
    }
};


class Application
{
private:
    Application() {}
    static Application* instance;
public:
    static Application* getInstance()
    {
        if (!instance)
        {
            instance = new Application();
        }
        return instance;
    }

    void Start()
    {
        vector<Client> clients;
        string email;
        string password;
        bool is_logged = false;
        int currentAccount;
        char option;
        char option1;
        Client client;
        char pass[100], ch;
        int accountChoice;
        double amount;
        int exitVar = 0;


        do {
            cout << "\n";
            system("cls");
            cout << "~~~~~~~~~~~~ WELCOME ~~~~~~~~~~~~" << "\n";
            cout << " 1. BECOME A CLIENT \n";
            cout << " 2. LOGIN \n";
            cout << " 0. EXIT \n";

            cout << "Please select a menu option: ";
            cin >> option1;

            switch (option1) {
                case '1': {
                    system("cls");
                    cout << "\n~~~~~~~~~ REGISTER ~~~~~~~~~\n";
                    cin >> client;
                    clients.push_back(client);
                    break;
                }
                case '2': {
                    system("cls");
                    cout << "\n~~~~~~~~~~  LOGIN  ~~~~~~~~~~\n";
                    cout << "\n EMAIL: ";
                    cin >> email;
                    cout << "\n PASSWORD: ";
                    for (int i = 0;;) {
                        ch = _getch();
                        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
                            pass[i] = ch;
                            ++i;
                            cout << '*';
                        }
                        if (ch == '\b' && i >= 1) {
                            cout << "\b \b";
                            --i;
                        }
                        if (ch == '\r') {
                            pass[i] = '\0';
                            break;
                        }
                    }
                    password = pass;

                    for (int i = 0; i < clients.size(); i++) {
                        if (clients[i].get_email() == email) {
                            if (clients[i].get_password() == password) {
                                is_logged = true;
                                currentAccount = i;
                                system("cls");
                                do
                                {
                                    cout << endl;
                                    cout << "~~~~~~~~~~~~ MENU ~~~~~~~~~~~~\n";
                                    cout << endl;
                                    cout << "1. SHOW ACCOUNTS\n";
                                    cout << "2. CREATE A NEW ACCOUNT\n";
                                    cout << "3. MAKE A DEPOSIT\n";
                                    cout << "4. MAKE A WITHDRAWAL\n";
                                    cout << "5. CONVERT ACCOUNT\n";
                                    cout << "6. DELETE AN ACCOUNT\n";
                                    cout << "7. TRANSFER MONEY TO ANOTHER ACCOUNT\n";
                                    cout << "8. SHOW TRANSACTIONS\n";
                                    cout << "0. EXIT" << endl;
                                    cout << endl;
                                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                                    cout << endl;

                                    cout << "Please select a menu option: ";
                                    cin >> option;
                                    switch (option)
                                    {
                                        case '1':
                                        {
                                            system("cls");
                                            clients.at(currentAccount).displayAccounts();
                                            break;

                                        }
                                        case '2':
                                        {
                                            cout << " 1. SAVINGS\n";
                                            cout << " 2. CURRENT\n";
                                            cout << " CHOOSE ACCOUNT TYPE: \n";
                                            cin >> option;
                                            switch (option)
                                            {
                                                case '1':
                                                {
                                                    system("cls");
                                                    SavingsAccount account;
                                                    cin >> account;
                                                    clients.at(currentAccount).createSavingsAccount(account);
                                                    break;
                                                }
                                                case '2':
                                                {
                                                    system("cls");
                                                    CheckingAccount account;
                                                    cin >> account;
                                                    clients.at(currentAccount).createCheckingAccount(account);
                                                    break;
                                                }
                                            }
                                            break;
                                        }

                                        case '3':
                                        {
                                            system("cls");
                                            try
                                            {
                                                for (int i = 0; i < clients.at(currentAccount).getAccounts().size(); i++)
                                                {
                                                    cout << i + 1 << "# " << clients.at(currentAccount).getAccounts().at(i).getAccountName() << "\n";
                                                }
                                                cout << "SELECT AN ACCOUNT: ";
                                                cin >> accountChoice;
                                                cout << "TYPE AN AMOUNT: ";
                                                cin >> amount;
                                                clients.at(currentAccount).depositAmount(amount, accountChoice-1);                                    }
                                            catch (const runtime_error& e)
                                            {
                                                cout << "Error: " << e.what() << endl;
                                            }
                                            break;
                                        }
                                        case '4':
                                        {
                                            system("cls");
                                            try
                                            {
                                                for(int i = 0; i < clients.at(currentAccount).getAccounts().size(); i++)
                                                {
                                                    cout << i + 1 << "# " << clients.at(currentAccount).getAccounts().at(i).getAccountName() << "\n";
                                                }
                                                cout << "SELECT AN ACCOUNT: ";
                                                cin >> accountChoice;
                                                cout << "TYPE AN AMOUNT: ";
                                                cin >> amount;
                                                try
                                                {
                                                    clients.at(currentAccount).withdrawAmount(amount, accountChoice-1);
                                                }
                                                catch (const runtime_error& e)
                                                {
                                                    cout << "Error: " << e.what() << endl;
                                                }
                                            }
                                            catch (const runtime_error& e)
                                            {
                                                cout << "Error: " << e.what() << endl;
                                            }
                                            break;
                                        }
                                        case '5':
                                        {

                                        }
                                        case '6':
                                        {

                                        }
                                        case '7':
                                        {

                                        }
                                        case '8':
                                        {

                                        }
                                        case '0':
                                            is_logged = false;
                                            exitVar = 1;
                                            break;
                                    }
                                } while (is_logged);

                                // break;
                            }
                        }
                    }
                    if (!is_logged && exitVar == 0) { cout << "\n ERROR! WRONG DETAILS! \n"; }
                    break;
                }
                case '0':
                    break;
                default:
                    system("cls");
                    cout << "\n Wrong choice! Please try again! \n";
            }
        } while (option1 != '0');
    }
};

Application* Application::instance = 0;

int main() {

    Application::getInstance()->Start();
    return 0;

}
