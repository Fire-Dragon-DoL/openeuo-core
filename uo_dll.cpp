#include "uo_dll.h"

using namespace std;

bool        DllLoaded   = false;
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

void init_dll_procs(VALUE self, const char* dll_path)
{
  HINSTANCE hDLL = LoadLibrary(dll_path);

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

    if (Open == NULL)
    {
      FreeLibrary(hDLL);
    }
    else
    {
      rb_iv_set(self, "@proc_address_Open", Qtrue);
    }
  }
}

void try_dll_load(VALUE self)
{
  VALUE dll_path_rb = rb_funcall(self, rb_intern("get_dll_path"), 0);
  char* dll_path    = StringValueCStr(dll_path_rb);

  init_dll_procs(self, dll_path);

  cout << "\nOpen " << Open << "\n";
  // rb_raise(rb_eLoadError, dll_path);
}

void Init_uo_dll()
{
	UoDll = rb_define_module("UoDll");

	rb_define_method(UoDll, "loaded?", (RUBY_METHOD)method_loaded, 0);
  rb_define_method(UoDll, "load!",   (RUBY_METHOD)method_load,   0);
}

VALUE method_load(VALUE self)
{
  VALUE loaded = rb_funcall(self, rb_intern("loaded?"), 0);

  if (loaded == Qfalse || loaded == Qnil) try_dll_load(self);

  return self;
}

VALUE method_loaded(VALUE self)
{
  return rb_iv_get(self, "@loaded");
}