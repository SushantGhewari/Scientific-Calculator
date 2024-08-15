#include "DatabaseUtils.h"
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

// Convert std::string (UTF-8) to std::wstring (UTF-16)
std::wstring stringToWstring(const std::string& str) {
    if (str.empty()) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

extern "C" __declspec(dllexport) void LogCalculation(const std::string& calculation, const std::string& result) {
    SQLHANDLE sqlEnvHandle;
    SQLHANDLE sqlConnectionHandle;
    SQLHANDLE sqlStatementHandle;
    SQLRETURN retCode;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle);
    SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

    SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnectionHandle);

    retCode = SQLConnect(sqlConnectionHandle, (SQLWCHAR*)L"DSN_NAME", SQL_NTS,
                         (SQLWCHAR*)L"USER", SQL_NTS, (SQLWCHAR*)L"PASSWORD", SQL_NTS);
    if (SQL_SUCCEEDED(retCode)) {
        SQLAllocHandle(SQL_HANDLE_STMT, sqlConnectionHandle, &sqlStatementHandle);

        std::wstring wquery = stringToWstring("INSERT INTO CalculationHistory (Calculation, Result) VALUES (?, ?);");
        SQLPrepare(sqlStatementHandle, (SQLWCHAR*)wquery.c_str(), SQL_NTS);

        std::wstring wcalculation = stringToWstring(calculation);
        std::wstring wresult = stringToWstring(result);

        SQLBindParameter(sqlStatementHandle, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 0, 0, (SQLPOINTER)wcalculation.c_str(), 0, NULL);
        SQLBindParameter(sqlStatementHandle, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 0, 0, (SQLPOINTER)wresult.c_str(), 0, NULL);

        SQLExecute(sqlStatementHandle);

        SQLFreeHandle(SQL_HANDLE_STMT, sqlStatementHandle);
    }

    SQLDisconnect(sqlConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

extern "C" __declspec(dllexport) void ManageHistory(size_t limit) {
    SQLHANDLE sqlEnvHandle;
    SQLHANDLE sqlConnectionHandle;
    SQLHANDLE sqlStatementHandle;
    SQLRETURN retCode;

    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle);
    SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);

    SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnectionHandle);

    retCode = SQLConnect(sqlConnectionHandle, (SQLWCHAR*)L"DSN_NAME", SQL_NTS,
                         (SQLWCHAR*)L"USER", SQL_NTS, (SQLWCHAR*)L"PASSWORD", SQL_NTS);
    if (SQL_SUCCEEDED(retCode)) {
        SQLAllocHandle(SQL_HANDLE_STMT, sqlConnectionHandle, &sqlStatementHandle);

        std::wstring wquery = stringToWstring("DELETE FROM CalculationHistory WHERE Id NOT IN (SELECT TOP ? Id FROM CalculationHistory ORDER BY Timestamp DESC);");
        SQLPrepare(sqlStatementHandle, (SQLWCHAR*)wquery.c_str(), SQL_NTS);

        SQLBindParameter(sqlStatementHandle, 1, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, (SQLPOINTER)&limit, 0, NULL);

        SQLExecute(sqlStatementHandle);

        SQLFreeHandle(SQL_HANDLE_STMT, sqlStatementHandle);
    }

    SQLDisconnect(sqlConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnectionHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}
