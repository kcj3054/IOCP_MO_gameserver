#pragma once

/*
* 
	그래프 알고리즘을 접목시켜서 정점들이 서로 역방향으로 (ex : 1-> 2, 2 -> 1)로 돌면서 
    사이클이 발생했으면 데드락에 걸렸다고 판단할 수 있음

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
	
	//교차 간선이 발생했는지 사이클을 확인하는 지 체크 
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
	std::vector<int>	_discoveredOrder; //노드가 발견된 순서 
	int					_discoveredCount = 0;
	std::vector<bool>		_visited; // Dfs(i)를 발견했는지 체크 
	std::vector<int>		_parent; //
};

