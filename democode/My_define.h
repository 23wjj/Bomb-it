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

#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
#define TIMER_BLINK600 2     /*600ms��ʱ��ʱ���־��*/
#define TIMER_BLINK100 3     /*100ms��ʱ��ʱ���־��*/
#define TIMER_BLINK1000 4    /*1000ms��ʱ��ʱ���־��*/ 


/*
 *  Variables
 * ---------
 * The following variables is widely used by several
 * functions in this program.
 
 *Edit By Jzz:
 *PlayerExist ���͸ĳ�����ṹ��ָ�����ͣ�
 *ָ��ǰ��������ϵ����� ��NULL��ʾû�е��� 
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
	int Character;//������ը����˭���õ� ���Ա�ͳ�ƽ�ɫը����Ŀ 
	BombP nxt;
};
typedef struct Map* MapP ;
struct Map{
	int Type;//��ʾ�˴���������ͣ�0Ϊ���ϰ���1��3Ϊ�п�ը�ϰ���2��4Ϊ�й̶��ϰ� 
	double BlockX,BlockY;//��ʾ�������Ͻǵ�����λ�� 
	struct character* Player;//��ʾ�˴�����������ң�0��ʾû�У�1��ʾ��
	BombP BombExist;//��ʾ�˴���������ը����0��ʾû�У�����ָ��ը���ĵ�ַ�� 
	int Item;//��ʾ�˴��ķ���ĵ������ͣ�0��ʾ�޵��ߣ���������Ϊ���ߵ�����
			 //1-ҩˮ 2-���� 3-��ɫը�������Ӹ�����4-���� 5-ѩ�� 6-���� 7-���� 
	int Dyeing;//���Ⱦɫ��enemy�ı��,��ֵ��Ϊ-1 
};
struct Map MapBlock[Line][Row];
struct Frozen_List{
	int Character;
	double time;
	FrozenP nxt;
};

struct character{
	int Shied;//��ʾ�Ƿ��ж��ƻ��� 
	int Blood;//��ʾ��ǰѪ�� 
	int direction;//��ʾ��Եķ��� 0��ʾ����1��ʾ�ϣ�2��ʾ����3��ʾ�� 
	double Speed;//��ʼֵΪ0.25����1/4���ӣ� 
	double PositionX,PositionY;//��ʾ���������ߵ�λ������ 
    int BombPower;//��ʼֵΪ1
	int Bombnum;//��ʾ���������õ�ը����������ֵΪ1 
	int Glove;
	int Frozen;//��ֵΪ0��������������Ϊ1 
	string Color1,Color2;
	string Gray1,Gray2;
};

/* Function prototypes */
void KeyboardEventProcess(int key,int event);/*������Ϣ�ص�����*/
void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void MouseEventProcess_mapeditor(int x, int y, int button, int event);
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/

void InitStateColumn(void);//��ʼ��״̬�� 
void InitCharacters(void);//��ʼ����ɫ
void InitMapState(void);//��ʼ����ͼ
void InitMap(void);//��ͼ�б��ʱ�����������ͼ 
void InitConsole(void);
void OpenFileMap(void);


int PassCheck();
void Draw_allbomb();
void PutBomb(int i,int x,int y);
void PreBomb(BombP T);
void DelBomb(BombP T);
void Enemy_move(int i);
void MoveFunction(int i,int move);//��ɫ�ƶ����� 
void GetItems(int i,int j,int k);//��ȡ���ߵĺ��� 
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

//������ĺ���
void Go_down(double dx,double dy,double ratio,string Color1,string Color2);
void Go_up(double dx,double dy,double ratio,string Color1,string Color2);
void Go_right(double dx,double dy,double ratio,string Color1,string Color2);
void Go_left(double dx,double dy,double ratio,string Color1,string Color2);
//�����ߵĺ���
void Draw_arc(double rx,double ry,double start,double sweep);//�����Ա����Ļ��� 
void Draw_bomb(double dx,double dy,double ratio);//ɱ�˵�ը�� 
void Draw_bomb_plus(double dx,double dy,double ratio);//�ռ���ը�� 
void Draw_drink(double dx,double dy,double ratio);//ҩˮ 
void Draw_rapid(double dx,double dy,double ratio);//���� 
void Draw_frozen(double dx,double dy,double ratio);//��ȴ 
void Draw_hand(double dx,double dy,double ratio);//��ը�� 
void Draw_heart(double dx,double dy,double ratio);//������ 
void Draw_shied(double dx,double dy,double ratio);//������  
void Draw_spark(double cx,double cy,double ratio);//��ը�Ļ� 

void DrawBarrier1(double x,double y,int n);//���ƹ̶��ϰ��� 
void DrawBarrier2(double x,double y,int n);//���ƿ�ը�ϰ��� 
void DrawPath(double x,double y);
void DrawTitle(double x,double y);
void Drawdisplay0bomb(double x,double y,double ratio);

void DrawRectangle(double start,double end,double width,double height,bool filled); 
void drawRectangle(double x, double y, double w, double h, int fillflag);
//
void Filled_rounded_rectangular(double x,double y,double a,double b,double r);
void Filled_leftrounded_rectangular(double x,double y,double a,double b,double r);
void Filled_rightrounded_rectangular(double x,double y,double a,double b,double r);


/*�˵����������޸���graphic.c�ļ��Ӷ���displayclear������Ϊȫ�ֺ���*/ 
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
/*��ͼ�༭������*/
static double winwidth, winheight;   // ���ڳߴ�
static int Type_Edit;
struct Map_Edit{
	int Type;//��ʾ�˴���������ͣ�0Ϊ���ϰ���1��3Ϊ�п�ը�ϰ���2��4Ϊ�й̶��ϰ� 
	double BlockX,BlockY;//��ʾ�������Ͻǵ�����λ�� 
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
