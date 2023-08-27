#include <iostream>
using namespace std;
class SinhVien{
    private:
        
        string id, ten, ns;
        double gpa;
    public:
        void xinChao();
        void diHoc();
};
void SinhVien:: diHoc(){
    cout << "do hoc!\n";
}
void SinhVien :: xinChao(){
    cout << "xin Chao \n";
}

main(){
    SinhVien x;
    x.diHoc();
    x.xinChao();
       
}
