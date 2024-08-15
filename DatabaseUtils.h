#ifndef DATABASE_UTILS_H
#define DATABASE_UTILS_H

#include <string>

extern "C" __declspec(dllexport) void LogCalculation(const std::string& calculation, const std::string& result);
extern "C" __declspec(dllexport) void ManageHistory(size_t limit);

#endif // DATABASE_UTILS_H
