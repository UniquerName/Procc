


#include <stdlib.h>
#include <time.h>

//Класс очередь

class TQueue
{
	int Li, Hi;
	int Size;
	int *pMem;
	int MemSize;
public:
	TQueue::TQueue(int n)
	{
		MemSize = n;
		Size = 0;
		Hi = 0;
		Li = 0;
		pMem = new int[MemSize];
		for (int i = 0; i < MemSize; i++)
			pMem[i] = 0;
	}

	TQueue::TQueue(const TQueue &q)
	{
		MemSize = q.MemSize;
		Size = q.Size;
		Hi = q.Hi;
		Li = q.Li;
		pMem = new int[MemSize];
		for (int i = 0; i < MemSize; i++)
			pMem[i] = q.pMem[i];
	}

	TQueue::~TQueue()
	{
		delete[]pMem;
	}

	int TQueue::GetNextIndex(int i)
	{
		return ++i%MemSize;
	}

	bool TQueue::IsEmpty() const
	{
		return (Size == 0);
	}


	bool TQueue::IsFull(void) const
	{
		return (Size == MemSize);
	}

	int TQueue::Show() const
	{
		return Size;
	}

	void TQueue::Put(const int Val)
	{
		Size++;
		Hi = GetNextIndex(Hi);
		pMem[Hi] = Val;
	}


	int TQueue::Peek(void)
	{
		return pMem[Li];
	}


	int TQueue::Push(void)
	{
		Size--;
		int i = Li;
		Li = GetNextIndex(Li);
		return pMem[i];
	}

	int TQueue::Show(void)
	{
		return MemSize;
	}

};

//Класс поток

class flo
{
	int MAX_RAND;

public:
	int crit = 100;
	bool flo::TaskGen()
	{
		//int srand = rand() % MAX_RAND;
		//printf("\n srand = %d", srand);
		return (rand() % MAX_RAND < crit);
	}

	void flo::InsCrit(int c)
	{
		crit = c;
	}

	flo::flo(int max)
	{
		MAX_RAND = max;
	}

};

//Класс процессор

class proc
{
	int MAX_RAND;
	int crit = 100;
	int tasknumber = 0;
public:
	bool IsOcc = 0;


	proc::proc(int max)
	{
		MAX_RAND = max;
	}

	void proc::InsCrit(int c)
	{
		crit = c;
	}

	bool proc::TaskProc()
	{
		int result = rand() % MAX_RAND;
		if (result < crit)//11111111111111
		{
			tasknumber++;
			IsOcc = 0;
		}
		else
			IsOcc = 1;
		return (result < crit);
	}

	int proc::GetNum()
	{
		return tasknumber;
	}
};