#include <iostream>
using namespace std;

int main(){
	char noun[6];	
	noun[0] = 'g';
	noun[1] = 'r';
	noun[2] = 'a';
	noun[3] = 'p';
	noun[4] = 'e';
	noun[5] = '\0';
	cout << noun << endl;		
	unsigned long addr=(unsigned long )noun;
	cout << addr << endl;
	cout << addr+2 <<endl;
	int ages[3];
	ages[0] = 23;
	ages[1] = 94;
	ages[2] = 34;
	return 0;
}
