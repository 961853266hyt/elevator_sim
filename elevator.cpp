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

void PrintCube(int num){           //打印num个方块 
	for(int i=0;i<num;i++) 
		printf("■");
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
	
	PrintCube(width);    //打印顶层
	printf("\n"); 
	
	for(i=1;i<=f->num*f->height;i++)
	{
		printf("■");
		if(i==e->current_pos)           //判断电梯所在的位置 
			PrintEle(e->capacity);
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
