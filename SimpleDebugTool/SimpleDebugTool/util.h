#pragma once

#include <Windows.h>

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

namespace KennyKerr
{
	struct SIMPLEDEBUGTOOL_API windows_exception
	{
		DWORD error;

		explicit windows_exception(DWORD const value = GetLastError());
	};

	auto SIMPLEDEBUGTOOL_API wait_one(
		HANDLE const h, DWORD const milliseconds = INFINITE) -> bool;
}
