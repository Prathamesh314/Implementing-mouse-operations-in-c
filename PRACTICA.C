#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <dos.h>

void main()
{
	union REGS regs, i, o;
	char array[50];
	int status, gd = DETECT, gm, button, x, y, ch = 1, choice, val, user;
	while (ch)
	{
		clrscr();
		printf("Enter 1 to check availability of mouse\nEnter 2 to Display mouse pointer in graphics mode\nEnter 3 to determine which mouse button is clicked\nEnter 4 to locate current position of mouse pointer\nEnter your choice:- ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			i.x.ax = 0;
			int86(0X33, &i, &o);
			val = (o.x.ax);
			if (val == 0)
			{
				printf("Mouse is not available...\n");
			}
			else
			{
				printf("Mouse is available...\n");
			}
			break;

		case 2:
			initgraph(&gd, &gm, "C:\\TC\\BGI");
			i.x.ax = 0;
			int86(0X33, &i, &o);
			if (val == 0)
			{
				printf("Mouse is not available...\n");
			}
			else
			{
				i.x.ax = 1;
				int86(0X33, &i, &o);
				getch();
			}
			break;
		case 3:
			initgraph(&gd, &gm, "C;\\TC\\BGI");
			settextstyle(DEFAULT_FONT, 0, 2);
			i.x.ax = 0;
			int86(0X33, &i, &o);
			val = (o.x.ax);
			if (val == 0)
			{
				printf("Mouse support not available...\n");
			}
			else
			{
				i.x.ax = 1;
				int86(0X33, &i, &o);
				getch();
				i.x.ax = 3;
				int86(0X33, &i, &o);
				button = o.x.ax;
				x = o.x.cx;
				y = o.x.dx;
				while (!kbhit())
				{
					i.x.ax = 3;
					int86(0X33, &i, &o);
					button = o.x.cx;
					x = o.x.cx;
					y = o.x.dx;
					if (button == 1)
					{
						button = -1;
						cleardevice();
						sprintf(array, "Left mouse button is clicked...\nrow:-%d col:-%d\n", x, y);
						outtext(array);
					}
					else
					{
						button = -1;
						cleardevice();
						sprintf(array, "Right mouse button is clicke....\nrow;-%d col:-%d\n", x, y);
						outtext(array);
					}
				}
			}
			break;
		case 4:
			regs.h.ah = 3;
			regs.h.bh = 0;
			int86(0X33, &regs, &regs);
			x = regs.h.dl;
			y = regs.h.dh;
			printf("Cursor position :- %d row, %d col\n", x, y);
			break;
		default:
			printf("Invalid number....\n");
			break;
		}
		printf("Do you want to continue [1/0] :- ");
		scanf("%d", &user);
		if (user == 0)
		{
			break;
		}
	}
}