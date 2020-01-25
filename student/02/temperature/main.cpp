#include <iostream>;
using namespace std;

int main()
{
    int n;
    float t1,t2;
    cout << "Enter a temperature: ";
    cin>>n;
    t1=n*1.8+32;
    t2=(n-32)/1.8;
    cout<<n<<" degrees Celsius is "<<t1<<" degrees Fahrenheit "<<endl;
    cout<<n<<" degrees Fahrenheit is "<<t2<<" degrees Celsius "<<endl;

    return 0;
}
