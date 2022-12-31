#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <math.h>
#include <windows.h>
#include <Windows.h>

using namespace std;

HDC hDC;
HANDLE StdOut;
WORD COLOR;
COORD BGN, POS;

const int RED RGB(255, 0, 0);
const int BLUE RGB(0, 0, 255);
const int GREEN RGB(0, 255, 0);
const int YELLOW RGB(255, 255, 0);
const int WHITE RGB(255, 255, 255);
const int BLACK RGB(0, 0, 0);
const int BACKGROUND RGB(12, 12, 12);
const int PINK RGB(255, 0, 127);

int mov;
int movx;

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF);
BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT);
BOOL PlotLine(HDC hDC, COORD BGN, COORD END);
BOOL PlotRect(HDC hDC, COORD BGN, COORD END);
BOOL PlotCirc(HDC hDC, COORD BGN, COORD END);
BOOL PlotTriangle(HDC hDC, POINT p[]);
COORD setCordScale(COORD POS, RECT pRECT);
void gotoxy(int x, int y);
void rectangle(int x1, int y1, int x2, int y2, int fill, int layout);
void arrow(int x1, int y1, int x2, int y2, int length, int width, int fill, int layout);
void displayText(int x, int y, char s[], int color, int font);
void convertNumToString(int n, char s[]);
void line(int x1, int y1, int x2, int y2, int color);
void setfontcolor(int color);
void emptyQueue(int x, int y, int size, int color);
void clrscr(int x1, int y1, int x2, int y2);
int checkValueError();

struct BOXNUMBER
{
	int x, y;
	int num;
	bool isVer;
	bool nextArrow;
	bool preArrow;
	BOXNUMBER* next;
	BOXNUMBER* pre;

	void show()
	{
		char s[100] = "0";
		convertNumToString(num, s);
		if (isVer)
		{
			int x1 = x, x2 = x + 30;
			int x3 = x2 + 30, x4 = x3 + 30;
			int y1 = y, y2 = y + 30;
			int y3 = y1, y4 = y2;
			rectangle(x1, y1, x2, y2, WHITE, BLUE);
			rectangle(x3, y3, x4, y4, WHITE, BLUE);
			line(x2 - 1, y1, x3 - 2, y1, BLUE);
			line(x2 - 1, y2 - 1, x3 - 2, y2 - 1, BLUE);
			int X = x1 + 37 - strlen(s) * 4;
			displayText(X, y1, s, YELLOW, 1);
		}
		else
		{
			int x1 = x, x2 = x + 30;
			int x3 = x1, x4 = x2;
			int y1 = y, y2 = y + 30;
			int y3 = y2 + 30, y4 = y3 + 30;
			rectangle(x1, y1, x2, y2, WHITE, BLUE);
			rectangle(x3, y3, x4, y4, WHITE, BLUE);
			line(x1, y2, x1, y3 - 2, BLUE);
			line(x2 - 1, y2, x2 - 1, y3 - 2, BLUE);
			int X = x1 + 7 - strlen(s) * 4;
			displayText(X, y1 + 30, s, YELLOW, 1);
		}
	}

	void showNextArrow(int delay)
	{
		if (nextArrow)
			arrow(x + 92, y + 10, next->x - 2, next->y + 10, 12, 6, RED, RED);
		Sleep(delay);
	}

	void showPreArrow(int delay)
	{
		if (preArrow)
			arrow(x - 2, y + 20, pre->x + 92, pre->y + 20, 12, 6, GREEN, GREEN);
		Sleep(delay);
	}

	void showArrow()
	{
		showNextArrow(0);
		showPreArrow(0);
	}

	void clearNextArrow(int delay)
	{
		if (nextArrow)
			arrow(x + 92, y + 10, next->x - 2, next->y + 10, 14, 8, BACKGROUND, BACKGROUND);
		Sleep(delay);
	}
	void clearPreArrow(int delay)
	{
		if (preArrow)
			arrow(x - 2, y + 20, pre->x + 92, pre->y + 20, 14, 8, BACKGROUND, BACKGROUND);
		Sleep(delay);
	}
	void clearArrow()
	{
		clearNextArrow(0);
		clearPreArrow(0);
	}

	void clear()
	{
		int x1, x2, y1, y2;
		if (isVer)
			x1 = x - 1, x2 = x + 90, y1 = y + 29, y2 = y + 60;
		else
			x1 = x - 1, x2 = x + 30, y1 = y + 29, y2 = y + 120;
		clrscr(x1, y1, x2, y2);
	}

	void movex(int x, int delay)
	{
		int direction = 1;
		if (this->x > x)
			direction = -1;
		while (this->x != x)
		{
			clear();
			this->x += direction;
			show();
			Sleep(delay);
		}
	}

	void movey(int y, int delay)
	{
		int direction = 1;
		if (this->y > y)
			direction = -1;
		while (this->y != y)
		{
			clear();
			this->y += direction;
			show();
			Sleep(delay);
		}
	}
};

struct LINK
{
	int x, y;
	int suc;
	LINK* next = nullptr;

	void show(int color)
	{
		LINK* p = this;
		int X, Y;
		while (p != nullptr)
		{
			char s[10] = "0";
			convertNumToString(p->suc, s);
			X = p->x + movx + 9 - strlen(s) * 4;
			Y = p->y + movx + 3;
			arrow(p->x + 19, p->y - 40, p->x + 19, p->y - 1, 12, 6, YELLOW, YELLOW);
			rectangle(p->x, p->y, p->x + 40, p->y + 40, color, BLUE);
			rectangle(p->x, p->y + 39, p->x + 40, p->y + 70, color, BLUE);
			displayText(X, Y, s, BLACK, 2);
			if (p->next != nullptr)
			{
				p->next->x = x;
				p->next->y = Y + 108;
			}
			p = p->next;
		}
	}
};

struct PAIR
{
	int suc;
	int pre;
	int x = 300 + movx;
	int y = 5 + mov;

	void show(int delay)
	{
		char s[30] = " ";
		char Suc[5] = "0";
		convertNumToString(suc, Suc);
		char Pre[5] = "0";
		convertNumToString(pre, Pre);
		strcat(s, Pre);
		strcat(s, " < ");
		strcat(s, Suc);
		rectangle(x, y, strlen(s) * 11 + x, y + 35, WHITE, GREEN);
		displayText(x, y, s, RED, 2);
		Sleep(delay);
		
	}

	void clear()
	{
		clrscr(x + movx - 1, y + mov - 1, x + movx + 70, y + 35 + mov);
	}
};

struct TOPO_NODE
{
	int x, y;
	int data;
	int COUNT;
	LINK* top;
	void disPlayCount(int color)
	{
		char s[10] = "0";
		convertNumToString(data, s);
		int X = x + movx + 9 - strlen(s) * 4;
		int Y = y + movx - 33;
		rectangle(x, y, x + 40, y + 40, color, BLUE);
		rectangle(x, y + 39, x + 40, y + 70, color, BLUE);
		displayText(X, Y, s, WHITE, 2);
		strcpy(s, "0");
		convertNumToString(COUNT, s);
		Y = y + movx + 3;
		displayText(X, Y, s, BLACK, 2);
		Sleep(1000);
	}
	void displayTop()
	{
		top->x = x;
		top->y = y + 111;
		top->show(WHITE);
	}
	void showSelected(int times, int c1, int c2)
	{
		for (int i = 0; i < times; i++)
		{
			int color = (i % 2) ? c1 : c2;
			disPlayCount(color);
		}
	}
};

BOXNUMBER* createBoxNumber(int val, bool isVerBox, int x, int y);
BOXNUMBER* createBoxNumber(int x, int y);

void initgraph(void)
{
	system("cls");
	mov = 30;
	movx = 0;
	HWND hWnd = GetConsoleWindow();
    //RECT    pRECT= {0};
    //COORD   POS1  = {0};
    //COORD   BGN1  = setCordScale(POS1,pRECT);
    //GetWindowRect(hWnd,&pRECT);
    hDC = GetWindowDC(hWnd);		
	StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void changey(int value) { if (value>-1000 && value <1000) mov = (short)value; }
void changex(int value) { if (value>-1000 && value <1000) movx = (short)value; }
int getmaxx(void) { return 640; }
int getmaxy(void) { return 300; }

void setfontcolor(int color)
{
	if (color < 0) color = -color;
	if (color > 15) color %= 16;
	switch (color)
	{
		case 0: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED); COLOR = COMMON_LVB_REVERSE_VIDEO; break;
		case 1: COLOR = (FOREGROUND_BLUE); break;
		case 2: COLOR = (FOREGROUND_GREEN); break;
		case 3: COLOR = (FOREGROUND_RED); break;
		case 4: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN); break;
		case 5: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED); break;
		case 6: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED); break;
		case 7: COLOR = (FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
		case 8: COLOR = (FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case 9: COLOR = (FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 10: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case 11: COLOR = (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 12: COLOR = (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case 13: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);break;
		case 14: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO); break;
		case 15: COLOR = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | COMMON_LVB_REVERSE_VIDEO | FOREGROUND_INTENSITY);break;
	}
	SetConsoleTextAttribute(StdOut, COLOR);
}

void line(int x1,int y1,int x2,int y2, int color)
{
	HPEN pen = getPen(PS_SOLID, 2, color);
	BGN.X = x1+movx; 
	BGN.Y = y1+mov; 
	POS.X = x2+movx; 
	POS.Y = y2+mov; 
	SelectObject(hDC, pen);
	PlotLine(hDC, BGN, POS);
	DeleteObject(pen);
}


void putpixel(int x,int y, int color)
{
	line(x,y,x,y, color);
}

void circle(int x,int y, int radius, int fill, int layout)
{
	HPEN pen = getPen(PS_SOLID, 2, layout);
	HBRUSH brush = CreateSolidBrush(fill);
	BGN.X = x+movx-radius/2; 
	BGN.Y = y+mov-radius/2; 
	POS.X = x+movx+radius/2; 
	POS.Y = y+mov+radius/2; 
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);
	PlotCirc (hDC, BGN, POS);
	DeleteObject(pen);
	DeleteObject(brush);
}

void rectangle(int x1,int y1,int x2,int y2, int fill, int layout)
{
	HPEN pen = getPen(PS_SOLID, 2, layout);
	HBRUSH brush = CreateSolidBrush(fill);
	BGN.X = x1+movx; 
	BGN.Y = y1+mov; 
	POS.X = x2+movx; 
	POS.Y = y2+mov;
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);
	PlotRect(hDC, BGN, POS);
	DeleteObject(pen);
	DeleteObject(brush);
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int fill, int layout)
{
	HPEN pen = getPen(PS_SOLID, 1, layout);
	HBRUSH brush = CreateSolidBrush(fill);
	SelectObject(hDC, pen);
	SelectObject(hDC, brush);
	POINT p[3] = { x1 + movx, y1 + mov, x2 + movx, y2 + mov, x3 + movx, y3 + mov };
	PlotTriangle(hDC, p);
	DeleteObject(pen);
	DeleteObject(brush);
}

void arrow(int x1, int y1, int x2, int y2, int length, int width, int fill, int layout)
{
	double dx = x2 - x1, dy = y2 - y1;
	double len = sqrt(dx * dx + dy * dy);
	double ux = dx / len, uy = dy / len;
	double vx = -uy, vy = ux;
	int X1 = x2, Y1 = y2;
	int X2 = int(x2 - length * ux + width * 0.5 * vx + 0.5), Y2 = int(y2 - length * uy + width * 0.5 * vy + 0.5);
	int X3 = int(x2 - length * ux - width * 0.5 * vx + 0.5), Y3 = int(y2 - length * uy - width * 0.5 * vy + 0.5);
	line(x1, y1, x2, y2, fill);
	triangle(X2, Y2, X1, Y1, X3, Y3, fill, layout);
}

void displayText(int x, int y, char s[], int color, int font)
{
	RECT rect;
	HWND consoleHandle = GetConsoleWindow();
	HDC deviceContext = GetDC(consoleHandle);
	SetTextColor(deviceContext, color);
	SetBkMode(deviceContext, TRANSPARENT);
	rect.left = x;
	rect.top = y;
	wchar_t wtext[100];
	mbstowcs(wtext, s, strlen(s) + 1);
	LPCWSTR message = wtext;
	HFONT f;
	if (font == 1)
		f = HFONT(GetStockObject(OEM_FIXED_FONT));
	else
		f = CreateFont(20, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Rockwell"));
	SelectObject(deviceContext, f);
	DrawText(deviceContext, message, -1, &rect, DT_BOTTOM);
	ReleaseDC(consoleHandle, deviceContext);
	DeleteObject(f);
	DeleteObject(&rect);
	DeleteObject(deviceContext);
}

void emptyStack(int x, int y, int size, int color)
{
	int x1 = x - 5, x2 = x1 + 100;
	int y1 = y, y2 = y1 + 35 * size;
	line(x1, y1, x1, y2, color);
	line(x2, y1, x2, y2, color);
	line(x1, y2, x2, y2, color);
}

void emptyQueue(int x, int y, int size, int color)
{
	int x1 = x, x2 = x1 + 30 * size;
	int y1 = y - 2, y2 = y1 + 90 + 3;
	line(x1, y1, x2, y1, color);
	line(x1, y2, x2, y2, color);
}

void gotoxy(int x, int y)
{
	BGN.X = x / 20; 
	BGN.Y = y / 20; 
    SetConsoleCursorPosition(StdOut, BGN);
}

void clearRange(int x1, int y1) {

	DWORD written;
	COORD topLeft = { x1, y1 / 20 };
	DWORD range = -1;
	FillConsoleOutputCharacterA(StdOut, ' ', range, topLeft, &written);
	SetConsoleCursorPosition(StdOut, topLeft);
}

void clrscr(int x1, int y1, int x2, int y2)
{
	HBRUSH pen = CreateSolidBrush(BACKGROUND);
	RECT rect;
	rect.left = x1;
	rect.right = x2;
	rect.top = y1;
	rect.bottom = y2;
	FillRect(hDC, &rect, pen);
	DeleteObject(&rect);
	DeleteObject(pen);
}

HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
{
    return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
}
 
BOOL SetPoint(HDC hDC, HPEN hPen, COORD PNT)
{
        EXTLOGPEN pINFO;
        GetObject(hPen,sizeof(EXTLOGPEN),&pINFO);
        SelectObject(hDC,hPen);
        return Ellipse
        (
            hDC,
            PNT.X - pINFO.elpWidth,
            PNT.Y + pINFO.elpWidth, 
            PNT.X + pINFO.elpWidth,
            PNT.Y - pINFO.elpWidth
        );
}
 
BOOL PlotLine(HDC hDC, COORD BGN, COORD END)
{
    MoveToEx(hDC,BGN.X,BGN.Y,NULL);
    return LineTo(hDC,END.X,END.Y);
}
 
BOOL PlotRect(HDC hDC, COORD BGN, COORD END)
{
    return Rectangle(hDC,BGN.X, BGN.Y, END.X, END.Y);
}
 
BOOL  PlotCirc(HDC hDC, COORD BGN, COORD END)
{
    return Ellipse(hDC,BGN.X, BGN.Y, END.X, END.Y);
}

BOOL PlotTriangle(HDC hDC, POINT p[])
{
	return Polygon(hDC, p, 3);
}

COORD setCordScale(COORD POS, RECT pRECT)
{
        if(POS.X == 0)
                POS.X = 1;
        if(POS.Y == 0)
                POS.Y = 1;
 
        int nROWS = 25;
        int nCOLS = 80;
 
        double CX = (pRECT.right - pRECT.left)/nCOLS;
        double CY = (pRECT.bottom - pRECT.top)/nROWS;
 
        //При текстовом режиме(text mode) экран  делится  на  ячейки
		//(80  или 40 колонок в ширину и 25 строк в высоту)
        POS.X *= CX;
        POS.Y *= CY;
 
        int xBORDER = GetSystemMetrics(SM_CXBORDER);//Ширина границы окна
        int yBORDER = GetSystemMetrics(SM_CYMENU);  //Высота заголовка окна ~= высоте строк меню
        int xDRAG = GetSystemMetrics(SM_CXDRAG);  //Число пикселей на гориз дрожение мыши
        int yDRAG = GetSystemMetrics(SM_CYDRAG);  //Число пикселей на вертик дрожение мыши
 
        POS.X += xBORDER + xDRAG;//Ширина границы окна + число пикселей на дрожение мыши
        POS.Y += yBORDER + yDRAG;
        return POS;
}

void convertNumToString(int n, char s[])
{
	bool flag = false;
	int i = 0;
	strcpy(s, "0");
	if (n < 0)
		flag = true;
	n = abs(n);
	while (n > 0)
	{
		s[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	if (flag)
		s[i++] = '-';
	_strrev(s);
}

BOXNUMBER* createBoxNumber(int val, bool isVerBox, int x, int y)
{
	BOXNUMBER* bNum = new BOXNUMBER;
	bNum->num = val;
	bNum->x = x;
	bNum->y = y;
	bNum->next = nullptr;
	bNum->pre = nullptr;
	bNum->isVer = isVerBox;
	bNum->show();
	return bNum;
}

BOXNUMBER* createBoxNumber(int x, int y)
{
	cout << "Enter the number: ";
	int val = checkValueError();
	BOXNUMBER* bNum = new BOXNUMBER;
	bNum->num = val;
	bNum->x = x;
	bNum->y = y;
	bNum->next = nullptr;
	bNum->pre = nullptr;
	bNum->isVer = true;
	bNum->nextArrow = false;
	bNum->preArrow = false;
	bNum->show();
	return bNum;
}

#endif


