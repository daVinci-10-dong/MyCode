#include<stdio.h>

int main()
{
	FILE *fp = fopen("","r");
	if( fp ){
		int num;
		fscanf(fp,"%d",&num);
		fclose(fp);
	}else{
		printf("�޷����ļ�\n");
	}
	return 0;
}
