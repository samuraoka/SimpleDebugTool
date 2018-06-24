#include "stdafx.h"
#include "event.h"

using KennyKerr::event_type;
using KennyKerr::event;

KennyKerr::event::event(event_type type) :
	h{ CreateEvent(nullptr, static_cast<BOOL>(type), false, nullptr) }
{
	if (!h) throw windows_exception();
}

KennyKerr::event::event(event && other) throw() :
	h{ other.h.release() }
{
}

auto KennyKerr::event::operator=(event && other) throw()->event &
{
	// std::move
	// https://en.cppreference.com/w/cpp/utility/move
	h = std::move(other.h);
	return *this;
}

auto event::set() throw() -> void
{
	VERIFY(SetEvent(h.get()));
}

auto event::clear() throw() -> void
{
	VERIFY(ResetEvent(h.get()));
}

auto event::wait(DWORD const milliseconds) throw() -> bool
{
	auto const result = WaitForSingleObject(h.get(), milliseconds);
	ASSERT(result == WAIT_OBJECT_0 || result == WAIT_TIMEOUT);

	return result == WAIT_OBJECT_0;
}

auto event::get() const throw() -> HANDLE
{
	return h.get();
}
