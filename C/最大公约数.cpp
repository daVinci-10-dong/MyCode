#include<stdio.h>

int main()
{
	int a,b;
	scanf("%d %d",&a,&b);
	/*
	int t=a;
	
	for(;t>0;t--){
		if(a%t==0){
			if(b%t==0){
				printf("���Լ����%d��",t);
				break;
			}
		}
}
	*/
	
	int t;
	
	while(b!=0){
		t=a%b;
		a=b;
		b=t;
	}
	printf("���Լ����%d��",a);
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	

