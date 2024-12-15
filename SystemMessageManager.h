#pragma once

/*
* broadcasting을 요하는 것들을 대상으로 보낼 수 있다. 
* 
* 전체적인 공지사항, 알림, 우편..
* 
*/


/*
* 브로드캐스팅을 하더라도, 어느정도 Tick 간격을 줘야한다, 
- 매번 계속적으로 브로드캐스팅할 것인지 ?
- 어느정도 시간 간격을 줄 것인지 ? 
- 시스템메시지에도 큐잉 시스템을 넣어서, 최대로 등록할 수 있는 시스템 메시지를 관리한다.
- 
- Timer라는 존재가 필요함
*/

class SystemMessageManager
{
public:

private:

	//systemMessageTimer
	// template<typename TFunc>
	// concept MemberFunctionT = std::is_member_function_pointer<std::decay_t<TFunc>>;

	//template<typename TFunc, template... Args>
	//void SystemMessageTimer(TFunc&& func, Args&&... args)
	//{
	//	//최대 갯수를 등록할 수 없도록한다. 

	//	//MessageSend를 생성 

	//	//bradCastInterval..

	//	//DoTimerObjFucn. (interval, this, .. boradcast, messageSend.)
	//}

	void BroadCast(/* SystemMessage::MessageSender* messageSender */)
	{
		//messageSender가 send를 담당함 
	}
};

// 첫 서버시작 시.. GSystemMessageManaber = new SyStemMessageManager ;..
inline SystemMessageManager* GSystemMessageManager = nullptr;

