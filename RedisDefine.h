#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Packet/Packet.h"

enum class RedisPacketID : UINT16
{
	/*
	* INVALID ~ END로 범위를 나누고 로직처리하는 부분에서 방어코드로 검증한다. 
	*/
	INVALID = 0,

	REQUES_LOGIN = 100,
	RESPONSE_LOGIN = 101,

	END = 300
};

struct RedisTask
{
	UINT32 userIndx = 0;
	char* pData = nullptr;
	UINT32 dataSize = 0;
	RedisPacketID packetID = RedisPacketID::INVALID;

	void Release()
	{
		if (pData != nullptr)
		{

		}
	}
};

#pragma pack(push, 1)

struct RedisLoginReq
{
	char UserID[MAX_USER_ID_LEN + 1];
	char UserPassword[MAX_USER_PW_LEN + 1];
};

#pragma pack(pop)
