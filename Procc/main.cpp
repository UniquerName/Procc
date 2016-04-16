#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include "queue.h"
#include <iostream> 
using namespace std;
#pragma warning(disable : 4996)
#define MAX_RANDOM 10
#define PRINT_TICKS 20


int main()
{
	setlocale(LC_ALL, "rus");
	int ignored = 0, pass = 0;
	int pc, fc;
	TQueue q(3);
	proc p(MAX_RANDOM);
	flo f(MAX_RANDOM);
	int ticks;
	int i, j = 0;
	srand(time(NULL));
	int taskdone = 0;
	int inqu = 0;

	/*���� ��������� �������*/

	printf("����� ������\n");
	do{
		scanf("%d", &ticks);
	} while (ticks <= 0);


	printf("�������� ����������\n");
	do{
		scanf("%d", &pc);
	} while ((pc <= 0) || (pc >= MAX_RANDOM));
	p.InsCrit(pc);

	printf("������������� ������ �����\n");
	do{
		scanf("%d", &fc);
	} while ((fc <= 0) || (fc >= MAX_RANDOM));
	f.InsCrit(fc);

	/*������ ����������� ������*/

	for (i = 1; i <= ticks; i++)
	{
		if (ignored != 0) printf("����� ���������������: %d\n", ignored);
		if (taskdone != 0) printf("����� ����������: %d\n", taskdone);
		if (inqu != 0) printf("����� � �������: %d\n", inqu);
		printf("\n__________________________________\n");
		printf("���� %d\n", i);
		if (f.TaskGen())
		{
			j++;
			printf(ticks< PRINT_TICKS ? "������ ���������\n" : "");
			if (q.IsFull())
			{
				printf(ticks< PRINT_TICKS ? "������ ���������������\n" : "");
				++ignored;
			}
			else
			{
				printf(ticks<PRINT_TICKS ? "������ �������� � �������\n" : "");
				q.Put(1);
				inqu++;
			}
		}
		if (p.IsOcc)
		{
			printf(ticks<PRINT_TICKS ? "��������� ���������� ������������ ������� ������\n" : "");
			if (p.TaskProc()){
				taskdone++;
				printf(ticks < PRINT_TICKS ? "��������� ��������� ������\n" : "");
				inqu--;
			}
		}
		else if (!q.IsEmpty())
		{
			printf(ticks < PRINT_TICKS ? "��������� ����� ��������� ����� ������\n" : "");
			q.Push();
			if (p.TaskProc())
			{
			taskdone++;
			printf(ticks < PRINT_TICKS ? "��������� ��������� ������\n" : "");
			inqu--;
			}
		}
		else
		{
			printf(ticks<PRINT_TICKS ? "��������� �����������\n" : "");
			pass++;
		}
	}
	
	/*����� ����������� ������*/
	
	
	printf("\n================\n");
	printf("����� ����������: %d\n", p.GetNum());
	int fl = 0;
	double mg = pass, mc = p.GetNum(), mv = ignored;
	while (!q.IsEmpty()) { fl++, q.Push(); }
	printf("����� � �������: %d\n", fl);
	printf("����� ���������: %d\n", j);
	printf("������� �������: %.2f\n", (mg / ticks) * 100);
	if (mc != 0)
		printf("������� ����� ���������: %.2f �����\n", (ticks - pass) / mc);
	else printf("������ �� ����������\n");
	printf("����������������� �����: %.0f \n", mv);
	if (mv!=0) printf("\t������� ����������������� �����: %.2f \n", (mv / ticks) * 100);
	_getch();
	return 0;

}



