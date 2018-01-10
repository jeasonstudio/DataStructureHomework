#include <iostream>

using namespace std;

class Integer {
private:
    int num;
public:
    Integer(int num) {
        this->num = num;
    }

    int gcd(Integer b) {
        int m = num,
                n = b.num,
                c = b.num;
        while (m % n != 0) {
            c = m % n;
            m = n;
            n = c;
        }
        return c;
    }
};

int main() {
    int a, b;
    cin >> a >> b;
    Integer A(a);
    Integer B(b);
    cout << A.gcd(B) << endl;
    return 0;
}