#include <iostream>
#include"smartpoint.h"
using namespace std;
using namespace dong;
class Test{
public:
    Test()
    {
        cout<<"Test()"<<endl;
    }
    ~Test()
    {
        cout<<"~Test()"<<endl;
    }
};

int main()
{
    Smartpoint<Test> sp=new Test();
    cout<<sp.isNULL()<<endl;
    return 0;
}
