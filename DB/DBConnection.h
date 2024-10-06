#pragma once

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>

class DBConnection
{
public:
	bool Connection(SQLHENV henv, const WCHAR* connectionString);
	// void Celar();

	bool Execute(const WCHAR* query);
	bool Fetch();
	int GetRowCount();
	void UnBind();

public:
	bool			BindParam(int paramIndex, bool* value, SQLLEN* index);
	bool			BindParam(int paramIndex, float* value, SQLLEN* index);
	bool			BindParam(int paramIndex, double* value, SQLLEN* index);
	bool			BindParam(int paramIndex, short* value, SQLLEN* index);
	bool			BindParam(int paramIndex, int* value, SQLLEN* index);
	bool			BindParam(int paramIndex, long* value, SQLLEN* index);
	bool			BindParam(int paramIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool			BindParam(int paramIndex, const WCHAR* str, SQLLEN* index);
	bool			BindParam(int paramIndex, const BYTE* bin, int size, SQLLEN* index);

	bool			BindCol(int columnIndex, bool* value, SQLLEN* index);
	bool			BindCol(int columnIndex, float* value, SQLLEN* index);
	bool			BindCol(int columnIndex, double* value, SQLLEN* index);
	bool			BindCol(int columnIndex, short* value, SQLLEN* index);
	bool			BindCol(int columnIndex, int* value, SQLLEN* index);
	bool			BindCol(int columnIndex, TIMESTAMP_STRUCT* value, SQLLEN* index);
	bool			BindCol(int columnIndex, WCHAR* str, int size, SQLLEN* index);
	bool			BindCol(int columnIndex, BYTE* bin, int size, SQLLEN* index);

public:

	//query를 실행 시 
	bool BindParam(SQLUSMALLINT paramIndex, SQLSMALLINT);

	//query 실행 후 데이터를 받아 올 때 
	bool BindCol();

private:
	//handle을 2개 소유한다. 
	SQLHDBC  _connection = SQL_NULL_HANDLE;
	SQLHSTMT _statement = SQL_NULL_HANDLE; // 상태를 확인 함
};

