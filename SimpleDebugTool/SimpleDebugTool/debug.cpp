#include "stdafx.h"
#include "Tracer.h"

Tracer::Tracer(char const *filename, unsigned const line) :
	m_pid{ _getpid() },
	m_filename{ filename },
	m_line{ line }
{
}

auto Tracer::operator()(wchar_t const *format, ...) const -> void
{
	wchar_t buffer[1024];
	auto count = swprintf_s(buffer, L"[%d] %S(%d): ", m_pid, m_filename, m_line);
	ASSERT(-1 != count);

	va_list args;
	va_start(args, format);
	ASSERT(-1 != _vsnwprintf_s(buffer + count, _countof(buffer) - count,
		_countof(buffer) - count - 1, format, args));
	va_end(args);

	OutputDebugString(buffer);
}
