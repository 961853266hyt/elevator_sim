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

void PrintCube(int num){           //��ӡnum������ 
	for(int i=0;i<num;i++) 
		printf("��");
}

void PrintSpace(int num){
	for(int i=0;i<num;i++) 
		printf("  ");                    
}

void PrintEle(int num){
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
			PrintEle(e->capacity);
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

void set(ptr_f f,ptr_e e){
	f->capacity=6;
	f->height=5;
	f->num=4;
	e->capacity=8;
	e->current_pos=10;
	return;
}

int main(){
	ptr_f f=(ptr_f)malloc(sizeof(struct floor));
	ptr_e e=(ptr_e)malloc(sizeof(struct elevator));
	set(f,e);
	PrintBuilding(f,e);
	return 0;
}
