#include "pch.h"
#include "DeadLockProfiler.h"


//
void DeadLockProfiler::PushLock(const char* name)
{
	//LockGuard guard(_lock)

	//Lock 아이디를  찾거나 발급한다. 
	int lockId = 0;

	auto infdIt = _nameToId.find(name);
	if (infdIt == _nameToId.end())
	{
		lockId = static_cast<int>(_nameToId.size());
		_nameToId[name] = lockId;
		_idToName[lockId] = name;

	}
}

void DeadLockProfiler::PopLock(const char* name)
{
	_lockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	//lockCount 잡은 lock 숫자 
	const int lockCount = static_cast<int>(_nameToId.size());
	
	//발견된 순서를 매개줄 것이다.  1 -> 2- > 3-> .. 
	_discoveredOrder = std::vector<int>(lockCount, -1);
	_discoveredCount = 0;
	_visited = std::vector<bool>(lockCount, -1);
	_parent = std::vector<int>(lockCount, -1);

	for (int lockId = 0; lockId < lockCount; ++lockId)
		Dfs(lockId);

	//연산이 끝났으면 정리

}

void DeadLockProfiler::Dfs(int here)
{
	//이미 방문했다 
	if (_discoveredOrder[here] != -1)
		return;

	_discoveredOrder[here] = _discoveredCount++;

	//모든 인접한 정점 순회 
	// auto findIt = _lockHois

}
