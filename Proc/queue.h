#define MemSize 10

class TQueue
{
	int Li, Hi;
	int Size;
	int *pMem;
	int GetNextIndex(int i);
public:
	TQueue(int n = MemSize);
	TQueue(const TQueue &q);
	~TQueue();
	bool IsEmpty(void) const;
	bool IsFull(void) const;

	void  Put(const int Val);
	int Peek(void);
	int Push(void);
};