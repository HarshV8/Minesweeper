/*
Made Just for fun - and as a Final Year Submission Project of my 12th Class
we were not allowed to have multiple files for  a project so its all clumsy,
also we were not allowed to use Graphic Libraries, so had to do some ascii art!

Not depreciated but has lots of problems compiling correctly!
Starts on Windows. Using windows.h to get the gotoxy(), wherex(),wherey() to work
but it does not exactly work the way it is supposed to.. 
*/

#include<fstream>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<windows.h>

using namespace std;

//Re-declaring every unsupported function again [duh!]

void cprintf(char s[]){
	printf("%s",s);
}

void clrscr(){
system("cls");
// Change to "clear" for Linux
}


void gotoxy( int column, int line )
  {
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
  }

int wherex()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD  result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.X;
  }

int wherey()
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD  result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.Y;
  }



void randomize(){
srand(time(0));
}
int random(int x){
int in_range = rand()%x;
return in_range;
}

struct player
{
char name[20];
int score;
clock_t time;
};
class game
{
    int t,u,mine,x1,y1,mode,flagcounter;
    int grid[20][20];
    char board[40][40];
public:
    clock_t watch,timer;
    int gamestat;
    game(int);
    void wintrue();
    int status(int,int);
    void sweep(int x,int y);
    void count(int,int);
    void boardinit(int,int);
    void display(int);
    void wincheck();
    void move(int);
};

game::game(int mod)
{   watch=clock();
    timer=clock();
	flagcounter=0;
    gamestat=0;
    mine=0;
    mode=mod;
    x1=(mode+5)*2;
    y1=(mode+3)*2-1;
    int c=2*x1+1;
    int r=2*y1+1;
  for(int i=0;i<r;i++)
{
for(int j=0;j<c;j++)
{
if(i%2!=0&&j%2!=0)
board[i][j]=char(254);
else if(i==j&&j==0)
board[i][j]=char(218);
else if(i==0&&j==(c-1))
board[i][j]=char(191);
else if(j==0&&i==(r-1))
board[i][j]=char(192);
else if(i==(r-1)&&j==(c-1))
board[i][j]=char(217);
else if(i==0&&j!=(c-1)&&j!=0)
{
if(j%2==0)
board[i][j]=char(194);
else board[i][j]=char(196);
}
else if(i==(r-1)&&j!=(c-1)&&j!=0)
{
if(j%2==0)
board[i][j]=char(193);
else board[i][j]=char(196);
}
else if(j==0&&i!=(r-1)&&i!=0)
{
if(i%2==0)
board[i][j]=char(195);
else board[i][j]=char(179);
}
else if(j==(c-1)&&i!=(r-1)&&i!=0)
{
if(i%2==0)
board[i][j]=char(180);
else board[i][j]=char(179);
}
else if(i!=0&&j!=0&&i!=(r-1)&&j!=(c-1))
{
if(i%2!=0&&j%2==0)
board[i][j]=char(179);
else if(i%2==0&&j%2!=0)
board[i][j]=char(196);
else if(i%2==0&&j%2==0)
board[i][j]=char(197);
}
}
}
t=13-(r-1)/2;
u=40-(c-1)/2;
display(1);
}

void game::boardinit(int x,int y)
{
	for(int l=0;l<y1;l++)
	{
		for(int o=0;o<x1;o++)
		{
			grid[l][o]=0;
		}
	}
    randomize();
    int k=0;
    mine=(x1)*(y1)/8;
    while(k<mine)
    {
	int i=random(y1);
	int j=random(x1);
	if(grid[i][j]!=-1&&i!=(y-t-1)/2&&j!=(x-u-1)/2)
	{
		grid[i][j]=-1;
		k++;
	    }
    }
    for(int i=0;i<y1;i++)
    {
	for(int j=0;j<x1;j++)
	{
		if(grid[i][j]!=-1)
		count(i,j);
	    }
    }
    sweep(x,y);
    display(0);
    watch=clock();
}
int game::status(int ii,int jj)
{int retkey=0;
    if(ii==0)
    {
	if(jj==0)
	retkey=-3;
	if(jj==x1-1)
	retkey=3;
	if(jj<x1-1&&jj>0)
	retkey=5;
    }
    else if(ii==y1-1)
    {
	if(jj==0)
	retkey=-13;
	if(jj==x1-1)
	retkey=13;
	if(jj<x1-1&&jj>0)
	retkey=-5;
    }
    else if(jj==0)
    {
	if(ii<y1-1&&ii>0)
	retkey=-15;
    }
    else if(jj==x1-1)
    {
	if(ii<y1-1&&ii>0)
	retkey=15;
    }
    else if(ii<y1-1&&jj<x1-1&&ii>0&&jj>0)
	retkey=8;
    else retkey=0;
    return retkey;
}
void game::count(int ii,int jj)
{
    if(grid[ii-1][jj-1]==-1&&status(ii-1,jj-1)!=0)grid[ii][jj]++;
    if(grid[ii-1][jj]  ==-1&&status(ii-1,jj)!=0)grid[ii][jj]++;
    if(grid[ii-1][jj+1]==-1&&status(ii-1,jj+1)!=0)grid[ii][jj]++;
    if(grid[ii][jj-1]  ==-1&&status(ii,jj-1)!=0)grid[ii][jj]++;
    if(grid[ii][jj+1]  ==-1&&status(ii,jj+1)!=0)grid[ii][jj]++;
    if(grid[ii+1][jj-1]==-1&&status(ii+1,jj-1)!=0)grid[ii][jj]++;
    if(grid[ii+1][jj]  ==-1&&status(ii+1,jj)!=0)grid[ii][jj]++;
    if(grid[ii+1][jj+1]==-1&&status(ii+1,jj+1)!=0)grid[ii][jj]++;
}
void game::sweep(int x,int y)
{
    int r=y-t;
    int c=x-u;
    int gr=(r-1)/2;
    int gc=(c-1)/2;
    if(grid[gr][gc]==-1)
    {
    gamestat=-1;
    board[r][c]=char(15);
    }
    else if(board[r][c]==char(254))
    {
	if(grid[gr][gc]!=0)
	board[r][c]=grid[gr][gc]+48;
	else if(grid[gr][gc]==0)
	{
	    board[r][c]=char(32);
	    if(status(gr,gc)==-3)
	    {
			sweep(x,y+2);
			sweep(x+2,y);
			sweep(x+2,y+2);
		}
		if(status(gr,gc)==3)
		{
			sweep(x-2,y);
			sweep(x,y+2);
			    sweep(x-2,y+2);
	    }
	    if(status(gr,gc)==-13)
	    {
		sweep(x+2,y);
		sweep(x,y-2);
		sweep(x+2,y-2);
	    }
	    if(status(gr,gc)==13)
	    {
		sweep(x-2,y);
		sweep(x,y-2);
		sweep(x-2,y-2);
	    }
	    if(status(gr,gc)==5)
	    {
		sweep(x-2,y);
		sweep(x+2,y);
		sweep(x-2,y+2);
		sweep(x+2,y+2);
		sweep(x,y+2);
	    }
	    if(status(gr,gc)==-5)
	    {
		sweep(x-2,y);
		sweep(x+2,y);
		sweep(x-2,y-2);
		sweep(x+2,y-2);
		sweep(x,y-2);
	    }
	    if(status(gr,gc)==-15)
	    {
		sweep(x,y-2);
		sweep(x,y+2);
		sweep(x+2,y+2);
		sweep(x+2,y-2);
		sweep(x+2,y);
	    }
	    if(status(gr,gc)==15)
	    {
		sweep(x,y+2);
		sweep(x,y-2);
		sweep(x-2,y-2);
		sweep(x-2,y+2);
		sweep(x-2,y);
	    }
	    if(status(gr,gc)==8)
	    {
		sweep(x,y-2);
		sweep(x,y+2);
		sweep(x-2,y-2);
		sweep(x-2,y);
		sweep(x-2,y+2);
		sweep(x+2,y-2);
		sweep(x+2,y);
		sweep(x+2,y+2);
	    }
		}
    }
}
void game::display(int k=0)
{

    int x,y;
    if(k==0)
    {
      x=wherex();
      y=wherey();
    }
    clrscr();
    int r=2*y1+1,c=2*x1+1;
    for(int i=0; i<r; i++)
    {
	for(int j=0; j<c; j++)
	{
	    gotoxy(u+j,t+i);
	    cout<<board[i][j];
	}
    }
    timer=(clock()-watch)/CLK_TCK;
    gotoxy(1,1);
    cout<<"MINES:"<<mine<<"\tFLAGS KEPT:"<<flagcounter<<"\tTIME ELAPSED:"<<timer;
    if(k==0)
    gotoxy(x,y);
    else gotoxy(u+1,t+1);
}
int menu()
{
    clrscr();
    gotoxy(35,2);
    cprintf("MineSweePeR");
    gotoxy(38,4);
    cprintf("Menu");
    cout<<"\n[0]How To Play\n[1]Play Now!\n[2]Highscore!\n[3]Exit!\n";
    int choice=0;
    cin>>choice;
    if(choice>3&&choice<1)
	choice=menu();
    clrscr();
    return choice;
}
void game::move(int k=0)
{
    char key,control=0;
    while(control==0)
    {
		while(kbhit())
	{
	    key=getch();
	    if(key==72)
			{

		if(wherey()>t+1)//up
		gotoxy(wherex(),wherey()-2);
		else
		gotoxy(wherex(),t+(y1*2)-1);
			}
	    if(key==80)
	       {
		     if(wherey()<t+(y1*2)-1)//down
		 gotoxy(wherex(),wherey()+2);
		 else gotoxy(wherex(),t+1);
	       }
	    if(key==75)
			{

			    if(wherex()>u+1)//left
		gotoxy(wherex()-2,wherey());
		else gotoxy(u+(x1*2)-1,wherey());
			}
	    if(key==77)
			{

			     if(wherex()<u+(x1*2)-1)//right
		 gotoxy(wherex()+2,wherey());
		 else gotoxy(u+1,wherey());
			}
	    if(key==' '&&k==1)
	    {
		boardinit(wherex(),wherey());
		control=1;
	    }
	    if(key==' '&&k==0&&board[wherey()-t][wherex()-u]==char(254))
	    {
			sweep(wherex(),wherey());
			display(0);
			control=1;
	    }
	    if(key=='x'&&k==0)
	    {
		if(board[(wherey()-t)][(wherex()-u)]==char(177)&&flagcounter>0)
		{
		 board[(wherey()-t)][(wherex()-u)]=char(254);
		 flagcounter--;display(0);
		 control=1;
		 }
	    }
	    if(key=='z'&&k==0)
	    {
			if(board[(wherey()-t)][(wherex()-u)]==char(254)&&flagcounter<mine)
		    {
			board[(wherey()-t)][(wherex()-u)]=char(177);
			flagcounter++;
			display(0);
			control=1;
		    }
	    }
	}
    }
    wincheck();
    timer=(clock()-watch);
}
void game::wincheck()
{
	int retkey=0;
	int counter=0;
	for(int i=0;i<y1;i++)
	{
		for(int j=0;j<x1;j++)
		{
			if(board[i*2+1][j*2+1]==char(15))
			retkey=-1;
			if(board[i*2+1][j*2+1]==char(254)||board[i*2+1][j*2+1]==char(177))
			counter++;
		}
	}
	if(counter==mine&&retkey!=-1)
	gamestat=1;
	else gamestat=retkey;
}

void welcom(){
clrscr();
const int xpos=11;
const int ypos=8;
int c1=1,c2=2,c3=3,c4=4,c5=5,c6=6,c7=8;
gotoxy(xpos,ypos);
gotoxy(xpos,wherey()+1);cprintf("\n/////////////////////////////////////////////////////////////");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("            ");cprintf("       ");cprintf("       ");cprintf("       ");cprintf("        ");cprintf("          ");cprintf("      ");cprintf("//");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  11    11");cprintf("  11111");cprintf("  11   ");cprintf("  11111");cprintf("  111111");cprintf("  111  111");cprintf(" 11111");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  11    11");cprintf("  11   ");cprintf("  11   ");cprintf("  11   ");cprintf("  11  11");cprintf("  111  111");cprintf(" 11   ");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  11    11");cprintf("  11   ");cprintf("  11   ");cprintf("  11   ");cprintf("  11  11");cprintf("  11 11 11");cprintf(" 11   ");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  11    11");cprintf("  11111");cprintf("  11   ");cprintf("  11   ");cprintf("  11  11");cprintf("  11    11");cprintf(" 11111");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  11 11 11");cprintf("  11   ");cprintf("  11   ");cprintf("  11   ");cprintf("  11  11");cprintf("  11    11");cprintf(" 11   ");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  111  111");cprintf("  11   ");cprintf("  11   ");cprintf("  11   ");cprintf("  11  11");cprintf("  11    11");cprintf(" 11   ");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("  111  111");cprintf("  11111");cprintf("  11111");cprintf("  11111");cprintf("  111111");cprintf("  11    11");cprintf(" 11111");cprintf("  //");
gotoxy(xpos,wherey()+1);cprintf("\n//");cprintf("                                                         //");
gotoxy(xpos,wherey()+1);cprintf("\n/////////////////////////////////////////////////////////////");
gotoxy(xpos,wherey()+1);cprintf("\n//                                                         //");
gotoxy(xpos,wherey()+1);cprintf("\n//          ");cprintf("      PRESS ANY KEY TO CONTINUE    ");cprintf("            //");
gotoxy(xpos,wherey()+1);cprintf("\n//                                                         //");
gotoxy(xpos,wherey()+1);cprintf("\n/////////////////////////////////////////////////////////////");
getch();
system("COLOR 2");
}
void highscore(player p)
{
if(p.score!=0)
{
player temp;
player p1[10];
int token=0;
ifstream high("highscore.sys",ios::binary|ios::in);
for(int i=0;i<10;i++)
{
p1[i].score=0;
high.read((char*)&p1[i],sizeof(player));
}
high.close();
for(int j=0;j<10;j++)
{
if(p.score>=p1[j].score&&p.score<p1[j].score)
token=j;
}
temp=p1[token];
p1[token]=p;
player temp1;
for(int k=token+1;k<10;k++)
{
temp1=p1[k];
p1[k]=temp;
temp=temp1;
}
ofstream hi("highscore.sys",ios::binary|ios::out);
for(int l=0;l<10;l++)
{
hi.write((char*)&p1[l],sizeof(player));
}
hi.close();
}
player p1[10];
ifstream high("highscore.sys",ios::binary|ios::out);
for(int i=0;i<10;i++)
high.read((char*)&p1[i],sizeof(player));
gotoxy(1,1);cprintf("PLAYER NAME");gotoxy(20,1);cprintf("SCORE");gotoxy(29,1);cprintf("TIME");

for(int k=0;k<10;k++)
{
gotoxy(1,k+2);puts(p1[k].name);gotoxy(20,k+2);cout<<p1[k].score;gotoxy(29,k+2);cout<<p1[k].time;
}
getch();
}

using namespace std;


int main()
{
{
    player pl[10];
	for(int pk=0;pk<10;pk++)
    {
    	strcpy(pl[pk].name,"no_one");
    	pl[pk].score=0;
    	pl[pk].time=0;
    }
    ofstream initial("highscore.sys",ios::binary);
    for(int pj=0;pj<10;pj++)
    initial.write((char*)&pl[pj],sizeof(player));
    initial.close();
}
    clrscr();
    welcom();
    clrscr();
    player p={"",0,0};
    int chi=menu();
    while(chi!=3)
    {
	clrscr();

	if(chi==2)
	highscore(p);
	else if(chi==1)
	{
	    clrscr();
	    int mode,n=1;
	    cout<<"Enter the mode:\n[1]easy   [2]medium   [3]hard\n";
	    cin>>mode;
	    if(mode>4)
	    mode=3;
	    if (mode<1)
	    mode=1;
	    game boardsweeper(mode);
	    boardsweeper.move(1);
	    while(n==1)
	    {
		boardsweeper.move();
		if(boardsweeper.gamestat!=0)
		{
		   n=0;
		}
	    }
	    getch();
	    clrscr();
	    if(boardsweeper.gamestat==1)
	    {
	    cout<<"              \n !!!!!!          YOU WIN            !!!!!!\n";
	    cout<<"\n\n enter player name:";
	    gets(p.name);
	    p.time=boardsweeper.timer/1000;
	    p.score=mode*10000-p.time;
	    if(p.score<0)
	    p.score=1;
	    cout<<"\nscore:"<<p.score<<"\ntime:"<<p.time;
	    getch();
	    clrscr();
	    highscore(p);
	    }
	    else
		{
		cout<<"                   !!!!!!        YOU Lose          !!!!!!!";
		getch();
		clrscr();
		highscore(p);
		}
	}
	else if(chi==0)
	{
		clrscr();
		gotoxy(12,1);cprintf("HOW TO PLAY\n");
		gotoxy(4,3);cprintf("The rules in Minesweeper are simple:");
        gotoxy(4,4);cprintf("Uncover a mine, and the game ends. Uncover an empty square,");
        gotoxy(4,5);cprintf(" and you keep playing.Uncover a number, and it tells you ");
	    gotoxy(4,6);cprintf("how many mines lay hidden in the eight surrounding squares");
	    gotoxy(4,7);cprintf("-information you use to deduce which nearby squares are safe to click.");
	    gotoxy(12,9);cprintf("HOW TO MOVE");
	    gotoxy(4,11);cprintf("Move with UP,DOWN,LEFT,RIGHT arrow keys");
	    gotoxy(4,12);cprintf("Flag a square with 'z'.Unflag a aquare with 'x'.");
        gotoxy(4,13);cprintf("Uncover a square with _(space).");
	    gotoxy(9,15);cprintf("Press any key to go to Menu");
	    getch();
	    system("color 2");
	}
	chi=menu();
    }
	getch();
	return 0;
}
