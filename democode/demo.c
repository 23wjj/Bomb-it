#include "My_define.h"

const int mseconds100 = 100;
const int mseconds500 = 500;   
const int mseconds600 = 300;
const int mseconds1000 = 1000;
int PAUSE,END;
string Hat_color="Darkkhaka",Tail_color="Moccasin";
int count=0;
int Enemy_track[3][100];
struct character enemy[4];// 0,1,2,是敌人，3是玩家 
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
char text[2][100]; /*输入的字符串缓冲区*/
int textlen[2],Isleft[2],textID=2;/*输入的字符串长度*/
double textx[2],texty[2]; /*字符串的起始位置*/
bool isDisplayText = FALSE;
int HaveMusic=1;
int Frozen_cnt=0;
string Filename[3];
int MapPattern;
bool DyeingPattern;//染色模式的开关 
string Dyeing_color[4]; 


int sizeof_Bomb=sizeof(struct Bomb_List);
BombP head=NULL,tail;
FrozenP frozen_head=NULL,frozen_tail=NULL;
FILE *fp;
int Buttonnum;

void KeyboardEventProcess(int key,int event){
	uiGetKeyboard(key, event);
	if(count==0&&textID<2){
		double oldradius;
	 	static char str[2] = {0, 0};
	     	switch (event) {
		 		case KEY_DOWN:
				 	switch (key) {
				     	case VK_BACK:case VK_DELETE:/*DELETE*/
							CurrentClear();
							SetEraseMode(TRUE);/*擦除前一个*/
							str[0]=text[textID][textlen[textID]-Isleft[textID]-1];//取当前字符宽度 
							textx[textID]-= TextStringWidth(str);//并且向前移动光标 
							MovePen(textx[textID],texty[textID]);
							DrawTextString(text[textID]+textlen[textID]-Isleft[textID]-1);MovePen(textx[textID],texty[textID]);//删去后面所有 
							SetEraseMode(FALSE);
							DrawTextString(text[textID]+textlen[textID]-Isleft[textID]);MovePen(textx[textID],texty[textID]);//重写后面除去删去字符的剩余字符串 
							int i;for(i=textlen[textID]-Isleft[textID]-1;i<textlen[textID];i++)
							text[textID][i]=text[textID][i+1];
							textlen[textID]--;//更新text[textID]字符串 
	                    break;
	                    case VK_LEFT:/*LEFT*/
				         	CurrentClear();
				         	Isleft[textID]++;//左移标志加一 
							str[0]=text[textID][textlen[textID]-Isleft[textID]];//取当前位宽 
		                    textx[textID] -= TextStringWidth(str);//光标左移 
		                    MovePen(textx[textID],texty[textID]);
	                    	break;
	                    case VK_RIGHT:/*RIGHT*/
	                    	if(Isleft[textID]){//如果当前光标不处于左移状态则不允许右移 
	                    		CurrentClear();
					         	Isleft[textID]--;//左移标志减一 
			                    str[0]=text[textID][textlen[textID]-Isleft[textID]-1];//取当前位宽 
		                    	textx[textID]+= TextStringWidth(str);//光标右移 
			                    MovePen(textx[textID],texty[textID]);
							}
	                    	break;
				 	}
					break;
				case KEY_UP:
					break;
		}	 
	}
	else if(count==1||count==5){
		if(event==KEY_DOWN&&key==VK_BACK)
		display0();
	}
	else if(count==2||count==6){
		if(event==KEY_DOWN&&key==VK_BACK)
		display1();
	}
	else if(count==3){
		if(END) return;
	 	if(event==KEY_DOWN){
	 	 	switch(key){
	 	 		case VK_UP:
	 	 			enemy[3].direction=3;
					MoveFunction(3,3);
				    break;
				case VK_LEFT:	
					enemy[3].direction=2;
					MoveFunction(3,2);
					break;
				case VK_DOWN:
					enemy[3].direction=1;
					MoveFunction(3,1);
					break;
				case VK_RIGHT:
					enemy[3].direction=0;
					MoveFunction(3,0);
					break;
				case VK_SPACE:
					if(enemy[3].Bombnum>0){
						PutBomb(3,(int)(enemy[3].PositionX-StateColumnWidth),(int)enemy[3].PositionY);
						enemy[3].Bombnum--;
					}
					break;
				case VK_TAB://Tab 键暂停，过会儿写一个鼠标可以点的按键 
					DisPause();
					break;
				case VK_CAPITAL:
					DisMusic();
					break;
			}
		}
    }
}
void TimerEventProcess(int timerID){
	if(PAUSE) return;
    bool erasemode;
    int i;
    BombP now;
	FrozenP newp;
	if(count==0){
		if(timerID==TIMER_BLINK500){
			erasemode = GetEraseMode();
		  SetEraseMode(isDisplayText);//根据当前显示标志来决定是显示还是隐藏字符串
		  MovePen(textx[textID]-NarrowOffset,texty[textID]);//将笔触移到夹缝处 
		  DrawLine(0,0.3);
		  MovePen(textx[textID],texty[textID]);//将笔触移回字符书写位置 
	      SetEraseMode(erasemode);
		  isDisplayText = !isDisplayText;//交替显示/隐藏字符串符号
		}
	}
	else if(count==3){
		switch (timerID) {
			//炸弹爆炸时间倒计时 
		    case TIMER_BLINK500:/*500ms*/
		    	if(head!=NULL){
					now=(BombP)head;
		    		for(;now!=NULL;now=now->nxt){
						now->time-=1;
						if(now->froze) now->time+=0.5;
						if(now->time==3&&HaveMusic)
						PlaySound(TEXT("11971.wav"),NULL,SND_FILENAME | SND_ASYNC);
					}
				}	
				newp=frozen_head;
				for(;newp!=NULL;newp=newp->nxt){
					newp->time--;
					if(newp->time<1.5)
						DelFrozen(newp);
				}
				break;
			//敌人自动移动 
			case TIMER_BLINK600: 
				for(i=0;i<3;i++) Enemy_move(i);
		    	break;
			//刷新屏幕
			case TIMER_BLINK100:{
				BombP now=head;
				for(;now!=NULL;now=now->nxt)if(now->time<=3){
					now->time--;
					DrawMap(now->x-1,now->x+1,now->y+1,now->y-1);
					Draw_spark(now->x+StateColumnWidth+0.4,now->y+1-0.4,0.8*(3-(double)now->time/3)*now->BombPower);
					if(now->time<0.01){
						DelBomb(now);
						int Power=now->BombPower;
						DrawMap(now->x-Power,now->x+Power,now->y+Power,now->y-Power);
						DrawAllPlayers();
					}
					if(now->x<now->BombPower) 
						InitStateColumn(),DrawStateItems();
				}
				break;
			}
			//游戏状态栏倒计时 
			case TIMER_BLINK1000:
				if(!(enemy[0].Blood|enemy[1].Blood|enemy[2].Blood))
					END=1,Draw_gamewin(WindowWidth/2,WindowHeight/2+2);
				else if(!ChangeClockDisplay()||!enemy[3].Blood)
					END=1,Draw_gameover(WindowWidth/2,WindowHeight/2+2);
				DrawStateItems();
				if(END==1){
					if(DyeingPattern) Draw_score();
					Draw_button(8.5,10.5,1.8,0.8,"退出","Gray");
					mciSendString("close 11638.mp3",NULL,0,NULL);
					cancelTimer(TIMER_BLINK100);//游戏暂停 
					cancelTimer(TIMER_BLINK500);
					cancelTimer(TIMER_BLINK600);
					cancelTimer(TIMER_BLINK1000);
				}
				break;
			default:
				break;
		}
	}
}
void MouseEventProcess(int x, int y, int button, int event){
	static double omx,omy;
	double mx = ScaleXInches(x);/*pixels --> inches*/
	double my = ScaleYInches(y);/*pixels --> inches*/
	uiGetMouse(x, y, button, event); //GUI获取鼠标
	if(END==1){
		switch (event) {
			case BUTTON_DOWN:
				if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])) exit(-1); 
			break;
			case MOUSEMOVE:{
				break;
			}
		}	
	}
	else if (count == 0) {
		switch (event) {
			case BUTTON_DOWN:
					 if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
				else if(Check_in_button(mx,my,Button[1])) Click_button(Button[1],0.1);
				else if(Check_in_button(mx,my,Button[2])) Click_button(Button[2],0.1);
				else if(Check_in_button(mx,my,Button[3])) Click_button(Button[3],0.1);
				else if(mx>=12.8&&mx<=16.8&&my>=8.4&&my<=8.8){
					textID=0;
					SetPenColor("White"); DrawRectangle(12.8,8.8,4,0.4,1);
					SetPenColor("Black"); MovePen(textx[textID],texty[textID]);
					startTimer(TIMER_BLINK500,mseconds500);
				}
				else if(mx>=12.8&&mx<=16.8&&my>=7.4&&my<=7.8){
					textID=1;
					SetPenColor("White"); DrawRectangle(12.8,7.8,4,0.4,1);
					SetPenColor("Black"); MovePen(textx[textID],texty[textID]);
					startTimer(TIMER_BLINK500,mseconds500);
				}
				else cancelTimer(TIMER_BLINK500,mseconds500),textID=2;;
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])){
					Click_button(Button[0],0);
					if(PassCheck()) display1();
				}
				else if(Check_in_button(mx,my,Button[1])){
					Click_button(Button[1],0);
					exit(0);
				}
				else if(Check_in_button(mx,my,Button[2])){
					Click_button(Button[2],0);
					display_help();
				}
				else if(Check_in_button(mx,my,Button[3])){
					Click_button(Button[3],0);
					display_about();
				}
				else;
			break; 
			case MOUSEMOVE:{
				break;
			}
		}
	}
	else if (count == 1) {
		switch (event) {
			case BUTTON_DOWN:
				if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
				if(Check_in_button(mx,my,Button[1])) Click_button(Button[1],0.1);
				if(Check_in_button(mx,my,Button[2])) Click_button(Button[2],0.1);
				if(Check_in_button(mx,my,Button[3])) Click_button(Button[3],0.1);
				if(Check_in_button(mx,my,Button[4])) Click_button(Button[4],0.1);
				else;
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])){
					int i;for(i=0;i<=1;i++) Button[i].color=ButtonColor;
					Button[0].color="Red";
					for(i=0;i<=1;i++) Click_button(Button[i],0);
					DyeingPattern=FALSE;
				}
				else if(Check_in_button(mx,my,Button[1])){
					int i;for(i=0;i<=1;i++) Button[i].color=ButtonColor;
					Button[1].color="Red";
					for(i=0;i<=1;i++) Click_button(Button[i],0);
					DyeingPattern=TRUE;
				}
				else if(Check_in_button(mx,my,Button[2])){
					Click_button(Button[2],0);
					Filename[0]="setting.txt";Filename[1]="mymap.txt";Filename[2]="map.txt";
					display2();
				}
				else if(Check_in_button(mx,my,Button[3])){
					Click_button(Button[3],0);
					display_store(); 
				}
				else if(Check_in_button(mx,my,Button[4])){
					Click_button(Button[4],0);
					display0();
				}
				else;
				break; 
			case MOUSEMOVE:{
				break;
			}
		}
	}
	else if (count == 2) {
		switch (event) {
			case BUTTON_DOWN:
				if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
				if(Check_in_button(mx,my,Button[1])) Click_button(Button[1],0.1);
				if(Check_in_button(mx,my,Button[2])) Click_button(Button[2],0.1);
				if(Check_in_button(mx,my,Button[3])) Click_button(Button[3],0.1);
				if(Check_in_button(mx,my,Button[4])) Click_button(Button[4],0.1);
				if(Check_in_button(mx,my,Button[5])) Click_button(Button[5],0.1);
				if(Check_in_button(mx,my,Button[6])) Click_button(Button[6],0.1);
				if(Check_in_button(mx,my,Button[7])) Click_button(Button[7],0.1);
				if(Check_in_button(mx,my,Button[8])) Click_button(Button[8],0.1);
				else;
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])){
					Click_button(Button[0],0);
					display1();
				}
				else if(Check_in_button(mx,my,Button[1])){
					int i;for(i=1;i<=4;i++) Button[i].color=ButtonColor;
					Button[1].color="Red";
					for(i=1;i<=4;i++) Click_button(Button[i],0);
					enemy[3].Color1="Chocolate";
					enemy[3].Color2="Chocolate(S)";
				}else if(Check_in_button(mx,my,Button[2])){
					int i;for(i=1;i<=4;i++) Button[i].color=ButtonColor;
					Button[2].color="Red";
					for(i=1;i<=4;i++) Click_button(Button[i],0);
					enemy[3].Color1="IndianRed";
					enemy[3].Color2="IndianRed(S)";
				}else if(Check_in_button(mx,my,Button[3])){
					int i;for(i=1;i<=4;i++) Button[i].color=ButtonColor;
					Button[3].color="Red";
					for(i=1;i<=4;i++) Click_button(Button[i],0);
					enemy[3].Color1="DeepPink";
					enemy[3].Color2="DeepPink(S)";
				}else if(Check_in_button(mx,my,Button[4])){
					int i;for(i=1;i<=4;i++) Button[i].color=ButtonColor;
					Button[4].color="Red";
					for(i=1;i<=4;i++) Click_button(Button[i],0);
					enemy[3].Color1="RoyalBlue";
					enemy[3].Color2="RoyalBlue(S)";
				}else if(Check_in_button(mx,my,Button[5])){
					int i;for(i=5;i<=7;i++) Button[i].color=ButtonColor;
					Button[5].color="Red";
					for(i=5;i<=7;i++) Click_button(Button[i],0);
					MapPattern=0;
					
				}else if(Check_in_button(mx,my,Button[6])){
					int i;for(i=5;i<=7;i++) Button[i].color=ButtonColor;
					Button[6].color="Red";
					for(i=5;i<=7;i++) Click_button(Button[i],0);
					MapPattern=1;
					
				}else if(Check_in_button(mx,my,Button[7])){
					int i;for(i=5;i<=7;i++) Button[i].color=ButtonColor;
					Button[7].color="Red";
					for(i=5;i<=7;i++) Click_button(Button[i],0);
					MapPattern=2;
					count=4;
					Initmain_Mapeditor();
				}else if(Check_in_button(mx,my,Button[8])){
					Click_button(Button[8],0);
					if(enemy[3].Color1) {
						count=3;
						Main_init();
						mciSendString("play 11638.mp3 repeat",NULL,0,NULL);
					}
				}
				else;
			break; 
			case MOUSEMOVE:{
				break;
			}
		}
	}
	else if (count == 5) {
		switch (event) {
			case BUTTON_DOWN:
				if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
				else;
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])){
					Click_button(Button[0],0);
					display0();
				}
			break; 
			case MOUSEMOVE:{
				break;
			}
		}
	}
	else if (count == 6) {
		switch (event) {
			case BUTTON_DOWN:
				if(Check_in_button(mx,my,Button[0])) Click_button(Button[0],0.1);
				else;
			break;
			case BUTTON_UP:
				if(Check_in_button(mx,my,Button[0])){
					Click_button(Button[0],0);
					display1();
				}
			break; 
			case MOUSEMOVE:{
				break;
			}
		}
	}
	else if(count==4){
		int i,j;
		switch (event) {
			case BUTTON_DOWN:
			  	if (button == LEFT_BUTTON) {
			  		for(i=0;i<Row;i++)
			  			for(j=0;j<Line;j++)
				  			if (TestinBox_mapeditor(mx, my, StateColumnWidth+j*BlockWidth,StateColumnWidth+(j+1)*BlockWidth,i*BlockWidth,(i+1)*BlockWidth)){
					  			MapBlock_Edit[i][j].Selected=1;
					  			Type_Edit=0;
				  			}
				}
				break;
		}
		display_mapeditor();//刷新显示 
	}
	else if(count==3){
		switch (event) {
			case BUTTON_DOWN:
				if(mx>=1&&mx<=1.5&&my>=0.5&&my<=1){
					SetPenColor("LightPink");
					Filled_rounded_rectangular(1,1,0.5,0.7,0.1);
					SetPenColor("DarkOrange");
					Filled_rounded_rectangular(1,0.95,0.5,0.5,0.1);
					SetPenColor("WhiteOrange");
					DrawRectangle(1.12,0.8,0.08,0.25,1);
					DrawRectangle(1.28,0.8,0.08,0.25,1);
				}
	         	else if(mx>=2.4&&mx<=2.9&&my>=0.5&&my<=1){
	         		SetPenColor("LightPink");
					Filled_rounded_rectangular(2.4,1,0.5,0.7,0.1);
					SetPenColor("DarkOrange");
					Filled_rounded_rectangular(2.4,0.95,0.5,0.5,0.1);
					SetPenColor("WhiteOrange");
					MovePen(2.525,0.75);
					StartFilledRegion(1);
					DrawLine(0,-0.15);
					DrawLine(0.07,0);
					DrawLine(0.15,-0.12);
					DrawLine(0,0.39);
					DrawLine(-0.15,-0.12);
					DrawLine(-0.07,0);
					EndFilledRegion();
				 }
			break;
			case BUTTON_UP:
				if(mx>=1&&mx<=1.5&&my>=0.5&&my<=1){
					DisPause();
				}
				else if(mx>=1.7&&mx<=2.2&&my>=0.5&&my<=1){
					count = 0;
					DisPause();
					display0();
				}
				else if(mx>=2.4&&mx<=2.9&&my>=0.5&&my<=1){
					DisMusic();
				}
	         	omx=mx,omy=my;
			break;
			case MOUSEMOVE:{
				break;
			}
		}
	}
}
void CharEventProcess(char ch){
	uiGetChar(ch); // GUI字符输入
	if (count == 0&&textID<2) {
		static char str[2] = {0, 0};
	    switch (ch) {
	    	case '\r':case 8: case 27: /*ESC*/
	    	//回车，退格键，ESC键都代表退出 
	 	    	break;
		    default:{//输入字符 
				int i,j;for(i=0,j=++textlen[textID];i<=Isleft[textID];i++,j--)
					text[textID][j]=text[textID][j-1];
				text[textID][j]=ch;//将所有字符向右挪动一格
				CurrentClear();
				SetEraseMode(TRUE);//擦除原来后面的所有字符
			    DrawTextString(text[textID]+j+1);MovePen(textx[textID],texty[textID]);
			    SetEraseMode(FALSE);//重新写入后面的字符串 
				DrawTextString(text[textID]+j);
				str[0]=ch;//取这个字符宽度，
				textx[textID]+=TextStringWidth(str);//并且将笔触位置向右移动
				MovePen(textx[textID],texty[textID]);
			}
		}
	}
}
void Main(){
	SetWindowTitle("BombIt!");
	SetWindowSize(WindowWidth, WindowHeight);
	InitGraphics();
	registerTimerEvent(TimerEventProcess);
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerCharEvent(CharEventProcess); // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	display0();
//	enemy[3].Color1="DeepPink";enemy[3].Color2="DeepPink(S)";
//	count=3;DyeingPattern=1;
//	Main_init();
}

