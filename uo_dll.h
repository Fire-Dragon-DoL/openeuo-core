#include <cstring>
#include <cstdio>
#include <iostream>
#include <ruby.h>

typedef VALUE(*RUBY_METHOD)(ANYARGS);

typedef int (__stdcall *OPEN)();
typedef void (__stdcall *CLOSE)(int);
typedef int (__stdcall *VERSION)();
typedef void (__stdcall *PUSHNIL)(int);
typedef void (__stdcall *PUSHBOOLEAN)(int, bool);
typedef void (__stdcall *PUSHINTEGER)(int, int);
typedef void (__stdcall *PUSHDOUBLE)(int, double);
typedef void (__stdcall *PUSHSTRREF)(int, char*);
typedef void (__stdcall *PUSHSTRVAL)(int, char*);
typedef bool (__stdcall *GETBOOLEAN)(int, int);
typedef int (__stdcall *GETINTEGER)(int, int);
typedef double (__stdcall *GETDOUBLE)(int, int);
typedef char* (__stdcall *GETSTRING)(int, int);
typedef int (__stdcall *GETTOP)(int);
typedef int (__stdcall *GETTYPE)(int, int);
typedef void (__stdcall *INSERT)(int, int);
typedef void (__stdcall *PUSHVALUE)(int, int);
typedef void (__stdcall *REMOVE)(int, int);
typedef void (__stdcall *SETTOP)(int, int);
typedef void (__stdcall *MARK)();
typedef void (__stdcall *CLEAN)();
typedef int (__stdcall *EXECUTE)(int);

extern "C" void Init_uo_dll();

VALUE method_load(VALUE);
VALUE method_loaded(VALUE);

void try_dll_load(VALUE);
void init_dll_procs(VALUE, const char*);