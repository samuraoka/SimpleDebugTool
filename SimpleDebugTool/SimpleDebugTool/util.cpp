#include "stdafx.h"
#include "util.h"

using KennyKerr::windows_exception;

windows_exception::windows_exception(DWORD const value) :
	error { value }
{
}

auto KennyKerr::wait_one(HANDLE const h, DWORD const milliseconds) -> bool
{
	auto const result = WaitForSingleObject(h, milliseconds);

	if (result == WAIT_OBJECT_0) return true;

	if (result == WAIT_TIMEOUT) return false;

	throw windows_exception();
}
