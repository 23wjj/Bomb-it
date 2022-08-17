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


void KeepFrozen(int i){
	FrozenP newp=(FrozenP)malloc(sizeof(Frozen));
	newp->nxt=NULL;newp->Character=i,newp->time=10;
	if(frozen_head==NULL) frozen_head=newp;
	else frozen_tail->nxt=newp;
	frozen_tail=newp;
	return;
}
//删除frozen的结点 
void DelFrozen(FrozenP P){
	enemy[P->Character].Frozen=0;
	DrawFrozenSplitBefore(P->Character);
	DrawOnePlayers(P->Character);
	DrawFrozenSplitAfter(P->Character);
	enemy[P->Character].Color1=enemy[P->Character].Gray1;
	enemy[P->Character].Color2=enemy[P->Character].Gray2;
	if(frozen_head==P){
		frozen_head=frozen_head->nxt;
		return;
	}
	FrozenP newp=frozen_head;
	for(;newp!=NULL;newp=newp->nxt)
	if(newp->nxt==P) break;
	if(newp->nxt==frozen_tail) newp=frozen_tail;
	//jzz add an 'else'
	else newp->nxt=newp->nxt->nxt;
}
void DrawFrozenBefore(int i){
	double x,y;
	//画角色之前画 
	x=enemy[i].PositionX;y=enemy[i].PositionY;
	SetPenColor("Aliceblue");
	MovePen(x-0.5,y+0.5);
	StartFilledRegion(1);
	DrawLine(0.2,0.2);
	DrawLine(1.0,0);
	DrawLine(0,-1.0);
	DrawLine(-0.2,-0.2);
	DrawLine(-1.0,0);
	DrawLine(0,1.0);
	EndFilledRegion();
	SetPenColor("Powderblue");
	SetPenSize(3);
	DrawLine(0.2,0.2);
	DrawLine(1.0,0);
	DrawLine(0,-1.0);
	DrawLine(-0.2,-0.2);
	DrawLine(-1.0,0);
	DrawLine(0,1.0);
	DrawLine(1.0,0);
	DrawLine(0.2,0.2);
	DrawLine(-0.2,-0.2);
	DrawLine(0,-1.0);
	SetPenSize(1);
}
void DrawFrozenAfter(int i){
	double x,y;
	x=enemy[i].PositionX;y=enemy[i].PositionY;
		//画角色之后再画 
	SetPenColor("Lightcyan");
	MovePen(x-0.5+0.1,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(0,0.8);
	DrawLine(0.5,-0.8);
	DrawLine(-0.5,0);
	EndFilledRegion();
	MovePen(x-0.5+0.1+0.6,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(-0.5,0.8);
	DrawLine(0.1,0);
	DrawLine(0.5,-0.8);
	DrawLine(-0.1,0);
	EndFilledRegion();
	MovePen(x-0.5+0.1+0.6+0.1,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(0.1,0);
	DrawLine(0,0.8);
	DrawLine(-0.6,0);
	DrawLine(0.5,-0.8);
	EndFilledRegion();
	SetPenSize(1);
}
void DrawFrozenSplitBefore(int i){
		double x,y;
	//画角色之前画 
	x=enemy[i].PositionX;y=enemy[i].PositionY;
	SetPenColor("Aliceblue");
	MovePen(x-0.5,y+0.5);
	StartFilledRegion(1);
	DrawLine(0.2,0.2);
	DrawLine(1.0,0);
	DrawLine(0,-1.0);
	DrawLine(-0.2,-0.2);
	DrawLine(-1.0,0);
	DrawLine(0,1.0);
	EndFilledRegion();
	SetPenColor("Powderblue");
	SetPenSize(3);
	DrawLine(0.2,0.2);
	DrawLine(1.0,0);
	DrawLine(0,-1.0);
	DrawLine(-0.2,-0.2);
	DrawLine(-1.0,0);
	DrawLine(0,1.0);
	DrawLine(1.0,0);
	DrawLine(0.2,0.2);
	DrawLine(-0.2,-0.2);
	DrawLine(0,-1.0);
	SetPenSize(1);
} 
void DrawFrozenSplitAfter(int i){
	double x,y,cx,cy;
	x=enemy[i].PositionX;y=enemy[i].PositionY;
	//画角色之后再画 
	SetPenColor("Lightcyan");
	MovePen(x-0.5+0.1,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(0,0.8);
	DrawLine(0.5,-0.8);
	DrawLine(-0.5,0);
	EndFilledRegion();
	MovePen(x-0.5+0.1+0.6,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(-0.5,0.8);
	DrawLine(0.1,0);
	DrawLine(0.5,-0.8);
	DrawLine(-0.1,0);
	EndFilledRegion();
	MovePen(x-0.5+0.1+0.6+0.1,y-0.5+0.1);
	StartFilledRegion(1);
	DrawLine(0.1,0);
	DrawLine(0,0.8);
	DrawLine(-0.6,0);
	DrawLine(0.5,-0.8);
	EndFilledRegion();
	SetPenSize(1);
	MovePen(x-0.5,y-0.5+0.2);
	SetPenColor("Aliceblue");
	StartFilledRegion(1);
	DrawArc(0.3,90,95);
	DrawArc(1,200,30);
	DrawArc(0.3,270,60); 
	DrawArc(10,270,4);
	DrawArc(0.8,270,50); 
	DrawArc(80,80,0.4);
	cx=GetCurrentX();cy=GetCurrentY();
	DrawLine((x-0.5)-cx,(y-0.5)-cy);
	DrawLine(0,0.2);
	EndFilledRegion();
}
void Draw_allbomb(){
	BombP now=head;
	for(;now!=NULL;now=now->nxt) 
	Draw_bomb(now->x+StateColumnWidth,now->y+1,0.8);
}
void PutBomb(int i,int x,int y){
	BombP now=(BombP)malloc(sizeof_Bomb);
	MapBlock[x][y].BombExist=now;
	now->x=x,now->y=y,now->time=10,now->froze=0;now->BombPower=enemy[i].BombPower;
	now->Character=i;
	if(head==NULL) head=now;
	else tail->nxt=now;
	tail=now;tail->nxt=NULL;
	return;
}
void PreBomb(BombP now){
	int x=now->x,y=now->y,Power=now->BombPower;
	MapBlock[x][y].BombExist=0;
	int i=0,j,step;
	for(step=1;step<=Power;step++)
	for(i=0;i<4;i++){
		int dxx=x+dx[i]*step,dyy=y+dy[i]*step;
		if(dxx>=0&&dxx<Row&&dyy>=0&&dyy<Line){
			MapP T=&MapBlock[dxx][dyy];
			if((T->Type)%2) T->Type=0;
			if(T->Type==0){
				int xx=rand()%20;
				if(xx<=7) T->Item=xx;				
			}
		}
	}
	for(i=0;i<4;i++)if(enemy[i].Blood>0){
		double ex=enemy[i].PositionX-StateColumnWidth;
		double ey=enemy[i].PositionY;
		if(fabs(ex-x)<1+Power&&fabs(ey-y)<1+Power){
			if(enemy[i].Shied==1) enemy[i].Shied=0;
			else enemy[i].Blood-=1;
			if(enemy[i].Blood==0){
				if(i==3) END=1;
				else Go_down(1.2,WindowHeight-(i+1)*0.8-i*1.5-0.3,0.8,"Gray","Dark Gray");
			}
			
		}
	}
}
void DelBomb(BombP T){
	PreBomb(T);
	//add by wjj 6.1
	enemy[T->Character].Bombnum++;
	if(head==T){
		head=head->nxt;
		return;
	}
	BombP now=head;
	for(;now!=NULL;now=now->nxt)
	if(now->nxt==T) break;
	if(now->nxt==tail) now=tail;
	now->nxt=now->nxt->nxt;
}
void GetItems(int i,int j,int k){
	string tmp1,tmp2;
	switch(MapBlock[j][k].Item){
		case 1:
			if(i==3&&enemy[i].BombPower<3) 
				enemy[i].BombPower++; 
			break;
		case 2:
			if(enemy[i].Speed<1)
			enemy[i].Speed+=0.25;
			break;
		case 3:
			if(i==3)
				enemy[i].Bombnum++;
			break;
		case 4:
			if(i==3)
				enemy[i].Glove=1;
			break;
		case 5:{
			enemy[i].Frozen=1;
			tmp1=enemy[i].Color1;tmp2=enemy[i].Color2;
			enemy[i].Gray1=tmp1;enemy[i].Gray2=tmp2;
			enemy[i].Color1="Light Gray";enemy[i].Color2="Dark Gray";
			KeepFrozen(i);
		}
			break;
		case 6:
			if(enemy[i].Blood<4&&enemy[i].Blood>0)
				enemy[i].Blood++;
			break;
		case 7:
			enemy[i].Shied=1;
			break;
		default:
			break;	
	} 
	MapBlock[j][k].Item=0;
	return;
}
void MoveFunction(int i,int move){
	double x,y,tmp;
	int j,k,j1,k1;
	if(enemy[i].Frozen);
	else{
		for(tmp=0.25;tmp<=enemy[i].Speed;tmp+=0.25){
			x=enemy[i].PositionX+dx[move]*0.25-StateColumnWidth;
			y=enemy[i].PositionY+dy[move]*0.25;
			j=x,k=y;
				//i,j整数点时候偏向上、向右取 
			if(x<0.3||y<0||(x>=WindowWidth-StateColumnWidth)||y>=WindowHeight){
				//edit: 修改边界判断 
				int abcd=0;
				return;
			}
			if(!MapBlock[j][k].Type){
				enemy[i].PositionX+=dx[move]*0.25;
				enemy[i].PositionY+=dy[move]*0.25;
				GetItems(i,j,k);//检测是否有道具 
				if(DyeingPattern)
					MapBlock[j][k].Dyeing=i; 
			}
		}
	}
	DrawMap((int)(x-1.5),(int)(x+1.5),(int)(y+1.5),(int)(y-1.5));
	DrawAllPlayers(i);
	//推炸弹的实现 
	BombP now=MapBlock[j][k].BombExist;
	if(now&&enemy[i].Glove){
		if(fabs(j-x)<0.25&&fabs(k-y)<0.25);
		else if(j+dx[move]<0||j+dx[move]>Line||k+dy[move]<0||k+dy[move]>Row);
		else if(MapBlock[j+dx[move]][k+dy[move]].Type);
		else if(MapBlock[j+dx[move]][k+dy[move]].BombExist==0){	
			MapBlock[j+dx[move]][k+dy[move]].BombExist=now;
			MapBlock[j][k].BombExist=0;
			now->x+=dx[move];
			now->y+=dy[move];
			enemy[i].Glove--;
		}
	}
}

void DrawMap(int l,int r,int u,int d){
	int i,j;
	if(l<0) l=0;
	if(d<0) d=0;
	if(r>=Line) r=Line-1;
	if(u>=Row) u=Row-1;
	SetPenColor("LightYellow");
	DrawRectangle(MapBlock[l][u].BlockX,MapBlock[l][u].BlockY,(r-l+1)*BlockWidth,(u-d+1)*BlockWidth,1);
	for(j=d;j<=u;j++)
	    for(i=l;i<=r;i++)
	    if(!MapBlock[i][j].Type)//如果是通道 
		{
			if(MapBlock[i][j].Dyeing>=0){
				SetPenColor(Dyeing_color[MapBlock[i][j].Dyeing]);
				DrawRectangle(MapBlock[i][j].BlockX,MapBlock[i][j].BlockY,1.0,1.0,1);
			}
			if(MapBlock[i][j].BombExist!=0) Draw_bomb(i+StateColumnWidth,j+1,0.8);
			else{
				switch(MapBlock[i][j].Item){
					case 1:Draw_drink    (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 2:Draw_rapid    (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 3:Draw_bomb_plus(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 4:Draw_hand     (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 5:Draw_frozen   (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 6:Draw_heart    (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					case 7:Draw_shied    (1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,0.8);break;
					default:break;
				}
			}
		}
	    else if(!(MapBlock[i][j].Type%2))//如果是固定障碍物 
	    	DrawBarrier1(1.0*MapBlock[i][j].BlockX,1.0*MapBlock[i][j].BlockY,(MapBlock[i][j].Type-1)/2);
		else//如果是可炸障碍物 
			DrawBarrier2(MapBlock[i][j].BlockX,MapBlock[i][j].BlockY,MapBlock[i][j].Type/2);
}
#endif
