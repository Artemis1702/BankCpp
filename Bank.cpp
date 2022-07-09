#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<cstring>
#include<sstream>
using namespace std;

struct Date//class for date
{
    int day,month,year;
};

class Account//main account class
{
protected:
    string FirstName;
    string LastName;
    Date dob;
    string AccountNumber;
    double Savings;
public:
    void Creation();
    void Deletion(string AccountNo);
    int Searching(string x);
};

class Passbook : public Account
{
protected:
    double WithdrawnAmount;
    double DepositAmount;
public:
    Passbook();
    void PassbookCreate();
    void PassbookUpdate();
    void PassbookRead();
    void Deposit();
    void Deposit(int);
    void Withdraw();
    void Withdraw(int);
};

class Loan 
{
private:
    Passbook pass;
    int Time;
    double Principal;
    double InterestRate = 6.5;
    int NumOfPayments;
    int accept = 1;
    double EMI;
    double Total;
    string AccountNumber;
public:
    void GetLoan();
    void Pay();
    double Balance();
    double Interest();
    void LoanRequests();
    void Approval();
};

void Account::Creation()
{
    // to create an account
    char slash_dummy;
    int check;
    cout<<"Enter First Name : ";
    cin>>FirstName;
    cout<<"Enter Last Name : ";
    cin>>LastName;
    cout<<"Enter date of birth in the form dd/mm/yyyy : ";
    cin>>dob.day>>slash_dummy>>dob.month>>slash_dummy>>dob.year;
    cout<<"Enter Account Number : ";
    cin>>AccountNumber;
    Savings = 200;
    //search whether account number present already
    check = Searching(AccountNumber);
    while(check == 1)
    {
        cout<<"Account Already Exists"<<endl;
        cout<<"Re-enter the account number"<<endl;
        cin>>AccountNumber;
        check = Searching(AccountNumber);
    }
    //creates/opens a file to store the information of all users
    fstream Creator;
    Creator.open("Logbook.txt",ios::app);
    if(!Creator)
    {
        cout<<"Failed!"<<endl;
    }
    else
    {
        cout<<"Creating new account"<<endl;
        Creator<<AccountNumber<<endl;
        Creator<<FirstName<<" "<<LastName<<endl;
        Creator<<dob.day<<"/"<<dob.month<<"/"<<dob.year<<endl;
        Creator<<endl;
        Creator.close();
    }
}

void Account::Deletion(string AccountNo)
{    
    int count = 1;
    int flag =0;
    string line;
    string temp =AccountNo;
    fstream Deleter;
    fstream Copier;
    Deleter.open("Logbook.txt");
    Copier.open("temp.txt");
    while (getline (Deleter, line))
    {
        if (line == temp)
        {
            flag = 1;
            while (getline (Deleter, line))
            {
                count++;
                if(count == 3)
                    break;
            }
        }
        Copier<<line<<endl;
    }
    if(flag == 0)
    {
        cout<<"No such account found"<<endl;
    }
    remove("Logbook.txt");
    rename("temp.txt","Logbook.txt");
}

int Account::Searching(string x)
{
    int flag = 0;
    string line;
    fstream reader;
    string temp =x;
    reader.open("Logbook.txt");
    while (getline(reader, line))
    {
        if (line == temp)
        {
            cout<<line<<endl;
            flag = 1;
            return 1;
        }
    }
    if(flag ==  0)
    {
        return 0;
    }

}
Passbook::Passbook()
{
    WithdrawnAmount = 0;
    DepositAmount = 0;
}

void Passbook::PassbookCreate()
{
    //Creates a Passbook file for a new user
    fstream Creator;
    cout<<"Passbook created!"<<endl;
    char ext[100] = ".txt";
    char fname[100];
    strcpy(fname, AccountNumber.c_str());
    strcat(fname,ext);
    Creator.open(fname);
    cout<<AccountNumber<<endl;
    Creator<<"Account Number : "<<AccountNumber<<endl;
    Creator<<"------------------------------------------------------------------------------------------Pass Book------------------------------------------------------------------------------------------"<<endl;
    Creator<<"| Date                       |Time                       |Withdrawn Amount                            |Deposit Amount                                  |Savings                             |"<<endl;
    Creator<<"|____________________________|___________________________|____________________________________________|________________________________________________|____________________________________|"<<endl;
    Creator.close();
}

void Passbook::PassbookUpdate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    fstream Adder;
    //Updating Passbook
    char ext[100] = ".txt";
    char fname[100];
    strcpy(fname, AccountNumber.c_str());
    strcat(fname,ext);
    Adder.open(fname,ios::app);
    Adder<<"| "<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/"<<1900+ltm->tm_year<<"|"<<ltm->tm_hour<<":"<<ltm->tm_min<<"|"<<WithdrawnAmount<<"|"<<DepositAmount<<"|"<<Savings<<"|"<<endl;
    Adder.close();
    DepositAmount=0;
    WithdrawnAmount=0;
}

void Passbook::PassbookRead()
{
    // to view passbook
    cout<<"Entered"<<endl;
    string Line;
    fstream Viewer;
    char ext[100] = ".txt";
    char fname[100];
    strcpy(fname, AccountNumber.c_str());
    strcat(fname,ext);
    Viewer.open(fname);
    while (getline (Viewer, Line))
    {
        cout<<Line<<endl;
    }
    Viewer.close();
}

void Passbook::Deposit()
{
    cout<<"\nEnter the amount of money to be deposited :  ";
    cin>>DepositAmount;
    Savings = Savings + DepositAmount;
}

void Passbook::Deposit(int x)
{
    DepositAmount = x;
    Savings = Savings + DepositAmount;
}

void Passbook::Withdraw()
{
    int p;
    cout<<"Your current account balance is "<<Savings<<endl;
    cout<<"\nThe amount of money you want to withdraw is : ";
    cin>>WithdrawnAmount;
    p = Savings - WithdrawnAmount;
    if(p<=200)
    {
        cout<<"\nThere is not enough money in your account\n";
        Withdraw();
    }
    else if(p>200)
    {
        Savings = p;
    }
}

void Passbook::Withdraw(int x)
{
    int p;
    WithdrawnAmount = x;
    Savings = Savings - WithdrawnAmount;
}

void Loan::GetLoan()
{
    cout<<"Enter the Prinicipal :";
    cin>>Principal;
    cout<<"Enter the time period of the loan(in years)";
    cin>>Time;
    fstream creator;
    creator.open("LoanRequests.txt",ios::app);
    cout<<"Please enter your account number again :";
    cin>>AccountNumber;
    creator<<AccountNumber<<endl;
    creator<<Principal<<endl;
    creator<<Time<<endl;
    creator<<endl;
    creator.close();
    cout<<"Your request is being processed";
}

void Loan::LoanRequests()
{
    char ch;
    string AccountNo;
    string Line;
    fstream viewer;
    viewer.open("LoanRequests.txt");
    while (getline (viewer, Line))
    {
        cout << Line;
    }
    viewer.close();
    cout<<"\n Do you want to accept the loan request : ";
    cin>>ch;
    if (ch == 'y')
    {
        cout<<"Accepted";
        accept = 1;
    }
    else
    {
        cout<<"Rejected";
        accept = 0;
        cout<<"Enter the account number : "<<endl;
        cin>>AccountNo;
        int count = 0;
        int flag = 0;
        string line;
        string temp = AccountNo;
        fstream deleter;
        fstream copier;
        deleter.open("LoanRequests.txt");
        copier.open("temp.txt");
        while (getline (deleter, line))
        {
            if (line == temp)
            {
                flag = 1;
                while (getline (deleter, line))
                {
                    count++;
                    if(count == 2)
                        break;
                }
            }
            copier<<line<<endl;
        }
        if(flag == 0)
        {
            cout<<"No such account found"<<endl;
        }
        remove("LoanRequests.txt");
        rename("temp.txt","LoanRequests.txt");
    }
}

void Loan::Approval()
{
    if (accept == 1)
    {
        cout<<"Your loan has been approved";
        pass.Deposit(Principal);
        int method;
        cout<<"Enter the type of re-payment method you want to do \n1. Anually \n2. Monthly\n";
        cin>>method;

        switch(method)
        {
            case 1:
                NumOfPayments = Time;
                Total = Principal*(1+(InterestRate*Time));
                EMI = Total/NumOfPayments;
                cout<<"Nummber of payments :"<<NumOfPayments;
                cout<<"Total Amount to pay :"<<Total;
                cout<<"Equated Installment :"<<EMI;
                break;
            case 2:
                NumOfPayments = Time*12;
                Total = Principal*(1+(InterestRate*Time));
                EMI = Total/NumOfPayments;
                cout<<"Nummber of payments :"<<NumOfPayments;
                cout<<"Total Amount to pay :"<<Total;
                cout<<"Equated Installment :"<<EMI;
                break;
        }
    }
    else
    {
        cout<<"Your loan has been rejected";
    }
}

void Loan::Pay()
{
    pass.Withdraw(EMI);
    NumOfPayments = NumOfPayments - 1;
    cout<<"Successfully paid\n";
    cout<<NumOfPayments<<"Installments left to be paid";
}

double Loan::Balance()
{
    return EMI * NumOfPayments;
}

double Loan::Interest()
{
    return Total - Principal;
}

Account* account;
Passbook pass;
Loan l;

int main()
{
    char user;
    account = &pass;
    string admin1 = "Suraj";
    string admin2 = "Tejas";
    string name,passwd,nline;
    cout<<"\nAre you the admin : ";
    cin>>user;
    if(user == 'y')
    {
        cout<<"Enter your Name : "<<endl;
        cin>>name;
        if((name == admin1)||(name == admin2))
        {
            cout<<"Admin ID exists"<<endl;
            cout<<"enter password"<<endl;
            cin>>passwd;
            ifstream check;
            check.open("AdminAccounts.txt");
            while(getline(check,nline))
            {
                if(nline == passwd)
                {
                    int ch, n;
                    string Accnum;
                    cout<<"Press 1 to delete an account \nPress 2 to see loan requests\n";
                    cin>>ch;
                    switch(ch)
                    {
                        case 1:
                            cout<<"\nEnter the account number to be deleted :";
                            cin>>Accnum;
                            n = account->Searching(Accnum);
                            if(n == 1)
                            {
                                cout<<"\nAccount exists\n";
                                account->Deletion(Accnum);
                            }
                            else
                            {
                                cout<<"\nAccount does not exist\n";
                                cout<<"\nRe-enter the account number to be deleted :";
                                cin>>Accnum;
                                n = account->Searching(Accnum);
                            }
                            break;
                        case 2:
                           l.LoanRequests(); 
                           break;
                    }
                }
                else
                    cout<<"Invalid Access"<<endl;
            }
        }
    }
    else
    {
        //normal user
        cout<<"\nWelcome user\n";
        char acc;
        cout<<"\nDo you have an account\n";
        cin>>acc;
        while(acc == 'y')
        {
            //account present
            string Accnum;
            int Accnumber, check;
            cout<<"Enter account number :";
            cin>>Accnum;
            check = account->Searching(Accnum);
            if(check == 1)
            {
                cout<<"Account found";
                int choice;
                do
                {
                    cout<<"\nPress 1 to deposit amount\nPress 2 to withdraw money \nPress 3 to display passbook \nPress 4 to do loan operations \nPress 5 to exit \n";
                    cin>>choice;
                    switch(choice)
                    {
                        case 1:
                            pass.Deposit();
                            pass.PassbookUpdate();
                            break;
                        case 2:
                            pass.Withdraw();
                            pass.PassbookUpdate();
                            break;
                        case 3:
                            pass.PassbookRead();
                            break;
                        case 4:
                            int ch;
                            cout<<"\nPress 1 to get a loan \nPress 2 to check whether loan has been approved \nPress 3 to pay instalments \nPress 4 to check balance \nPress 5 to check interest \nPress 6 to exit\n ";
                            cin>>ch;
                            switch(ch)
                            {
                                case 1:
                                    l.GetLoan();
                                    break;
                                case 2:
                                    l.Approval();
                                    pass.PassbookUpdate();
                                    break;
                                case 3:
                                    l.Pay();
                                    pass.PassbookUpdate();
                                    break;
                                case 4:
                                    l.Balance();
                                    break;
                                case 5:
                                    l.Interest();
                                    break;
                                case 6:
                                    break;
                            }
                            break;
                        case 5:
                            break;
                        default:
                            cout<<"\nYou have passed the wrong key \n";
                            break;
                    }
                }while(choice != 5);

            }
            if(check == 0)
            {
                cout<<"\nDo you have an account\n";
                cin>>acc;
            }
            break;
        }
        while(acc == 'n')
        {
            //account to be created
            account->Creation();
            pass.PassbookCreate();
            int choice;
            do
            {
                cout<<"\nPress 1 to deposit amount\nPress 2 to withdraw money \nPress 3 to display passbook \nPress 4 to do loan operations \nPress 5 to exit \n";
                cin>>choice;
                switch(choice)
                {
                    case 1:
                        pass.Deposit();
                        pass.PassbookUpdate();
                        break;
                    case 2:
                        pass.Withdraw();
                        pass.PassbookUpdate();
                        break;
                    case 3:
                        pass.PassbookRead();
                        break;
                    case 4:
                        int ch;
                        cout<<"\nPress 1 to get a loan \nPress 2 to check whether loan has been approved \nPress 3 to pay instalments \nPress 4 to check balance \nPress 5 to check interest \nPress 6 to exit\n ";
                        cin>>ch;
                        switch(ch)
                        {
                            case 1:
                                l.GetLoan();
                                break;
                            case 2:
                                l.Approval();
                                pass.PassbookUpdate();
                                break;
                            case 3:
                                l.Pay();
                                pass.PassbookUpdate();
                                break;
                            case 4:
                                l.Balance();
                                break;
                            case 5:
                                l.Interest();
                                break;
                            case 6:
                                break;
                        }
                        break;
                    case 5:
                        break;
                    default:
                        cout<<"\nYou have passed the wrong key \n";
                        break;
                }
            }while(choice != 5);
            break;
        }
    }
}
