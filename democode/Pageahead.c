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
extern struct character enemy[4];// 0,1,2,�ǵ��ˣ�3����� 
extern int dx[4];
extern int dy[4];
extern char text[2][100]; /*������ַ���������*/
extern int textlen[2],Isleft[2],textID;/*������ַ�������*/
extern double textx[2],texty[2]; /*�ַ�������ʼλ��*/
extern bool isDisplayText;
extern int HaveMusic;
extern int Frozen_cnt;
extern string Filename[3];
extern int MapPattern;
extern bool DyeingPattern;//Ⱦɫģʽ�Ŀ��� 
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
	drawLabel(15.9, 1, "����");
	drawLabel(16.9, 1, "����");
	SetPenColor("BombOrange");
	Filled_rounded_rectangular(10.3,11,7,4.3,0.6);
	Draw_labal(11.8,15.8,10.7,9.7,"��   Ϸ   ��   ¼","Orange");
	
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
	drawLabel(12.9,8.5, "�������û���");
	SetPenColor("Gray");
	drawLabel(12.9,7.5, "����������");
	SetPointSize(15);
	SetPenColor("Brown");
    drawLabel(0.1,3*WindowHeight/20,"������Ч��������������Ʒ��"); 
    drawLabel(0.1,2*WindowHeight/20,"����bug���������Ƿ���");
	drawLabel(0.1,1*WindowHeight/20,"δ���/������ģʽ�����ڴ�����л���ķ������������һ�в����еĲ��������ʾ��ֿ��Ǹ��"); 
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
	drawLabel(WindowWidth/2-TextStringWidth("��   Ϸ   ˵   ��")/2,9*WindowHeight/10,"��   Ϸ   ˵   ��"); 
	drawLabel(WindowWidth/10,8*WindowHeight/10,"1.������ѧ�ź����뿪ʼ�����Ϸ");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"2.ģʽѡ�������������Ҫ�����ģʽ"); 
	drawLabel(WindowWidth/10,6*WindowHeight/10,"3.ѡ�񾭵��ͼ���Ѹ������������б༭����Ҫ�ĵ�ͼ");
	drawLabel(WindowWidth/10,5*WindowHeight/10,"4.ѡ������ٿص������ɫ��ע�⣺δѡ�����ｫ�޷���ʼ��Ϸ");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"5.ʹ�ü����ϵ� [��]  [��]  [��]  [��] ���������ƶ�����");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"6.�ո����space����ը����Tab�� ��ͣ/������Ϸ����д���� �ر�/��������");
	drawLabel(WindowWidth/10,2*WindowHeight/10,"7.�û�������Ϊ������20�������ַ�������ʼ����ΪASCLL���λ֮��");
	SetPenColor("Red");
	drawLabel(WindowWidth/2-TextStringWidth("��л�����뱾��Ϸ�����߲���")/2,WindowHeight/10,"��л�����뱾��Ϸ�����߲���"); 
	
}
void drawEditText_about(){
	SetPenColor("Black");
	drawLabel(WindowWidth/2-TextStringWidth("��   ��   ��   ��")/2,9*WindowHeight/10,"��   ��   ��   ��");
	drawLabel(WindowWidth/10,8*WindowHeight/10,"�����ߣ�xxx��xxx��xxx");
	drawLabel(WindowWidth/10,7*WindowHeight/10,"��л�½�����ʦ���ٴ�����ʦ�Ա������ָ��֧��"); 
	drawLabel(WindowWidth/10,6*WindowHeight/10,"����ͼ�ο⣺Libgraphics");
	drawLabel(WindowWidth/10,4*WindowHeight/10,"���һ�α༭ʱ�䣺2021/6/4");
	drawLabel(WindowWidth/10,3*WindowHeight/10,"�༭�ߣ�xxx");
	drawLabel(WindowWidth/10,2*WindowHeight/10,"��Ϸ����ը���ˣ�(Bombman!)      �汾�ţ�1.0.0"); 
	 
}
void display_help(){
	count=5;Buttonnum=0;
	SetPointSize(16); 
	displayclear();
	Draw_button(17,19,1.6,1,"������ҳ","Gray");
	drawEditText_help();
}
void display_about(){
	count=5;Buttonnum=0;
	SetPointSize(16); 
	displayclear();
	Draw_button(17,19,1.6,1,"������ҳ","Gray");
	drawEditText_about();
}
void display1() {
	count=1;Buttonnum=0;
	displayclear(); 
	SetPointSize(16); 
	Draw_labal(7,12,10,9,"��   Ϸ   ģ   ʽ","Mediumslateblue");
	Draw_button(5,8,8,5,"��  ��  ģ  ʽ",ButtonColor);
	Draw_button(11,14,8,5,"Ϳ  ɫ  ģ  ʽ",ButtonColor);
	Draw_button(8.5,10.5,4,3,"ȷ   ��",ButtonColor);
	Draw_button(18,19.2,12.4,11.7,"�̵�","Blue");
	Draw_button(18,19.2,11.3,10.6,"��ҳ","Blue");
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
	Draw_button(17.5,19,1.6,1,"�� ��","Gray");
	double i;for(i=10;i>=0;i-=1.5) ZongZi(7.5,i,1); 
	ZJUEagle(6,12.5,0.2);
	ZJUEagle(11,12.5,0.2);
	SetPointSize(30);
	drawLabel(8.5,11.5,"��   ��");
	SetPointSize(16);
	Draw_labal(3,5,10,9,"��   ɫ","Brown");
	Draw_labal(12,14,10,9,"��   ��","Brown");
	SetPointSize(12);
	Draw_bomb_plus(9.0,8,1.0);//�ռ���ը�� 
	drawLabel(10.0,8-0.8,"���ɷ���ը����Ŀ+1");
	Draw_drink(9.0,7.0,1.0);//ˮ 
	drawLabel(10.0,7-0.8,"��ը������������3������£�ը������+1");
	Draw_rapid(9.0,6.0,1.0);//���� 
	drawLabel(10.0,6-0.8,"���ƶ��ٶȲ�����4������£��ƶ��ٶ�+1");
	Draw_frozen(9.0,5.0,1.0);//��ȴ 
	drawLabel(10.0,5-0.8,"��������ʱ���޷��ƶ�");
	Draw_hand(9.0,4.0,1.0);//��ը�� 
	drawLabel(10.0,4-0.8,"���н������ƶ�ը��һ��");
	Draw_heart(9.0,3.0,1.0);//������ 
	drawLabel(10.0,3-0.8,"������ֵ�����Ŀ��ĵ�ʱ������ֵ+1");
	Draw_shied(9.0,2.0,1.0);//������
	drawLabel(10.0,2-0.8,"��÷����ܣ���ը����ը��ʱ���ܹ�����һ���˺�"); 
	Go_down(2,8,1,"Chocolate","Chocolate(S)");
	drawLabel(4,7.5,"��ʵ��"); 
	Go_down(2,6,1,"IndianRed","IndianRed(S)");
	drawLabel(4,5.5,"������"); 
	Go_down(2,4,1,"DeepPink","DeepPink(S)");
	drawLabel(4,3.5,"�ɰ���"); 
	Go_down(2,2,1,"RoyalBlue","RoyalBlue(S)");
	drawLabel(4,1.5,"������"); 
	SetPointSize(16);
}
#endif
