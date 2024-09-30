#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// User class for registration and login
class User 
{
    int UUID;
    string Name;
    int Pass;
    string Email;

public:

    void Register() 
	{
        cout<<"---- Create your account to handle and track your Finance ----"<<endl;
        cout<<"\nEnter your details: "<<endl;
        srand(time(0));  
        UUID=rand() % 10000;
        cout<<"User Name: ";
        cin>>Name;
        cout<<"Pass Key: ";
        cin>>Pass;
        cout<<"Email: ";
        cin>>Email;

        ofstream UserFile("user.txt", ios::app); 
        if (!UserFile) 
		{
            cerr<<"Unable to open File!"<<endl;
            return;
        }
        UserFile<<Name<<" "<<Pass<<" "<<Email<<" "<<UUID<<endl;
        UserFile.close();

        cout<<"Register Successful!" << endl;
        cout<<"Your UUID is: "<<UUID<<" (Don't forget your UUID!)"<<endl;
    }

    bool Login(int &loggedInUUID) 
	{
        string inputName;
        int inputPass;
        string inputEmail;
        int inputUUID;

        string storedName;
        int storedPass;
        string storedEmail;
        int storedUUID;

        cout<<"\n---- Login to your Finance Account ----"<<endl;
        cout<<"User Name: ";
        cin>>inputName;
        cout<<"Pass Key: ";
        cin>>inputPass;
        cout<<"Email: ";
        cin>>inputEmail;
        cout<<"UUID: ";
        cin>>inputUUID;

        ifstream UserFile("user.txt");
        if (!UserFile) 
		{
            cerr<<"Unable to open File!"<<endl;
            return false;
        }

        bool isLoggedIn=false;
        while (UserFile>>storedName>>storedPass>>storedEmail>>storedUUID) 
		{
            if (storedName==inputName && storedPass==inputPass && storedEmail==inputEmail && storedUUID==inputUUID) 
			{
                isLoggedIn=true;
                loggedInUUID=storedUUID;
                break;
            }
        }
        UserFile.close();

        if(isLoggedIn) 
		{
            cout<<"Login Successful!"<<endl;
        } 
		else 
		{
            cout<<"Failed to login. Invalid data entered!"<<endl;
        }
        return isLoggedIn;
    }
};

class Transaction 
{
    time_t Date;
    string Description;
    int Amount;

public:
    Transaction(time_t date, string desc, int amount) : Date(date), Description(desc), Amount(amount) {}

    void inputDetails() 
	{
        Date=time(0);
        cout<<"Enter Amount of Transaction: ";
        cin>>Amount;
        cin.ignore();
        cout<<"Enter Description of Transaction: ";
        getline(cin, Description);
    }

    void DisplayDetails() const 
	{
        cout<<"\n---Details of Transaction---"<<endl;
        cout<<"Amount: "<<Amount;
        cout<<"\nDescription: "<<Description;
        cout<<"\nTime: "<<ctime(&Date);
    }

    const time_t& getDate() const {return Date;}  // Return a reference to Date
    int getAmount() const {return Amount;}
    string getDescription() const {return Description;}
};

// TransactionManagement class for handling user's finance
class TransactionManagement 
{
    int TotalBalance=0;
    string balanceFile;
    string transactionFile;

public:
    TransactionManagement(const string& balanceFilename, const string& transactionFilename) 
	: balanceFile(balanceFilename), transactionFile(transactionFilename) 
    {
        ifstream file(balanceFile);
        if(file.is_open()) 
        {
            file>>TotalBalance;
            cout<<"Your Balance: "<<TotalBalance;
            file.close();
        } 
        else 
        {
            ofstream newFile(balanceFile);
            if (newFile.is_open()) 
            {
                newFile<<TotalBalance<<endl;  // Initialize file with balance
                newFile.close();
            }
        }
    }

    // Add amount to balance and save details in transaction file
    void AddAmount() 
    {
        int amount;
        cout<<"\nEnter Amount To Add: ";
        cin>>amount;
        TotalBalance+=amount;
        cout<<"Amount Added: "<<amount<<endl;
        cout<<"Updated Balance: "<<TotalBalance<<endl;

        Transaction add(time(0), "Added Funds", amount);
        add.DisplayDetails();
        saveTransaction("Added Funds", add);
        updateBalance();  
    }

    // Add expense and save details in transaction file
    void AddExpense() 
    {
        int amount;
        string description;
        cout<<"\nExpense Amount: ";
        cin>>amount;
        cin.ignore();
        cout<<"Expense Description: ";
        getline(cin, description);

        if (amount>TotalBalance) 
        {
            cout<<"Insufficient Balance!"<<endl;
            return;
        }
        TotalBalance -= amount;
        cout<<"Expense Added: "<<amount<<endl;
        cout<<"Updated Balance: "<<TotalBalance<<endl;

        Transaction expense(time(0), description, amount);
        expense.DisplayDetails();
        saveTransaction(description, expense);
        updateBalance(); 
    }

    // Save transaction details in a separate transaction file
    void saveTransaction(const string& type, const Transaction& transaction)
    {
        ofstream transFile(transactionFile, ios::app);
        if (transFile.is_open()) 
        {
            transFile<<"\n---Details of Transaction---"<<endl;
            transFile<<"Amount: " << transaction.getAmount()<<endl;
            transFile<<"Description: "<<transaction.getDescription()<<endl;
            transFile<<"Time: "<<ctime(&transaction.getDate());  // Format the time
            transFile<<"--------------------------"<<endl;
            transFile.close();  
        } 
        else 
        {
            cerr<<"Unable to open transaction file to save transaction!"<<endl;
        }
    }

    void updateBalance()
    {
        ofstream balanceFileOut(balanceFile, ios::trunc);
        if (balanceFileOut.is_open()) 
        {
            balanceFileOut<<TotalBalance<<endl;
            balanceFileOut.close();
        } 
        else 
        {
            cerr<<"Unable to update balance file!"<<endl;
        }
    }
};


int main() 
{
    User user;
    int loggedInUUID;
    int choice;

    cout<<"Welcome to Finance Management System"<<endl;
    cout<<"1. Login\n2. Register\n";
    cout<<"Enter your choice: ";
    cin>>choice;

    if (choice==1) 
    {
        if (!user.Login(loggedInUUID)) 
        {
            return 0; 
        }
    } 
    else if(choice==2) 
    {
        user.Register();
        return 0;
    } 
    else 
    {
        cout<<"Invalid choice!"<<endl;
        return 0;
    }

    // After successful login, handle transactions
    string balanceFile=to_string(loggedInUUID) + "_balance.txt";
    string transactionFile=to_string(loggedInUUID) + "_transactions.txt";
    TransactionManagement tm(balanceFile, transactionFile);

    do 
    {
        cout<<"\n-----Transaction Menu-----\n";
        cout<<"1. Add Amount\n";
        cout<<"2. Add Expense\n";
        cout<<"3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch (choice) 
        {
            case 1:
                tm.AddAmount();
                break;
            case 2:
                tm.AddExpense();
                break;
            case 3:
                cout<<"exiting.\n";
                break;
            default:
                cout<<"Invalid choice! select 1 2 or 3";
                break;
        }

    } 
	while (choice!=3);
    return 0;  
}
