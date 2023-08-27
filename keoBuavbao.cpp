#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

int main() {
	srand(time(0));
	char c = 0;
	char a[3];
	a[0] = 'K';
	a[1] = 'B';
	a[2] = 'G';
	int d = 0;
	
	X:
	cout << "\t\t\t\tDIEM : " << d << "\n\n\n";
	int m = rand() % 3;
 	if (m == 0) {
	 	cout << "Keo !" << endl ;
		c = getch();
		if (c == 98) { cout << "Ban thang roi !" ; d++;
		Sleep(1000);
		system("cls"); goto X; }
		else cout << "Ban thua roi !" ;
		
		}

	if (m == 1) {
		cout << "Bua !" << endl;
		c = getch();
		if (c == 103) { cout << "Ban thang roi !" ; d++;
		Sleep(1000);
		system("cls"); goto X; }
		else cout << "Ban thua roi !" ;
		
		}

	if (m == 2) {
		cout << "Giay !" << endl;
		c = getch();
		if (c == 107) { cout << "Ban thang roi !" ; d++;
		Sleep(1000);
		system("cls"); goto X; }
		else cout << "Ban thua roi !" ;
		
		}
}