/******************************************************************************
	appender.h: description
	Copyright (C) 2012 Wang Bin <wbsecg1@gmail.com>
	
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


#ifndef APPENDER_H
#define APPENDER_H


typedef void (*appender)(const char* msg);


void ezlog_registerAppender(appender handle); //installHandler(handler)
void ezlog_unregisterAppender(appender handle);


enum LogOpenMode {
	Append = 0x01, New = 0x02, OPEN_ON_WRITE = 0x04
};

#define IS_OPEN_ON_WRITE(m) ((m & OPEN_ON_WRITE) == OPEN_ON_WRITE)

void ezlog_add_logfile(const char* path, int mode); //LogOpenMode
void ezlog_remove_logfile(const char* path);

//pre defined appenders: file, console
//just output the layout_string()
void console_appender(const char* msg);
void file_appender(const char* msg);

// for internal use
void __log_to_appenders(const char* msg);



#endif // APPENDER_H