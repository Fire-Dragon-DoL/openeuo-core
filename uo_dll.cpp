#include "uo_dll.h"

using namespace std;

OPEN        Open        = NULL;
CLOSE       Close       = NULL;
VERSION     Version     = NULL;
PUSHNIL     PushNil     = NULL;
PUSHBOOLEAN PushBoolean = NULL;
PUSHINTEGER PushInteger = NULL;
PUSHDOUBLE  PushDouble  = NULL;
PUSHSTRREF  PushStrRef  = NULL;
PUSHSTRVAL  PushStrVal  = NULL;
GETBOOLEAN  GetBoolean  = NULL;
GETINTEGER  GetInteger  = NULL;
GETDOUBLE   GetDouble   = NULL;
GETSTRING   GetString   = NULL;
GETTOP      GetTop      = NULL;
GETTYPE     GetType     = NULL;
INSERT      Insert      = NULL;
PUSHVALUE   PushValue   = NULL;
REMOVE      Remove      = NULL;
SETTOP      SetTop      = NULL;
MARK        Mark        = NULL;
CLEAN       Clean       = NULL;
EXECUTE     Execute     = NULL;

VALUE UoDll = Qnil;

void Init_dll_procs()
{
  HINSTANCE hDLL = LoadLibrary("uo.dll");

  if (hDLL != NULL)
  {
    Open        = (OPEN)        GetProcAddress( hDLL, "Open"        );
    Close       = (CLOSE)       GetProcAddress( hDLL, "Close"       );
    Version     = (VERSION)     GetProcAddress( hDLL, "Version"     );
    PushNil     = (PUSHNIL)     GetProcAddress( hDLL, "PushNil"     );
    PushBoolean = (PUSHBOOLEAN) GetProcAddress( hDLL, "PushBoolean" );
    PushInteger = (PUSHINTEGER) GetProcAddress( hDLL, "PushInteger" );
    PushDouble  = (PUSHDOUBLE)  GetProcAddress( hDLL, "PushDouble"  );
    PushStrRef  = (PUSHSTRREF)  GetProcAddress( hDLL, "PushStrRef"  );
    PushStrVal  = (PUSHSTRVAL)  GetProcAddress( hDLL, "PushStrVal"  );
    GetBoolean  = (GETBOOLEAN)  GetProcAddress( hDLL, "GetBoolean"  );
    GetInteger  = (GETINTEGER)  GetProcAddress( hDLL, "GetInteger"  );
    GetDouble   = (GETDOUBLE)   GetProcAddress( hDLL, "GetDouble"   );
    GetString   = (GETSTRING)   GetProcAddress( hDLL, "GetString"   );
    GetTop      = (GETTOP)      GetProcAddress( hDLL, "GetTop"      );
    GetType     = (GETTYPE)     GetProcAddress( hDLL, "GetType"     );
    Insert      = (INSERT)      GetProcAddress( hDLL, "Insert"      );
    PushValue   = (PUSHVALUE)   GetProcAddress( hDLL, "PushValue"   );
    Remove      = (REMOVE)      GetProcAddress( hDLL, "Remove"      );
    SetTop      = (SETTOP)      GetProcAddress( hDLL, "SetTop"      );
    Mark        = (MARK)        GetProcAddress( hDLL, "Mark"        );
    Clean       = (CLEAN)       GetProcAddress( hDLL, "Clean"       );
    Execute     = (EXECUTE)     GetProcAddress( hDLL, "Execute"     );

    if (!Open) FreeLibrary(hDLL);
  }
}

void Init_uo_dll()
{
	UoDll = rb_define_module("UoDll");
	rb_define_method(UoDll, "test1", (RUBY_METHOD)method_test1, 0);
}

VALUE method_test1(VALUE self)
{
	return self;
}