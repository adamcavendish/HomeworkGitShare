#include <iostream>
using namespace std;

int LCSlength(int a, int b, char * x, char * y)
{
	int c[51][51],d[51][51];
	int i,j;
	c[0][0]=0;
	for(i = 1; i <= a; i++) c[i][0] = 0;
	for(i = 1; i <= b; i++) c[0][i] = 0;
	for(i = 1; i <= a; i++)
	{
		for(j = 1; j <= b; j++)
		{
			if(x[i-1] == y[j-1])
			{
				c[i][j] = c[i-1][j-1] + 1;
				d[i][j] = 1;
			}
			else if(c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				d[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j-1];
				d[i][j] = 3;
			}
		}
	}
	return c[a][b];
}

int main()
{
	int Times,Case=0,a,b,length;
	cin >> Times;
	for(int i = 0 ; i < Times ; i++)
	{
		cin >> a >> b;
		char x[50],y[50];
		for(int xi = 0 ; xi < a ; xi++)
		{
			cin >> x[xi] ;
		}
		for(int yi = 0 ; yi < b ; yi++)
		{
			cin >> y[yi] ;
		}
		length = LCSlength(a,b,x,y);
		cout<< "Case " << ++Case << endl 
            << length <<endl;  
	}
	return 0;
}
