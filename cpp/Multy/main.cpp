#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int E,G,A,L;
    int c = 0;
    for(L = 0;L < 10;L++){
        E = L*L;
        if(E > 10){
            c = E;
            E %= 10;
            c /= 10;
        }
        for(A = 0;A < 10;A++){
            G = (A*L+c)%10;
            if(((E*100+G*10+A)*L+c)/10 == L*10+A)
                break;
        }
    }
    cout<<"E G A L："<<E<<" "<<G<<" "<<A<<" "<<--L<<endl;
    return 0;
}
