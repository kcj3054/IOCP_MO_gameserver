#include "pch.h"
#include "DeadLockProfiler.h"


//
void DeadLockProfiler::PushLock(const char* name)
{
	//LockGuard guard(_lock)

	//Lock ���̵�  ã�ų� �߱��Ѵ�. 
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
	//lockCount ���� lock ���� 
	const int lockCount = static_cast<int>(_nameToId.size());
	
	//�߰ߵ� ������ �Ű��� ���̴�.  1 -> 2- > 3-> .. 
	_discoveredOrder = std::vector<int>(lockCount, -1);
	_discoveredCount = 0;
	_visited = std::vector<bool>(lockCount, -1);
	_parent = std::vector<int>(lockCount, -1);

	for (int lockId = 0; lockId < lockCount; ++lockId)
		Dfs(lockId);

	//������ �������� ����

}

void DeadLockProfiler::Dfs(int here)
{
	//�̹� �湮�ߴ� 
	if (_discoveredOrder[here] != -1)
		return;

	_discoveredOrder[here] = _discoveredCount++;

	//��� ������ ���� ��ȸ 
	// auto findIt = _lockHois

}
