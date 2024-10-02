#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Transaction{
    string type;
    double amount;
    string date;

    public:
    Transaction(string type, double amount, string date){
        this->type = type;
        this->amount = amount;
        this->date = date;
    }

    void displayTransaction()const{
        cout<<"Type: "<<type<<", Amount: "<<amount<<", Date: "<<date<<endl;
    }
};

class Account{
    protected:
    string ownerName;
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

    public:
    Account(string name, int number, double initialBalance){
        this->ownerName = name;
        this->accountNumber = number;
        this->balance = initialBalance;
    }

    void deposit(double amount){
        balance+=amount;
        transactions.push_back(Transaction("Deposit",amount,"2024-10-02"));
        cout<<"Deposited: "<<amount<<endl;
    }

    virtual bool withDraw(double amount){
        if(balance>= amount){
            balance-=amount;
            transactions.push_back(Transaction("Withdrawal",amount,"2024-10-02"));
            return true;
        }
        cout<<"Insufficient Balance."<<endl;
        return false;
    }

    double getBalance(){
        return balance;
    }

    void displayTransactions() const{
        for(const auto& c:transactions){
            c.displayTransaction();
        }
    }

    virtual ~Account(){
        cout<<"Account Is Closed."<<endl;
    }
};

class SavingsAccount :public Account{
    private:
    double interestRate;
    public:
    SavingsAccount(string name,int number,double initialBalance,double rate):Account(name ,number,initialBalance),interestRate(rate){}

    void applyInterest(){
        double interest = balance*interestRate;
        balance+=interest;
        transactions.push_back(Transaction("Interest",interest,"2024-10-02"));
        cout<<"Interest applied: "<<interest<<endl;
    }
};

class CheckingAccount : public Account{
    private:
    double overdraftLimit;
    public:
    CheckingAccount(string name,int number,double initialBalance,double limit):Account(name,number,initialBalance),overdraftLimit(limit){}

    bool withDraw(double amount)override{
        if(balance+overdraftLimit>=amount){
            balance-=amount;
            transactions.push_back(Transaction("Withdrawal",amount,"2024-10-02"));
            cout<<"Withdrew: "<<amount<<endl;
            return true;
        }
        cout<<"Exceeds overdraft limit!"<<endl;
        return false;
    }
};


int main(){
    SavingsAccount savings("shubham ",1001,1000,0.05);
    savings.deposit(500);
    savings.applyInterest();
    savings.displayTransactions();
    cout<<"Savings Account Balance: "<<savings.getBalance()<<endl;


    CheckingAccount checking("shubham",1002,500,200);
    checking.withDraw(600);
    checking.withDraw(150);
    checking.displayTransactions();
    cout<<"Checking Balance: "<<checking.getBalance()<<endl;

    return 0;
}