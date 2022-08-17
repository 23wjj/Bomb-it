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


void DrawRectangle(double start,double end,double width,double height,bool filled){
	MovePen(start,end);
	if(filled){
		StartFilledRegion(1);
		DrawLine(width,0);
		DrawLine(0,-height);
		DrawLine(-width,0);
		DrawLine(0,height);
		EndFilledRegion(); 
	}
	else{
		DrawLine(width,0);
		DrawLine(0,-height);
		DrawLine(-width,0);
		DrawLine(0,height);
	}	 
}
double rad(double x){return x*3.1415926535/180;}
void Draw_arc(double rx,double ry,double start,double sweep){
	double x=GetCurrentX()-rx*cos(rad(start));
	double y=GetCurrentY()-ry*sin(rad(start));
	double mint = rad(start);
    double maxt = rad(start + sweep);
	double ix0 = x+rx*cos(mint), ix1;
    double iy0 = x+ry*sin(mint), iy1;
	double dt = rad(1),t;
    if(sweep>0){
	    for (t = mint + dt; t < maxt; t += dt) {
	        ix1 = x+rx * cos(t);
	        iy1 = x+ry * sin(t);
	        DrawLine(ix1-ix0,iy1-iy0);
	        ix0 = ix1;
	        iy0 = iy1;
	    }
	}else{
	    for (t = mint - dt; t > maxt; t -= dt) {
	        ix1 = x+rx * cos(t);
	        iy1 = x+ry * sin(t);
	        DrawLine(ix1-ix0,iy1-iy0);
	        ix0 = ix1;
	        iy0 = iy1;
	    }
	}
}
void Filled_rounded_rectangular(double x,double y,double a,double b,double r){
	MovePen(x+r,y);
	StartFilledRegion(1);
	Draw_arc(r,r,90,90);
	DrawLine(0,-b+2*r);
	Draw_arc(r,r,180,90);
	DrawLine(a-2*r,0);
	Draw_arc(r,r,270,90);
	DrawLine(0,b-2*r);
	Draw_arc(r,r,0,90);
	DrawLine(-a+2*r,0);
	EndFilledRegion();
}
void Filled_leftrounded_rectangular(double x,double y,double a,double b,double r){
	MovePen(x+r,y);
	StartFilledRegion(1);
	Draw_arc(r,r,90,90);
	DrawLine(0,-b+2*r);
	Draw_arc(r,r,180,90);
	DrawLine(a-r,0);
	DrawLine(0,b);
	DrawLine(-a+r,0);
	EndFilledRegion();
}
void Filled_rightrounded_rectangular(double x,double y,double a,double b,double r){
	MovePen(x,y);
	StartFilledRegion(1);
	DrawLine(0,-b+r);
	DrawLine(a-r,0);
	Draw_arc(r,r,270,90);
	DrawLine(0,b-2*r);
	Draw_arc(r,r,0,90);
	DrawLine(-a+r,0);
	EndFilledRegion();
}
void displayclear(){
	SetPenColor("LightYellow");
	DrawRectangle(0,WindowHeight,WindowWidth,WindowHeight,1); 
	double i=0,j=0;
	SetPenColor("BombOrange");
	for(i=0;i<=WindowWidth-1;i++)
		for(j=0;j<=WindowHeight-1;j++)
			Drawdisplay0bomb(i,j,1.0);
}
void Draw_button(double l,double r,double u,double d,string Text,string color){
	SetPenColor("LightYellow");
	DrawRectangle(l, u, r-l, u-d+0.2,1);
	double a=TextStringWidth(Text);
	SetPenColor(color);
	Filled_rounded_rectangular(l, u, r-l, u-d,0.2);
	MovePen((l+r)/2-a/2, (u+d)/2-0.1);
	SetPenColor("White");
	DrawTextString(Text);
		Button[Buttonnum].r=r;
		Button[Buttonnum].l=l;
		Button[Buttonnum].u=u;
		Button[Buttonnum].d=d; 
		Button[Buttonnum].Text=Text;
		Button[Buttonnum].color=color;
		Buttonnum++;
}
void Click_button(struct Button T,double d){
	double a=TextStringWidth(T.Text);
	SetPenColor("LightYellow");
	DrawRectangle(T.l-0.1, T.u+0.05, T.r-T.l+0.2, T.u-T.d+0.2,1);
	SetPenColor(T.color);
	Filled_rounded_rectangular(T.l, T.u-d, T.r-T.l, T.u-T.d,0.2);
	MovePen((T.l+T.r)/2-a/2, (T.u+T.d)/2-0.1-d);
	SetPenColor("White");
	DrawTextString(T.Text);
}
int Check_in_button(double x,double y,struct Button T){
	if(x>=T.l&&x<=T.r&&y>=T.d&&y<=T.u) return 1;
	return 0;
}
void Draw_labal(double l,double r,double u,double d,string Text,string color){
	double a=TextStringWidth(Text);
	SetPenColor(color);
	Filled_rounded_rectangular(l, u, r-l, u-d,0.2);
	MovePen((l+r)/2-a/2, (u+d)/2-0.1);
	SetPenColor("White");
	DrawTextString(Text);
}
void CurrentClear(){ 
	textx[textID] = GetCurrentX();
	texty[textID] = GetCurrentY();
	SetEraseMode(TRUE);
	MovePen(textx[textID]-NarrowOffset,texty[textID]);/*将笔触移到夹缝处*/
	DrawLine(0,0.3);/*删掉光标线*/ 
	MovePen(textx[textID],texty[textID]);/*将笔触移回字符书写位置*/
	SetEraseMode(FALSE);
}
int PassCheck(){
	if(textlen[0]==0) return 0;
	int x1=0,x2=0,i;
	for(i=0;i<textlen[1];i++) 
	x1=x1*10+text[1][i]-'0';
	for(i=0;i<textlen[0];i++) 
	x2+=text[0][i]%10;
	return (x1==x2);
}
#endif
