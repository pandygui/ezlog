/******************************************************************************
    prepost.h: Add function calls before/after main()
    Copyright (C) 2012-2013 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/

#ifndef PREPOST_H
#define PREPOST_H

/*Avoid a compiler warning when the arguments is empty,
 *e.g. PRE_FUNC_ADD(foo). The right one is PRE_FUNC_ADD(f,)*/

/*
 *http://buliedian.iteye.com/blog/1069072
 *http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/md/ppc/_crt.c.htm
 */
#if defined(_MSC_VER)
#pragma section(".CRT$XIU", long, read)
#pragma section(".CRT$XPU", long, read)
#define _CRTALLOC(x) __declspec(allocate(x))

/*TODO: Auto unique naming*/
typedef int (__cdecl *_PF)(); /* why not void? */
/*static to avoid multiple defination*/
#define PRE_FUNC_ADD(f, .../*args*/) \
    static int init_##f() { f(__VA_ARGS__); return 0;} \
    _CRTALLOC(".CRT$XIU") static _PF pinit_##f [] = { init_##f }; /*static void (*pinit_##f)() = init_##f //__cdecl */
#define POST_FUNC_ADD(f, .../*args*/) \
    static int deinit_##f() { f(__VA_ARGS__); return 0;} \
    _CRTALLOC(".CRT$XPU") static _PF pdeinit_##f [] = { deinit_##f };
#elif defined(__GNUC__)
#define PRE_FUNC_ADD(f, ...) \
    extern  void init_##f(); \
    __attribute__((constructor)) void init_##f() { f(__VA_ARGS__); }
#define POST_FUNC_ADD(f, ...) \
    extern  void deinit_##f(); \
    __attribute__((destructor)) void deinit_##f() { f(__VA_ARGS__); }

#else
#ifndef __cplusplus
#error Not supported for C: PRE_FUNC_ADD, POST_FUNC_ADD
#endif
#include <stdlib.h>
/*static var init, atexit*/
#define PRE_FUNC_ADD(f, ...) \
    static int init_##f() { f(__VA_ARGS__); return 0; } \
    static int v_init_##f = init_##f();
/*Works for C++. For C, gcc will throw an error:
 *initializer element is not constant */
/*atexit do not support arguments*/
#define POST_FUNC_ADD(f, ...) \
    static void atexit_##f() { atexit(f); } \
    PRE_FUNC_ADD(atexit_##f)
#endif

#endif // PREPOST_H
