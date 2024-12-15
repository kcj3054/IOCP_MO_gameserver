#include "pch.h"
#include "GameServer.h"

#include <memory>

using namespace std;

const UINT16 SERVER_PORT = 7700;
const UINT16 MAX_CLIENT = 100;		//�� �����Ҽ� �ִ� Ŭ���̾�Ʈ ��
const UINT32 MAX_IO_WORKER_THREAD = 4;  //������ Ǯ�� ���� ������ ��

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
	* - shared_ptr�� ���� �����ǰ��ִ� ��ü�� ����Ų��.
	* - non - ownership (�������̾���)
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

	//thread lock�� �ƴ� 
	//weakPtr.lock�� ��ȯ���� shared_ptr�� ���� 
	if (auto sharedPtr1 = weakPtr.lock())
	{
		cout << "*sharedPtr :" << *sharedPtr << endl;
		cout << "sharedPtr1.use_count() : " << sharedPtr1.use_count() << endl;
	}

	//shared_ptr�� ���� �����Ǵ� object�� �����Ѵ�. 
	weakPtr.reset();

	if (auto sharedPtr2 = weakPtr.lock())
	{

	}
	else
	{
		cout << "not get resource " << endl;
	}

	//ref count�� ��Ʒ� ���� 
	/*
	* ó���� sharedPtr�� ������� �� ref count�� 1�εư�, weak_ptr�� ref count�� ������Ű���ʴ´�. 
	* �׷��ٰ� if (auto sharedPtr1 = weakPtr.lock())���� sharedPtr1�� ������ sharedPtr�� ����Ű�� ���� ����Ű�⿡ 
	* ref count�� �����ϰԵȴ�. 
	*/
















	//new Ű���带 ���� �Ҵ�� �޸𸮴� �����ͷθ� ���� �� �ִ�.
	// ������ �׻� ��ȿ�� ��ü�� �����Ѿ��Ѵ�. 

	//������ �������� �Ҵ�� �޸��� �ּҰ��� �ƴ϶�, ���� ��ü�� ���� ���ε��ȴ� 
	/*Base* b = new Derived();
	b->func();

	Derived d; 
	Base& bRef = d;*/

	// Base& b2 = new Derived(); //�ȉ� 

	return 0;
}