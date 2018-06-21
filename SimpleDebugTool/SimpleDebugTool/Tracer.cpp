#include "stdafx.h"
#include "Tracer.h"

Tracer::Tracer(char const *filename, unsigned const line) :
	m_filename{ filename },
	m_line{ line }
{
}

template <typename... Args>
auto Tracer::operator()(wchar_t const *format, Args... args) const -> void
{
	wchar_t buffer[1024];
	auto count = swprintf_s(buffer, L"%S(%d): ", m_filename, m_line);
	ASSERT(-1 != count);

	ASSERT(-1 != _snwprintf_s(buffer + count, _countof(buffer) - count,
		_countof(buffer) - count - 1, format, args...));

	OutputDebugString(buffer);
}
