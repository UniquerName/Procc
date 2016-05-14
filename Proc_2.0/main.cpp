#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<locale.h>
#include "TQueue.h"
#include <iostream> 
using namespace std;
#pragma warning(disable : 4996)
#define MAX_RANDOM 10
#define PRINT_TICKS 15


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

	/*Ввод начальных условий*/

	printf("Число тактов \n\t\t(при кол-ве более 15 пропускается потактовая статистика)\n");
	do{
		scanf("%d", &ticks);
	} while (ticks <= 0);


	printf("Мощность процессора\n");
	do{
		scanf("%d", &pc);
	} while ((pc <= 0) || (pc >= MAX_RANDOM));
	p.InsCrit(pc);

	printf("Интенсивность потока задач \n\t\t(очередь может содержать %d задачи)\n", q.Show()+1);
	do{
		scanf("%d", &fc);
	} while ((fc <= 0) || (fc >= MAX_RANDOM));
	f.InsCrit(fc);

	/*Начало потактового вывода*/

	for (i = 1; i <= ticks; i++)
	{
		
		
		if (ticks< PRINT_TICKS) printf("\nТакт %d\n", i);
		if (f.TaskGen())
		{
			j++;
			printf(ticks< PRINT_TICKS ? "Задача поступила\n" : "");
			if (q.IsFull())
			{
				printf(ticks< PRINT_TICKS ? "Задача проигнорирована\n" : "");
				++ignored;
			}
			else
			{
				printf(ticks<PRINT_TICKS ? "Задача помещена в очередь\n" : "");
				q.Put(1);
				inqu++;
			}
		}
		if (p.IsOcc)
		{
			printf(ticks<PRINT_TICKS ? "Процессор продолжает обрабатывать прошлую задачу\n" : "");
			if (p.TaskProc()){
				taskdone++;
				printf(ticks < PRINT_TICKS ? "Процессор обработал задачу\n" : "");
				inqu--;
			}
		}
		else if (!q.IsEmpty())
		{
			printf(ticks < PRINT_TICKS ? "Процессор начал обработку новой задачи\n" : "");
			q.Push();
			if (p.TaskProc())
			{
				taskdone++;
				printf(ticks < PRINT_TICKS ? "Процессор обработал задачу\n" : "");
				inqu--;
			}
		}
		else
		{
			printf(ticks<PRINT_TICKS ? "Процессор простаивает\n" : "");
			pass++;
		}
		
		if ((ignored != 0) && (ticks< PRINT_TICKS)) printf("Задач проигнорировано: %d\n", ignored);
		if ((taskdone != 0) && (ticks< PRINT_TICKS)) printf("Задач обработано: %d\n", taskdone);
		if ((inqu != 0) && (ticks< PRINT_TICKS)) printf("Задач в очереди: %d\n", inqu);
		printf(ticks< PRINT_TICKS ? "\n__________________________________\n" : "");
	}

	/*конец потактового вывода*/


	printf("\n================\n");
	printf("Задач обработано: %d\n", p.GetNum());
	int fl = 0;
	double mg = pass, mc = p.GetNum(), mv = ignored;
	while (!q.IsEmpty()) { fl++, q.Push(); }
	printf("Задач в очереди: %d\n", inqu); // было fl
	printf("Задач поступило: %d\n", j);
	printf("Процент простоя: %.2f\n", (mg / ticks) * 100);
	if (mc != 0)
		printf("Среднее время обработки: %.2f такта\n", (ticks - pass) / mc);
	else printf("Задачи не обработаны\n");
	printf("Проигнорированных задач: %.0f \n", mv);
	if (mv != 0) printf("\tПроцент проигнорированных задач: %.2f \n", (mv / ticks) * 100);
	_getch();
	return 0;

}

