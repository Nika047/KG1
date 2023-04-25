#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"

using namespace std;

class Line
{
public:
	int x1, y1, x2, y2;

	Line(int x1, int y1, int x2, int y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

private:

};

Line line1(1, 1, 0, 0);
Line line2(1, 1, 0, 0);
Line *current = &line1;

void drawing()
{
	setactivepage(0);
	clearviewport();
	setcolor(15);

	moveto(line1.x1, line1.y1);
	lineto(line1.x2, line1.y2);

	int x1 = line2.x1, y1 = line2.y1, x2 = line2.x2, y2 = line2.y2;
	int dx = abs(x2 - x1), dy = abs(y2 - y1), x0, y0;
	int i1 = dx - dy;

	if (x1 < x2) x0 = 1;
	else x0 = -1;
	if (y1 < y2) y0 = 1;
	else y0 = -1;

	putpixel(x2, y2, 9);

	while (x1 != x2 || y1 != y2)
	{
		putpixel(x1, y1, 9);
		int i2 = i1 * 2;

		if (i2 > -dy)
			(i1 -= dy) & (x1 += x0);
		if (i2 < dx)
			(i1 += dx) & (y1 += y0);
	}

	setvisualpage(0);
}

void input()
{
	char c = toupper(getch());

	if (c == '9')
	{
		int x = ceil((current->x2 - current->x1) * cos(-0.0176) - (current->y2 - current->y1) * sin(-0.0176));
		int y = ceil((current->x2 - current->x1) * sin(-0.0176) + (current->y2 - current->y1) * cos(-0.0176));
		current->x2 = current->x1 + x;
		current->y2 = current->y1 + y;
	}

	else if (c == '0')
	{
		int x = ceil((current->x2 - current->x1) * cos(0.0176) - (current->y2 - current->y1) * sin(0.0176));
		int y = ceil((current->x2 - current->x1) * sin(0.0176) + (current->y2 - current->y1) * cos(0.0176));
		current->x2 = current->x1 + x;
		current->y2 = current->y1 + y;
	}

	else if (c == KEY_UP)
	{
		current->y1 -= 10;
		current->y2 -= 10;
	}

	else if (c == KEY_DOWN)
	{
		current->y1 += 10;
		current->y2 += 10;
	}

	else if (c == KEY_LEFT)
	{
		current->x1 -= 10;
		current->x2 -= 10;
	}

	else if (c == KEY_RIGHT)
	{
		current->x1 += 10;
		current->x2 += 10;
	}

	else if (c == '-')
	{
		current->x2 = current->x1 + (current->x2 - current->x1) * 0.5;
		current->y2 = current->y1 + (current->y2 - current->y1) * 0.5;
	}

	else if (c == '+')
	{
		current->x2 = current->x1 + (current->x2 - current->x1) * 2;
		current->y2 = current->y1 + (current->y2 - current->y1) * 2;
	}

	else if (c == ' ')
	{
		if (current == &line1)
			current = &line2;
		else current = &line1;
	}

	drawing();
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initwindow(1000, 500);
	drawing();

	while (1)
		input();
}