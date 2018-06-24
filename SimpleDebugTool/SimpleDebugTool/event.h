#pragma once

#include <utility>
#include "handle.h"
#include "util.h"

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

namespace KennyKerr
{
	enum class event_type
	{
		auto_reset,
		manual_reset,
	};

	class SIMPLEDEBUGTOOL_API event
	{
		null_handle h;

	public:
		// Meaning of = delete after function declaration
		// https://stackoverflow.com/questions/5513881/meaning-of-delete-after-function-declaration
		event(event const &) = delete;
		auto operator=(event const &)->event & = delete;
		~event() = default;

		explicit event(event_type type);

		// Move Constructors and Move Assignment Operators (C++)
		// https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp
		// 
		// Throw keyword in function's signature
		// https://stackoverflow.com/questions/1055387/throw-keyword-in-functions-signature
		event(event && other) throw();

		auto operator=(event && other) throw()->event &;

		auto set() throw() -> void;
		auto clear() throw() -> void;
		auto wait(DWORD const milliseconds = INFINITE) throw() -> bool;
		auto get() const throw()->HANDLE;
	};
}
