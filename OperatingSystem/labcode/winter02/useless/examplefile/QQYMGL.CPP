#include <iostream>
#include<stdlib.h>
//#include<conio.h>
#include<stdio.h>
#include<time.h>
//const int Bsize=4;
using namespace std;

typedef struct BLOCK{
	int pagenum;
	int accessed;

}BLOCK;

long int pc;//cheng xu ji shu qi
int n;//que ye ji shu qi
static int a[255];
BLOCK block[32];
//*************************************************************
void init( );     //chu shi hua
int findExist(int curpage);//cha zhao shi fou you gai ye mian
int findSpace( );//cha zhao shi fou you kong xian kong jian
int findReplace( );//cha zhao ying zhi huan de ye mian
void display ( );//shu chu
void suijishu( );//chang sheng sui ji shu
void pagestring( );//zhuan hua wei ye mian
void OPT( );
void LRU( );
//*************************************************************
void init(int Bsize)
{
	srand(time(NULL));
   for(int i=0;i<Bsize;i++)
   {
	   block[i].pagenum=-1;
       block[i].accessed=0;
       pc=n=0;
   }
}
//-------------------------------------------------------------
int findExist(int curpage,int Bsize)
{

    for(int i=0; i<Bsize; i++)
	{
		if(block[i].pagenum == curpage )
			return i;
	}
    return -1;
}
//-------------------------------------------------------------
int findSpace(int Bsize)
{
	for(int i=0; i<Bsize; i++)
	{
	   if(block[i].pagenum == -1)
	return i;
	}

    return -1;
}
//-------------------------------------------------------------
int findReplace(int Bsize)
{
	int pos = 0;
	for(int i=0; i<Bsize; i++)
	{
		if(block[i].accessed >block[pos].accessed)
			pos = i;
	}
	return pos;
}
//-------------------------------------------------------------
void display(int Bsize)
{
   for(int i=0; i<Bsize; i++)
   {
	   if(block[i].pagenum != -1)
	   {
	    cout<<block[i].pagenum<<"\t";

	   }
   }
   cout<<endl;
}
//-------------------------------------------------------------
void suijishu(int pc)
{   int flag=0;
    //cin>>pc;
    //randomize( );
    cout<<"________________________________________________________________"<<endl;
    cout<<"THE VIRTUAL ADDRESS STREAM AS FOLLOWS:"<<endl;
    for(int i=0;i<255;i++)
	{  if(i%40==0)getchar();
		a[i]=pc;
		if(flag%2==0) pc=(pc + 1)%32767;
		if(flag==1) pc=rand( )% (pc-1);
		if(flag==3) pc=pc+1+(rand( )%(32767-(pc+1)));
		flag=(flag+1)%4;
		cout<<"a["<<i<<"]="<<a[i]<<"   \t";
		if((i+1)%5==0) cout<<endl;
	}
	getchar();
}
//-------------------------------------------------------------
void pagestring( )
{ int pageno[255];
	for(int i=0;i<255;i++)
	{  cout<<"pageno["<<i<<"]="<<a[i]/1024<<"\t";
	   if((i+1)%5==0) cout<<endl;
	   if((i+1)%50==0)getchar();
	}
 cout<<endl;

}
//-------------------------------------------------------------
int OPT(int Bsize)
{
	int exist,space,position,pa ;
	long int curpage;
    for(int i=0;i<255;i++)
	{
		if(i%40==0) getchar( );
		pc=a[i];
	    curpage=pc/1024;
	    exist = findExist(curpage,Bsize);
		if(exist==-1)
		{
			space = findSpace (Bsize);
			if(space != -1)
			{
				block[space].pagenum = curpage;
				display(Bsize);
			    n=n+1;
			}
			else
			{
				for(int k=0;k<Bsize;k++)
				{
					for(int j=i;j<255;j++)
					{
						if(block[k].pagenum!= a[j]/1024)
						{
							block[k].accessed = 1000;
						}
						else
						{
							block[k].accessed = j;
							break;

						}
					}
				}
				position = findReplace(Bsize);
				block[position].pagenum = curpage;
				display(Bsize);
				n++;
			}
		}
	}
	//cout<<"QUE YE CI SHU:"<<n<<endl;
	//cout<<"MING ZHONG lV:"<<(1-(n/255.0))*100<<"%"<<endl;
	return n;
}
//-------------------------------------------------------------
int LRU(int Bsize)
{
	int qy;
	int exist,space,position ;
	int curpage;
    for(int i=0;i<255;i++)
	{
		if(i%40==0)
			getchar( );
		pc=a[i];
	    curpage=pc/1024;
	    exist = findExist(curpage,Bsize);
		if(exist==-1)
		{
			space = findSpace(Bsize);
			if(space != -1)
			{
				block[space].pagenum = curpage;
				display(Bsize);
			    n=n+1;
			}
			else
			{
				position = findReplace(Bsize);
				block[position].pagenum = curpage;
				display(Bsize);
				n++;
			}
		}
		else
		{
			block[exist].accessed = -1;
		}
		for(int j=0; j<4; j++)
		{
			block[j].accessed++;
		}
	}
	//cout<<"QUE YE CI SHU:"<<n<<endl;
	//cout<<"MING ZHONG lV:"<<(1-(n/255.0))*100<<"%"<<endl;
	return n;
}

//*************************************************************
int main( )
{
  int  select,pagesize,Bsize,O=0,L=0;
  long int pc;
  char exit,contuion;
 for(;;)
 {
	 //clrscr();
  O=L=0;
   for(;;)
  {cout<<"PLEASE INPUT THE PAGESIZE(1 2 4 8)K:";
   cin>>pagesize;
   if(pagesize==1||pagesize==2||pagesize==4||pagesize==8)break;
   cout<<"error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  }
   Bsize=32/pagesize;
   /*for(;;)
  {
   cout<<"PLEASE INPUT THE BLOCKSIZE(4-32):";
   cin>>Bsize;
   if(Bsize>=4&&Bsize<=32)break;
   cout<<"error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
   }*/

   cout<<"YOUR CHOOSE IS: "<<pagesize<<"K"<<"("<<pagesize*1024<<")!"<<endl;
   cout<<"BLOCK SIZE IS: "<<Bsize<<"!"<<endl;
   for(;;)
   {
   cout<<"PLEASE INPUT ADDRESS(0-32767):";
   cin>>pc;
   if(pc>=0&&pc<=32767)
   {
   suijishu(pc);
   break;}
   cout<<"error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
   }
   getchar();
   cout<<"________________________________________________________________"<<endl;
   cout<<"PAGE NUMBER WITH SIZE "<<pagesize<<"K FOR EACH ADDRESS IS:"<<endl;
   pagestring( );
    for(;;)
    {
      cout<<"                    PLEASE CHOOSE ALGORITHM:"<<endl;
      cout<<"         =========================================="<<endl;
      cout<<"         |          1:OPT   2:LRU  3:RESULT       |"<<endl;
      cout<<"         =========================================="<<endl;
      cin>>select;
      cout<<"________________________________________________________________"<<endl;
      init(Bsize);
      if(select==1)
	  {cout<<"OPT:"<<endl;
	   O=OPT(Bsize);}
      else if(select==2)
	  {cout<<"LRU:"<<endl;
	   L=LRU(Bsize);}
      else if(select==3)
      { if(O==0&&L==0)
	cout<<"NO RESULT!!!"<<endl;
	else if(O==0&&L!=0)
	cout<<"YOU HAVE NOT DO OPT"<<endl;
	else if(L==0&&O!=0)
	cout<<"YOU HAVE NOT DO LRU"<<endl;
	else if(O!=0&&L!=0)break;
	cout<<"DO YOU WANT CONTINUE?(Y/N)"<<endl;
	cin>>contuion;
	if(contuion=='N'||contuion=='n')break;
	}
    }
   if(O!=0&&L!=0)
   {
   cout<<"       QUE YE CI SHU                  MING ZHONG lV"<<endl<<endl;
   cout<<"OPT"<<"        "<<O<<"                          "<<(1-(O/255.0))*100<<"%"<<endl<<endl;
   cout<<"LRU"<<"        "<<L<<"                          "<<(1-(L/255.0))*100<<"%"<<endl<<endl;
   }
   cout<<"-------------------------------------------------------------------"<<endl;
   cout<<"DO YOU WANT EXIT THE PROGRAME?(Y/N)";
   cin>>exit;
   cout<<endl;
   if(exit=='Y'||exit=='y')break;
  }
}
