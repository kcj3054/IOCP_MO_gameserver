#include "../pch.h"

#include "DBConnection.h"
#include <string>

bool DBConnection::Connection(SQLHENV  henv, const WCHAR* connectionString)
{
    //handle 생성
    if (::SQLAllocHandle(SQL_HANDLE_DBC, henv, &_connection) != SQL_SUCCESS)
        return false;

    WCHAR stringBuffer[MAX_PATH] = { 0 };
    ::wcscpy_s(stringBuffer, connectionString);

    //결과 받을 버퍼 
    WCHAR resultString[MAX_PATH] = { 0 };
    SQLSMALLINT resultStringLen = 0;

    // 데이터베이스에 연결
    SQLCHAR retConString[1024];
    SQLRETURN ret = ::SQLDriverConnectW(
        _connection,
        NULL,
        reinterpret_cast<SQLWCHAR*>(stringBuffer),
        _countof(stringBuffer),
        OUT reinterpret_cast<SQLWCHAR*>(resultString),
        _countof(resultString),
        OUT & resultStringLen,
        SQL_DRIVER_NOPROMPT
    );

    if (::SQLAllocHandle(SQL_HANDLE_STMT, _connection, &_statement) != SQL_SUCCESS)
        return false;

    return false;
}

bool DBConnection::Execute(const WCHAR* query)
{
    auto ret = SQLExecDirectW(_statement, (SQLWCHAR*)query, SQL_NTSL);
    return false;
}

bool DBConnection::Fetch()
{
    SQLRETURN ret = ::SQLFetch(_statement);

    if (ret != SQL_SUCCESS || ret != SQL_SUCCESS_WITH_INFO)
    {
        return false;
    }
    return true;
}

int DBConnection::GetRowCount()
{
    return 0;
}

//SQL BIND로 묶었던 것들을 깔끔하게 CLEAR한다 
void DBConnection::UnBind()
{
    ::SQLFreeStmt(_statement, SQL_UNBIND);
    ::SQLFreeStmt(_statement, SQL_RESET_PARAMS);
    ::SQLFreeStmt(_statement, SQL_CLOSE);
}
