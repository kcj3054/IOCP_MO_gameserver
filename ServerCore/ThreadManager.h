#pragma once

#include <thread>
#include <functional>


class ThreadManager
{
public:
	ThreadManager() = default;
	~ThreadManager() = default;

public:
	void Launch(std::function<void(void)> callback);

	void Join();

	static void InitTLS();
	static void DestroyTLS();

private:
	// Mutex;
};

