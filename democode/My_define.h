#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include "imgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#pragma comment(lib,"Winmm.lib")
/*
 * Constants
 * ---------
 * The following constants control the sizes of the
 * various elements in the display.
 */
 
#define WindowWidth 19.0
#define WindowHeight 13.0
#define Row 13
#define Line 15
#define BlockWidth 1.0
#define StateColumnWidth (WindowWidth-BlockWidth*Line)
#define StateColumnBlockWidth 2.0 
#define StateColumnButtonh 0.5
#define StateColumnButtonHeight 1.0                     
#define StateColumnButtonWidth 2.0
#define NarrowOffset 0.005
#define ButtonColor "Orange"
#define MapWidth (Line*BlockWidth)
#define RATIO 0.5

#define TIMER_BLINK500  1     /*500ms定时器事件标志号*/
#define TIMER_BLINK600 2     /*600ms定时器时间标志号*/
#define TIMER_BLINK100 3     /*100ms定时器时间标志号*/
#define TIMER_BLINK1000 4    /*1000ms定时器时间标志号*/ 


/*
 *  Variables
 * ---------
 * The following variables is widely used by several
 * functions in this program.
 
 *Edit By Jzz:
 *PlayerExist 类型改成人物结构体指针类型，
 *指向当前坐标格子上的人物 ，NULL表示没有敌人 
 */

typedef struct Bomb_List * BombP;
typedef struct Bomb_List Bomb;
typedef struct Frozen_List Frozen;
typedef struct Frozen_List * FrozenP;
struct Bomb_List{
	int x,y;
	double time;
	int tim;
	int froze;
	int BombPower;
	int Character;//标记这个炸弹是谁放置的 ，以便统计角色炸弹数目 
	BombP nxt;
};
typedef struct Map* MapP ;
struct Map{
	int Type;//表示此处方块的类型，0为无障碍，1、3为有可炸障碍，2、4为有固定障碍 
	double BlockX,BlockY;//表示方块左上角的坐标位置 
	struct character* Player;//表示此处方块有无玩家，0表示没有，1表示有
	BombP BombExist;//表示此处方块有无炸弹，0表示没有，否则指向炸弹的地址； 
	int Item;//表示此处的方块的道具类型，0表示无道具，其它数字为道具的种类
			 //1-药水 2-加速 3-蓝色炸弹（增加个数）4-手套 5-雪花 6-生命 7-盾牌 
	int Dyeing;//存放染色的enemy的编号,初值置为-1 
};
struct Map MapBlock[Line][Row];
struct Frozen_List{
	int Character;
	double time;
	FrozenP nxt;
};

struct character{
	int Shied;//表示是否有盾牌护体 
	int Blood;//表示当前血量 
	int direction;//表示面对的方向 0表示东，1表示南，2表示西，3表示北 
	double Speed;//初始值为0.25（即1/4格子） 
	double PositionX,PositionY;//表示格子中轴线的位置坐标 
    int BombPower;//初始值为1
	int Bombnum;//表示可连续放置的炸弹数量，初值为1 
	int Glove;
	int Frozen;//初值为0，遇到道具则置为1 
	string Color1,Color2;
	string Gray1,Gray2;
};

/* Function prototypes */
void KeyboardEventProcess(int key,int event);/*键盘消息回调函数*/
void CharEventProcess(char c);/*字符消息回调函数*/
void MouseEventProcess(int x, int y, int button, int event);/*鼠标消息回调函数*/
void MouseEventProcess_mapeditor(int x, int y, int button, int event);
void TimerEventProcess(int timerID);/*定时器消息回调函数*/

void InitStateColumn(void);//初始化状态栏 
void InitCharacters(void);//初始化角色
void InitMapState(void);//初始化地图
void InitMap(void);//地图有变更时，重新输出地图 
void InitConsole(void);
void OpenFileMap(void);


int PassCheck();
void Draw_allbomb();
void PutBomb(int i,int x,int y);
void PreBomb(BombP T);
void DelBomb(BombP T);
void Enemy_move(int i);
void MoveFunction(int i,int move);//角色移动函数 
void GetItems(int i,int j,int k);//获取道具的函数 
void DisPause();
void DisMusic();
void StartFilledRegion(double density);
void EndFilledRegion(void);

void DrawStateItems(void);
void DrawAllPlayers();
void DrawOnePlayers(int i);
void DrawMap(int l,int r,int u,int d);
void Draw_pause();
void Draw_continue();
void DrawItems(void);
void Draw_gameover(double cx,double cy);
void Draw_gamewin(double cx,double cy);
void Draw_score();

//画人物的函数
void Go_down(double dx,double dy,double ratio,string Color1,string Color2);
void Go_up(double dx,double dy,double ratio,string Color1,string Color2);
void Go_right(double dx,double dy,double ratio,string Color1,string Color2);
void Go_left(double dx,double dy,double ratio,string Color1,string Color2);
//画道具的函数
void Draw_arc(double rx,double ry,double start,double sweep);//画可以被填充的弧线 
void Draw_bomb(double dx,double dy,double ratio);//杀人的炸弹 
void Draw_bomb_plus(double dx,double dy,double ratio);//收集的炸弹 
void Draw_drink(double dx,double dy,double ratio);//药水 
void Draw_rapid(double dx,double dy,double ratio);//加速 
void Draw_frozen(double dx,double dy,double ratio);//冷却 
void Draw_hand(double dx,double dy,double ratio);//推炸弹 
void Draw_heart(double dx,double dy,double ratio);//加生命 
void Draw_shied(double dx,double dy,double ratio);//防护盾  
void Draw_spark(double cx,double cy,double ratio);//爆炸的火花 

void DrawBarrier1(double x,double y,int n);//绘制固定障碍物 
void DrawBarrier2(double x,double y,int n);//绘制可炸障碍物 
void DrawPath(double x,double y);
void DrawTitle(double x,double y);
void Drawdisplay0bomb(double x,double y,double ratio);

void DrawRectangle(double start,double end,double width,double height,bool filled); 
void drawRectangle(double x, double y, double w, double h, int fillflag);
//
void Filled_rounded_rectangular(double x,double y,double a,double b,double r);
void Filled_leftrounded_rectangular(double x,double y,double a,double b,double r);
void Filled_rightrounded_rectangular(double x,double y,double a,double b,double r);


/*菜单处理函数，修改了graphic.c文件从而将displayclear（）改为全局函数*/ 
struct Button{
	double l,r,u,d;
	string Text,color;
}Button[20];

void DisplayClear(void);
void displayclear();
void drawEditText(void);
void display0(void);
void display1(void);
void display2(void);
void Draw_labal(double l,double r,double u,double d,string Text,string color);
void Draw_button(double l,double r,double u,double d,string Text,string color);
void Click_button(struct Button T,double d);
int Check_in_button(double x,double y,struct Button T);
void drawEditText_help();
void display_help();
void display_about();
void display_store();
void drawEditText_about();

void DrawFrozenBefore(int i);
void DrawFrozenAfter(int i);
void DrawFrozenSplitBefore(int i);
void DrawFrozenSplitAfter(int i); 
void KeepFrozen(int i);
void DelFrozen(FrozenP P); 
/*地图编辑器函数*/
static double winwidth, winheight;   // 窗口尺寸
static int Type_Edit;
struct Map_Edit{
	int Type;//表示此处方块的类型，0为无障碍，1、3为有可炸障碍，2、4为有固定障碍 
	double BlockX,BlockY;//表示方块左上角的坐标位置 
	int Selected;
};
struct Map_Edit MapBlock_Edit[Row][Line];
void Initmain_Mapeditor(void);
void InitMap_mapeditor(void);
void InitMapState_mapeditor(void); 
int TestinBox_mapeditor(double x, double y, double x1, double x2, double y1, double y2);
void display_mapeditor(void); 
void drawButtons_mapeditor(void);
void DrawLineAndRow_mapeditor(void); 
void DrawMap_mapeditor(void);
void SaveMap_mapeditor(void);
void CurrentClear();
