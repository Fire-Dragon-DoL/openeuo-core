// #include <windows.h>
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

OPEN Open;
CLOSE Close;
VERSION Version;
PUSHNIL PushNil;
PUSHBOOLEAN PushBoolean;
PUSHINTEGER PushInteger;
PUSHDOUBLE PushDouble;
PUSHSTRREF PushStrRef;
PUSHSTRVAL PushStrVal;
GETBOOLEAN GetBoolean;
GETINTEGER GetInteger;
GETDOUBLE GetDouble;
GETSTRING GetString;
GETTOP GetTop;
GETTYPE GetType;
INSERT Insert;
PUSHVALUE PushValue;
REMOVE Remove;
SETTOP SetTop;
MARK Mark;
CLEAN Clean;
EXECUTE Execute;

using namespace std;

// Defining a space for information and references about the module to be stored internally
VALUE Uo = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
extern "C" void Init_uo_dll();

// Prototype for our method 'test1' - methods are prefixed by 'method_' here
extern "C" VALUE method_test1(VALUE self);

// The initialization method for this module
void Init_uo_dll() {
	Uo = rb_define_module("UoDll");
	rb_define_method(Uo, "test1", (RUBY_METHOD)method_test1, 0);
}

// Our 'test1' method.. it simply returns a value of '10' for now.
VALUE method_test1(VALUE self) {
	return self;
}