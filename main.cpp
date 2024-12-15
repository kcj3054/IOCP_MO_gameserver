#include "pch.h"
#include "GameServer.h"

#include <memory>

using namespace std;

const UINT16 SERVER_PORT = 7700;
const UINT16 MAX_CLIENT = 100;		//총 접속할수 있는 클라이언트 수
const UINT32 MAX_IO_WORKER_THREAD = 4;  //쓰레드 풀에 넣을 쓰레드 수

class Base
{
public:
	virtual void func()
	{
		std::cout << "i am base fun" << std::endl;
	}
};

class Derived : public Base
{
public:
	virtual void func() override
	{
		std::cout << "i am derived fun " << std::endl;
	}
};

int main()
{
	/*
	* weak_ptr 
	* - shared_ptr에 의해 관리되고있는 개체를 가리킨다.
	* - non - ownership (소유권이없다)
	* - weak_ptr is created as a copy of shared_ptr
	* - 
	*/



	auto sharedPtr = std::make_shared<int>(100);
	weak_ptr<int> weakPtr(sharedPtr);
	
	// - weak_ptr is created as a copy of shared_ptr
	weak_ptr<int> weakPtr2 = sharedPtr;
	
	cout << "weakPtr.use_count() : " << weakPtr.use_count() << endl;
	cout << "weakPtr2.use_count() : " << weakPtr2.use_count() << endl;
	cout << "weakPtr.expired(): " << weakPtr.expired() << endl;

	//thread lock이 아님 
	//weakPtr.lock의 반환으로 shared_ptr을 받음 
	if (auto sharedPtr1 = weakPtr.lock())
	{
		cout << "*sharedPtr :" << *sharedPtr << endl;
		cout << "sharedPtr1.use_count() : " << sharedPtr1.use_count() << endl;
	}

	//shared_ptr에 의해 관리되던 object를 해제한다. 
	weakPtr.reset();

	if (auto sharedPtr2 = weakPtr.lock())
	{

	}
	else
	{
		cout << "not get resource " << endl;
	}

	//ref count를 헤아려 보자 
	/*
	* 처음에 sharedPtr를 만들었을 때 ref count는 1로됐고, weak_ptr은 ref count를 증가시키지않는다. 
	* 그러다가 if (auto sharedPtr1 = weakPtr.lock())에서 sharedPtr1이 기존에 sharedPtr이 가리키던 것을 가리키기에 
	* ref count가 증가하게된다. 
	*/
















	//new 키워드를 통해 할당된 메모리는 포인터로만 받을 수 있다.
	// 참조는 항상 유효한 개체를 가리켜야한다. 

	//참조는 동적으로 할당된 메모리의 주소값이 아니라, 실제 개체에 직접 바인딩된다 
	/*Base* b = new Derived();
	b->func();

	Derived d; 
	Base& bRef = d;*/

	// Base& b2 = new Derived(); //안됌 

	return 0;
}