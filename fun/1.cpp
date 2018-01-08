#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class dice
{
private:
    int num;
public:
    int getnum(){
        srand(time(0));//产生随机数
        num = rand() % 6 + 1;//利用产生的随机数计算点数
        return num;
    };
};
int main()
{
    dice d;
    cout << "摇出的点数:" <<d.getnum()<<endl;
    return 0;
}
/*int dice::getnum()
{
    srand(time(0));
    num = rand() % 6 + 1;
    return num;
}
*/
