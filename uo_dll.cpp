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
QUERY       Query       = NULL;

bool      DllLoaded = false;
VALUE     UoDll     = Qnil;
HINSTANCE hDLL      = NULL;

void init_dll_procs(VALUE self, const char* dll_path)
{
  hDLL = LoadLibrary(dll_path);

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
    Query       = (QUERY)       GetProcAddress( hDLL, "Query"       );

    // Always bind even if load failed
    bind_dll_procs_to_ruby(self);

    if (Open == NULL)
    {
      FreeLibrary(hDLL);
      hDLL = NULL;
    }
    else
      DllLoaded = true;
  }
}

void bind_dll_procs_to_ruby(VALUE self)
{
  rb_define_method(UoDll, "open",         (RUBY_METHOD)method_open,         0);
  rb_define_method(UoDll, "close",        (RUBY_METHOD)method_close,        1);
  rb_define_method(UoDll, "version",      (RUBY_METHOD)method_version,      0);
  rb_define_method(UoDll, "push_nil",     (RUBY_METHOD)method_push_nil,     1);
  rb_define_method(UoDll, "push_boolean", (RUBY_METHOD)method_push_boolean, 2);
  rb_define_method(UoDll, "push_integer", (RUBY_METHOD)method_push_integer, 2);
  rb_define_method(UoDll, "push_double",  (RUBY_METHOD)method_push_double,  2);
  rb_define_method(UoDll, "push_str_ref", (RUBY_METHOD)method_push_str_ref, 2);
  rb_define_method(UoDll, "push_str_val", (RUBY_METHOD)method_push_str_val, 2);
  rb_define_method(UoDll, "get_boolean",  (RUBY_METHOD)method_get_boolean,  2);
  rb_define_method(UoDll, "get_integer",  (RUBY_METHOD)method_get_integer,  2);
  rb_define_method(UoDll, "get_double",   (RUBY_METHOD)method_get_double,   2);
  rb_define_method(UoDll, "get_string",   (RUBY_METHOD)method_get_string,   2);
  rb_define_method(UoDll, "get_top",      (RUBY_METHOD)method_get_top,      1);
  rb_define_method(UoDll, "get_type",     (RUBY_METHOD)method_get_type,     2);
  rb_define_method(UoDll, "insert",       (RUBY_METHOD)method_insert,       2);
  rb_define_method(UoDll, "push_value",   (RUBY_METHOD)method_push_value,   2);
  rb_define_method(UoDll, "remove",       (RUBY_METHOD)method_remove,       2);
  rb_define_method(UoDll, "set_top",      (RUBY_METHOD)method_set_top,      2);
  rb_define_method(UoDll, "mark",         (RUBY_METHOD)method_mark,         0);
  rb_define_method(UoDll, "clean",        (RUBY_METHOD)method_clean,        0);
  rb_define_method(UoDll, "execute",      (RUBY_METHOD)method_execute,      1);
  rb_define_method(UoDll, "query",        (RUBY_METHOD)method_query,        1);
}

void try_dll_load(VALUE self)
{
  VALUE dll_path_rb = rb_funcall(self, rb_intern("get_dll_path"), 0);
  char* dll_path    = StringValueCStr(dll_path_rb);

  init_dll_procs(self, dll_path);

  if (!DllLoaded) rb_raise(rb_eLoadError, dll_path);
}

void Init_uo_dll()
{
  UoDll = rb_define_module("UoDll");

  rb_define_method(UoDll, "loaded?",     (RUBY_METHOD)method_loaded,      0);
  rb_define_method(UoDll, "load!",       (RUBY_METHOD)method_load,        0);
  rb_define_method(UoDll, "unload!",     (RUBY_METHOD)method_unload,      0);
  rb_define_method(UoDll, "hello_world", (RUBY_METHOD)method_hello_world, 0);
}

VALUE method_load(VALUE self)
{
  if (!DllLoaded) try_dll_load(self);

  return Qnil;
}

VALUE method_unload(VALUE self)
{
  if (DllLoaded) FreeLibrary(hDLL);

  return Qnil;
}

VALUE method_loaded(VALUE self)
{
  return DllLoaded ? Qtrue : Qfalse;
}

VALUE method_hello_world(VALUE self)
{
  int hUo;
  char* title;

  method_load(self);

  hUo = Open();
  SetTop(hUo, 0);
  PushStrRef(hUo, const_cast<char*>("Get"));
  PushStrRef(hUo, const_cast<char*>("CliTitle"));
  Execute(hUo);
  title = GetString(hUo, 1);
  cout << "Hello world, client title is: " << title;
  Close(hUo);

  method_unload(self);
}

/***********************
 *       Exports       *
 ***********************/

VALUE method_open(VALUE self)
{
  return INT2FIX(Open());
}

VALUE method_close(VALUE self, VALUE hUo)
{
  Close(FIX2INT(hUo));
  return Qnil;
}

VALUE method_version(VALUE self)
{
  return INT2FIX(Version());
}

VALUE method_push_nil(VALUE self, VALUE hUo)
{
  PushNil(FIX2INT(hUo));
  return Qnil;
}

VALUE method_push_boolean(VALUE self, VALUE hUo, VALUE value)
{
  PushBoolean(FIX2INT(hUo), !(value == Qnil || value == Qfalse));
  return Qnil;
}

VALUE method_push_integer(VALUE self, VALUE hUo, VALUE value)
{
  PushInteger(FIX2INT(hUo), FIX2INT(value));
  return Qnil;
}

VALUE method_push_double(VALUE self, VALUE hUo, VALUE value)
{
  PushDouble(FIX2INT(hUo), NUM2DBL(value));
  return Qnil;
}

/**
 * XXX: What's the difference between these two methods: PushStrRef and Val?
 *      Looks like it doesn't change a lot, basically allocation handle
 *      internally in Val. When passed to ruby, they will always be reallocated,
 *      so we don't really notice anything about this.
 *      Ref: https://www.easyuo.com/forum/viewtopic.php?f=37&t=39638
 **/
VALUE method_push_str_ref(VALUE self, VALUE hUo, VALUE str_ref)
{
  PushStrRef(FIX2INT(hUo), StringValueCStr(str_ref));
  return Qnil;
}

VALUE method_push_str_val(VALUE self, VALUE hUo, VALUE str_val)
{
  PushStrVal(FIX2INT(hUo), StringValueCStr(str_val));
  return Qnil;
}

VALUE method_get_boolean(VALUE self, VALUE hUo, VALUE index)
{
  return GetBoolean(FIX2INT(hUo), FIX2INT(index)) ? Qtrue : Qfalse;
}

VALUE method_get_integer(VALUE self, VALUE hUo, VALUE index)
{
  return INT2FIX(GetInteger(FIX2INT(hUo), FIX2INT(index)));
}

VALUE method_get_double(VALUE self, VALUE hUo, VALUE index)
{
  return rb_float_new(GetDouble(FIX2INT(hUo), FIX2INT(index)));
}

VALUE method_get_string(VALUE self, VALUE hUo, VALUE index)
{
  return rb_str_new2(GetString(FIX2INT(hUo), FIX2INT(index)));
}

VALUE method_get_top(VALUE self, VALUE hUo)
{
  return INT2FIX(GetTop(FIX2INT(hUo)));
}

VALUE method_get_type(VALUE self, VALUE hUo, VALUE index)
{
  return INT2FIX(GetType(FIX2INT(hUo), FIX2INT(index)));
}

VALUE method_insert(VALUE self, VALUE hUo, VALUE index)
{
  Insert(FIX2INT(hUo), FIX2INT(index));
  return Qnil;
}

VALUE method_push_value(VALUE self, VALUE hUo, VALUE index)
{
  PushValue(FIX2INT(hUo), FIX2INT(index));
  return Qnil;
}

VALUE method_remove(VALUE self, VALUE hUo, VALUE index)
{
  Remove(FIX2INT(hUo), FIX2INT(index));
  return Qnil;
}

VALUE method_set_top(VALUE self, VALUE hUo, VALUE index)
{
  SetTop(FIX2INT(hUo), FIX2INT(index));
  return Qnil;
}

VALUE method_mark(VALUE self)
{
  Mark();
  return Qnil;
}

VALUE method_clean(VALUE self)
{
  Clean();
  return Qnil;
}

VALUE method_execute(VALUE self, VALUE hUo)
{
  return INT2FIX(Execute(FIX2INT(hUo)));
}

/**
 * XXX: Method not documented, I suppose is like Execute
 **/
VALUE method_query(VALUE self, VALUE hUo)
{
  return INT2FIX(Query(FIX2INT(hUo)));
}