#ifndef MY_DEFINE_H
#include "My_define.h"
extern const int mseconds100;
extern const int mseconds500;  
extern const int mseconds600;
extern const int mseconds1000;
extern int PAUSE,END;
extern string Hat_color,Tail_color;
extern int count;

extern int Enemy_track[3][100];
extern struct character enemy[4];// 0,1,2,是敌人，3是玩家 
extern int dx[4];
extern int dy[4];
extern char text[2][100]; /*输入的字符串缓冲区*/
extern int textlen[2],Isleft[2],textID;/*输入的字符串长度*/
extern double textx[2],texty[2]; /*字符串的起始位置*/
extern bool isDisplayText;
extern int HaveMusic;
extern int Frozen_cnt;
extern string Filename[3];
extern int MapPattern;
extern bool DyeingPattern;//染色模式的开关 
extern string Dyeing_color[4]; 
extern struct Map MapBlock[Line][Row];

extern int sizeof_Bomb;
extern BombP head,tail;
extern FrozenP frozen_head,frozen_tail;
extern FILE *fp;
extern int Buttonnum;


void display2() {
	count=2;Buttonnum=0;
	displayclear();
	SetPointSize(16); 
	Draw_labal(7,12,12.6,11.6,"地    图    选    择","Mediumslateblue");
	Draw_labal(7,12,8.1,7.1,"形    象    选    择","Mediumslateblue");
	Go_down(2,5.5,1.5,"Chocolate","Chocolate(S)");
	Go_down(6,5.5,1.5,"IndianRed","IndianRed(S)");
	Go_down(10,5.5,1.5,"DeepPink","DeepPink(S)");
	Go_down(14,5.5,1.5,"RoyalBlue","RoyalBlue(S)");
	Draw_button(15,18,1.5,0.5,"返回上一界面",ButtonColor);
	Draw_button(2,4,3.4,2.8,"Pick",ButtonColor);
	Draw_button(6,8,3.4,2.8,"Pick",ButtonColor);
	Draw_button(10,12,3.4,2.8,"Pick",ButtonColor);
	Draw_button(14,16,3.4,2.8,"Pick",ButtonColor);
	Draw_button(2,6,10.6,9.6,"经      典",ButtonColor);
	Draw_button(7.5,11.5,10.6,9.6,"文      件",ButtonColor);
	Draw_button(13,17,10.6,9.6,"编      辑",ButtonColor);
	Draw_button(7,12,2,1,"确  认  以  开  始",ButtonColor);
}
void Main_init() /*仅初始化执行一次*/
{
	Dyeing_color[0]="White";
	Dyeing_color[1]="Powderblue";
	Dyeing_color[2]="Turquoise"; 
	Dyeing_color[3]="Darkgoldenrod"; 
	
    DisplayClear();
	InitMapState(); 
	InitMap();
	InitStateColumn();
	DrawAllPlayers();
	PAUSE=0;
	mciSendString("play 11638.mp3 repeat",NULL,0,NULL);
	startTimer(TIMER_BLINK600,mseconds600);
    startTimer(TIMER_BLINK500,mseconds500);
    startTimer(TIMER_BLINK100,mseconds100);
    startTimer(TIMER_BLINK1000,mseconds1000);
}
void InitStateColumn(void){
	SetPenColor("LightPink");
	DrawRectangle(0,WindowHeight,StateColumnWidth,WindowHeight,1);
	int i;
	SetPenColor("DarkPink");
	for(i=0;i<5;i++)
		DrawRectangle(1.0,WindowHeight-0.3*(i+1)-i*StateColumnBlockWidth,StateColumnBlockWidth,StateColumnBlockWidth,1);
	for(i=0;i<4;i++)
		Go_down(1.2,WindowHeight-(i+1)*0.8-i*1.5-0.3,0.8,enemy[i].Color1,enemy[i].Color2);
		
	SetPenColor("DarkOrange");
	Filled_rounded_rectangular(1,1,0.5,0.5,0.1);
	Filled_rounded_rectangular(1.7,1,0.5,0.5,0.1);
	Filled_rounded_rectangular(2.4,1,0.5,0.5,0.1);
	SetPenColor("WhiteOrange");
	DrawRectangle(1.12,0.85,0.08,0.25,1);
	DrawRectangle(1.28,0.85,0.08,0.25,1);
	DrawRectangle(1.84,0.84,0.2,0.2,1);
	MovePen(2.525,0.8);
	StartFilledRegion(1);
	DrawLine(0,-0.15);
	DrawLine(0.07,0);
	DrawLine(0.15,-0.12);
	DrawLine(0,0.39);
	DrawLine(-0.15,-0.12);
	DrawLine(-0.07,0);
	EndFilledRegion();
}
void InitCharacters(void){
	int i;
	for(i=0;i<4;i++){
		enemy[i].BombPower=1;
		enemy[i].Blood=3;
		enemy[i].Speed=0.25;
		enemy[i].Shied=0;
		enemy[i].Bombnum=1;
		enemy[i].Glove=0;
		if(i<3)
		enemy[i].Color1="Mediumslateblue",
		enemy[i].Color2="Mediumslateblue(S3)";
	}
	enemy[0].PositionX=enemy[3].PositionX=StateColumnWidth+3*BlockWidth+0.5;
	enemy[1].PositionX=enemy[2].PositionX=StateColumnWidth+11*BlockWidth+0.5; 
	enemy[0].PositionY=enemy[1].PositionY=3*BlockWidth+0.5;
	enemy[2].PositionY=enemy[3].PositionY=9*BlockWidth+0.5;
	enemy[0].direction=enemy[1].direction=3;
	enemy[2].direction=enemy[3].direction=1;
	enemy[3].PositionX-=BlockWidth;
}
void InitMapState(void){
	int i,j,n,sign=0;
	for(i=0;i<Line;i++)
		for(j=0;j<Row;j++){
			MapBlock[i][j].BlockX=BlockWidth*i+StateColumnWidth;
			MapBlock[i][j].BlockY=BlockWidth*(j+1);
			MapBlock[i][j].Player=NULL;
			MapBlock[i][j].BombExist=NULL;
			MapBlock[i][j].Item=0;
			MapBlock[i][j].Dyeing=-1;
		}
	InitCharacters();
	OpenFileMap();
}
void InitMap(void){
	int i,j;
	SetPenColor("LightYellow");
	DrawRectangle(StateColumnWidth,WindowHeight,WindowWidth,WindowHeight,1);
	for(j=Row-1;j>=0;j--)
	    for(i=0;i<Line;i++){
	    if(!MapBlock[i][j].Type)//如果是通道 
		;
	    else if(!(MapBlock[i][j].Type%2))//如果是固定障碍物 
	    	DrawBarrier1(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,(MapBlock[i][j].Type-1)/2);
		else//如果是可炸障碍物 
			DrawBarrier2(MapBlock[i][j].BlockX,MapBlock[i][j].BlockY,MapBlock[i][j].Type/2);
		}
}
void OpenFileMap(void){
	int i,j;
	char ch;
	if((fp=fopen("setting.txt","r"))==NULL){
			printf("File open error!\n");
			exit(0);
		}
	for(j=Row-1;j>=0;j--){
		for(i=0;i<Line;i++){ 
			ch=fgetc(fp);
			MapBlock[i][j].Type=ch-'0';
		}
		fgetc(fp);
	}
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
}
void Draw_pause(){
	SetPenColor("Light Gray");
	Filled_rounded_rectangular(WindowWidth/2-2,WindowHeight/2+2,4,4,1);
	SetPenColor("Dark Gray");
	Filled_rounded_rectangular(WindowWidth/2-1.1,WindowHeight/2+1,0.7,2,0.35);
	Filled_rounded_rectangular(WindowWidth/2+0.4,WindowHeight/2+1,0.7,2,0.35);
	SetPenColor("Black");
}
void Draw_continue(){
	SetPenColor("Light Gray");
	Filled_rounded_rectangular(WindowWidth/2-2,WindowHeight/2+2,4,4,1);
	SetPenColor("Dark Gray");
	MovePen(WindowWidth/2-0.8,WindowHeight/2+0.75);
	StartFilledRegion(1);
	DrawLine(0,-1.5);
	Draw_arc(0.25,0.25,180,120);
	DrawLine(1.3,0.75);
	Draw_arc(0.25,0.25,-60,120);
	DrawLine(-1.3,0.75);
	Draw_arc(0.25,0.25,60,120);
	EndFilledRegion();
	SetPenColor("Black");
}
char timedisplay[5]={'0','1',':','3','0'};
void WriteText(double dx,double dy,string S){
	SetPenColor("DarkPink");
	DrawRectangle(dx,dy+0.3,TextStringWidth(S),0.3,1);
	SetPenColor("Black");
	MovePen(dx,dy);
	DrawTextString(S);
}
void DrawStateItems(void){
	char *num[10]={"0","1","2","3","4","5","6","7","8","9"};
	int i,j,cnt=0;
	for(i=0;i<4;i++,cnt=0){
		double yy=WindowHeight-0.3*(i+1)-i*StateColumnBlockWidth;
		SetPenColor("LightPink");
		DrawRectangle(3.0,yy,0.5,2,1);
		DrawRectangle(0.5,yy,0.5,2,1);
		
		Draw_bomb(3.0,yy,0.5);
		WriteText(2.7,yy-0.4,num[enemy[i].Bombnum]);
		
		Draw_rapid(3.0,yy-0.5,0.5);
		WriteText(2.7,yy-0.9,num[(int)(enemy[i].Speed*4)]); 
		
		if(enemy[i].Glove)
			Draw_hand(3.0,yy-1-cnt*0.5,0.5),cnt++;
		if(enemy[i].BombPower>1)
			Draw_drink(3.0,yy-1-cnt*0.5,0.5),cnt++;
		if(enemy[i].Shied==1)
			Draw_shied(3.0,yy-1-cnt*0.5,0.5),cnt++;
		for(j=0;j<enemy[i].Blood;j++)
			Draw_heart(0.5,yy-j*0.5,0.5);
	}
	WriteText(1.2,WindowHeight-0.3*(i+4)-4*StateColumnBlockWidth+0.2,"倒计时");
	WriteText(1.4,WindowHeight-0.3*(i+4)-4*StateColumnBlockWidth-0.3,timedisplay);
}
int ChangeClockDisplay(void){
	if(timedisplay[4]>'0')
			timedisplay[4]--;
		else{
			if(timedisplay[3]>'0')
				timedisplay[3]--;
			else{
				if(timedisplay[1]>'0')
					timedisplay[1]--;
				else{
					return 0;
				}
				timedisplay[3]='5';
			}
			timedisplay[4]='9';
		}
		return 1;
}
#endif
