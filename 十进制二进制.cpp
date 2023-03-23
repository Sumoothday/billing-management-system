#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
	int a[16];
	int b[16];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	int x,y;
	scanf("%d %d",&x,&y);
	for(int i=15;i>=0;i--)
	{
		if(x>=pow(2,i))
		{
			a[i]=1;
			x-=pow(2,i);
		}
		if(x==0)
		{
			break;
		}
		
	}
		for(int i=15;i>=0;i--)
	{
		if(y>=pow(2,i))
		{
			b[i]=1;
			y-=pow(2,i);
		}
		if(y==0)
		{
			break;
		}
		
	}
	int s=0;
	for(int i=8;i<=15;i++)
	{
		if(a[i]==1)
		{
			s+=pow(2,i);
		}
		if(b[i]==1)
		{
			s+=pow(2,i-8);
		}
	}
	printf("%d",s);
}