#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#define downwards 0
#define upwards 1

#define wall 0
#define pass 1
#define ele  2
#define person 3
#define map_w 300
#define map_h 300
int Map[map_w][map_h];    //���ÿ���������ӡ�����ͣ�wall��pass,etc. 
int set_flag=0;            //�ж��Ƿ���й��Զ������� 
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

void PrintBuild(ptr_f f,ptr_e e);
void PrintCube(int num);
void PrintSpace(int num);
void PrintStar(int num);
void set(ptr_f f,ptr_e e);
void MainMenu(ptr_f f,ptr_e e);
void default_sim(ptr_f f,ptr_e e);
void PrintBuild(ptr_f f,ptr_e e){
	int width=3+f->capacity+e->capacity;
	int height=f->height*f->num+2;
	if(width>=map_w||height>=map_h)
	{
		printf("���볬�����ƣ�����\n"); 
		exit(0); 
	}
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			switch(Map[i][j])
			{
				case(wall):printf("��");break;
				case(pass):printf("  ");break;
				case(ele): printf("**");break;
				case(person):printf("��");break;
				default:printf("%d",abs(Map[i][j]));break;   //�ø�������ֵ����ÿ����Ҫȥ��¥���� 
			}                  
		}
		printf("%d",i);
		printf("\n");  
	}
} 
void SetMap(ptr_f f,ptr_e e){
	int i,j;
	int width=3+f->capacity+e->capacity;
	for(i=0;i<=f->num*f->height+1;i++)
	{	 
		for(j=0;j<width;j++)
		{	
		
			if(i==0||i==f->num*f->height+1||j==0||j==e->capacity+1||j==width-1||(i%f->height==0&&j>e->capacity))
			{
				Map[i][j]=wall;	
			}
			else
			{
				Map[i][j]=pass;
			}
			if(i==e->current_pos&&j>0&&j<=e->capacity)   //���ݵ�ǰλ�� 
			{
				Map[i][j]=ele;
			}		
		}
	}
	return;
}

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

void MainMenu(ptr_f f,ptr_e e){
	system("cls");
	int choice;
	PrintStar(4);printf("����ģ��");PrintStar(4);
	printf("\n");
	printf("       1����ʼģ��\n       2���Զ�������\n       3��\n       4��\n       0���˳�\n");
	PrintStar(12);
	printf("    ��ѡ��");
	scanf("%d",&choice);
	switch(choice){
		case(1):default_sim(f,e);break;   //Ĭ������ 
		case(2):set(f,e);break;
		case(3):break;
		case(4):break;
		case(0):break;
	}
		
	return;
}
void default_sim(ptr_f f,ptr_e e){
	if(!set_flag)
	{
	printf("����δ�������ã�����ΪĬ�����õ�ģ��\n"); 
	e->capacity=7;
	f->height=5;
	f->num=5;
	f->capacity=6;
	e->current_pos=f->num*f->height;  //Ĭ������ 
	}
	SetMap(f,e);
	PrintBuild(f,e);
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
	e->current_pos=f->num*f->height;   //Ĭ�ϵ��ݴӵײ���� 
	PrintStar(16);
	SetMap(f,e);
	printf("\n"); 
	printf("���óɹ�������\n"); 
	set_flag=1;
	system("pause");
	MainMenu(f,e);
	return;
}

int main(){
	ptr_f f=(ptr_f)malloc(sizeof(struct floor));
	ptr_e e=(ptr_e)malloc(sizeof(struct elevator));
	MainMenu(f,e);	
	return 0;
}
