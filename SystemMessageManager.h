#pragma once

/*
* broadcasting�� ���ϴ� �͵��� ������� ���� �� �ִ�. 
* 
* ��ü���� ��������, �˸�, ����..
* 
*/


/*
* ��ε�ĳ������ �ϴ���, ������� Tick ������ ����Ѵ�, 
- �Ź� ��������� ��ε�ĳ������ ������ ?
- ������� �ð� ������ �� ������ ? 
- �ý��۸޽������� ť�� �ý����� �־, �ִ�� ����� �� �ִ� �ý��� �޽����� �����Ѵ�.
- 
- Timer��� ���簡 �ʿ���
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
	//	//�ִ� ������ ����� �� �������Ѵ�. 

	//	//MessageSend�� ���� 

	//	//bradCastInterval..

	//	//DoTimerObjFucn. (interval, this, .. boradcast, messageSend.)
	//}

	void BroadCast(/* SystemMessage::MessageSender* messageSender */)
	{
		//messageSender�� send�� ����� 
	}
};

// ù �������� ��.. GSystemMessageManaber = new SyStemMessageManager ;..
inline SystemMessageManager* GSystemMessageManager = nullptr;

