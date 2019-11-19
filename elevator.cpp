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
#define max_floor 20      //最多有几层楼
#define map_w 100
#define map_h 100
#define sleeptime 500     //运行一次间隔时间ms
int Map[map_w][map_h];    //存放每个格子需打印的类型，wall，pass,etc. 
int set_flag=0;           //判断是否进行过自定义设置 
int clk=0;                //电梯运行计时器 


typedef struct floor_list{      //每个楼层对应一个线性表数组，						 
	int *elem;			        //其中的elem存放该楼层人的信息 
	int current_num;          //当前楼层人数 
}*info,List;      
  
typedef struct floor{
	int height;     	//楼层高度 
	int capacity;   	//楼层最多容纳的人数 
	int num;        	//楼层数量 
	List L[max_floor];             //线性表数组 
	
}floor_info,*ptr_f;   

typedef struct elevator{
	int capacity;   	//电梯最多容纳人数 
	int direction;  	//运行的方向  downwards或upwards 
	int current_pos;	//当前纵坐标
	int current_num;    //当前电梯人数 
	int current_floor;  //当前电梯在第几层
	int door_status;    //判断电梯门有没有开  open和close
	int* elem;          //引入线性表存储电梯中的人的信息，表中的值代表想去的楼层数 
}ele_info,*ptr_e;

ptr_f f;  //楼层信息结构体指针 
ptr_e e;  //电梯信息结构体指针
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
void SetEle();         //在二维数组中设定电梯的位置 
int RandNum(int min,int max){           //生成min<=x<=max的随机数
    int result = rand()%(max-min+1)+min;
	return result;
}
void EleRun(){
	SetMap();
	SetEle();                      //楼层电梯初始化 
	while(1){
		if(clk==0)                 //楼层信息初始化
		{
			PeopleSim(); 
		 	e->direction=upwards;
		}
		e->current_floor=GetFloor(e->current_pos);
		if(e->current_pos%f->height==0)
		{  				//达到某一层
			e->door_status=open;
			/*
			PeopleChange();  //人员进出
			*/ 
		}
		else{
			e->door_status=close;
		} 
		PrintBuild();
		clk++;
		ElePosChange();//根据运行方向改变电梯位置
	}
	return;
}
/*
int IsDoorOpen(){             //判断开门的条件
	if(e->current_pos%f->height==0&&) return 1;
	return 0;
}
/*
void PeopleChange(){










	return;
}
*/
int GetFloor(int i){              //将给定纵坐标转化成楼层  最底层为0层
	int floor=f->num-((i-1)/f->height)-1;
	return floor;
}
void PeopleSim(){
	for(int i=0;i<f->num;i++)
	{
		f->L[i].current_num=RandNum(0,f->capacity);         //生成该层正在等候的人数
		for(int j=0;j<f->L[i].current_num;j++)
		{                 //随机生成各自想要去的楼层
			f->L[i].elem=(int*)malloc(f->capacity*sizeof(int)); //对elem线性表初始化
			while((f->L[i].elem[j]=RandNum(0,f->num-1))==i){    //如果想要去的是当前楼层，则重新生成 
				;
			} 
			Map[(f->num-i)*f->height-1][e->capacity+2+j]=person;          	//在图上标识这是个活人
			Map[(f->num-i)*f->height-2][e->capacity+2+j]=-(f->L[i].elem[j]); //这个人上方的位置 用负数的绝对值显示想去的楼层
		}
	}
	return;
}
void PrintBuild(){
	int width=3+f->capacity+e->capacity;
	int height=f->height*f->num+2;
	if(width>=map_w||height>=map_h)
	{
		printf("输入超过限制！！！\n"); 
		exit(0); 
	}
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			switch(Map[i][j])
			{
				case(wall):printf("■");break;
				case(pass):printf("  ");break;
				case(ele): printf("**");break;
				case(person):printf("★");break;
				default:printf("%d ",abs(Map[i][j]));break;   //用负数绝对值代表每个人要去的楼层数 
			}                  
		}
		printf("%d",i);
		printf("\n");  
	}
	printf("当前已运行%d秒...\n",clk);
	printf("电梯正在第%d层\n",e->current_floor);
	Sleep(500);
	system("cls");
} 

void SetMap(){            //map初始化
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
	for(int j=1;j<=e->capacity;j++)  //电梯的位置 
	{          
		Map[e->current_pos][j]=ele; 
	}
	return;
} 

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

void MainMenu(){
	system("cls");
	int choice;
	PrintStar(4);printf("电梯模拟");PrintStar(4);
	printf("\n");
	printf("       1、开始模拟\n       2、自定义设置\n       3、\n       4、\n       0、退出\n");
	PrintStar(12);
	printf("    请选择：");
	scanf("%d",&choice);
	switch(choice){
		case(1):DefaultSim();break;   //默认设置 
		case(2):Set();break;
		case(3):break;
		case(4):break;
		case(0):break;
	}	
	return;
}

void ElePosChange(){    //根据运行 方向改变电梯位置
	int j;
	if(e->direction==downwards)
	{
		e->current_pos++;	
		for(j=1;j<=e->capacity;j++)  
		{	          
			Map[e->current_pos][j]=ele;      //确定电梯的位置 
			Map[e->current_pos-1][j]=pass;   //消除上次电梯 
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
	if((GetFloor(i)==e->current_floor)&&(i%f->height!=0)&&(e->door_status==open)&&(j==e->capacity+1))     //控制电梯门的开关
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
	printf("您还未进行设置，以下为默认设置的模拟\n"); 
	e->capacity=7;
	f->height=5;
	f->num=5;
	f->capacity=6;
	e->current_pos=f->num*f->height;  //默认设置 
	}
	EleRun();
	/*
	SetMap();
	PeopleSim();          //随机生成等候人的楼层分布
	PrintBuild();*/
	system("pause");
	MainMenu();
	return;
} 
void Set(){
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
	e->current_pos=f->num*f->height;   //默认电梯从底层出发 
	e->direction=upwards;
	PrintStar(16);
	SetMap();
	SetEle();
	printf("\n"); 
	printf("设置成功！！！\n"); 
	set_flag=1;
	system("pause");
	MainMenu();
	return;
}

int main(){
	srand((unsigned)time(NULL));
	f=(ptr_f)malloc(sizeof(struct floor));      //结构体初始化 
	e=(ptr_e)malloc(sizeof(struct elevator));
	MainMenu();	
	return 0;
}
