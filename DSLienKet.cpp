#include <iostream>
#include <string>
using namespace std;
struct hocVien
{
    int IDHv;
    string tenHV;
    int namSinh;
};
struct NodeHv
{
    hocVien hv;
    NodeHv *next;

};
void ouPutHv(hocVien h){
    cout << "ma Hv:"<< h.IDHv << endl;
    cout << "ten hoc vien: " <<  h.tenHV << endl ;
    cout << "nam sinh : " << h.namSinh << endl;
    cout <<"=====================================" << endl;
}
void init(NodeHv *&head){
    head= NULL;
}
NodeHv* createNode(hocVien x){
    NodeHv *p = new NodeHv;
    p->hv = x;
    p->next = NULL;
    return p;
}
void addFirst(NodeHv *&head, hocVien x)
{   
    NodeHv *p = createNode(x);
    p->next = head;
    head = p; 
}
void outPut(NodeHv *head){
    NodeHv *p = head;
    while(p!=NULL){
        ouPutHv(p->hv);
        p = p->next;

    }
}
int main(){ 
    hocVien h1;
    h1.IDHv = 123123;
    h1.tenHV = "Le Minh An";
    h1.namSinh = 2004;
    hocVien h2 ;
    h2.IDHv = 3123152;
    h2.tenHV = " Le Minh Tuan";
    h2.namSinh = 1978;
    NodeHv *head;
    init(head);
    addFirst(head,h1);
    addFirst(head, h2);
    outPut(head);
}