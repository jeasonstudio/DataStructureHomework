#include <iostream>
using namespace std;
const double PI = 3.1416;

class round{
    double radius;
public:
    round(double r){
        radius = r;
    }
    void setradius(double r){
        radius = r;
    }
    double deal(){
        return 2*PI*radius;
    }
};

class square{
    double A;
public:
    square(double a){
        A = a;
    }
    void seta(double a){
        A = a;
    }
    double deal(){
        return 4*A;
    }
};

class rectangle{
    double A,B;
public:
    rectangle(double a,double b){
        A = a;
        B = b;
    }
    void setaandb(double a,double b){
        A = a;
        B = b;
    }
    double deal(){
        return 2*(A+B);
    }
};

int main(int argc, const char * argv[]) {
    int type = 0;
    double a,b,radius;
    round r(0);
    rectangle rt(0,0);
    square s(0);
    cout<<"请输入需要计算周长的图形类型(1-圆形 2-长方形 3-正方形):";
    cin>>type;
    switch(type){
        case 1:
            cout << "请输入圆的半径为：";
            cin >> radius;
            r.setradius(radius);
            cout<<"圆"<< radius <<"的周长为："<< r.deal() <<endl;
            break;
        case 2:
            cout << "请输入矩形的长，宽（以空格分隔）：";
            cin >> a >> b;
            rt.setaandb(a, b);
            cout<<"矩形"<< a <<","<<b<<"的周长为："<< rt.deal() <<endl;
            break;
        case 3:
            cout << "请输入正方形的边长为：";
            cin >> a;
            s.seta(a);
            cout<<"正方形"<< a <<"的周长为："<< s.deal() <<endl;
            break;
        default:
            cout << "输入错误!"<<endl;
    }
}

