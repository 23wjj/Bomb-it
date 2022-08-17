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



void display0(){
	count=0;Buttonnum=0;
	memset(textlen,0,sizeof(textlen));
	memset(text,0,sizeof(text));
	textID=2;
	displayclear();
	DrawTitle(2.0,10.0);
	SetPointSize(16); 
	Draw_button(12,16,6.3,5.3,"Start Game!",ButtonColor); 
	Draw_button(12,16,4.8,3.8,"Quit Game",ButtonColor);
	Draw_button(16,16.5,2.2,1.5,"?","Orange");
	Draw_button(17,17.5,2.2,1.5,"i","Orange");
	SetPenColor("Black");
	drawLabel(15.9, 1, "帮助");
	drawLabel(16.9, 1, "关于");
	SetPenColor("BombOrange");
	Filled_rounded_rectangular(10.3,11,7,4.3,0.6);
	Draw_labal(11.8,15.8,10.7,9.7,"游   戏   登   录","Orange");
	
	SetPenColor("Black");
	drawLabel(12.7-TextStringWidth("user ID:"),8.45, "user ID:");
	SetPenColor("White");
	DrawRectangle(12.8,8.8,4,0.4,1);
	
	textx[0]=12.9,texty[0]=8.45;
	
	SetPenColor("Black");
	drawLabel(12.7-TextStringWidth("Passwords:"),7.45, "Passwords:");
	SetPenColor("White");
	DrawRectangle(12.8,7.8,4,0.4,1);
	textx[1]=12.9,texty[1]=7.45;
	
	SetPointSize(10);
	SetPenColor("Gray");
	drawLabel(12.9,8.5, "请输入用户名");
	SetPenColor("Gray");
	drawLabel(12.9,7.5, "请输入密码");
	SetPointSize(15);
	SetPenColor("Brown");
    drawLabel(0.1,3*WindowHeight/20,"开发中效果，不代表最终品质"); 
    drawLabel(0.1,2*WindowHeight/20,"如遇bug，请向我们反馈");
	drawLabel(0.1,1*WindowHeight/20,"未完成/开发的模式敬请期待，感谢您的反馈，开发组对一切测试中的不良体验表示诚挚的歉意"); 
	SetPenColor("Black");
	SetPointSize(16);
}
void Drawdisplay0bomb(double x,double y,double ratio){
	double width=1.0*ratio;
	MovePen(x+0.5*ratio,y+0.9*ratio);
	SetPenSize(5);
	DrawArc(0.3*ratio,90,-300);
	MovePen(x+0.55*ratio,y+0.48*ratio);
	DrawArc(0.1*ratio,-90,120);
	MovePen(x+0.8*ratio,y+0.8*ratio);
	DrawArc(0.1*ratio,90,90); 
	SetPenSize(3);
	MovePen(x+0.8*ratio,y+0.9*ratio);
	DrawArc(0.05*ratio,170,-50);
	MovePen(x+0.86*ratio,y+0.88*ratio);
	DrawArc(0.05*ratio,179,-50);
	MovePen(x+0.9*ratio,y+0.82*ratio);
	DrawArc(0.05*ratio,110,-50);
	MovePen(x+0.90*ratio,y+0.78*ratio);
	DrawArc(0.05*ratio,90,-50);
	SetPenSize(1);
}
void DrawTitle(double x,double y){
	MovePen(x,y);
	SetPenColor("DarkOrange");
	StartFilledRegion(1);
	DrawLine(0,-1.6);DrawLine(0.7,0);DrawArc(0.4,-90,180);DrawArc(0.4,-90,180);DrawLine(-0.7,0);
	EndFilledRegion();
	MovePen(x+0.3,y-0.2);
	SetPenColor("BombOrange");
	StartFilledRegion(1);
	DrawLine(0,-0.4);DrawLine(0.2,0);DrawArc(0.2,-90,180);DrawLine(-0.2,0);
	EndFilledRegion(); 
	MovePen(x+0.3,y-0.9);
	StartFilledRegion(1);
	DrawLine(0,-0.4);DrawLine(0.2,0);DrawArc(0.2,-90,180);DrawLine(-0.2,0);
	EndFilledRegion(); 
	Draw_bomb(x+1.2,y+0.2,2.0);
	SetPenColor("TitleYellow");
	MovePen(x+3.5,y-1.6);
	StartFilledRegion(1);
	DrawLine(0,1.6);DrawLine(0.5,0);DrawLine(0.2,-0.3);DrawLine(0.2,0.3);DrawLine(0.5,0);DrawLine(0,-1.6);
	DrawLine(-0.3,0);DrawLine(0,1.3);DrawLine(-0.2,-0.3);DrawLine(-0.4,0);DrawLine(-0.2,0.3);DrawLine(0,-1.3);DrawLine(-0.3,0);
	EndFilledRegion(); 
	MovePen(x+3.8,y-1.8);
	Go_down(x+3.8,y-1.0,0.5,"Mediumslateblue","Mediumslateblue(S3)");
	MovePen(x+5.5,y);
	SetPenColor("Powderblue");
	StartFilledRegion(1);
	DrawLine(0,-1.6);DrawLine(0.7,0);DrawArc(0.4,-90,180);DrawArc(0.4,-90,180);DrawLine(-0.7,0);
	EndFilledRegion();
	MovePen(x+5.8,y-0.2);
	SetPenColor("Cyan");
	StartFilledRegion(1);
	DrawLine(0,-0.4);DrawLine(0.2,0);DrawArc(0.2,-90,180);DrawLine(-0.2,0);
	EndFilledRegion(); 
	MovePen(x+5.8,y-0.9);
	StartFilledRegion(1);
	DrawLine(0,-0.4);DrawLine(0.2,0);DrawArc(0.2,-90,180);DrawLine(-0.2,0);
	EndFilledRegion(); 
	SetPenColor("TitleGreen");
	DrawRectangle(x+2.0,y-2.5,0.3,1.7,1); 
	SetPenColor("Mediumslateblue");
	DrawRectangle(x+3.0,y-2.5,1.5,0.3,1);
	DrawRectangle(x+3.6,y-2.8,0.3,1.4,1);
	Draw_spark(x+5.0,y-4.0,2.0);
}
void drawEditText_help(){
	SetPenColor("Black");
	drawLabel(WindowWidth/2-TextStringWidth("游   戏   说   明")/2,9*WindowHeight/10,"游   戏   说   明"); 
	drawLabel(WindowWidth/10,8*WindowHeight/10,"1.请输入学号和密码开始你的游戏");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"2.模式选择界面请点击你想要游玩的模式"); 
	drawLabel(WindowWidth/10,6*WindowHeight/10,"3.选择经典地图（已给出）或是自行编辑你想要的地图");
	drawLabel(WindowWidth/10,5*WindowHeight/10,"4.选择你想操控的人物角色，注意：未选择人物将无法开始游戏");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"5.使用键盘上的 [上]  [下]  [左]  [右] 进行人物移动控制");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"6.空格键（space）放炸弹，Tab键 暂停/继续游戏，大写锁定 关闭/开启声音");
	drawLabel(WindowWidth/10,2*WindowHeight/10,"7.用户名可以为不超过20的任意字符串，初始密码为ASCLL码个位之和");
	SetPenColor("Red");
	drawLabel(WindowWidth/2-TextStringWidth("感谢您参与本游戏开发者测评")/2,WindowHeight/10,"感谢您参与本游戏开发者测评"); 
	
}
void drawEditText_about(){
	SetPenColor("Black");
	drawLabel(WindowWidth/2-TextStringWidth("关   于   我   们")/2,9*WindowHeight/10,"关   于   我   们");
	drawLabel(WindowWidth/10,8*WindowHeight/10,"开发者：xxx，xxx，xxx");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"感谢陈建海老师，荣大中老师对本程序的指导支持"); 
	drawLabel(WindowWidth/10,6*WindowHeight/10,"引用图形库：Libgraphics");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"最后一次编辑时间：2021/6/4");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"编辑者：xxx");
	drawLabel(WindowWidth/10,2*WindowHeight/10,"游戏名：炸弹人！(Bombman!)      版本号：1.0.0"); 
	 
}
void display_help(){
	count=5;Buttonnum=0;
	SetPointSize(16); 
	displayclear();
	Draw_button(17,19,1.6,1,"返回主页","Gray");
	drawEditText_help();
}
void display_about(){
	count=5;Buttonnum=0;
	SetPointSize(16); 
	displayclear();
	Draw_button(17,19,1.6,1,"返回主页","Gray");
	drawEditText_about();
}
void display1() {
	count=1;Buttonnum=0;
	displayclear(); 
	SetPointSize(16); 
	Draw_labal(7,12,10,9,"游   戏   模   式","Mediumslateblue");
	Draw_button(5,8,8,5,"街  机  模  式",ButtonColor);
	Draw_button(11,14,8,5,"涂  色  模  式",ButtonColor);
	Draw_button(8.5,10.5,4,3,"确   定",ButtonColor);
	Draw_button(18,19.2,12.4,11.7,"商店","Blue");
	Draw_button(18,19.2,11.3,10.6,"主页","Blue");
}

void ZJUEagle(double dx,double dy,double ratio){
	SetPenColor("Blue");
	SetPenSize(3);
	MovePen(dx,dy);
	int i=0;
	DrawLine(3.0*ratio,0);
	DrawArc(1.0*ratio,90,-90);
	DrawLine(1.0*ratio,2.0*ratio);
	DrawArc(2.0*ratio,120,-60);
	DrawLine(-0.75*ratio,-0.5*ratio);
	DrawLine(0.75*ratio,-1.5*ratio);
	DrawArc(1.0*ratio,180,-90);
	DrawLine(3.0*ratio,0);
	DrawArc(1.0*ratio,0,-90);
	DrawLine(-1.0*ratio,0); 
	for(i=0;i<4;i++){
		DrawLine(-0.25*ratio,-0.5*ratio);
		DrawLine(1.25*ratio,0);
		DrawArc(1.0*ratio,0,-90);
		DrawLine(-0.75*ratio,0);
	}
	DrawLine(-0.5*ratio,-1.0*ratio);
	DrawLine(-0.5*ratio,1.0*ratio);
	for(i=0;i<4;i++){
		DrawLine(-0.75*ratio,0);
		DrawArc(1.0*ratio,-90,-90);
		DrawLine(1.25*ratio,0);
		DrawLine(-0.25*ratio,0.5*ratio);
	}
	DrawLine(-1.0*ratio,0);
	DrawArc(1.0*ratio,-90,-90);
	SetPenSize(1);

}
void ZongZi(double dx,double dy,double ratio){
	MovePen(dx,dy);
	SetPenColor("Flesh");
	StartFilledRegion(1);
	DrawArc(1.0*ratio,60,-60);
	DrawArc(1.0*ratio,-60,-60);
	DrawArc(1.0*ratio,180,-60);
	EndFilledRegion(); 
	StartFilledRegion(1);
	DrawLine(-0.5*ratio,-0.5*pow(3,0.5)*ratio);
	DrawLine(1.0*ratio,0);
	DrawLine(-0.5*ratio,0.5*pow(3,0.5)*ratio);
	EndFilledRegion();
	MovePen(dx-pow(3,0.5)/4*ratio,dy-pow(3,0.5)/2*ratio+0.5*ratio);
	SetPenColor("TitleGreen");
	SetPenSize(5);
	MovePen(dx+0.5*ratio,dy-0.5*pow(3,0.5)*ratio);
	StartFilledRegion(1);
	DrawArc(1.0*ratio,-90,-60);
	DrawArc(1.0*ratio,150,30);
	DrawArc(1.0*ratio,-120,60);
	EndFilledRegion();
	MovePen(dx-0.5*ratio,dy-0.5*pow(3,0.5)*ratio);
	DrawArc(1.0*ratio,-90,60); 
	SetPenColor("Black");
	MovePen(dx-0.10*ratio,dy-0.20*ratio);
	StartFilledRegion(1);
	DrawArc(0.02*ratio,0,360);
	EndFilledRegion();
	MovePen(dx+0.10*ratio,dy-0.20*ratio);
	StartFilledRegion(1);
	DrawArc(0.02*ratio,0,360); 
	EndFilledRegion();
	MovePen(dx-0.15*ratio,dy-0.35*ratio);
	SetPenColor("Red");
	StartFilledRegion(1);
	DrawArc(0.04*ratio,0,360);
	EndFilledRegion();
	MovePen(dx+0.2*ratio,dy-0.35*ratio);
	StartFilledRegion(1);
	DrawArc(0.04*ratio,0,360);
	EndFilledRegion();
	SetPenSize(1);
}
void display_store(){
	count = 6;Buttonnum=0;
	SetPointSize(16); 
	displayclear();
	Draw_button(17.5,19,1.6,1,"返 回","Gray");
	double i;for(i=10;i>=0;i-=1.5) ZongZi(7.5,i,1); 
	ZJUEagle(6,12.5,0.2);
	ZJUEagle(11,12.5,0.2);
	SetPointSize(30);
	drawLabel(8.5,11.5,"商   店");
	SetPointSize(16);
	Draw_labal(3,5,10,9,"角   色","Brown");
	Draw_labal(12,14,10,9,"道   具","Brown");
	SetPointSize(12);
	Draw_bomb_plus(9.0,8,1.0);//收集的炸弹 
	drawLabel(10.0,8-0.8,"最多可放置炸弹数目+1");
	Draw_drink(9.0,7.0,1.0);//水 
	drawLabel(10.0,7-0.8,"在炸弹威力不超过3的情况下，炸弹威力+1");
	Draw_rapid(9.0,6.0,1.0);//加速 
	drawLabel(10.0,6-0.8,"在移动速度不超过4的情况下，移动速度+1");
	Draw_frozen(9.0,5.0,1.0);//冷却 
	drawLabel(10.0,5-0.8,"冰冻，短时间无法移动");
	Draw_hand(9.0,4.0,1.0);//推炸弹 
	drawLabel(10.0,4-0.8,"向行进方向移动炸弹一格");
	Draw_heart(9.0,3.0,1.0);//加生命 
	drawLabel(10.0,3-0.8,"当生命值不满四颗心的时候，生命值+1");
	Draw_shied(9.0,2.0,1.0);//防护盾
	drawLabel(10.0,2-0.8,"获得防护盾，在炸弹爆炸的时候能够避免一次伤害"); 
	Go_down(2,8,1,"Chocolate","Chocolate(S)");
	drawLabel(4,7.5,"老实棕"); 
	Go_down(2,6,1,"IndianRed","IndianRed(S)");
	drawLabel(4,5.5,"活力红"); 
	Go_down(2,4,1,"DeepPink","DeepPink(S)");
	drawLabel(4,3.5,"可爱粉"); 
	Go_down(2,2,1,"RoyalBlue","RoyalBlue(S)");
	drawLabel(4,1.5,"忧郁蓝"); 
	SetPointSize(16);
}
#endif
