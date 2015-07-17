

#include<graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define RIGHT_KEY 19712
#define ENTER_KEY 7181
#define ESCAPE_KEY 283
#define BLACK 24
int maxx,maxy;
int i,j,w,H,w2,P,i2;
void Ellipse(void);
void Computer(void);
void Computer2(void);
int Menu(int NoButt,char *menu[]);
char * menu1[] = { "Send" ,"View","Exit" };
char * menu2[] = { "Connect" ,"Exit" };
char str[10];

int main(void)
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics mode */
	initgraph(&gdriver, &gmode, "d:\\apps\\borlandc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}
	cleardevice();
 setbkcolor(3) ;
	maxx = getmaxx()+20;
	maxy = getmaxy()+20;
	setlinestyle(SOLID_LINE, 0, 2);
	//line(maxx/2-35, (maxy/10)+40, (maxx/2)+60, (maxy/10)+40);
	//line(5, 5, 20, 10);
	rectangle(maxx/8,maxy/8,7*maxx/8,7*maxy/8);

	setfillstyle(SOLID_FILL,24);
	bar(maxx/8-1,maxy/8-2,7*maxx/8,maxy/8);
	bar(maxx/8-1,maxy/8-2,maxx/8,7*maxy/8+1);
	bar(7*maxx/8+1,maxy/8-2,7*maxx/8,7*maxy/8+1);
	bar(maxx/8-1,7*maxy/8,7*maxx/8,7*maxy/8+1);

	//setfillstyle(SOLID_FILL,LIGHTCYAN);
	setfillstyle(SOLID_FILL,WHITE);               //fILLING THE INNER WINDOW
	bar(maxx/8,maxy/8,7*maxx/8,7*maxy/8);

	setfillstyle(SOLID_FILL,BLUE);
	bar(maxx/8+1,maxy/8-2,7*maxx/8-1,maxy/8+16);     //TITLE BAR
	setfillstyle(SOLID_FILL,WHITE);
	bar(maxx/8-1,maxy/8-1,7*maxx/8,maxy/8-.8);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	settextstyle(SMALL_FONT, HORIZ_DIR, 6);
	setcolor(WHITE);
	outtextxy(maxx/8+2, maxy/8+4, "Parallel Processing Using Distributed Processors");

	//menu[] = { "Send" ,"View","Exit" };
	P = Menu(2,menu2);
	outtextxy(maxx/2,maxy/2,itoa(P,str,10));
	if ( P+1==1)
	{ Computer();
	getch();

	}
       Computer2();
	getch();
	exit(1);
	P = Menu(3,menu1 );
	outtextxy(maxx/2,maxy/2,itoa(P,str,10));
	getch();


	//closegraph();
	return 0;
}

 int Menu(int NoButt,char *menu[])
 {
	#define BUTTON_COLOR  LIGHTCYAN
	setcolor(BLACK);
	for ( i=1;i<NoButt+1;i++)
	{
		//i=bioskey();
		w =(1.5*i)*maxx/8;
		setfillstyle(SOLID_FILL,WHITE);
		bar(w+2,5.975*maxy/8,w+2+maxx/8,6.5*maxy/8);   //Erase Previous Back Light
		setfillstyle(SOLID_FILL,BLACK);
		if (i>1)
		bar(w+2,5.975*maxy/8,w+2+maxx/8,6.5*maxy/8);   //Back Light
		setfillstyle(SOLID_FILL,BUTTON_COLOR);
		bar(w,6*maxy/8,w+maxx/8,6.5*maxy/8);
		setlinestyle(SOLID_LINE,1,1);
		rectangle(w,6*maxy/8,w+maxx/8,6.5*maxy/8);
		if ( i==1)
		{ //setcolor(BLUE);
			setlinestyle(DOTTED_LINE,1,2);
			rectangle(w+5,6*maxy/8+5,w+maxx/8-5,6.5*maxy/8-5);
		}
	}
	setcolor(BLACK);
	settextjustify(LEFT_TEXT, LEFT_TEXT);
	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	w=0;
	for ( i=1;i<NoButt+1;i++)
	{
		w =(1.5*i)*maxx/8;
		outtextxy(w+maxx/85*(i-1)+10,6.3*maxy/8,menu[i-1]);
	}

		H=0;
	i2=2;
    for(;;)
    {
	j=bioskey(0);
	// if (j==RIGHT_KEY) H=1;
	if (i2==NoButt+1) i2=1;
		 //	j=bioskey(0);
		 if (j==RIGHT_KEY) { H=1;   P =i2;}
			if (j==ENTER_KEY) { H=99;}
	if (  H != 99 )
		for (i=1;i<NoButt+1;i++)
	 {
		w =(1.5*i)*maxx/8;
		if ( ( H==1) && (P==i))
		{
			setfillstyle(SOLID_FILL,WHITE);
			bar(w+2,5.975*maxy/8,w+2+maxx/8,6.5*maxy/8);   //Back Light
		}
		else
		{

			setfillstyle(SOLID_FILL,BLACK);
			//bar(w+3,5.95*maxy/8,w+3+maxx/8,6.5*maxy/8);   //Back Light
			bar(w+2,5.975*maxy/8,w+2+maxx/8,6.5*maxy/8);   //Back Light
		}
		setlinestyle(SOLID_LINE,1,1);
		setfillstyle(SOLID_FILL,BUTTON_COLOR);
		bar(w,6*maxy/8,w+maxx/8,6.5*maxy/8);
		rectangle(w,6*maxy/8,w+maxx/8,6.5*maxy/8);
		if ( ( H==1) && (P==i))
		{
			setlinestyle(DOTTED_LINE,1,2);
			rectangle(w+5,6*maxy/8+5,w+maxx/8-5,6.5*maxy/8-5);

		}
		w2 =(1.5*i)*maxx/8;
		setcolor(BLACK);
		outtextxy(w2+maxx/85*(i-1)+10,6.3*maxy/8,menu[i-1]);
	} //END OF FOR
	else
	 return(P);
		H=0;
	 i2++;

  }
  }
  void Ellipse(void)
  {
	setcolor(RED);
	setfillstyle(SOLID_FILL,BLUE);
	fillellipse(6.5*maxx/8,6.3*maxy/8,17,17);
	setfillstyle(SOLID_FILL,RED);
	fillellipse(6.5*maxx/8,6.3*maxy/8,15,15);

	setfillstyle(SOLID_FILL,BLUE);
	fillellipse(6*maxx/8,6.3*maxy/8,17,17);
	setfillstyle(SOLID_FILL,GREEN);
	fillellipse(6*maxx/8,6.3*maxy/8,15,15);
   }
 void Computer(void)
 {

       setcolor(BLACK);
       setfillstyle(SOLID_FILL,8);
       bar(1.5*maxx/8,3*maxy/8,2.7*maxx/8,4.4*maxy/8); //Comp Main
	bar(1.5*maxx/8,4.6*maxy/8,2.7*maxx/8,5*maxy/8); //Comp Join
	setfillstyle(SOLID_FILL,8);
	bar(1.95*maxx/8,4.4*maxy/8,2.3*maxx/8,4.6*maxy/8); //Comp Base
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(1.6*maxx/8,3.2*maxy/8,2.6*maxx/8,4.2*maxy/8); //Comp Inside

  }
 void Computer2(void)
 {
	void far *buf[4];
	unsigned size;
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,8);
	bar(5*maxx/8,3*maxy/8,2.95*maxx/4,4*maxy/8); //Comp Main
	bar(10.5*maxx/16,4*maxy/8,11.2*maxx/16,4.3*maxy/8); //Comp Join
	setfillstyle(SOLID_FILL,8);
	bar(5*maxx/8,4.15*maxy/8,2.95*maxx/4,4.45*maxy/8); //Comp Base
	setfillstyle(SOLID_FILL,LIGHTBLUE);
	bar(5.1*maxx/8,3.15*maxy/8,2.89*maxx/4,3.85*maxy/8); //Comp Inside
	size = imagesize(5*maxx/8,3*maxy/8, 2.95*maxx/4,4.45*maxy/8); /* get byte size of image */
	buf[0] = farmalloc(size);
	 getimage(5*maxx/8,3*maxy/8, 2.95*maxx/4,4.45*maxy/8, buf[0]);
  }






