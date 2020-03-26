#include <iostream>

using namespace std;

template<typename T>
void Swap(T& a,T& b)
{
    T t=a;
    a=b;
    b=t;
    return;
}

template<class T>
class OP
{
public:
    T process(T v)
    {
        return v*v;
    }
};

int main()
{
    int a=2;
    int b=1;
    Swap(a,b);
    cout<<"a="<<a<<"b="<<b<<endl;

    OP<int> opint;
    OP<float> opfloat;
    cout<<opint.process(10)<<endl;
    cout<<opfloat.process(3.3)<<endl;

    return 0;
}
