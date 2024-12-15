#include "pch.h"
#include "CoreGlobal.h"

#include "SendBuffer.h"

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GSendBufferManager = new SendBufferManager();
	}

	~CoreGlobal()
	{
		delete GSendBufferManager;

	}
} GCoreGlobal;