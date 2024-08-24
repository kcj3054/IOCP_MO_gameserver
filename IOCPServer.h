#pragma once
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "mswsock.lib")

#include "ClientInfo.h"
#include "Define.h"
#include <thread>
#include <vector>
#include <iostream>


/*
* iocp에서 풀링하는 역할드은 커널에서한다 
*/

/*
* 비동기용 소켓 함수들은 일단 무조건 return. 
* 어떠한 읽기 쓰기가 발생하면 WorkerThread 쪽의 GetQueuedCompletion~가 풀리는 것. 
*/
class IOCPServer
{
public:
	IOCPServer() = default;
	
	virtual ~IOCPServer()
	{
		//윈속의 사용을 끝낸다.
		WSACleanup();		
	}

	//소켓을 초기화하는 함수
	bool Init(const UINT32 maxIOWorkerThreadCount_)
	{
		WSADATA wsaData;
		
		int nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (0 != nRet)
		{
			printf("[에러] WSAStartup()함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		//연결지향형 TCP , Overlapped I/O 소켓을 생성
		mListenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, WSA_FLAG_OVERLAPPED);

		if (mListenSocket == INVALID_SOCKET)
		{
			printf("[에러] socket()함수 실패 : %d\n", WSAGetLastError());
			return false;
		}

		MaxIOWorkerThreadCount = maxIOWorkerThreadCount_;

		printf("소켓 초기화 성공\n");
		return true;
	}
		
	//서버의 주소정보를 소켓과 연결시키고 접속 요청을 받기 위해 소켓을 등록하는 함수
	bool BindandListen(int nBindPort)
	{
		SOCKADDR_IN		stServerAddr;
		stServerAddr.sin_family = AF_INET;
		stServerAddr.sin_port = htons(nBindPort); //서버 포트를 설정한다.		
		//어떤 주소에서 들어오는 접속이라도 받아들이겠다.
		//보통 서버라면 이렇게 설정한다. 만약 한 아이피에서만 접속을 받고 싶다면
		//그 주소를 inet_addr함수를 이용해 넣으면 된다.
		stServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		//위에서 지정한 서버 주소 정보와 cIOCompletionPort 소켓을 연결한다.
		if (bind(mListenSocket, (SOCKADDR*)&stServerAddr, sizeof(SOCKADDR_IN)) != 0)
		{
			return false;
		}

		//접속 요청을 받아들이기 위해 cIOCompletionPort소켓을 등록하고 
		//접속대기큐를 5개로 설정 한다.

		if (listen(mListenSocket, 5) != 0)
		{
			return false;
		}

		//CompletionPort객체 생성 요청을 한다.
		mIOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, MaxIOWorkerThreadCount);

		// IOCP를 생성하는 부분이 아니라, IOCP에 내 SOCKET을 연동하는 부분이다. 
		auto iocpHandle = CreateIoCompletionPort((HANDLE)mListenSocket, mIOCPHandle, (UINT32)0, 0);
		if (iocpHandle == nullptr)
		{
			return false;
		}

		return true;
	}

	//접속 요청을 수락하고 메세지를 받아서 처리하는 함수
	bool StartServer(const UINT32 maxClientCount)
	{
		CreateClient(maxClientCount);
		
		//CreateAccepterThread, CreateWokerThread 순서 바꿈으로써 터트리기.. 

		CreateAccepterThread();

		//접속된 클라이언트 주소 정보를 저장할 구조체
		CreateWokerThread();
		return true;
	}

	//생성되어있는 쓰레드를 파괴한다.
	void DestroyThread()
	{
		mIsWorkerRun = false;
		CloseHandle(mIOCPHandle);
		
		for (auto& workerThread : mIOWorkerThreads)
		{
			if (workerThread.joinable())
			{
				workerThread.join();
			}
		}
		
		//Accepter 쓰레드를 종요한다.
		isAccepterRun = false;
		closesocket(mListenSocket);
		
		if (mAccepterThread.joinable())
		{
			mAccepterThread.join();
		}		
	}

	bool SendMsg(const UINT32 sessionIndex_, const UINT32 dataSize_, char* pData)
	{
		auto pClient = GetClientInfo(sessionIndex_);
		return pClient->SendMsg(dataSize_, pData);
	}
	
	virtual void OnConnect(const UINT32 clientIndex_) {}

	virtual void OnClose(const UINT32 clientIndex_) {}

	virtual void OnReceive(const UINT32 clientIndex_, const UINT32 size_, char* pData_) {}

private:
	/*
	* 미리 생성해 두면 오버헤드가 줄어든다. 
	*/
	void CreateClient(const UINT32 maxClientCount)
	{
		for (UINT32 i = 0; i < maxClientCount; ++i)
		{
			auto client = new ClientInfo;
			client->Init(i, mIOCPHandle);

			mClientInfos.push_back(client);
		}
	}

	//WaitingThread Queue에서 대기할 쓰레드들을 생성
	void CreateWokerThread()
	{
		unsigned int uiThreadId = 0;
		//WaingThread Queue에 대기 상태로 넣을 쓰레드들 생성 권장되는 개수 : (cpu개수 * 2) + 1 
		
		printf("[CreateWokerThread] : %d", MaxIOWorkerThreadCount);

		for (int i = 0; i < MaxIOWorkerThreadCount; i++)
		{
			mIOWorkerThreads.emplace_back([this](){ WokerThread(); });			
		}

		printf("WokerThread 시작..\n");
	}
	
	//사용하지 않는 클라이언트 정보 구조체를 반환한다.
	ClientInfo* GetEmptyClientInfo()
	{
		for (auto& client : mClientInfos)
		{
			if (client->IsConnectd() == false)
			{
				return client;
			}
		}

		return nullptr;
	}

	/*
	* clientSession을 미리 만들어두니, sessionIndex에 따른 Client 정보를 가지고 올 수 있다 
	*/
	ClientInfo* GetClientInfo(const UINT32 sessionIndex)
	{
		return mClientInfos[sessionIndex];		
	}


	// CreateAccepterThread와 WorkerThread를 따로 두는 것은 
	/*
	* Accept는 딱 연결만 담당하도록 분리하고 이외에 IO들 네트워크처리부분들은 WorkertThread로 분리하면
	* 효율이있다. 
	*/
	//accept요청을 처리하는 쓰레드 생성
	bool CreateAccepterThread()
	{
		mAccepterThread = std::thread([this]() { AccepterThread(); });
		
		printf("AccepterThread 시작..\n");
		return true;
	}
		  		
	//Overlapped I/O작업에 대한 완료 통보를 받아 그에 해당하는 처리를 하는 함수
	void WokerThread()
	{
		//CompletionKey를 받을 포인터 변수
		ClientInfo* pClientInfo = nullptr;
		//함수 호출 성공 여부
		BOOL bSuccess = TRUE;
		//Overlapped I/O작업에서 전송된 데이터 크기
		DWORD dataTransferred = 0;
		//I/O 작업을 위해 요청한 Overlapped 구조체를 받을 포인터
		LPOVERLAPPED lpOverlapped = NULL;

		while (mIsWorkerRun)
		{
			/*
			* 여기에 어떠한 정지된 시간이 없다면 시스템은 무리가 가지만 GetQueuedCompletionStatus가 그것을 방지
			* 해줌
			*/
			// 여기서 GetQueuedCompletionStatus iocp의 특성이 보인다. 
			// While로 계속 돌면서 GetQueuedCompletionStatus를 호출하는 것이 아니라, 
			// GetQueuedCompletionStatus를 통해 완료된 이벤트가 있는 것이 아니라면 해당 함수 호출부에 
			// blocking 함수처럼 대기하고있어서 while안에 따로 thread sleep 구문이 필요가 없다. 

			/*
			* dataTransferred -> WSARecv에 의하여 발생한 것이라면 읽어들인 수,
			* WSASend에 의하여 발생한 것이라면 전송한 바이트 수를 가리킨다. 
			*/

			/*
			* CompletionKey
			* ->  연결과정에 전달하였을 때도 넘긴 값 CreateIOCompletion... 
			* -> 
			*/
			bSuccess = GetQueuedCompletionStatus(mIOCPHandle,
				&dataTransferred,					// 실제로 전송된 바이트
				(PULONG_PTR)&pClientInfo,		// CompletionKey
				&lpOverlapped,				// Overlapped IO 객체
				INFINITE);					// 대기할 시간

			auto overlappedEx = (OverlappedEX*)lpOverlapped;

			//========================== 추가된 함수 ===================
			//==========================BattleNetGameServer=====================

			//Accpet일 수도 있으니 아래 행위처럼하려면 AcceptThread를 완전 분리해야함 
			//if (lpOverlapped != nullptr && dataTransferred == 0)
			//{
			//	//접속이 끊김 , recv 일 때도 0은 이상한 것이고 send할 때도 패킷을 안보낸 것은 말이 안된다 
			//	//closeSocket. 
			//	
			//	//EnqueueClose(pClientInfo)
			//	CloseSocket(pClientInfo);
			//}


			//recv 시 0byte일 경우 처리 
			//clienetsession 제거 
			if (overlappedEx->m_eOperation == IOOperation::RECV && dataTransferred == 0)
			{
				std::cout << "zero byte recv -> close socket" << std::endl;
				CloseSocket(pClientInfo);
			}

			// GetQueuedCompletionStatus에서 알게된 m_eOperation 요청 종류 
			switch (overlappedEx->m_eOperation)
			{
				// Accept는 Worker말고 AcceptThread에서 담당해서 처리하는 것으로 빼자 
				// 
			case IOOperation::ACCEPT:
				//miocphandle이 다 동일하지  ?.. 
				pClientInfo = GetClientInfo(overlappedEx->SessionIndex);

				if (pClientInfo->AcceptCompletion())
				{
					InterlockedIncrement(&clientCount);
					OnConnect(pClientInfo->GetIndex());
				}
				else
				{
					std::cout << "AcceptCompletion 실패" << std::endl;

					CloseSocket(pClientInfo, true);
				}
				break;

			case IOOperation::RECV:
				OnReceive(pClientInfo->GetIndex(), dataTransferred, pClientInfo->RecvBuffer());
				
				//================= BattleNetGameServer===================
				// Recv 후 다음번 읽기를 위한 비동기 읽기 시도 ..
				// PostRecv

				pClientInfo->BindRecv();
				break;

			case IOOperation::SEND:
				//================= BattleNetGameServer===================
				// Send 후 다음번 읽기를 위한 비동기 읽기 시도 ..
				// 

				//해당 부분에서 이뤄져야할 것은 
				/*
				* TCP 특성상 하나의 패킷단위로 데이터가 이동하는 것이 아니라서.. 
				* 정확하나의 패킷이 전송되도록 체크하는 부분이 이뤄져야한다. 그부분이 SendCompleted..
				* 원하는 바이트 수가, 보내는 바이트 수 확인
				*/
				pClientInfo->SendCompleted(dataTransferred);

				//PostSendReset(pClientInfo, dataTransferred)
				break;

			default:
				printf("Client Index(%d)에서 예외상황\n", pClientInfo->GetIndex());
				break;
			}

		}
	}

	//사용자의 접속을 받는 쓰레드
	void AccepterThread()
	{
		while (isAccepterRun)
		{
			for (auto client : mClientInfos)
			{
				if (client->IsConnectd())
				{
					continue;
				}

				client->PostAccept(mListenSocket);
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(32));
		}
	}

	
	//소켓의 연결을 종료 시킨다.
	void CloseSocket(ClientInfo* pClientInfo, bool bIsForce = false)
	{
		auto clientIndex = pClientInfo->GetIndex();

		pClientInfo->Close(bIsForce);
		
		OnClose(clientIndex);
	}



	UINT32 MaxIOWorkerThreadCount = 0;

	//클라이언트 정보 저장 구조체
	std::vector<ClientInfo*> mClientInfos;

	//클라이언트의 접속을 받기위한 리슨 소켓
	SOCKET		mListenSocket = INVALID_SOCKET;
	
	//접속 되어있는 클라이언트 수
	long			clientCount = 0;
	
	//IO Worker 스레드
	std::vector<std::thread> mIOWorkerThreads;

	//Accept 스레드
	std::thread	mAccepterThread;

	//CompletionPort객체 핸들
	HANDLE		mIOCPHandle = INVALID_HANDLE_VALUE;
	
	//작업 쓰레드 동작 플래그
	bool		mIsWorkerRun = true;

	//접속 쓰레드 동작 플래그
	bool		isAccepterRun = true;
};