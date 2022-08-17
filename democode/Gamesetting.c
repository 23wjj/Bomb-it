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

int Axxt[10][10]={
{62,99,96,96,111,99,99,103,63},
{24,24,60,60,102,102,126,195,195},
{195,195,195,231,255,255,219,219,195},
{252,192,192,192,248,192,192,192,252},
{62,99,99,99,99,99,99,99,62},
{195,195,102,102,102,60,60,24,24},
{252,192,192,192,248,192,192,192,252},
{252,198,198,198,252,198,198,198,198},
};
int Bxxt[10][10]={
{195,195,195,195,219,219,231,195,195},
{255,255,24,24,24,24,24,255,255},
{227,227,243,211,219,203,207,199,199}
};
void Draw_point(double x,double y,double size){
	MovePen(x,y); 
	SetPenColor("Green");
	StartFilledRegion(1);
	DrawLine(size,0);
	DrawLine(0,-size);
	DrawLine(-size,0);
	DrawLine(0,size);
	EndFilledRegion();
}
void Draw_gameover(double cx,double cy){
	PlaySound(TEXT("9547.wav"),NULL,SND_FILENAME | SND_ASYNC);
	Buttonnum=0;
	double dx=cx-1,dy=cy+0.9;
	SetPenColor("Black");
	Filled_rounded_rectangular(cx-4,dy+0.5,8,8,0.5);
	int i,j,k;double size=0.06;
	for(i=0;i<8;i++)
	for(j=0;j<9;j++)
	for(k=0;k<8;k++)
	if((Axxt[i][j])&(1<<k)){
		if(i<7)	 Draw_point(dx-k*0.1+(i%4)*0.9,dy-j*0.1-(i>3),size);
		if(i==7) Draw_point(dx+2.5-k*0.1,dy-j*0.1-1,size);
	}
	SetPenColor("Gray");
	dy-=2.9;dx-=1.5; 
	MovePen(dx,dy);
	DrawTextString("一胜一负,兵家常势。");
	MovePen(dx+2,dy-0.6);
	DrawTextString("----《旧唐书·裴度传》");
}

void Draw_gamewin(double cx,double cy){
	PlaySound(TEXT("9347.wav"),NULL,SND_FILENAME | SND_ASYNC);
	Buttonnum=0;
	double dx=cx-1,dy=cy+0.9;
	SetPenColor("Black");
	Filled_rounded_rectangular(cx-4,dy+0.5,8,8,0.5);
	int i,j,k;double size=0.1;
	for(i=0;i<3;i++)
	for(j=0;j<9;j++)
	for(k=0;k<8;k++)
	if((Bxxt[i][j])&(1<<k))
		Draw_point(dx-k*0.15+i*1.5,dy-j*0.15,size);
	SetPenColor("Gray");
	dy-=2.9;dx-=1.5; 
	MovePen(dx,dy);
	DrawTextString("王者之兵，胜而不骄");
	MovePen(dx+2,dy-0.6);
	DrawTextString("----《商军书·战法》");
}
void DisPause(){
	PAUSE=~PAUSE;
	if(!PAUSE){
		Draw_continue();
		InitMap();
				SetPenColor("LightPink");
				Filled_rounded_rectangular(1,1,0.5,0.7,0.1);
				SetPenColor("DarkOrange");
				Filled_rounded_rectangular(1,1,0.5,0.5,0.1);
				SetPenColor("WhiteOrange");
				DrawRectangle(1.12,0.85,0.08,0.25,1);
				DrawRectangle(1.28,0.85,0.08,0.25,1);
	}
	else{
		Draw_pause();
				SetPenColor("LightPink");
				Filled_rounded_rectangular(1,1,0.5,0.7,0.1);
				SetPenColor("DarkOrange");
				Filled_rounded_rectangular(1,1,0.5,0.5,0.1);
				SetPenColor("WhiteOrange");
				MovePen(1.15,0.875);
				StartFilledRegion(1);
				DrawLine(0,-0.3);
				DrawLine(0.2,0.15);
				DrawLine(-0.2,0.15);
				EndFilledRegion();	
	}
}
void DisMusic(){
	SetPenColor("LightPink");
	Filled_rounded_rectangular(2.4,1,0.5,0.7,0.1);
	SetPenColor("DarkOrange");
	Filled_rounded_rectangular(2.4,1,0.5,0.5,0.1);
	SetPenColor("WhiteOrange");
	MovePen(2.525,0.8);
	StartFilledRegion(1);
	DrawLine(0,-0.15);
	DrawLine(0.07,0);
	DrawLine(0.15,-0.12);
	DrawLine(0,0.39);
	DrawLine(-0.15,-0.12);
	DrawLine(-0.07,0);
	EndFilledRegion();
	HaveMusic=1-HaveMusic;
	if(!HaveMusic){
		MovePen(2.475,0.925);
		SetPenColor("Red");
		SetPenSize(2);
		DrawLine(0.35,-0.35);
		SetPenSize(1);
		SetPenColor("Black");
		mciSendString("close 11638.mp3",NULL,0,NULL);
	}
	if(HaveMusic) mciSendString("play 11638.mp3 repeat",NULL,0,NULL);;
}
int blocknum[4];
char a[10]="0",b[10]="00";
void Draw_score(){
	int i,j;
	for(i=0;i<Line;i++)
	for(j=0;j<Row;j++)
	if(MapBlock[i][j].Dyeing>=0)
	blocknum[MapBlock[i][j].Dyeing]++;
//	blocknum[0]=28-blocknum[1]-blocknum[2]-blocknum[3];
	SetPenColor("White");
	for(i=0;i<4;i++){
		MovePen(7,5.2-i*0.7);
		DrawTextString("characer       get           blocks!");
		a[0]+=i+1;b[0]+=blocknum[i]/10;b[1]+=blocknum[i]%10;
		MovePen(8.7,5.2-i*0.7);DrawTextString(a);
		MovePen(10,5.2-i*0.7);DrawTextString(b);
		a[0]-=i+1;b[0]-=blocknum[i]/10;b[1]-=blocknum[i]%10;
	}
}
#endif
