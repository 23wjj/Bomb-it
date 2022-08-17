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

extern int sizeof_Bomb;
extern BombP head,tail;
extern FrozenP frozen_head,frozen_tail;
extern FILE *fp;
extern int Buttonnum;


FILE *fs_Edit;
void Initmain_Mapeditor(void){
	displayclear();
	InitMap_mapeditor();
    InitMapState_mapeditor();
    winwidth = WindowWidth;
    winheight = WindowHeight;
} 
void InitMap_mapeditor(void){
	int i,j;
	for(i=0;i<Row;i++)
		for(j=0;j<Line;j++){
			MapBlock_Edit[i][j].BlockX=BlockWidth*j+StateColumnWidth;
			MapBlock_Edit[i][j].BlockY=BlockWidth*(i+1);
		}
}
void InitMapState_mapeditor(void){
	int i,j;
	for(i=0;i<Row;i++)
		for(j=0;j<Line;j++){
			MapBlock_Edit[i][j].Type=0; 
			MapBlock_Edit[i][j].Selected=0;
		}
}
// 按钮
void drawButtons_mapeditor(){
	double h = StateColumnButtonHeight;  // 控件高度
	double x = 1.0;
	double y = winheight-0.5; 
	double w = StateColumnButtonWidth; // 控件宽度
	char *names[8]={"OrangeHouse","GreenHouse","Lamp","Tree","clear","Street","Save","Back"};
	int k=1;
    for(k=1;k<9;k++)
    	if(button(GenUIID(k-1),x,y-(k-1)*(h+StateColumnButtonh)-h,w,h,names[k-1]))
			Type_Edit=k;		
}
void display_mapeditor(){
	// 清屏
	DisplayClear();		
	// 按钮
	drawButtons_mapeditor();
	SetPenColor("LightYellow");
	drawRectangle(StateColumnWidth,0,MapWidth,WindowHeight,1);
	DrawLineAndRow_mapeditor();
	if(Type_Edit==5)
		InitMapState_mapeditor();	
	else if(Type_Edit==8){
		count=2;
		DisplayClear();
		display2();
	}
	else if(Type_Edit==7)
		SaveMap_mapeditor();
	else
		DrawMap_mapeditor(); 
	Type_Edit=0;	
}
void DrawLineAndRow_mapeditor(void){
	int i;
	MovePen(4.0,0);
	SetPenColor("Black");
	for(i=0;i<=Row;i++){
		DrawLine(MapWidth,0);
		MovePen(StateColumnWidth,(i+1)*BlockWidth);
	}
	MovePen(4.0,0);
	for(i=0;i<=Line;i++){
		DrawLine(0,WindowHeight);
		MovePen(StateColumnWidth+(i+1)*BlockWidth,0);
	}
}
void DrawMap_mapeditor(void){
	int i,j;
	for(i=0;i<Row;i++){
		for(j=0;j<Line;j++){
			if(MapBlock_Edit[i][j].Selected&&!Type_Edit){
				SetPenColor("Blue");
				DrawRectangle(MapBlock_Edit[i][j].BlockX,MapBlock_Edit[i][j].BlockY,BlockWidth,BlockWidth,1);
			}
			else if(MapBlock_Edit[i][j].Selected&&Type_Edit){
				if(Type_Edit<3){
					DrawBarrier1(MapBlock_Edit[i][j].BlockX,MapBlock_Edit[i][j].BlockY,Type_Edit-1);
					MapBlock_Edit[i][j].Type=2*Type_Edit;//1->2是橙房子，2->4是绿房子 
					MapBlock_Edit[i][j].Selected=0;
				}
				else if(Type_Edit<5){
					DrawBarrier2(MapBlock_Edit[i][j].BlockX,MapBlock_Edit[i][j].BlockY,Type_Edit-3);
					MapBlock_Edit[i][j].Type=2*Type_Edit-5;//3->1,是路灯，4->3，是树木 
					MapBlock_Edit[i][j].Selected=0;
				}
				else if(Type_Edit==6){
					SetPenColor("LightYellow");
					DrawPath(MapBlock_Edit[i][j].BlockX,MapBlock_Edit[i][j].BlockY);
					MapBlock_Edit[i][j].Type=0;
					MapBlock_Edit[i][j].Selected=0;
				}
			}
			else if(!MapBlock_Edit[i][j].Selected){
				if(!MapBlock_Edit[i][j].Type);	
	    		else if(!(MapBlock_Edit[i][j].Type%2))//如果是固定障碍物 
	    			DrawBarrier1(1.0*MapBlock_Edit[i][j].BlockX,1.0*MapBlock_Edit[i][j].BlockY,(MapBlock_Edit[i][j].Type-1)/2);
				else//如果是可炸障碍物 
					DrawBarrier2(MapBlock_Edit[i][j].BlockX,MapBlock_Edit[i][j].BlockY,MapBlock_Edit[i][j].Type/2);
			}
		}
	}
}
int TestinBox_mapeditor(double x, double y, double x1, double x2, double y1, double y2){
	return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
void SaveMap_mapeditor(void){
	if((fs_Edit=fopen("map.txt","w"))==NULL){
		InitConsole();
		printf("File open error!\n");
		exit(0);
	}
	int i,j;
	for(i=Row-1;i>=0;i--){
		for(j=0;j<Line;j++){
				fprintf(fs_Edit,"%c",MapBlock_Edit[i][j].Type+'0');	
		}
		fprintf(fs_Edit,"\n");
	}
	if(fclose(fs_Edit)){
		InitConsole();
		printf("Can not close the file!\n");
		exit(0);
	}
}
#endif
