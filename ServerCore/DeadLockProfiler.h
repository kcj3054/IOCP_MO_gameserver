#pragma once

/*
* 
	�׷��� �˰����� ������Ѽ� �������� ���� ���������� (ex : 1-> 2, 2 -> 1)�� ���鼭 
    ����Ŭ�� �߻������� ������� �ɷȴٰ� �Ǵ��� �� ����

*/

#include <vector>
#include <map>
#include <unordered_map>
#include <mutex>
#include <stack>
#include <set>

class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	
	//���� ������ �߻��ߴ��� ����Ŭ�� Ȯ���ϴ� �� üũ 
	void CheckCycle(); 

private:
	void Dfs(int index); 

private:
	std::unordered_map<const char*, int>	_nameToId;
	std::unordered_map<int, const char*>	_idToName;
	std::stack<int>							_lockStack;

	std::map<int, std::set<int>>					_lockHistory;
	std::mutex _lock;

private:
	std::vector<int>	_discoveredOrder; //��尡 �߰ߵ� ���� 
	int					_discoveredCount = 0;
	std::vector<bool>		_visited; // Dfs(i)�� �߰��ߴ��� üũ 
	std::vector<int>		_parent; //
};

