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


void Draw_bomb(double dx,double dy,double ratio){
	SetPenColor("Black");
	double r=0.3*ratio,Wid=0.03*ratio;
	dy-=r*1.2;dx+=r/3*2;
	//顶部方口 
	SetPenColor("Black");
	MovePen(dx+r,dy);
	StartFilledRegion(1);
	DrawLine(Wid*3,0);
	DrawLine(0,Wid);
	DrawLine(-Wid*6,0);
	DrawLine(0,-Wid);
	EndFilledRegion();
	//炸弹主体 
	SetPenColor("Dark Gray");
	MovePen(dx,dy-r);
	StartFilledRegion(1);
	Draw_arc(r,r,180,360);
	EndFilledRegion();
	//周遭深色 
	SetPenColor("Black");
	MovePen(dx+r+0.866*r,dy-r-0.5*r);
	StartFilledRegion(1);
	Draw_arc(r,r,-30,360);
	Draw_arc(r*0.92,r*0.9,-30,360);
	EndFilledRegion();
	//大块亮斑 
	SetPenColor("Light Gray");
	MovePen(dx+r*2-Wid*1.5,dy-r);
	StartFilledRegion(1);
	Draw_arc(r-Wid/2,r-Wid/2,0,-60);
	Draw_arc(Wid/2,Wid/2,-60,-180);
	Draw_arc(r-Wid*1.5,r-Wid*1.5,-60,60);
	Draw_arc(Wid/2,Wid/2,180,-180);
	EndFilledRegion();
	//小块亮斑 
	SetPenColor("White");
	MovePen(dx+r*2-Wid*2.5,dy-r+Wid*1.5);
	StartFilledRegion(1);
	Draw_arc(Wid/2,Wid/2,-90,360);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(dx+r,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	SetPenColor("Dark Gray");
	MovePen(dx+r+Wid/4,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	MovePen(dx+r+Wid/2,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	MovePen(dx+r+Wid/4*3,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	SetPenColor("Yellow");
	StartFilledRegion(1);
	Draw_arc(Wid,Wid,220,360);
	EndFilledRegion();
	SetPenColor("Orange");
	StartFilledRegion(1);
	DrawArc(Wid*0.5,220,360);
	EndFilledRegion();
	SetPenColor("Black");	
}
void Draw_spark(double cx,double cy,double ratio){
	double a=0.1*ratio;
	MovePen(cx+a*0.5,cy+ratio*0.46);
	SetPenColor("Orange");
	StartFilledRegion(1);
	DrawLine(a*0.05,-a*2.6);
	DrawLine(a*1.2,a*1.5);
	DrawLine(-0.4*a,-a*1.9);
	DrawLine(a*3,a*2);
	DrawLine(-a*2.4,-a*3.1);
	DrawLine(a*1.9,-a*0.7);
	DrawLine(-a*2,-a*0.4);
	DrawLine(a*2.5,-a*2.6);
	DrawLine(-a*3.3,a*1.3);
	DrawLine(a*0.2,-a*1.8);
	DrawLine(-a*1.2,a*1.7);
	DrawLine(-a*0.3,-a*1.6);
	DrawLine(-a*0.5,a*1.6);
	DrawLine(-a*1.3,-a*2.9);
	DrawLine(a*0.1,a*3.4);
	DrawLine(-a*2,a*0.5);
	DrawLine(a*1.9,a*0.3);
	DrawLine(-a*2.3,a*1.3);
	DrawLine(a*2.3,a*0.1);
	DrawLine(-a*2.6,a*2.9);
	DrawLine(a*2.8,-a*1.8);
	DrawLine(a*0.1,a*2.4);
	DrawLine(a*1.1,-a*2.2);
	DrawLine(a*1,a*2.8);
	EndFilledRegion();
	MovePen(cx,cy+a*1.2);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawLine(a*2.5,a*3);
	DrawLine(-a*1.3,-a*3.4);
	DrawLine(a*3.6,a*0.7);
	DrawLine(-a*3.7,-a*2.2);
	DrawLine(a*3.3,-a*0.8);
	DrawLine(-a*3.2,-a*0.7);
	DrawLine(a*0.1,-a*2.2);
	DrawLine(-a*1.4,a*3.1);
	DrawLine(-a*2.7,-a*3.1);
	DrawLine(a*1.5,a*3.5);
	DrawLine(-a*2.4,-a*0.5);
	DrawLine(a*2,a*1.2);
	DrawLine(-a*2.1,a*2.4);
	DrawLine(a*2.9,-a*1.5);
	DrawLine(-a*0.3,a*3.6);
	DrawLine(a*1.3,-a*3.5);
	EndFilledRegion();
	SetPenColor("Yellow");
	MovePen(cx-a,cy);
	StartFilledRegion(1);
	Draw_arc(a*1.04,a*0.96,-110,-230);
	Draw_arc(a*1.44,a*0.96,110,-200);
	Draw_arc(a*1.12,a*0.88,10,-300);
	EndFilledRegion();
	SetPenColor("Black");
}
void Draw_bomb_plus(double dx,double dy,double ratio){
	double r=0.3*ratio,Wid=0.03*ratio;
	dy-=r*1.2;dx+=r/3*2;
	//顶部方口 
	SetPenColor("SteelBlue2");
	MovePen(dx+r,dy);
	StartFilledRegion(1);
	DrawLine(Wid*3,0);
	DrawLine(0,Wid);
	DrawLine(-Wid*6,0);
	DrawLine(0,-Wid);
	EndFilledRegion();
	//炸弹主体 
	SetPenColor("SteelBlue");
	MovePen(dx,dy-r);
	StartFilledRegion(1);
	Draw_arc(r,r,180,360);
	EndFilledRegion();
	//周遭深色 
	SetPenColor("SteelBlue2");
	MovePen(dx+r+0.866*r,dy-r-0.5*r);
	StartFilledRegion(1);
	Draw_arc(r,r,-30,360);
	Draw_arc(r*0.92,r*0.9,-30,360);
	EndFilledRegion();
	//大块亮斑 
	SetPenColor("Light Gray");
	MovePen(dx+r*2-Wid*1.5,dy-r);
	StartFilledRegion(1);
	Draw_arc(r-Wid/2,r-Wid/2,0,-60);
	Draw_arc(Wid/2,Wid/2,-60,-180);
	Draw_arc(r-Wid*1.5,r-Wid*1.5,-60,60);
	Draw_arc(Wid/2,Wid/2,180,-180);
	EndFilledRegion();
	//小块亮斑 
	SetPenColor("White");
	MovePen(dx+r*2-Wid*2.5,dy-r+Wid*1.5);
	StartFilledRegion(1);
	Draw_arc(Wid/2,Wid/2,-90,360);
	EndFilledRegion();
	SetPenColor("SteelBlue");
	MovePen(dx+r,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	SetPenColor("SteelBlue2");
	MovePen(dx+r+Wid/4,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	MovePen(dx+r+Wid/2,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	MovePen(dx+r+Wid/4*3,dy+Wid);
	Draw_arc(r*2,r,180,-50);
	SetPenColor("Black");
	
}

void Draw_drink(double dx,double dy,double ratio){
	double a=ratio*0.1;
	//紫色药水顶面 
	SetPenColor("Purple");
	MovePen(dx+a*3,dy-a*7);
	StartFilledRegion(1);
	Draw_arc(a*2,a,-180,360);
	EndFilledRegion();
	//药水侧面 
	SetPenColor("Purple2");
	MovePen(dx+a*3,dy-a*7);
	StartFilledRegion(1);
	Draw_arc(a*2,a,-180,180);
	DrawLine(a,-a*2);
	DrawLine(-6*a,0);
	DrawLine(a,a*2);
	EndFilledRegion();
	//药水小泡 
	SetPenColor("Purple1");
	MovePen(dx+a*3.6,dy-a*8);
	StartFilledRegion(1);
	Draw_arc(a/3,a/3,-180,180);
	EndFilledRegion();
	MovePen(dx+a*3,dy-a*8.5);
	StartFilledRegion(1);
	Draw_arc(a/4,a/4,-180,180);
	EndFilledRegion();
	//瓶子 
	SetPenSize((int)(3*ratio));
	SetPenColor("SteelBlue1");
	MovePen(dx+a*1.3,dy-a*9.35);
	DrawLine(a*7.4,0);
	DrawLine(-a*2.2,a*4.4);
	DrawLine(0,a*1.5);
	Draw_arc(a*1.8,a*0.8,-30,360);
	DrawLine(0,a*0.5);
	Draw_arc(a*1.8,a*0.8,-30,360);
	MovePen(dx+a*1.3,dy-a*9.35);
	DrawLine(a*2.2,a*4.4);
	DrawLine(0,a*1.5);
	DrawLine(0,-a/3);
	DrawLine(a*0.5,0);
	DrawLine(0,-a*1.2);
	DrawLine(0,a*1.2);
	DrawLine(a*0.5,0);
	DrawLine(0,-a*0.8);
	DrawLine(0,a*0.8);
	SetPenSize(1);
	SetPenColor("Black");
}

void Draw_rapid(double dx,double dy,double ratio){
	double a=0.1*ratio;	
	SetPenColor("Orange");
	MovePen(dx+a*9.5,dy-a*5);
	StartFilledRegion(1);
	Draw_arc(a,a,0,-45);
	DrawLine(-a*3.2,-a*3.2);
	Draw_arc(a/2,a/2,-45,-135);
	DrawLine(0,a);
	Draw_arc(a/2,a/2,180,-45);
	DrawLine(a*1.5,a*1.5);
	Draw_arc(a*0.8,a*0.8,-60,120);
	DrawLine(-a*1.5,a*1.5);
	Draw_arc(a/2,a/2,0,45);
	DrawLine(0,a);
	Draw_arc(a/2,a/2,180,-135);
	DrawLine(a*3.2,-a*3.2);
	Draw_arc(a,a,45,-45);
	EndFilledRegion();	
	MovePen(dx+a*5.5,dy-a*5);
	StartFilledRegion(1);
	Draw_arc(a,a,0,-45);
	DrawLine(-a*3.2,-a*3.2);
	Draw_arc(a/2,a/2,-45,-135);
	DrawLine(0,a);
	Draw_arc(a/2,a/2,180,-45);
	DrawLine(a*1.5,a*1.5);
	Draw_arc(a*0.8,a*0.8,-60,120);
	DrawLine(-a*1.5,a*1.5);
	Draw_arc(a/2,a/2,0,45);
	DrawLine(0,a);
	Draw_arc(a/2,a/2,180,-135);
	DrawLine(a*3.2,-a*3.2);
	Draw_arc(a,a,45,-45);
	EndFilledRegion();
	SetPenColor("Black");
}

void Draw_frozen(double dx,double dy,double ratio){
	double a=0.3*ratio,theta,beta;	
	SetPenSize((int)(2.5*ratio));
	SetPenColor("SteelBlue2");
	MovePen(dx+a*1.5,dy-a*2.2);
	for(theta=0;theta<=6.2831852;theta+=3.1415926/3){
		DrawLine(a/2*cos(theta),a/2*sin(theta));
		for(beta=-3.1415926/4;beta<=3.1415926/4;beta+=3.1415926/4)
		DrawLine(a/2*cos(theta+beta),a/2*sin(theta+beta)),
		DrawLine(-a/2*cos(theta+beta),-a/2*sin(theta+beta));
		DrawLine(-a/2*cos(theta),-a/2*sin(theta));
	}
	SetPenColor("SteelBlue");
	MovePen(dx+a*2.2,dy-a*1.5);
	for(theta=0;theta<=6.2831852;theta+=3.1415926/3){
		DrawLine(a/2*cos(theta),a/2*sin(theta));
		for(beta=-3.1415926/4;beta<=3.1415926/4;beta+=3.1415926/4)
		DrawLine(a/2*cos(theta+beta),a/2*sin(theta+beta)),
		DrawLine(-a/2*cos(theta+beta),-a/2*sin(theta+beta));
		DrawLine(-a/2*cos(theta),-a/2*sin(theta));
	}
	SetPenSize(1);
	SetPenColor("Black");
}

void Draw_hand(double dx,double dy,double ratio){
	double a=0.1*ratio/3;	
	SetPenColor("Gray");
	MovePen(dx+a*3.5,dy-a*14.5);
	StartFilledRegion(1);
	Draw_arc(a*4,a*6,110,-65);
	DrawLine(a*2,-a*0.85);
	DrawLine(a,a*2.2);
	DrawLine(-a*2.8,a*10);
	Draw_arc(a,a,180,-90);
	Draw_arc(a*2,a*3,90,-20);
	DrawLine(a*3,-a*9);
	DrawLine(a,0);
	DrawLine(0,a*10);
	Draw_arc(a*1.1,a*0.8,170,-160);
	DrawLine(0,-a*10);
	DrawLine(a,-a*0.3);
	DrawLine(a*3,a*8.5);
	Draw_arc(a*2,a*3,110,-20);
	Draw_arc(a,a,90,-100);
	DrawLine(-a*2.9,-a*8.3);
	DrawLine(a*0.9,-a*0.4);
	DrawLine(a*4,a*6);
	Draw_arc(a*1.2,a*0.8,120,-40);
	Draw_arc(a*1.5,a*1.5,40,-60);
	DrawLine(-a*4,-a*6);
	DrawLine(a*0.3,-a*2);
	Draw_arc(a*4,a*7,-10,-60);
	DrawLine(0,-a);
	Draw_arc(a*3.3,a*1,-10,-160);
	DrawLine(0,a*1.5);
	DrawLine(-a*3.5,a*3);
	DrawLine(-a*2.5,a*3.3);
	DrawLine(-a*2.8,a*1.8);
	EndFilledRegion();
	SetPenColor("Black");
	MovePen(dx+a*3.5,dy-a*14.5);
	Draw_arc(a*4,a*6,110,-65);
	DrawLine(a*2,-a*0.85);
	DrawLine(a,a*2.2);
	DrawLine(-a*2.8,a*10);
	Draw_arc(a,a,180,-90);
	Draw_arc(a*2,a*3,90,-20);
	DrawLine(a*3,-a*9);
	DrawLine(a,0);
	DrawLine(0,a*10);
	Draw_arc(a*1.1,a*0.8,170,-160);
	DrawLine(0,-a*10);
	DrawLine(a,-a*0.3);
	DrawLine(a*3,a*8.5);
	Draw_arc(a*2,a*3,110,-20);
	Draw_arc(a,a,90,-100);
	DrawLine(-a*2.9,-a*8.3);
	DrawLine(a*0.9,-a*0.4);
	DrawLine(a*4,a*6);
	Draw_arc(a*1.2,a*0.8,120,-40);
	Draw_arc(a*1.5,a*1.5,40,-60);
	DrawLine(-a*4,-a*6);
	DrawLine(a*0.3,-a*2);
	Draw_arc(a*4,a*7,-10,-60);
	DrawLine(0,-a);
	Draw_arc(a*3.3,a*1,-10,-160);
	DrawLine(0,a*1.5);
	DrawLine(-a*3.5,a*3);
	DrawLine(-a*2.5,a*3.3);
	DrawLine(-a*2.8,a*1.8);
	MovePen(dx+a*13.5,dy-a*22);
	DrawLine(-a*1.3,a*6);
	MovePen(dx+a*15,dy-a*21.5);
	DrawLine(-a*0.3,a*6);
	MovePen(dx+a*16.5,dy-a*22);
	DrawLine(a*1,a*6);
}

void Draw_heart(double dx,double dy,double ratio){
	double a=0.25*ratio;	
	SetPenColor("Red");
	MovePen(dx+a*2,dy-a*3.5);
	StartFilledRegion(1);
	DrawLine(a*1.4,a*1.1);
	Draw_arc(a,a,-45,180);
	Draw_arc(a,a,45,180);
	DrawLine(a*1.4,-a*1.1);
	EndFilledRegion();
	SetPenColor("Black");
}
void Draw_shied(double dx,double dy,double ratio){
	double a=0.15*ratio;	
	SetPenColor("Gold");
	MovePen(dx+a*2.5,dy-a*1.5);
	StartFilledRegion(1);
	Draw_arc(a*10,a*10,100,-20);
	Draw_arc(a*3,a*3,200,40);
	Draw_arc(a*4.5,a*12,-40,-45);
	Draw_arc(a*4.5,a*12,265,-45);
	Draw_arc(a*3,a*3,-60,40);
	EndFilledRegion();
	SetPenColor("Turquoise");
	MovePen(dx+a*3.9,dy-a*2.5);
	StartFilledRegion(1);
	DrawLine(0,-a*1.8);
	DrawLine(-a,0); 
	Draw_arc(a*3,a*8,232,-12);
	Draw_arc(a*1.5,a*1.5,-60,40);
	Draw_arc(a*6,a*6,97,-7);	
	EndFilledRegion();
	
	MovePen(dx+a*4.6,dy-a*5);
	StartFilledRegion(1);
	DrawLine(0,-a);
	Draw_arc(a*2,a*5.3,-85,30);
	DrawLine(-a,0);	
	EndFilledRegion();
	
	SetPenColor("DeepSkyBlue");
	MovePen(dx+a*3.9,dy-a*5);
	StartFilledRegion(1);
	DrawLine(0,-a);
	Draw_arc(a*2,a*5.3,265,-30);
	DrawLine(a,0);	
	EndFilledRegion();
	
	MovePen(dx+a*4.6,dy-a*2.5);
	StartFilledRegion(1);
	DrawLine(0,-a*1.8);
	DrawLine(a,0); 
	Draw_arc(a*3,a*8,-52,12);
	Draw_arc(a*1.5,a*1.5,240,-40);
	Draw_arc(a*6,a*6,83,7);	
	EndFilledRegion();
	
	a=0.125*ratio;
	SetPenColor("GoldEnrod");
	MovePen(dx+a*5.05,dy-a*3);
	DrawLine(0,-a*4);
	MovePen(dx+a*3.4,dy-a*5.5);
	DrawLine(a*3.5,0);
	SetPenSize(2); 
	MovePen(dx+a*3.33,dy-a*2.3);
	Draw_arc(a*10,a*10,100,-20);
	Draw_arc(a*3,a*3,200,40);
	Draw_arc(a*4.5,a*12,-40,-45);
	Draw_arc(a*4.5,a*12,265,-45);
	Draw_arc(a*3,a*3,-60,40);
	SetPenColor("Black");
	SetPenSize(1); 
}
#endif
