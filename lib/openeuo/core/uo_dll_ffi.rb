require 'ffi'

module Openeuo::Core::UoDllFfi
  extend  FFI::Library

  def loaded?
    @loaded
  end

  # This is managed in this way because I want to input dll path dinamically
  def load!
    unless @permanently_loaded
      dll_path = self.class.get_dll_path
      Openeuo::Core::UoDllFfi.class_eval do

        ffi_lib dll_path

        attach_function :open,         'Open',        [               ], :int
        attach_function :close,        'Close',       [ :int          ], :void
        attach_function :version,      'Version',     [               ], :int
        attach_function :push_nil,     'PushNil',     [ :int          ], :void
        attach_function :push_boolean, 'PushBoolean', [ :int, :bool   ], :void
        attach_function :push_integer, 'PushInteger', [ :int, :int    ], :void
        attach_function :push_double,  'PushDouble',  [ :int, :double ], :void
        attach_function :push_str_ref, 'PushStrRef',  [ :int, :string ], :void
        attach_function :push_str_val, 'PushStrVal',  [ :int, :string ], :void
        attach_function :get_boolean,  'GetBoolean',  [ :int, :int    ], :bool
        attach_function :get_integer,  'GetInteger',  [ :int, :int    ], :int
        attach_function :get_double,   'GetDouble',   [ :int, :int    ], :double
        attach_function :get_string,   'GetString',   [ :int, :int    ], :string
        attach_function :get_top,      'GetTop',      [ :int          ], :int
        attach_function :get_type,     'GetType',     [ :int, :int    ], :int
        attach_function :insert,       'Insert',      [ :int, :int    ], :void
        attach_function :push_value,   'PushValue',   [ :int, :int    ], :void
        attach_function :remove,       'Remove',      [ :int, :int    ], :void
        attach_function :set_top,      'SetTop',      [ :int, :int    ], :void
        attach_function :mark,         'Mark',        [               ], :void
        attach_function :clean,        'Clean',       [               ], :void
        attach_function :execute,      'Execute',     [ :int          ], :int
        attach_function :query,        'Query',       [ :int          ], :int
      end

      @permanently_loaded = true
    end
    @loaded = true

    nil
  end

  def unload!
    @loaded = false

    nil
  end
end