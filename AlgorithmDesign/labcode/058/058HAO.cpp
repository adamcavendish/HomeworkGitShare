#include<iostream>  
#include<iomanip>  
using namespace std;  
  
struct node{  
    int num;  
    int left;  
    int right;  
    int judge;  
    int parent;  
};  
  
int min(node *T,int n)  
{  
    int i,t=0;  
    while(T[t].judge ==0)  
        t++;  
    for(i=1;i<n;i++)  
    {  
        if(T[i].judge==1){  
            if(T[i].num<=T[t].num)  
                t=i;  
        }  
    }  
    T[t].judge =0;  
    return t;  
}  
  
  
  
void Merge(node *T,int &n)  
{  
    int l,r,num1;  
    r=min(T,n);  
    l=min(T,n);  
    num1=T[l].num +T[r].num ;  
    T[n].num =num1;  
    T[n].left =l;  
    T[n].right =r;  
    T[n].judge =1;  
    T[r].parent =n;  
    T[l].parent =n;  
    n++;  
}  
  
void huff(int p,node *T,int N,char *str,int &count)  
{  
    while(p!=N)  
    {  
        if(p==T[T[p].parent].left )  
            str[count++]='0';  
        else  
            str[count++]='1';  
        p=T[p].parent ;  
    }  
}  
      
  
  
int main()  
{  
    int TT,tt;  
    cin>>TT;  
    for(tt=0;tt<TT;tt++){  
        int n,i,N;  
        node T[100];  
        cin>>n;  
        N=n;  
        for(i=0;i<n;i++)  
        {  
            cin>>T[i].num ;  
            T[i].left=-1;  
            T[i].right =-1;  
            T[i].judge=1;  
            T[n].parent =-1;  
        }  
        for(i=0;i<N-1;i++){  
            Merge(T,n);  
        }  
        cout<<"Case "<<tt+1<<endl;  
        for(i=0;i<N;i++)  
        {  
            int count=0,j;  
            char str[100];  
            cout<<T[i].num <<' ';  
            huff(i,T,n-1,str,count);  
            for(j =count-1;j>=0;j--)  
                cout<<str[j];  
            cout<<endl;  
        }  
        cout<<endl;  
    }  
    return 0;  
}  