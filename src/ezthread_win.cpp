/******************************************************************************
	ezthread: a tiny thread wrapper for c++
	Copyright (C) 2011 Wang Bin <wbsecg1@gmail.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
******************************************************************************/

#include "ezthread.h"
#include <windows.h>
#include <process.h>

unsigned long threadId()
{
	return GetCurrentThreadId();
}

long pid()
{
	return _getpid();
}

struct ezmutexprivate {
	CRITICAL_SECTION _criticalSection;
};

ezmutex::ezmutex()
:d(new ezmutexprivate)
{
	InitializeCriticalSection(&d->_criticalSection);
}

ezmutex::~ezmutex()
{
	DeleteCriticalSection(&d->_criticalSection);
	delete d;
}

void ezmutex::lock()
{
	EnterCriticalSection(&d->_criticalSection);
}

void ezmutex::unlock()
{
	LeaveCriticalSection(&d->_criticalSection);
}

