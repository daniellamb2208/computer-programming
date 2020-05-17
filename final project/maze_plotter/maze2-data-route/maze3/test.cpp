#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	fstream f;
	f.open("maze_route2.txt",ios::in);
	int count = 0;
	int a;
	char c;
	while(f>>a>>c)
	{
		count++;
		
	}
	f.close();
	cout<<count;
}
