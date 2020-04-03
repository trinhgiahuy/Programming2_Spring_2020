#include <iostream>
#include<memory>
using namespace std;

int main()
{

    shared_ptr<int> smart1 (new int (6));
    shared_ptr<int> smart2 (make_shared<int>(9));

    cout<<smart1 << " " << *smart1<< "   " << smart1.use_count() <<endl;
    cout<<smart2 << " " << *smart2<< "    " << smart2.use_count()<<endl;

    *smart1 = *smart1 + 3 ;
    cout<<"                                                     "<<endl;
    cout<<smart1 << " " << *smart1<< "   " << smart1.use_count() <<endl;
    cout<<smart2 << " " << *smart2<< "    " << smart2.use_count()<<endl;
    cout<<"                                                     "<<endl;
    smart1 = smart2 ;

    cout<<smart1 << " " << *smart1<< "   " << smart1.use_count() <<endl;
    cout<<smart2 << " " << *smart2<< "    " << smart2.use_count()<<endl;
    cout<<"                                                     "<<endl;
    return 0;
}
