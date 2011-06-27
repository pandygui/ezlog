/******************************************************************************
	ezlog test
	Copyright (C) 2011 Wangbin <wbsecg1@gmail.com>

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

#include "ezlog.h"

int main(int argc, char** argv)
{
	ezlog_init_output("log.txt", Append);
	ezlog_init_format("YY%-%MM%-%DD% %hh%:%mm%:%ss% [tid:%tid% pid:%pid%]-[%file%] %func% @%line%: ");
	ezlog_msg("Hello, cruel world!");
	ezlog_error("Damn! %s", __DATE__);
	ezlog_msg();

	ezlog_log("Only in log file!");

	ezlog_fini();
	return 0;
}

