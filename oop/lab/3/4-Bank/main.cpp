#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

class SavingsAccount {
private:
    int id;
    double balance;
    double rate;
    int lastDate;
    double accumulation;
    void record(int date, double samount) {
        lastDate = date;
        double nbalance = balance + samount;
        cout << "the balance changed from " << fixed << setprecision(2) << balance << "￥" << "to " << nbalance
             << "￥" << endl;
    }
    void accumulate(int date) {
        accumulation += balance * (date - lastDate) * rate;
    }
    double processAmount(double amount){
        return (floor(amount * 100))/100;
    }

public:
    SavingsAccount(int date, int id, double rate) {
        this->id = id;
        balance = 0;
        this->rate = rate;
        lastDate = date;
        accumulation = 0;
    }
    int getId() const {
        return id;
    }
    double getBalance() const {
        return balance;
    }
    double getRate() const {
        return rate;
    }
    void show() {
        cout << "account infomation" << endl;
        cout << "account id:" << id << endl;
        cout << "total balance:" << fixed << setprecision(2) << balance << "￥" << endl;
        cout << "dalily rate:" << fixed << setprecision(2) << rate << "%" << endl;
    }
    void desposit(int date, double amount) {
        cout << "desposit " << fixed << setprecision(2) << amount << "￥" << endl;
        accumulate(date);
        record(date, processAmount(amount));
        balance += processAmount(amount);
    }
    void withdraw(int date, double amount) {
        cout << "withdraw " << fixed << setprecision(2) << amount << "￥" << endl;
        accumulate(date);
        record(date, -processAmount(amount));
        balance -= processAmount(amount);
    }
    void settle(int date) {
        accumulate(date);
        cout << "settle interest " << fixed << setprecision(2) << accumulation << "￥" << endl;
        desposit(date, accumulation);
        accumulation = 0;
    }
};


int main() {
    SavingsAccount sa(1, 1, 0.1);
    sa.show();
    sa.desposit(3, 500.501);
    sa.settle(5);
    sa.withdraw(7, 300.5);
    sa.settle(10);
    return 0;
}