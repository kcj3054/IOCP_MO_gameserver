#pragma once

#include <thread>


template<typename T>
class ThreadFunctor
{
public:

private:
	using MemFunc = bool(T::*)(); 
	T* mObject;  //�ɹ� �Լ��� ȣ���� ��ü 
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

	//�� �ɹ� �Լ��� ���� ThreadFunctor ���� 
	ThreadFunctor<T> threadFunctor1(object, f1);
	ThreadFunctor<T> threadFunctor2(object, f2);

	//���� ������ ���� 
	/*std::thread t1(.... );
	std::thread t2();
	std::thread t3();
	std::thread t4();*/

	t1.join();
}