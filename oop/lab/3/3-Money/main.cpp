#include <iostream>

using namespace std;

class Money {
private:
    static double profitRate;
    double balance;
public:
    Money(double balance) {
        this->balance = balance;
    }
    static void setProfitRate(double rate) {
        profitRate = rate;
    };
    void addProfit() {
        balance *= (1 + profitRate);
    }
    void deposit(double amount) {
        balance += amount;
    }
    void withdraw(double amount) {
        balance -= amount;
    }
    double getBalance() {
        return balance;
    }
};
double Money::profitRate = 0;
int main() {
    int n;
    while (cin >> n) {
        double profitRate;
        cin >> profitRate;
        Money::setProfitRate(profitRate);
        Money y(0); 
        int operation;
        double amount;
        for (int i = 0; i < n; ++i) {
            y.addProfit();
            cin >> operation >> amount;
            if (operation == 0)
                y.deposit(amount);
            else
                y.withdraw(amount);
        }
        cout << y.getBalance() << endl;
    }
    return 0;
}
