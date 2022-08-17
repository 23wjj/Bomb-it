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


void DrawPath(double x,double y){
	SetPenColor("LightYellow");
	MovePen(x,y);
	StartFilledRegion(1); 
	DrawLine(BlockWidth,0);
	DrawLine(0,BlockWidth);
	DrawLine(-BlockWidth,0);
	DrawLine(0,-BlockWidth);
	EndFilledRegion();
}
void DrawBarrier1(double x,double y,int n){
	char color[6][12]={"DarkOrange","LightOrange","WhiteOrange","DarkGreen","LightGreen","WhiteGreen"};
	
	SetPenColor(color[3*n+0]);	
	MovePen(x,y-BlockWidth/4);	
	StartFilledRegion(1);
	DrawLine(3*BlockWidth/8,BlockWidth/4);
	DrawLine(0,-BlockWidth/2);
	DrawLine(-3*BlockWidth/8,-BlockWidth/4);
	DrawLine(0,BlockWidth/2);
	EndFilledRegion();
    MovePen(x+BlockWidth*5/8,y);
	StartFilledRegion(1);
	DrawLine(3*BlockWidth/8,-BlockWidth/4);
	DrawLine(0,-BlockWidth/2);
	DrawLine(-3*BlockWidth/8,BlockWidth/4);
	DrawLine(0,BlockWidth/2);
	EndFilledRegion();
	
		
	SetPenColor(color[3*n+1]);
	DrawRectangle(x+BlockWidth*3/8,y,BlockWidth/4,BlockWidth/2,1);
	
    SetPenColor(color[3*n+2]);
	MovePen(x,y-BlockWidth*3/4);
	StartFilledRegion(1);
	DrawLine(BlockWidth*3/8,BlockWidth/4);
	DrawLine(BlockWidth/4,0);
	DrawLine(BlockWidth*3/8,-BlockWidth/4);
	DrawLine(0,-BlockWidth/4);
	DrawLine(-BlockWidth,0);
	DrawLine(0,BlockWidth/4);
	EndFilledRegion();
	
	SetPenColor(color[3*n+0]);
	DrawRectangle(x+BlockWidth*3/8,y-BlockWidth*3/4,BlockWidth/4,BlockWidth/4,1);
} 
void DrawBarrier2(double x,double y,int n){
	int i;
	//绘制树木 
	if(n){
		SetPenColor("Brown");
		DrawRectangle(x+BlockWidth*3/8,y-BlockWidth/2,BlockWidth/4,BlockWidth/2,1);
				
		SetPenColor("TreeGreen");
		for(i=0;i<4;i++){
			MovePen(x+BlockWidth*(5-i)/8,y-BlockWidth/8*(1+i));
			StartFilledRegion(1);
			DrawArc(BlockWidth/8,0,360);
			EndFilledRegion();
		}
		for(i=0;i<4;i++){
			MovePen(x+BlockWidth*(6-i)/8,y-BlockWidth/8*(i+2));
			StartFilledRegion(1);
			DrawArc(BlockWidth/8,0,360);
			EndFilledRegion();
		}
		for(i=0;i<3;i++){
			MovePen(x+BlockWidth*(7-i)/8,y-BlockWidth/8*(i+3));
			StartFilledRegion(1);
			DrawArc(BlockWidth/8,0,360);
			EndFilledRegion();
		}
		for(i=0;i<2;i++){
			MovePen(x+BlockWidth*(8-i)/8,y-BlockWidth/8*(i+4));
			StartFilledRegion(1);
			DrawArc(BlockWidth/8,0,360);
			EndFilledRegion();
		}
	}
	//绘制路灯 
	else{
		SetPenColor("Light Gray");
		MovePen(x+BlockWidth,y-BlockWidth*3/4);
		StartFilledRegion(1);
		DrawArc(BlockWidth,60,60);
		DrawArc(BlockWidth,-120,60);
		EndFilledRegion();
		DrawRectangle(x+BlockWidth*7/16,y-BlockWidth/8,BlockWidth/8,BlockWidth*5/8,1);
		SetPenColor("Yellow");
		StartFilledRegion(1);
		MovePen(x+BlockWidth/2,y-BlockWidth/4);
		DrawArc(BlockWidth/2,-30,60);
		DrawArc(BlockWidth/2,150,60);
		EndFilledRegion();
	}
}
void DrawItems(void){
	int i,j;
	int n;
	for(i=0;i<Line;i++)
		for(j=0;j<Row;j++)
			if((n=MapBlock[i][j].Item))
				switch (n){
					case 1:Draw_drink(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 2:Draw_rapid(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 3:Draw_bomb_plus(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 4:Draw_hand(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 5:Draw_frozen(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					default:break;
				}
}
#endif
