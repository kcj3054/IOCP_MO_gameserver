#include "GameServer.h"
#include <string>
#include <iostream>



const UINT16 SERVER_PORT = 7700;
const UINT16 MAX_CLIENT = 100;		//총 접속할수 있는 클라이언트 수
const UINT32 MAX_IO_WORKER_THREAD = 4;  //쓰레드 풀에 넣을 쓰레드 수

/*
* - smart pointer는 일단  raw pointer를 wrapping 한 것이다. 
* - 아래 class MyInt도 동일하게 스마트포인터라고 볼 수 있다 물론 refcount는 없다.
* - 중점적인 목적은 new로 생성된 object의 life time을 관리한다고 볼 수 있다. 
*	- 아리에서 MyInt 타입으로 인스턴싱된 개체는 따로 delete를 하지 않고 MyInt에서 내부적으로 delete를 해준다.
*	- 정말 데이터가 많아진다면 new - delete를 맞춘다는 것은 불가능. 사람이 하는 것은 실수가 나오기 마련.!
*/
class MyInt
{
public:
	explicit MyInt(int* p = nullptr)
	{
		data = p;
	}

	~MyInt() { delete data; }

	int& operator * () { return *data; }
private:
	int* data{ nullptr };
};

class Foo
{
public:
	Foo(int x) : _x{x} {}
	int getX() { return _x; }
	~Foo() { std::cout << "~Foo" << std::endl; }
private:
	int _x = 0;
};

void fun(std::shared_ptr<Foo> sp)
{
	std::cout << "fun : " << sp.use_count() << std::endl;
}

int main()
{

	//GameServer server;

	////소켓을 초기화
	//server.Init(MAX_IO_WORKER_THREAD);

	////소켓과 서버 주소를 연결하고 등록 시킨다.
	//server.BindandListen(SERVER_PORT);

	//server.Run(MAX_CLIENT);
	//while (true)
	//{
	//	;
	//}
	//return 0;

	//int* p = new int(10);
	//MyInt myint = MyInt(p); // P의 POINTER를 PASSING TO MyInt ... p포인터를 MyInt로 넘긴다. 
	//std::cout << *myint << std::endl;

	//shared_ptr<> p(new Foo()).. 
	// sp0, sp1, sp2... Foo개체를 가리키는 스마트포인터들이 증가하낟.
	// -> 어떤 개체인지, 또 다른 것은 control block ->,,, 

	//shared_ptr에서 reference count인 control block은 thread safe하지만, 어떤 객체인지 가리키는 T*는 thread safe
	// 하지 않다. 

	// make_shared는 미리 메모리 할당한 후 개체 타입을 정하는 것이라서 new 키워드가 없다 
	// 
	std::shared_ptr<Foo> sp = std::make_shared<Foo>(200);
	std::cout << sp.get() << std::endl;
	std::cout << sp.use_count() << std::endl; // reference count, -> thread safe
	std::shared_ptr<Foo> sp1(new Foo(100));
	std::shared_ptr<Foo> sp2 = sp;
	std::cout << sp.use_count() << std::endl;


	std::thread t1(fun, sp), t2(fun, sp), t3(fun, sp);

	std::cout << "main : " << sp.use_count() << std::endl;
	t1.join(); t2.join(); t3.join();
	//주목할 점은 ~ deconstructor은 한번만 호출된다. 
}

/*
* [방 나기기]
*  -> 단순 해당 유저만 나가는 것이 아니라 다른 유저들한테도 나간 것을 알려줘야한다. 방 내에서 broadcasting.
* 
* 실무코드는 방어코드가 중요하다. 
* 
* -> io가 부하가 크다, 로직 처리 스레드와는 분리하는 것이 좋ㄷ
*/