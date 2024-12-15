# IOCP 기반의 MO 게임서버 


# 스레드 사용 전략 

- 네트워크 스레드와 패킷처리용 스레드를 분리했습니다. 

- MainThread(1), Network처리용 workerThread, 패킷처리용 Worker Thread, Redis처리만을 담당하는 redisWorkerThread들로 구성하였습니다.

- 스레드 사용 부분에서는 IO가 가장 시간이 많이 소요되기에 IO를 담당하는 스레드와 로직단 패킷처리를 하는 스레드는 공용으로 사용하지 않습니다.
  
# c++ 

- c++ 표준의 thread와 redisManager 부분에서는 jthread를 사용하면서 기존방식과 modern한 c++ 스타일의 차이점들을 학습하고자했습니다. 


## 기능 

-  Room이나 session들은 미리 사용할만큼 생성 해 놓는 방식으로 진행했습니다. 게임 진행 중에 동적으로 생성을 하게된다면 서버에 부하가 될 수 있으므로 미리 사용할 만큼 생성하는 방식으로 진행하였습니다. 
  

- [x] deadlock profiler 연동
    - 사용한 deadlock profiler는 그래프 탐색기법에서 사이클이 발생했을 경우 deadlock에 걸렸다고 판단한다. (a -> b, b -> a 교차간선)  
    - 데드락 프로파일러는 디버깅 버전에서만 사용하도록한다. 
  
- [x] redis 연동
  
- [ ] 방 생성

- [ ] 관전자 기능
  
- [ ] 채팅 
    - 방내 모든 사람에게 알리는 채팅 및 귓속말 구현 
    - 채팅 구현 시 패킷 검증 및 채팅 금지 대상인지 체크 (캐싱을 이용한 체크로 검증)


## 참고 사항 

- protobuf 21.x 버전부터 abseil 라이브러리에 의존성이 추가되어서, 편리하게 cmake gui로 바로 sln을 바로 만들 수 없다. 사전에 abseil 라이브러리를 먼저 만들어놓아야한다.  해당 문제를 회피하고자 현 repository에서는 프로토버퍼 20.x 버전으로 낮춰서 사용중입니다. 

- 프로젝트 초반부에는 protobuf나 필요한 라이브러리들을 vcpkg로 설정하였지만 편의를 위해서 정적 lib으로 대체하고있습니다.

