#pragma once
#include <iostream>
#include "graphics.h"
#include "graphic_queue.h"

using namespace std;

void readData(int& n, PAIR array[]);
PAIR createPair();
void topoSort(int n, PAIR array[]);
int maxArray(int n, PAIR array[]);
void runTopo();
void showN(int N);
void showP();
void runTopo()
{
	int n;
	PAIR arr[100];
	readData(n, arr);
	system("cls");
	cin.ignore();
	cin.get();
	topoSort(n, arr);
}

void readData(int& n, PAIR array[])
{
	cout << "Enter the number of pairs: ";
	cin >> n;
	for (int i = 0; i < n; i++)
		array[i] = createPair();
}

PAIR createPair()
{
	PAIR p;
	cout << "Enter the value of j (j < k): ";
	cin >> p.pre;
	cout << "Enter the value of k: ";
	cin >> p.suc;
	return p;
}

void topoSort(int n, PAIR array[])
{
	int N = maxArray(n, array);
	GRAPHIC_QUEUE QLINK;
	TOPO_NODE nodes[100];
	int F;
	int xOut = 200, yOut = 800;
	int x = 100, y = 100;
	QLINK.init(800, 600, 8);
	char temp[10] = "COUNT[k]";
	displayText(0, 100, temp, WHITE, 2);
	strcpy(temp, " ");
	strcat(temp, "TOP[k]");
	displayText(0, 130, temp, WHITE, 2);

	for (int i = 1; i <= N; i++)
	{
		nodes[i].data = i;
		nodes[i].COUNT = 0;
		nodes[i].top = nullptr;
		nodes[i].x = x;
		nodes[i].y = y;
		nodes[i].disPlayCount(WHITE);
		x += 60;
	}

	showN(N);

	for (int i = 0; i < n; i++)
	{
		int j = array[i].pre;
		int k = array[i].suc;
		array[i].show(1000);
		nodes[k].showSelected(4, WHITE, RED);
		nodes[k].COUNT++;
		nodes[k].disPlayCount(WHITE);
		LINK* P = new LINK;
		P->suc = k;
		P->next = nodes[j].top;
		nodes[j].top = P;
		nodes[j].showSelected(2, WHITE, GREEN);
		nodes[j].displayTop();
		array[i].clear();
	}

	for (int i = 1; i <= N; i++)
	{
		if (nodes[i].COUNT == 0)
		{
			nodes[i].showSelected(4, WHITE, RED);
			BOXNUMBER* b = createBoxNumber(i, false, QLINK.x - 10, QLINK.y);
			QLINK.push(b);
		}
		else
			nodes[i].showSelected(2, WHITE, GREEN);
	}

	while (!QLINK.empty())
	{
		BOXNUMBER* p = QLINK.pop(QLINK.x + QLINK.maxSize * 30 + 10, QLINK.y);
		p->movey(yOut, 1);
		p->movex(xOut, 1);
		xOut += 50;
		int F = p->num;
		N--;
		showN(N);
		LINK* P = new LINK;
		P = nodes[F].top;
		while (P != nullptr)
		{
			P->show(PINK);
			nodes[P->suc].showSelected(4, WHITE, RED);
			nodes[P->suc].COUNT--;
			if (nodes[P->suc].COUNT == 0)
			{
				nodes[P->suc].showSelected(4, WHITE, YELLOW);
				BOXNUMBER* b = createBoxNumber(P->suc, false, QLINK.x - 10, QLINK.y);
				QLINK.push(b);
			}
			P->show(WHITE);
			P = P->next;
		}
	}

	if (N != 0)
	{
		char s[50] = "VIOLATION OF THE HYPOTHETIS OF PARTICAL ORDER!";
		displayText(1000, 180, s, WHITE, 2);
	}
	gotoxy(0, 900);
}

int maxArray(int n, PAIR array[])
{
	int m = 0;
	for (int i = 0; i < n; i++)
		m = max(max(m, array[i].pre), array[i].suc);
	return m;
}

void showN(int N)
{
	int x = 1000;
	int y = 100;
	char n[3];
	convertNumToString(N, n);
	char s[10] = "N = ";
	strcat(s, n);
	clrscr(x, y + 30, x + 90, y + 70);
	displayText(x, y, s, WHITE, 2);
}