#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#include<time.h>
#define downwards 0
#define upwards 1

#define wall 0
#define pass 1
#define ele  2
#define person 3
#define map_w 100
#define map_h 100
int Map[map_w][map_h];    //���ÿ���������ӡ�����ͣ�wall��pass,etc. 
int set_flag=0;           //�ж��Ƿ���й��Զ������� 
int clk=0;                //�������м�ʱ�� 


typedef struct floor_list{      //ÿ��¥���Ӧһ�����Ա����飬						 
	int *elem;			        //���е�elem��Ÿ�¥���˵���Ϣ 
	int current_num;          //��ǰ¥������ 
}*info,List;      
  
typedef struct floor{
	int height;     	//¥��߶� 
	int capacity;   	//¥��������ɵ����� 
	int num;        	//¥������ 
	int current_floor;  //��ǰ¥�� 
	info L;             //���Ա������ͷָ�� 
	
}floor_info,*ptr_f;   

typedef struct elevator{
	int capacity;   	//��������������� 
	int direction;  	//���еķ���  downwards��upwards 
	int current_pos;	//��ǰ������
	int current_num;  //��ǰ�������� 
	int* elem;          //�������Ա�洢�����е��˵���Ϣ�����е�ֵ������ȥ��¥���� 
}ele_info,*ptr_e;

ptr_f f;  //¥����Ϣ�ṹ��ָ�� 
ptr_e e;  //������Ϣ�ṹ��ָ��
int RandNum(int min,int max);
void PrintBuild();
void PrintCube(int num);
void PrintSpace(int num);
void PrintStar(int num);
void set();
void MainMenu();
void DefaultSim();
int RandNum(int min,int max){           //����min<=x<=max�������
	srand((unsigned)time(NULL));
    int result = rand()%(max-min+1)+min;
	return result;
}
void PeopleSim(){
	for(int i=0;i<f->num;i++)
	{
		f->L[i].current_num=RandNum(0,f->capacity);         //���ɸò����ڵȺ������
		for(int j=0;j<f->L[i].current_num;j++)
		{                 //������ɸ�����Ҫȥ��¥��
			f->L[i].elem=(int*)malloc(f->capacity*sizeof(int)); //��elem���Ա��ʼ��
			f->L[i].elem[j]=RandNum(1,f->num-1);
			Map[(f->num-i)*f->height][e->capacity+2+j]=person;          //��ͼ�ϱ�ʽ���Ǹ�����
			Map[(f->num-i)*f->height-1][e->capacity+2+j]=-(f->L[i].elem[j]); //������Ϸ���λ�� �ø����ľ���ֵ��ʾ��ȥ��¥��
		}
	}
	return;
}
void PrintBuild(){
	PeopleSim();
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
void SetMap(){
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

void MainMenu(){
	system("cls");
	int choice;
	PrintStar(4);printf("����ģ��");PrintStar(4);
	printf("\n");
	printf("       1����ʼģ��\n       2���Զ�������\n       3��\n       4��\n       0���˳�\n");
	PrintStar(12);
	printf("    ��ѡ��");
	scanf("%d",&choice);
	switch(choice){
		case(1):DefaultSim();break;   //Ĭ������ 
		case(2):set();break;
		case(3):break;
		case(4):break;
		case(0):break;
	}
		
	return;
}

void ElePosChange(){
	if(e->direction==downwards)
	{
		e->current_pos++;	
	}
	else
	{
		e->current_pos--;
	}
	return;
}

void DefaultSim(){
	system("cls");
	if(!set_flag)
	{
	printf("����δ�������ã�����ΪĬ�����õ�ģ��\n"); 
	e->capacity=7;
	f->height=5;
	f->num=5;
	f->capacity=6;
	e->current_pos=f->num*f->height;  //Ĭ������ 
	}
	SetMap();
	PrintBuild();
	system("pause");
	MainMenu();
	return;
} 
void set(){
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
	/* 
	e->L=CreatList(e->capacity);
	f->L=CreatList(f->capacity);      //���Ա��ʼ�� 
	*/ 

	f->L=(info)malloc(f->num*sizeof(struct floor_list));                        	//�ṹ�������ʼ�� 
	
	e->current_pos=f->num*f->height;   //Ĭ�ϵ��ݴӵײ���� 
	e->direction=upwards;
	PrintStar(16);
	SetMap();
	printf("\n"); 
	printf("���óɹ�������\n"); 
	set_flag=1;
	system("pause");
	MainMenu();
	return;
}

int main(){
	f=(ptr_f)malloc(sizeof(struct floor));      //�ṹ���ʼ�� 
	e=(ptr_e)malloc(sizeof(struct elevator));

	MainMenu();	
	return 0;
}
