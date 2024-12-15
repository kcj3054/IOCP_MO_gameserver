#pragma once

#include <memory>
#include <vector>
#include <array>

class SendBuffer : std::enable_shared_from_this<SendBuffer> 
{
public:
	
	SendBuffer(int buffSize);
	~SendBuffer() = default;
	
	//byte*
	int WriteSize() { return _writeSize; }

	void CopyData(void* data, int len);

private:
	std::vector<char*>	_buffer;
	int					_writeSize = 0;
};



/*
* SendBufferChunk
* 
* SendBufferChunk는 커다란 메모리 공간을 할당 해 놓고 사용할 목적을 둔다.! 또한 chunk를 할당한 후 다시 delete로 지우는 것이 아니다.
* SendBufferChunk또한 refCount로 관리가 되어있어야한다.
*/
class SendBufferChunk : public std::enable_shared_from_this<SendBufferChunk>
{
#define SEND_BUFF_CHUNK_SIZE 0x1000
public:
	
	SendBufferChunk() = default;
	~SendBufferChunk() = default;

public:
	
	void	Reset();

	// [			] ~ 큰 크기의 sendBufferChunk를 할당 받지만, 해당 공간을 open한 후 SendBuffer로 관리하겠다는 의미
	SendBuffer* Open(int allockSize);

	void		Close(int writeSize);

	bool		isOpen() { return _open; }
	// char* Buffer() { return &_buffer[_usedSize]; }

private:

	std::array<char*, SEND_BUFF_CHUNK_SIZE> _buffer = {};
	
	//sendbuffer chunk를 open했는지 체크
	bool _open = false;
	
	//사용한 크기.
	int _usedSize = 0;
};


/*
* SendBufferManaer
*/

class SendBufferManager
{
public:

	// 큰 sendBuffer가 존재할 때 사용할 만큼 영역을 open한다는 의미 -> 그후 사용이 끝났으면 해당영역을 다 사용하는 것이 아니라
	// Close() 해준다 close의 의미는 사용한 만큼 사용하고 닫겠다는 의미 

	SendBuffer* Open(int size);
	
private:
	SendBufferChunk*	Pop();
	void				Push(SendBufferChunk* buffer);

	static void			PushGlobal(SendBufferChunk* buffer);


private:

	//use_lock;
	std::vector<SendBufferChunk*>	_sendBufferChunks;
};