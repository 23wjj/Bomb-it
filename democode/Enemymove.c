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

int stackx[100],stacky[100],stacktop;
int dis[20][20],lstx[20][20],lsty[20][20];
void Enemy_move(int i){
	if(enemy[i].Blood==0) return;
	int x=enemy[i].PositionX-StateColumnWidth,y=enemy[i].PositionY;
	int nx,nnx,ny,nny,move,ii,j;
	if(Enemy_track[i][0]){
		move=Enemy_track[i][Enemy_track[i][0]];
		Enemy_track[i][0]--;
		enemy[i].direction=move;
		MoveFunction(i,move); 
		return;
	}
	else if(MapBlock[x][y].BombExist!=NULL){
		int scale=(MapBlock[x][y].BombExist)->BombPower;
		stacktop=1;
		stackx[stacktop]=x;
		stacky[stacktop]=y;
		for(ii=0;ii<Line;ii++)
		for(j=0;j<Row;j++)
		dis[ii][j]=10000;
		dis[x][y]=0;
		int sx=-1,sy=-1;
		while(stacktop){
			nx=stackx[stacktop],ny=stacky[stacktop];stacktop--;
//			if(nx!=x&&ny!=y) break;
			if(abs(nx-x)>scale+1||abs(ny-y)>scale+1){
				if(sx<0||dis[nx][ny]<dis[sx][sy])
					sx=nx,sy=ny;
			}
			else for(j=0;j<4;j++){
				nnx=dx[j]+nx;nny=dy[j]+ny;
				if(nnx<0||nnx>Row||nny<0||nny>Line) continue;
				if(MapBlock[nnx][nny].Type) continue;
				if(dis[nnx][nny]>dis[nx][ny]+1){
					dis[nnx][nny]=dis[nx][ny]+1;
					lstx[nnx][nny]=nx;lsty[nnx][nny]=ny;
					stacktop++;
					stackx[stacktop]=nnx;
					stacky[stacktop]=nny;
				}
			}
		}
		if(sx>=0) nx=sx,ny=sy;
		Enemy_track[i][0]=0;
		while(nx!=x||ny!=y){
			nnx=lstx[nx][ny];nny=lsty[nx][ny];//从nn走向n 
			if(nnx==nx-1){
				Enemy_track[i][++Enemy_track[i][0]]=0;
				Enemy_track[i][++Enemy_track[i][0]]=0;
				Enemy_track[i][++Enemy_track[i][0]]=0;
				Enemy_track[i][++Enemy_track[i][0]]=0;
			}
			else if(nnx==nx+1){
				Enemy_track[i][++Enemy_track[i][0]]=2;
				Enemy_track[i][++Enemy_track[i][0]]=2;
				Enemy_track[i][++Enemy_track[i][0]]=2;
				Enemy_track[i][++Enemy_track[i][0]]=2;
			}
			else if(nny==ny-1){
				Enemy_track[i][++Enemy_track[i][0]]=3;
				Enemy_track[i][++Enemy_track[i][0]]=3;
				Enemy_track[i][++Enemy_track[i][0]]=3;
				Enemy_track[i][++Enemy_track[i][0]]=3;
			}
			else{
				Enemy_track[i][++Enemy_track[i][0]]=1;
				Enemy_track[i][++Enemy_track[i][0]]=1;
				Enemy_track[i][++Enemy_track[i][0]]=1;
				Enemy_track[i][++Enemy_track[i][0]]=1;
			}
			nx=nnx,ny=nny;
		}
	}
	else{
		move=rand()%18;//move 0 东 1 南 2 西 3 北 4 不动+放置炸弹 
		if(move<17){
			move=move/4;
			enemy[i].direction=move;
			MoveFunction(i,move); 
		}
		else if(enemy[i].Bombnum){
			enemy[i].Bombnum--;
			PutBomb(i,(int)(enemy[i].PositionX-StateColumnWidth),(int)enemy[i].PositionY);
		}
	} 
}
#endif
