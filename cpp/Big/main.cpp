#include <iostream>
using namespace std;
int deal(){
    int s[4] = {0,0,0,0};
    int i;
    for(i = 0;i < 4;i++){
        s[i] = 1;
        if(((s[0] == 0) + (s[2] == 1) + (s[1] == 1) + (s[1] != 1)) == 3)
            break;
        s[i] = 0;
    }
    return i;
}

int main(int argc, const char * argv[]) {
    int index = deal();
    switch (index) {
        case 0:
            cout<<"A"<<endl;
            break;
        case 1:
            cout<<"B"<<endl;
            break;
        case 2:
            cout<<"C"<<endl;
            break;
        case 3:
            cout<<"D"<<endl;
            break;
        default:
            break;
    }
    return 0;
}
