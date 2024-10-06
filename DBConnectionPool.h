#pragma once

#include "DBConnection.h"
#include <vector>

class DBConnectionPool
{
public:

	bool Connect(__int32 connectionCount, const char* connectionString);
	// void Clear();

	DBConnection* Pop();
	void Push(DBConnection* connection);
private:
	//use_lock;..

	std::vector<DBConnection> _connections;
	SQLHENV  _environment = SQL_NULL_HANDLE; //ENV를 담당하는 HANDLE이다 
};

