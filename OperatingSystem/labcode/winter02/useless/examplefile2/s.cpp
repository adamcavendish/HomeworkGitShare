// s.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iomanip.h>
#include<vector> 
using namespace std;
#define random(x) (rand()%x)
#define MAX_LENGTH 320
struct produce
{
	int num;   //指令序号
	int zhiling;  //指令地址
	int virtualpage;  //指令虚页号
	produce *next;
};
struct produce*creatlist();
void insert(struct produce *first,struct produce *s); //插入一个节点（尾插法）
void print(struct produce *first);                   //打印函数
int max(vector<vector<int> >,int );
struct produce*creatlist()
{
	srand((int)time(0));
	struct produce*first=new produce;
	first->next=NULL;
	int m=0,m1=0;
	/*
	int yanzheng[20]={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
	for (int i=0;i<(MAX_LENGTH/4);i++)
	{
		struct produce *s0;
		s0=new produce;
		s0->num=i*4+0;
		s0->zhiling=yanzheng[i*4+0];
		s0->virtualpage=s0->zhiling;
		insert(first,s0);
		struct produce *s1;
		s1=new produce;
		s1->num=i*4+1;
		s1->zhiling=yanzheng[i*4+1];
		s1->virtualpage=s1->zhiling;
		insert(first,s1);
		struct produce *s2;
		s2=new produce;
		s2->num=i*4+2;
		s2->zhiling=yanzheng[i*4+2];
		s2->virtualpage=s2->zhiling;
		insert(first,s2);
		struct produce *s3;
		s3=new produce;
		s3->num=i*4+3;
		s3->zhiling=yanzheng[i*4+3];
		s3->virtualpage=s3->zhiling;
		insert(first,s3);
	}
	//*/
	//*
	for (int i=0;i<(MAX_LENGTH/4);i++)
	{
		struct produce *s0;
		s0=new produce;
		m=random(MAX_LENGTH);
		s0->num=i*4+0;
		s0->zhiling=m+1;
		s0->virtualpage=s0->zhiling/10;
		insert(first,s0);
		m1=random(m+1);
		struct produce *s1;
		s1=new produce;
		s1->num=i*4+1;
		s1->zhiling=m1;
		s1->virtualpage=s1->zhiling/10;
		insert(first,s1);
		struct produce *s2;
		s2=new produce;
		s2->num=i*4+2;
		s2->zhiling=m1+1;
		s2->virtualpage=s2->zhiling/10;
		insert(first,s2);
		struct produce *s3;
		s3=new produce;
		s3->num=i*4+3;
		s3->zhiling=random(MAX_LENGTH-m1-2)+m1+2;
		s3->virtualpage=s3->zhiling/10;
		insert(first,s3);
	}//*/
	return first;
}
void insert(struct produce *first,struct produce *s)
{
	struct produce *r=first;
	struct produce *p;
	while(r){p=r;r=r->next;}
	p->next=s;p=s;
	p->next=NULL;
}
void print(struct produce *first)                    //打印函数
{
	struct produce *p;
	p =first->next;
	cout<<"随机产生的指令的信息如下"<<endl;
	cout<<"指令序号  "<<"指令地址 "<<"指令虚页号"<<endl;
	while (p)
	{
		cout<<p->num<<'\t'<<p->zhiling<<setw(14)<<p->virtualpage<<endl;
		p=p->next;
	}
}
int max(vector<vector<int> > page,int Maxpage)
{
	int a=0,position=0;
	for (int i=0;i<Maxpage;i++)
	{
		if (page[i][1]>a)
		{
			a=page[i][1];
			position=i;
		}
	}
	return position;
}
//先来先出调度算法：fifo.h
#ifndef FIFO_H
#define FIFO_H
void fifo(struct produce *first,int Maxpage)
{
	vector<int> page(Maxpage);//
	for (int i=0;i<Maxpage;i++)page[i]=-1;
	int rear=0;//定义一个变量，指向要被替换的位置
	int pages;//定义变量保存当前指令的所在的地址
	int count1=0;//
	int count2=0;//缺页次数
	int find=1;
	struct produce *p=first->next;
	while (p)
	{
		pages=p->virtualpage;
		for(int i=0;i<Maxpage;i++)
		{
			if (page[i]==-1||count1<Maxpage)
			{
				page[i]=pages;
				count1 ++;
				count2 ++;
				find =1;
				break;
			}
			else if (page[i]==pages)				
			{
				find =1;
				break;
			}
			find=0;
		}
		if (find==0)
		{
			page[rear]=pages;
			rear ++;
			rear=rear%Maxpage;
			count2 ++;
		}
		p=p->next;
	}
	cout<<"FIFO调度算法缺页次数 缺页率   命中率"<<endl;
	cout<<count2<<setw(25)<<double(count2)/MAX_LENGTH<<setw(10)<<1-double(count2)/MAX_LENGTH<<endl;
}
#endif FIFO_H

//LRU调度算法lru.h
#ifndef LRU_H
#define LRU_H
#include<vector>
using namespace std;
//int max(vector<vector<int> >,int );
void lru(struct produce*first,int Maxpage)
{
	struct produce*p=first->next;
	vector<vector<int> >  page2(Maxpage, vector<int>(2)); 
	int count1=0;     //定义内存已经被占用的页数
	int count2=0;    //定义记录缺页次数
	int equal=0;    //定义判断如果当前页数与比较的页数，如果相等则为1，否则为0
	int place=0;   //定义要替换的位置
	for (int i=0;i<Maxpage;i++)
	{
		page2[i][0]=-1;page2[i][1]=0;
	}
	while (p)
	{
		if (count1<Maxpage)
		{
			for (int i=0;i<Maxpage;i++)
			{
				page2[i][1]=page2[i][1]+1;
				if (page2[i][0]==-1)
				{
					page2[i][0]=p->virtualpage;
					count2++;
					break;
				}
				else if (page2[i][0]==p->virtualpage)
				{
					page2[i][1] =1;
				}
			}
			count1++;
		}
		else
		{
			for (int i=0;i<Maxpage;i++)
			{
				page2[i][1] +=1;
				if (page2[i][0]==p->virtualpage)
				{equal=1;place=i;break;}
			}
			if (equal==1)
			{
				page2[place][1] =1;
				equal=0;
			}
			else 
			{
				place = max(page2,Maxpage);
				page2[place][1]=1;
				page2[place][0]=p->virtualpage;
				count2++;
			}
		}
		p=p->next;
	}
	cout<<"LRU调度算法缺页次数  缺页率   命中率"<<endl;
	cout<<count2<<setw(24)<<double(count2)/MAX_LENGTH<<setw(10)<<1-double(count2)/MAX_LENGTH<<endl;
}
#endif  LRU_H

//OPT调度算法opt.h
#ifndef OPT_H
#define OPT_H
#include<vector>
using namespace std;
int search(struct produce*place,int position);
void opt(struct produce*first,int Maxpage)
{
	struct produce*p =first->next;
	vector<vector<int> >  page3(Maxpage, vector<int>(2));
	int count1=0;      //定义内存已被使用的页数
	int count2=0;     //定义缺页次数
	int current=0;   //定义当前工作位置
	int equal=0;    //定义判断如果当前页数与比较的页数，如果相等则为1，否则为0
	int place=0;   //定义要替换的位置
	for (int i=0;i<Maxpage;i++)
	{
		page3[i][0]=-1;page3[i][1]=0;
	}
	while (p)
	{
		//cout<<1111<<endl;
		if (count1<Maxpage)
		{
			for (int i=0;i<Maxpage;i++)
			{
				if (page3[i][0]==-1)
				{
					page3[i][0]=p->virtualpage;
					page3[i][1]=search(p,current);
					count2++;
					break;
				}
				else if (page3[i][0]==p->virtualpage)
				{
					page3[i][1]=search(p,current);
				}
			}
			count1++;
		}
		else
		{
			for (int i=0;i<Maxpage;i++)
			{
				if (page3[i][0]==p->virtualpage)
				{equal=1;place=i;break;}
			}
			if (equal==1)
			{
				page3[place][1] =search(p,current);
				equal=0;
			}
			else
			{
				place = max(page3,Maxpage);
				page3[place][1]=search(p,current);
				page3[place][0]=p->virtualpage;
				count2 +=1;
			}
		}
		p=p->next;
		current +=1;
	}
	cout<<"OPT调度算法缺页次数 缺页率  命中率"<<endl;
	cout<<count2<<setw(25)<<double(count2)/MAX_LENGTH<<setw(10)<<1-double(count2)/MAX_LENGTH<<endl;
}
int search(struct produce*place,int position)
{
	struct produce*p=place->next;
	int current=place->virtualpage;
	int position1=position+1;
	while(p)
	{
		if (current==p->virtualpage)
		{
			return position1;
		}
		position1++;
		p=p->next;
	}
	return position1;
}
#endif

//主函数 控制台ccglmain.cpp
void main()
{
	int S;                             //定义变量记录用户选择
	char again;                       //定义变量用户选择继续还是退出
	cout<<"开始产生内存指令"<<endl;
	struct produce *first=creatlist();//产生随机指令
	cout<<"打印产生的指令信息"<<endl;
	print(first);//打印产生的指令信息
	while (1)
	{
		int Maxpage=3;//定义内存最大页面数
		cout<<"11122022\n";
		cout<<"输入你的选择"<<endl;
		cout<<"1:FIFO(先进先出)调度算法\n"<<"2:LRU(最近最少使用算法)\n"<<"3:OPT(最佳淘汰算法)\n"<<"4:清屏"<<endl;
		cin>>S;
		while(S>4||S<1)
		{
			cout<<"输入错误重新输入"<<endl;
			cin>>S;
		}
		if (S!=4)
		{
			while(Maxpage<=32)
			{
				switch(S)
				{
				case 1:fifo(first,Maxpage);break;
				case 2:lru(first,Maxpage);break;
				case 3:opt(first,Maxpage);break;
				default:break;
				}
				Maxpage++;
			}
			cout<<"是否继续调用其他算法？是请按y/Y,否请按其它键"<<endl;
			cin>>again;
			if(again=='y'||again=='Y')
			{
				continue;
			}
			else break;
		}
		else system("cls");
	}
}
