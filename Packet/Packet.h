#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//- 로그인 요청
// const int MAX_USER_ID_LEN = 32;
constexpr int MAX_USER_ID_LEN = 32;
// const int MAX_USER_PW_LEN = 32;
constexpr int MAX_USER_PW_LEN = 32;


struct PacketData
{
	UINT32 SessionIndex = 0;
	UINT32 DataSize = 0;
	char* pPacketData = nullptr;

	void Set(PacketData& vlaue)
	{
		SessionIndex = vlaue.SessionIndex;
		DataSize = vlaue.DataSize;

		pPacketData = new char[vlaue.DataSize];
		CopyMemory(pPacketData, vlaue.pPacketData, vlaue.DataSize);
	}

	void Set(UINT32 sessionIndex_, UINT32 dataSize_, char* pData)
	{
		SessionIndex = sessionIndex_;
		DataSize = dataSize_;

		pPacketData = new char[dataSize_];
		CopyMemory(pPacketData, pData, dataSize_);
	}

	void Release()
	{
		delete pPacketData;
	}
};

struct PacketInfo
{
	int cliendtIndex = 0;
	int packetID = 0;
	int dataszie = 0;

	char* packet;
};

enum class PacketID
{
	// CLIENT
	LOGIN_REQUEST = 101,
	LOGIN_RESPONSE= 102

	// DB

	// SERVER
};