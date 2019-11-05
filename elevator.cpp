#include<stdio.h>
#include<stdlib.h> 
#define downwards 0
#define upwards 1
 
typedef struct floor{
	int height;     	//楼层高度 
	int capacity;   	//楼层最多容纳的人数 
	int num;        	//楼层数量 
	int current_floor;  //当前楼层 
	
}floor_info,*ptr_f;

typedef struct elevator{
	int capacity;   	//电梯最多容纳人数 
	int direction;  	//运行的方向  downwards或upwards 
	int current_pos;	//当前纵坐标 
	
}ele_info,*ptr_e;

void PrintCube(int num);
void PrintSpace(int num);
void PrintStar(int num);
void PrintBuilding(ptr_f f,ptr_e e);
void set(ptr_f f,ptr_e e);
void MainMenu(ptr_f f,ptr_e e);

void PrintCube(int num){           //打印num个方块 
	for(int i=0;i<num;i++) 
		printf("■");
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
	
	PrintCube(width);    //打印顶层
	printf("\n"); 
	
	for(i=1;i<=f->num*f->height;i++)
	{
		printf("■");
		if(i==e->current_pos)           //判断电梯所在的位置 
			PrintStar(e->capacity);
		else 
			PrintSpace(e->capacity);		
				
		printf("■");
		if(i%f->height==0)
		{
			PrintCube(f->capacity+1);	
		}
		else
		{
			PrintSpace(f->capacity);
			printf("■");
		}
		printf("\n");
		
	}	
	PrintCube(width);    //打印底层 
	printf("\n");
	return;
}

void MainMenu(ptr_f f,ptr_e e){
	int choice;
	PrintStar(4);printf("电梯模拟");PrintStar(4);
	printf("\n");
	printf("       1、\n       2、设置\n       3、\n       4、\n       0、退出\n");
	PrintStar(12);
	printf("    请选择：");
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
	PrintStar(7);printf("设置");PrintStar(7);
	printf("\n");
	printf("请输入楼层数量：");
	scanf("%d",&(f->num)); 
	printf("请输入一层楼的高度（一个方格为1）：");
	scanf("%d",&(f->height));
	printf("请输入一层楼的宽度（一个方格为1）：");
	scanf("%d",&(f->capacity));
	printf("请输入电梯的最大容纳人数：");
	scanf("%d",&(e->capacity));
	PrintStar(16);
	printf("\n"); 
	printf("设置成功！！！\n"); 
	/*
	f->capacity=6;
	f->height=5;
	f->num=4;
	e->capacity=8;*/
	e->current_pos=f->num*f->height;    //默认电梯底层出发 
	return;
}

int main(){
	ptr_f f=(ptr_f)malloc(sizeof(struct floor));
	ptr_e e=(ptr_e)malloc(sizeof(struct elevator));
	MainMenu(f,e);	
	PrintBuilding(f,e);
	return 0;
}
