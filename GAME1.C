#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<alloc.h>
#include<stdlib.h>
void begin();

void *ball;

void image1();

void gameover(char [],int);

void main()

{
   int gd=DETECT,gm;
   int c;
   int i=100,a=0;
   int l=150,t=150;
   int x=1,y=1;
   int s=0,d=0;
   int xstep=1,ystep=1;
   float e=0;
   char ch,score[9];
   int r;
   initgraph(&gd,&gm,"c:\\turboc3\\bgi");

   begin();

   image1();

   while(1)
   {
     c=0;

     while(c<=5){

     setcolor(BROWN);
     outtextxy(452,450,"PRESS ESC TO EXIT");
     setfillstyle(SOLID_FILL,BROWN);
//for moving solid at the four sides//
     bar3d(i,50,i+80,60,10,10);//3d bar position left,top,right,bottom//
     bar3d(50,i,60,i+80,10,10);
     bar3d(i,430,i+80,440,10,10);
     bar3d(430,i,440,i+80,10,10);
     setcolor(RED);
     setfillstyle(SOLID_FILL,RED);
//solid for left upper corner//      //corner bar positions//
     bar3d(50,50,60,100,10,10);
     bar3d(50,50,100,60,10,10);
//solid for left bottom corner//
     bar3d(50,390,60,440,10,10);
     bar3d(50,430,100,440,10,10);
//solid for right upper corner//
     bar3d(430,50,440,100,10,10);
     bar3d(390,50,440,60,10,10);
//solid for right bottom corner//
     bar3d(430,390,440,440,10,10);
     bar3d(390,430,440,440,10,10);
     if(kbhit())
     {
	ch=getch();
	if(ch=='d' || ch == 'D'){
	a=6;     //on pressing d the position increases by 6 units to the right and up//
	}
	if(ch=='a'||ch=='A')// on pressing a, to the left and down//
	{
	a=-6;
	}
	if(ch==27)exit(0); //esc to exit//
     }
     if(i<=getmaxx()-535)
     {
     a=1; //bar  moves right automatically when it reaches extreme lefr//
     }
     if(i>=getmaxx()-335)
     {
     a=-1;       //bar moves to the left automatically when it reaches extreme right//
     }
     i=i+a;   //transferring of position of 3d bar and ball//
     c++;       //frame delete and create delay//
     putimage(l,t,ball,COPY_PUT);
     e=e+0.001;
     if((l>=getmaxx()-220//if ball reaches to th right,it returns to left//
     ||l<=70) //if ball reaches to the left, return to right//
     &&
     ((t>=i-5&&t<=100+i+5)//rebound when touches the bar 3d//
     ||(t>=70&&t<=102) //rebound when touches the bar 3d//
     ||(t>=428&&t<=462)))
     {
	x*=-1;
	sound(100);  //plays the sound//
	s=0;
	xstep=x*(random(5)+2); //returns to left with a random velocity//
	ystep=y*(random(4)+1); //random returns a number between 0 to the arguiment - 1//
	if(l<=70)
	l=70;
	else
	l=getmaxx()-220;
	d=d+1;
     }
     if((t>=getmaxy()-72||t<=70)&&((l>=i-5&&l<=100+i+5)||(l>=70&&l<=102)||(l>=388&&l<=422)))
     {
	y*=-1;
	sound(100);
	s=0;
	ystep=y*(random(5)+2);
	xstep=x*(random(4)+1);
	if(t<=70)t=70;
	else
	t=getmaxy()-72;
	d=d+1;
     }
     sprintf(score,"YOUR SCORE:%d",d);  //sends formatted output as string//
     settextstyle(COMPLEX_FONT,HORIZ_DIR,1);
     setcolor(WHITE);
     outtextxy(0,0,score);//score display in the gameplay screen//
     l+=x+xstep+0.5;  //changes the position of the bitmap image//
     t+=y+ystep+0.5; //also changes the position of image//
     s++;
     if(s==4)
     {
	nosound();       //sets the buzzing time of the speaker//
     }
    }
    cleardevice();      //clears graphics screen//

if(l<=65||t<=65||l>=getmaxx()-215||t>getmaxy()-68){
gameover(score,d);//gameover when ball goes out of the boundary//
}
}
}


void begin()   //THE LOADING SCREEN//
{
   int i;
   float load=0;
   image1();
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,8);
   outtextxy(100,50,"WELCOME");
   outtextxy(120,150,"TO THE");
   sleep(3);
   cleardevice();
   setcolor(YELLOW);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,10);
   outtextxy(120,100,"BOOSH");
   settextstyle(DEFAULT_FONT,HORIZ_DIR,1);
   outtextxy(220,380,"PLEASE WAIT WHILE LOADING");
   rectangle(5,390,635,422);
   for(i=10;i<=610;i++)              //Loading bar movement//
   {
     putimage(i,400,ball,COPY_PUT);
     load=load+0.02;
     delay(load);
   }

}


void image1()
{
   setcolor(WHITE);
   setfillstyle(SOLID_FILL,RED);
   fillellipse(5,5,5,5);
   ball=malloc(imagesize(0,0,10,10));
   getimage(0,0,10,10,ball);

}




void gameover(char score[9],int d)
{
   FILE *fp;
   char cha;
   int hs;
   int p;
   char high[10];
   setbkcolor(BLACK);
   fp=fopen("high.txt","r"); //reads the value of high score that is stored since the creation of file//
   setcolor(GREEN);
   setfillstyle(SOLID_FILL,YELLOW);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,6);
   outtextxy(100,80,"GAME OVER");
   setcolor(YELLOW);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
   outtextxy(170,300,score);
   fscanf(fp,"%d",&p);
   fclose(fp);
   hs=p;
   if(d>hs)
   {
   hs=d;
   fp=fopen("high.txt","w"); //writes the high score to the file//
   fprintf(fp,"%d",hs);
   fclose(fp);
   }
   sprintf(high,"HIGH SCORE:%d",hs);   //prints formatted output as string//
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
   outtextxy(220,350,high);
   sleep(3);
   exit(0);
   }
