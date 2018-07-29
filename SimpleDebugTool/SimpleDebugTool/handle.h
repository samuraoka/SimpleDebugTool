#pragma once

#include <Windows.h>
#include "debug.h"

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

namespace KennyKerr
{
	template <typename Traits>
	class SIMPLEDEBUGTOOL_API unique_handle
	{
		using pointer = typename Traits::pointer;

		pointer m_value;

		auto close() throw () -> void
		{
			if (*this)
			{
				Traits::close(m_value);
			}
		}

	public:

		// Meaning of = delete after function declaration
		// https://stackoverflow.com/questions/5513881/meaning-of-delete-after-function-declaration
		unique_handle(unique_handle const &) = delete;
		auto operator=(unique_handle const &)->unique_handle & = delete;

		// Throw keyword in function's signature
		// https://stackoverflow.com/questions/1055387/throw-keyword-in-functions-signature
		explicit unique_handle(pointer value = Traits::invalid()) throw() :
			m_value{ value }
		{
		}

		// Move Constructors and Move Assignment Operators (C++)
		// https://docs.microsoft.com/en-us/cpp/cpp/move-constructors-and-move-assignment-operators-cpp
		unique_handle(unique_handle && other) throw() :
			m_value{ other.release() }
		{
		}

		auto operator=(unique_handle && other) throw() -> unique_handle &
		{
			if (this != &other)
			{
				reset(other.release());
			}

			return *this;
		}

		~unique_handle() throw()
		{
			close();
		}

		explicit operator bool() const throw()
		{
			return m_value != Traits::invalid();
		}

		auto get() const throw() -> pointer
		{
			return m_value;
		}

		auto release() throw() -> pointer
		{
			auto value = m_value;
			m_value = Traits::invalid();
			return value;
		}

		auto reset(pointer value = Traits::invalid()) throw() -> bool
		{
			if (m_value != value)
			{
				close();
				m_value = value;
			}

			return static_cast<bool>(*this);
		}

		//TODO
	};

	//TODO

	struct SIMPLEDEBUGTOOL_API null_handle_traits
	{
		using pointer = HANDLE;

		static auto invalid() throw() -> pointer
		{
			return nullptr;
		}

		static auto close(pointer value) throw() -> void
		{
			SIMPLE_VERIFY(CloseHandle(value));
		}
	};

	//TODO

	using null_handle = unique_handle<null_handle_traits>;
	//TODO
}
