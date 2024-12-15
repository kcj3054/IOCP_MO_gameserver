#pragma once

#include <thread>


template<typename T>
class ThreadFunctor
{
public:

private:
	using MemFunc = bool(T::*)(); 
	T* mObject;  //맴버 함수를 호출할 개체 
	MemFunc mFunctor;

public:

	bool Execute()
	{
		return (mObject->*mFunctor)();
	}
};

template<typename T>
bool ExecuteFunctionWithThreads(T* object, bool (T::*f1)(), bool (T::* f2)(), bool (T::* f3)(), bool (T::* f4)())
{

	//각 맴버 함수에 대해 ThreadFunctor 생성 
	ThreadFunctor<T> threadFunctor1(object, f1);
	ThreadFunctor<T> threadFunctor2(object, f2);

	//각각 스레드 생성 
	/*std::thread t1(.... );
	std::thread t2();
	std::thread t3();
	std::thread t4();*/

	t1.join();
}