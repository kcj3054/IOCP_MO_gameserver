#pragma once
/*
*  RW SPINLOCK
* 
* ->32bit flag를 이용한다.
* 
* [WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
* 
* W : Write Flag (Exclusive Lock Owner ThreadID)
* R : ReadFlag (shared Lock Count)
*/

/*
* // 동일 스레드가 Write가 한 후에는 Read를 할 수 있다
* Write를 잡은 상태에서 Read를 잡을 수는 있다.
*	-> Write를 잡은 상태에서 
* 
* 
* Read를 잡은 상태에서 Write를 잡을 수는 없다. // Read를 잡았다는 것은 여러 스레드가 Read를 하고있는 상황 일 수도있다 이러한 상태에서 
* Write를 한다는 것은 값을 변질 시킬 수 있다. , 애당초 값을 쓰는 것이라면 W->R로 가는 것이 맞다 
*/
#include <atomic>

class Lock
{
public:
	enum : unsigned int
	{
		ACQUIRE_TIMEOUT_TIC = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0xFFFF'0000,
		EMPTY_FLAG = 0x0000'0000
	};

public:
	void WriteLock();
	void WriteUnLock();
	void ReadLock();
	void ReadUnLock();

private:
	std::atomic<unsigned int> _lockFlag = EMPTY_FLAG;
	int _writeCount = 0;
};

