require 'ffi'

module UoDllFfi
  extend FFI::Library

  def loaded?
    @loaded
  end

  def load!
    unless @permanently_loaded
      dll_path = self.class.get_dll_path
      UoDllFfi.class_eval do
        ffi_lib dll_path

        attach_function :open,         'Open',        [],              :int
        attach_function :set_top,      'SetTop',      [:int, :int],    :void
        attach_function :push_str_ref, 'PushStrRef',  [:int, :string], :void
        attach_function :push_integer, 'PushInteger', [:int, :int],    :void
        attach_function :execute,      'Execute',     [:int],          :int
        attach_function :get_integer,  'GetInteger',  [:int, :int],    :int
        attach_function :get_string,   'GetString',   [:int, :int],    :string
        attach_function :get_type,     'GetType',     [:int, :int],    :int
        attach_function :version,      'Version',     [],              :int
        attach_function :close,        'Close',       [:int],          :void
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