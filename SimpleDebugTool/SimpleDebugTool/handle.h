#pragma once

#include <Windows.h>
#include "debug.h"

namespace KennyKerr
{
	template <typename Traits>
	class unique_handle
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
		//TODO

		explicit unique_handle(pointer value = Traits::invalid()) throw() :
			m_value{ value }
		{
		}

		//TODO

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

		//TODO
	};

	//TODO

	struct null_handle_traits
	{
		using pointer = HANDLE;

		static auto invalid() throw() -> pointer
		{
			return nullptr;
		}

		static auto close(pointer value) throw() -> void
		{
			VERIFY(CloseHandle(value));
		}
	};

	//TODO

	using null_handle = unique_handle<null_handle_traits>;
	//TODO
}
