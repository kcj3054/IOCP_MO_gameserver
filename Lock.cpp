#include "pch.h"
#include "Lock.h"

void Lock::WriteLock()
{
	//아무도 소유 및 공유하고 있지 않을 때 경합해서 소유권을 얻는다. 
	//_lockFlag.load() & WRITE_THREAD_MASK -> 하위 16bit는 0으로 밀고 
	// FFF와 _lockFlag는 어떻게 될까 ?
	// 
	const int lockTrheadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	
	//동일 쓰레드 ID가 다시 WRITE LOCK을 걸 시 ++하면서 허용한다 
	/*
	* if(LThreadId == lockTrheadId) _writeCount++;
	*/

	//아무도 소유 및 공유하고 있지 앟을 때 경합해서 소유권을 얻는다.
	const int beginTick = ::GetTickCount64();
	// const int desired = ()
}

void Lock::WriteUnLock()
{

}

void Lock::ReadLock()
{
	//동일한 스레드가 소유하고 있다면 무조건 성공 . ->
	//동일한 스레드가  데이터를 쓰고, 후에 읽는 것은 아무 의미 없기에..

	//아무도 소유하고 있지 않을 때 (아무도 Write 하고있지 않을 때..)는 경합해서 공유 카운트를 올린다.
	// 
	while (true)
	{

	}
}

void Lock::ReadUnLock()
{

}
