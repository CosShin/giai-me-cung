#include <iostream>
using namespace std;
int searchlist(int a[], int n, int x){
    for(int i = 0; i<=n; i++){
        if(a[i]==x)
            return i;
    }
        return -1;
}
int binarySearch(int a[], int n, int x)
{
    int left = 0;
    int right = n - 1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (a[mid] == x) {
            return mid;
        }
        else if (a[mid] > x) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int main()
{
    cout<< "ket qua tim kim: "<< endl;
    int a[]= {1,2,23,2341231,23,321};
    int n = sizeof(a)/sizeof(a[0]);
    int x =binarySearch (a,n,1);
    cout<< x;
}