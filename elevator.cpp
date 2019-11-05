#include<stdio.h>
#include<stdlib.h> 
#define downwards 0
#define upwards 1
 
typedef struct floor{
	int height;     	//¥��߶� 
	int capacity;   	//¥��������ɵ����� 
	int num;        	//¥������ 
	int current_floor;  //��ǰ¥�� 
	
}floor_info,*ptr_f;

typedef struct elevator{
	int capacity;   	//��������������� 
	int direction;  	//���еķ���  downwards��upwards 
	int current_pos;	//��ǰ������ 
	
}ele_info,*ptr_e;

void PrintCube(int num);
void PrintSpace(int num);
void PrintStar(int num);
void PrintBuilding(ptr_f f,ptr_e e);
void set(ptr_f f,ptr_e e);
void MainMenu(ptr_f f,ptr_e e);

void PrintCube(int num){           //��ӡnum������ 
	for(int i=0;i<num;i++) 
		printf("��");
}

void PrintSpace(int num){
	for(int i=0;i<num;i++) 
		printf("  ");                    
}

void PrintStar(int num){
	for(int i=0;i<num;i++) 
		printf("**"); 
}
void PrintBuilding(ptr_f f,ptr_e e){
	int i,j;
	int width=3+f->capacity+e->capacity;
	
	PrintCube(width);    //��ӡ����
	printf("\n"); 
	
	for(i=1;i<=f->num*f->height;i++)
	{
		printf("��");
		if(i==e->current_pos)           //�жϵ������ڵ�λ�� 
			PrintStar(e->capacity);
		else 
			PrintSpace(e->capacity);		
				
		printf("��");
		if(i%f->height==0)
		{
			PrintCube(f->capacity+1);	
		}
		else
		{
			PrintSpace(f->capacity);
			printf("��");
		}
		printf("\n");
		
	}	
	PrintCube(width);    //��ӡ�ײ� 
	printf("\n");
	return;
}

void MainMenu(ptr_f f,ptr_e e){
	int choice;
	PrintStar(4);printf("����ģ��");PrintStar(4);
	printf("\n");
	printf("       1��\n       2������\n       3��\n       4��\n       0���˳�\n");
	PrintStar(12);
	printf("    ��ѡ��");
	scanf("%d",&choice);
	switch(choice){
		case(1):break;
		case(2):set(f,e);break;
		case(3):break;
		case(4):break;
		case(0):break;
	}
		
	return;
}

void set(ptr_f f,ptr_e e){
	int choice;
	system("cls");
	PrintStar(7);printf("����");PrintStar(7);
	printf("\n");
	printf("������¥��������");
	scanf("%d",&(f->num)); 
	printf("������һ��¥�ĸ߶ȣ�һ������Ϊ1����");
	scanf("%d",&(f->height));
	printf("������һ��¥�Ŀ�ȣ�һ������Ϊ1����");
	scanf("%d",&(f->capacity));
	printf("��������ݵ��������������");
	scanf("%d",&(e->capacity));
	PrintStar(16);
	printf("\n"); 
	printf("���óɹ�������\n"); 
	/*
	f->capacity=6;
	f->height=5;
	f->num=4;
	e->capacity=8;*/
	e->current_pos=f->num*f->height;    //Ĭ�ϵ��ݵײ���� 
	return;
}

int main(){
	ptr_f f=(ptr_f)malloc(sizeof(struct floor));
	ptr_e e=(ptr_e)malloc(sizeof(struct elevator));
	MainMenu(f,e);	
	PrintBuilding(f,e);
	return 0;
}
