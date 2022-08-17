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


void DrawAllPlayers(){
	int i=3;while(i>=0) DrawOnePlayers(i--);
}
void DrawOnePlayers(int i){
	int direction;
	double PositionX,PositionY;
	string tmp1,tmp2;
	if(enemy[i].Blood>0){
		direction=enemy[i].direction;
		PositionX=enemy[i].PositionX;
		PositionY=enemy[i].PositionY;
		if(enemy[i].Frozen)
			DrawFrozenBefore(i);
		switch(direction){
			case 0:
				Go_right(PositionX-0.175+0.25*RATIO,PositionY+0.175-0.25+0.5-0.25*RATIO,RATIO,enemy[i].Color1,enemy[i].Color2);
				break;
			case 1:
				Go_down(PositionX-0.3-0.25*RATIO,PositionY+0.175+0.5-0.25-0.25*RATIO,RATIO,enemy[i].Color1,enemy[i].Color2);
				break;
			case 2:
				Go_left(PositionX-0.175-0.25*RATIO,PositionY+0.175+0.5-0.25-0.25*RATIO,RATIO,enemy[i].Color1,enemy[i].Color2);
				break;
			case 3:
				Go_up(PositionX-0.3-0.25*RATIO,PositionY+0.175+0.5-0.25-0.25*RATIO,RATIO,enemy[i].Color1,enemy[i].Color2);
				break;
		}
		if(enemy[i].Frozen)
			DrawFrozenAfter(i);
	}
}
void Go_down(double dx,double dy,double ratio,string Color1,string Color2){
	double Size_x=1.2*ratio,Size_y=1*ratio,Wid=0.05*ratio;
	double Eye_x=0.1*ratio,Eye_y=0.2*ratio;
	SetPenColor(Color2);
	MovePen(dx+Size_x-Wid*1.2,dy-Size_y+Wid*1.2);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*4,-45,45);
	DrawLine(0,Size_y-Wid*8);
	DrawLine(-Wid*7,-Wid*7);
	DrawLine(0,-Size_y+Wid*8);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_x,dy-Wid*4);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*4,0,90);
	DrawLine(-Wid*5,-Wid*5);
	DrawArc(Wid*4,90,-90);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_x-Wid*6,dy-Wid*2);
	StartFilledRegion(1);
	DrawLine(Wid*7,Wid*7);
	DrawLine(-Size_x+Wid*8,0);
	DrawArc(Wid*4,90,55);
	DrawLine(-Wid*5,-Wid*5);
	DrawLine(Size_x-Wid*6,0);
	EndFilledRegion();
	
	SetPenColor(Color1);
	Filled_rounded_rectangular(dx,dy,Size_x,Size_y,ratio*0.2);
	SetPenColor("Flesh");
	Filled_rounded_rectangular(dx+Wid*2,dy-Wid*2,Size_x-4*Wid,Size_y-4*Wid,ratio*0.2);
	SetPenColor("Black");
	MovePen(dx+Size_x/5*2,dy-Size_y/2);
	StartFilledRegion(1);
	Draw_arc(Eye_x,Eye_y,0,360);
	EndFilledRegion();
	MovePen(dx+Size_x/5*4,dy-Size_y/2);
	StartFilledRegion(1);
	Draw_arc(Eye_x,Eye_y,0,360);
	EndFilledRegion();
	
	SetPenColor(Hat_color);
	MovePen(dx+Size_x/2+Wid,dy+Wid*3);
	StartFilledRegion(1);
	Draw_arc(Size_x/2,Size_x/2,180,-50);
	Draw_arc(Wid*2.5,Wid*2.5,200,360);
	Draw_arc(Size_x/2.5,Size_x/2.5,150,62);
	Draw_arc(Size_x/10.5,Size_x/21,0,-180);
	EndFilledRegion();
	
	SetPenColor("Black");
}
void Go_up(double dx,double dy,double ratio,string Color1,string Color2){
	double Size_x=1.2*ratio,Size_y=1*ratio,Wid=0.05*ratio; 
	double Size_tail=0.15*ratio;
	SetPenColor(Color2);
	MovePen(dx+Size_x-Wid*1.2,dy-Size_y+Wid*1.2);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*4,-45,45);
	DrawLine(0,Size_y-Wid*8);
	DrawLine(-Wid*7,-Wid*7);
	DrawLine(0,-Size_y+Wid*8);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_x,dy-Wid*4);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*4,0,90);
	DrawLine(-Wid*5,-Wid*5);
	DrawArc(Wid*4,90,-90);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_x-Wid*6,dy-Wid*2);
	StartFilledRegion(1);
	DrawLine(Wid*7,Wid*7);
	DrawLine(-Size_x+Wid*8,0);
	DrawArc(Wid*4,90,55);
	DrawLine(-Wid*5,-Wid*5);
	DrawLine(Size_x-Wid*6,0);
	EndFilledRegion();
	
	SetPenColor(Color1);
	Filled_rounded_rectangular(dx,dy,Size_x,Size_y,ratio*0.2);
	
	MovePen(dx+Size_x/2+Size_tail,dy-Size_y+2*Size_tail);
	SetPenColor(Tail_color);
	StartFilledRegion(1);
	Draw_arc(Size_tail,Size_tail,0,360);
	EndFilledRegion();
	SetPenColor("Black");
	
	SetPenColor(Hat_color);
	MovePen(dx+Size_x/2+Wid*5,dy+Wid*3);
	StartFilledRegion(1);
	Draw_arc(Size_x/2,Size_x/2,0,50);
	Draw_arc(Wid*2.5,Wid*2.5,-20,360);
	Draw_arc(Size_x/2.5,Size_x/2.5,30,-62);
	Draw_arc(Size_x/10.5,Size_x/21,180,180);
	EndFilledRegion();
	SetPenColor("Black");
}
void Go_right(double dx,double dy,double ratio,string Color1,string Color2){
	double Size_thick=0.7*ratio,Size_y=1*ratio,Wid=0.05*ratio;
	double Size_tail=0.15*ratio;
	double Eye_x=0.05*ratio,Eye_y=0.2*ratio;
	
	SetPenColor(Color2);
	MovePen(dx+Wid*0.88,dy-Size_y+Wid*0.88);
	StartFilledRegion(1);
	DrawLine(-Wid*5,Wid*5);
	Draw_arc(Wid*3,Wid*3,225,-45);
	DrawLine(0,Size_y-Wid*6);
	DrawLine(Wid*6.5,-Wid*6.5);
	DrawLine(0,-Size_y+Wid*6);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx,dy-Wid*3);
	StartFilledRegion(1);
	DrawLine(-Wid*5,Wid*5);
	Draw_arc(Wid*3,Wid*3,180,-90);
	DrawLine(Wid*5,-Wid*5);
	Draw_arc(Wid*3,Wid*3,90,90);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Wid*4.5,dy-Wid*1.5);
	StartFilledRegion(1);
	DrawLine(-Wid*6.5,Wid*6.5);
	DrawLine(+Size_thick-Wid*6,0);
	Draw_arc(Wid*3,Wid*3,90,-45);
	DrawLine(Wid*5,-Wid*5);
	DrawLine(-Size_thick+Wid*7,0);
	EndFilledRegion();
	
	SetPenColor(Color1);
	Filled_rounded_rectangular(dx,dy,Size_thick,Size_y,ratio*0.15);
	SetPenColor("Flesh");
	Filled_leftrounded_rectangular(dx+Size_thick*3/4,dy-Size_y/8,Size_thick/4,Size_y*3/4,Wid*1.5);
	SetPenColor("Black");
	MovePen(dx+Size_thick+Eye_x,dy-Size_y/2);
	StartFilledRegion(1);
	Draw_arc(Eye_x,Eye_y,0,360);
	EndFilledRegion();
	
	SetPenColor(Tail_color);
	MovePen(dx-Wid*3,dy-Size_y+2.866*Size_tail+Wid*3);
	StartFilledRegion(1);
	DrawArc(Size_tail,60,240);
	Draw_arc(0.333*Size_tail,0.866*Size_tail,-90,180);
	EndFilledRegion();
	
	SetPenColor(Hat_color);
	MovePen(dx+Size_thick/2-Wid,dy+Wid*3);
	StartFilledRegion(1);
	Draw_arc(Size_y/2,Size_y/2,0,70);
	Draw_arc(Wid*2.5,Wid*2.5,-20,360);
	Draw_arc(Size_y/2.2,Size_y/2.2,50,-67);
	Draw_arc(Size_thick/7.5,Size_thick/12,180,180);
	EndFilledRegion();
	SetPenColor("Black");
}
void Go_left(double dx,double dy,double ratio,string Color1,string Color2){
	double Size_thick=0.7*ratio,Size_y=1*ratio,Wid=0.05*ratio;
	double Size_tail=0.15*ratio;
	double Eye_x=0.05*ratio,Eye_y=0.2*ratio;
	SetPenColor(Color2);
	MovePen(dx+Size_thick-Wid*0.88,dy-Size_y+Wid*0.88);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*3,-45,45);
	DrawLine(0,Size_y-Wid*6);
	DrawLine(-Wid*6.5,-Wid*6.5);
	DrawLine(0,-Size_y+Wid*6);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_thick,dy-Wid*3);
	StartFilledRegion(1);
	DrawLine(Wid*5,Wid*5);
	DrawArc(Wid*3,0,90);
	DrawLine(-Wid*5,-Wid*5);
	DrawArc(Wid*3,90,-90);
	EndFilledRegion();
	
	SetPenColor(Color2);
	MovePen(dx+Size_thick-Wid*4.5,dy-Wid*1.5);
	StartFilledRegion(1);
	DrawLine(Wid*6.5,Wid*6.5);
	DrawLine(-Size_thick+Wid*6,0);
	DrawArc(Wid*3,90,45);
	DrawLine(-Wid*5,-Wid*5);
	DrawLine(Size_thick-Wid*7,0);
	EndFilledRegion();
	
	SetPenColor(Color1);
	Filled_rounded_rectangular(dx,dy,Size_thick,Size_y,ratio*0.15);
	SetPenColor("Flesh");
	Filled_rightrounded_rectangular(dx,dy-Size_y/8-Wid,Size_thick/4,Size_y*3/4,Wid*1.5);
	SetPenColor("White");
	DrawLine(0,Size_y*3/4);
	SetPenColor("Black");
	MovePen(dx+Eye_x,dy-Size_y/2);
	StartFilledRegion(1);
	Draw_arc(Eye_x,Eye_y,0,360);
	EndFilledRegion();
	
	SetPenColor(Tail_color);
	MovePen(dx+Size_thick+Wid*3,dy-Size_y+2.866*Size_tail+Wid*3);
	StartFilledRegion(1);
	DrawArc(Size_tail,120,-240);
	Draw_arc(0.333*Size_tail,0.866*Size_tail,-90,-180);
	EndFilledRegion();
	
	SetPenColor(Hat_color);
	MovePen(dx+Size_thick/2+Wid,dy+Wid*3);
	StartFilledRegion(1);
	Draw_arc(Size_y/2,Size_y/2,180,-70);
	Draw_arc(Wid*2.5,Wid*2.5,200,360);
	Draw_arc(Size_y/2.2,Size_y/2.2,130,67);
	Draw_arc(Size_thick/7.5,Size_thick/12,0,-180);
	EndFilledRegion();
	SetPenColor("Black");
}
#endif
