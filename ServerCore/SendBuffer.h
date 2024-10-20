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
* SendBufferChunk�� Ŀ�ٶ� �޸� ������ �Ҵ� �� ���� ����� ������ �д�.! ���� chunk�� �Ҵ��� �� �ٽ� delete�� ����� ���� �ƴϴ�.
* SendBufferChunk���� refCount�� ������ �Ǿ��־���Ѵ�.
*/
class SendBufferChunk : public std::enable_shared_from_this<SendBufferChunk>
{
#define SEND_BUFF_CHUNK_SIZE 0x1000
public:
	
	SendBufferChunk() = default;
	~SendBufferChunk() = default;

public:
	
	void	Reset();

	// [			] ~ ū ũ���� sendBufferChunk�� �Ҵ� ������, �ش� ������ open�� �� SendBuffer�� �����ϰڴٴ� �ǹ�
	SendBuffer* Open(int allockSize);

	void		Close(int writeSize);

	bool		isOpen() { return _open; }
	// char* Buffer() { return &_buffer[_usedSize]; }

private:

	std::array<char*, SEND_BUFF_CHUNK_SIZE> _buffer = {};
	
	//sendbuffer chunk�� open�ߴ��� üũ
	bool _open = false;
	
	//����� ũ��.
	int _usedSize = 0;
};


/*
* SendBufferManaer
*/

class SendBufferManager
{
public:

	// ū sendBuffer�� ������ �� ����� ��ŭ ������ open�Ѵٴ� �ǹ� -> ���� ����� �������� �ش翵���� �� ����ϴ� ���� �ƴ϶�
	// Close() ���ش� close�� �ǹ̴� ����� ��ŭ ����ϰ� �ݰڴٴ� �ǹ� 

	SendBuffer* Open(int size);
	
private:
	SendBufferChunk*	Pop();
	void				Push(SendBufferChunk* buffer);

	static void			PushGlobal(SendBufferChunk* buffer);


private:

	//use_lock;
	std::vector<SendBufferChunk*>	_sendBufferChunks;
};