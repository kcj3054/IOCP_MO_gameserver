# IOCP 기반의 MO 게임서버 


# 스레드 사용 전략 

- 네트워크 스레드와 패킷처리용 스레드를 분리했습니다. 

- MainThread(1), Network처리용 workerThread, Redis처리만을 담당하는 redisWorkerThread들로 구성하였습니다.


# c++ 

- c++ 표준의 thread와 redisManager 부분에서는 jthread를 사용하면서 기존방식과 modern한 c++ 스타일의 차이점들을 학습하고자했습니다. 

# 방처리 및 session 처리 


- Room이나 session들은 미리 사용할만큼 생성 해 놓는 방식으로 진행했습니다. 게임 진행 중에 동적으로 생성을 하게된다면 서버에 부하가 될 수 있으므로 미리 사용할 만큼 생성하는 방식으로 진행하였습니다. 