#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#include<time.h>
#include<windows.h>

#define downwards 0
#define upwards 1
#define open 2
#define close 3
#define wall 4
#define pass 5 
#define ele  6 
#define person 7 
#define max_floor 20      //����м���¥
#define map_w 100
#define map_h 100
#define sleeptime 500     //����һ�μ��ʱ��ms
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
	List L[max_floor];             //���Ա����� 
	
}floor_info,*ptr_f;   

typedef struct elevator{
	int capacity;   	//��������������� 
	int direction;  	//���еķ���  downwards��upwards 
	int current_pos;	//��ǰ������
	int current_num;    //��ǰ�������� 
	int current_floor;  //��ǰ�����ڵڼ���
	int door_status;    //�жϵ�������û�п�  open��close
	int* elem;          //�������Ա�洢�����е��˵���Ϣ�����е�ֵ������ȥ��¥���� 
}ele_info,*ptr_e;

ptr_f f;  //¥����Ϣ�ṹ��ָ�� 
ptr_e e;  //������Ϣ�ṹ��ָ��
int RandNum(int min,int max);
int GetFloor(int i);
void PrintBuild();
void PrintCube(int num);
void PrintSpace(int num);
void PrintStar(int num);
void Set();
void MainMenu();
void DefaultSim();
void SetMap(); 
void ElePosChange();
void PeopleSim();
void SetEle();         //�ڶ�ά�������趨���ݵ�λ�� 
int RandNum(int min,int max){           //����min<=x<=max�������
    int result = rand()%(max-min+1)+min;
	return result;
}
void EleRun(){
	SetMap();
	SetEle();                      //¥����ݳ�ʼ�� 
	while(1){
		if(clk==0)                 //¥����Ϣ��ʼ��
		{
			PeopleSim(); 
		 	e->direction=upwards;
		}
		e->current_floor=GetFloor(e->current_pos);
		if(e->current_pos%f->height==0)
		{  				//�ﵽĳһ��
			e->door_status=open;
			/*
			PeopleChange();  //��Ա����
			*/ 
		}
		else{
			e->door_status=close;
		} 
		PrintBuild();
		clk++;
		ElePosChange();//�������з���ı����λ��
	}
	return;
}
/*
int IsDoorOpen(){             //�жϿ��ŵ�����
	if(e->current_pos%f->height==0&&) return 1;
	return 0;
}
/*
void PeopleChange(){










	return;
}
*/
int GetFloor(int i){              //������������ת����¥��  ��ײ�Ϊ0��
	int floor=f->num-((i-1)/f->height)-1;
	return floor;
}
void PeopleSim(){
	for(int i=0;i<f->num;i++)
	{
		f->L[i].current_num=RandNum(0,f->capacity);         //���ɸò����ڵȺ������
		for(int j=0;j<f->L[i].current_num;j++)
		{                 //������ɸ�����Ҫȥ��¥��
			f->L[i].elem=(int*)malloc(f->capacity*sizeof(int)); //��elem���Ա��ʼ��
			while((f->L[i].elem[j]=RandNum(0,f->num-1))==i){    //�����Ҫȥ���ǵ�ǰ¥�㣬���������� 
				;
			} 
			Map[(f->num-i)*f->height-1][e->capacity+2+j]=person;          	//��ͼ�ϱ�ʶ���Ǹ�����
			Map[(f->num-i)*f->height-2][e->capacity+2+j]=-(f->L[i].elem[j]); //������Ϸ���λ�� �ø����ľ���ֵ��ʾ��ȥ��¥��
		}
	}
	return;
}
void PrintBuild(){
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
				default:printf("%d ",abs(Map[i][j]));break;   //�ø�������ֵ����ÿ����Ҫȥ��¥���� 
			}                  
		}
		printf("%d",i);
		printf("\n");  
	}
	printf("��ǰ������%d��...\n",clk);
	printf("�������ڵ�%d��\n",e->current_floor);
	Sleep(500);
	system("cls");
} 

void SetMap(){            //map��ʼ��
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
		

		}
	}

	
	return;
}
void SetEle(){
	for(int j=1;j<=e->capacity;j++)  //���ݵ�λ�� 
	{          
		Map[e->current_pos][j]=ele; 
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
		case(2):Set();break;
		case(3):break;
		case(4):break;
		case(0):break;
	}	
	return;
}

void ElePosChange(){    //�������� ����ı����λ��
	int j;
	if(e->direction==downwards)
	{
		e->current_pos++;	
		for(j=1;j<=e->capacity;j++)  
		{	          
			Map[e->current_pos][j]=ele;      //ȷ�����ݵ�λ�� 
			Map[e->current_pos-1][j]=pass;   //�����ϴε��� 
		}
	}
	else
	{
		e->current_pos--;
		for(j=1;j<=e->capacity;j++)  
		{          
			Map[e->current_pos][j]=ele; 
			Map[e->current_pos+1][j]=pass; 
		}
	}
	if(e->current_pos==f->height*f->num&&e->direction==downwards||e->current_pos==f->height&&e->direction==upwards)
	{
		e->direction=!(e->direction);
	}
	/* 
	if((GetFloor(i)==e->current_floor)&&(i%f->height!=0)&&(e->door_status==open)&&(j==e->capacity+1))     //���Ƶ����ŵĿ���
	{
		Map[i][j]=pass;
	}
	*/ 
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
	EleRun();
	/*
	SetMap();
	PeopleSim();          //������ɵȺ��˵�¥��ֲ�
	PrintBuild();*/
	system("pause");
	MainMenu();
	return;
} 
void Set(){
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
	e->direction=upwards;
	PrintStar(16);
	SetMap();
	SetEle();
	printf("\n"); 
	printf("���óɹ�������\n"); 
	set_flag=1;
	system("pause");
	MainMenu();
	return;
}

int main(){
	srand((unsigned)time(NULL));
	f=(ptr_f)malloc(sizeof(struct floor));      //�ṹ���ʼ�� 
	e=(ptr_e)malloc(sizeof(struct elevator));
	MainMenu();	
	return 0;
}
