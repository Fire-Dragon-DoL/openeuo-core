require 'ffi'
require 'pathname'
require 'pry'

module UoDll
	extend FFI::Library

	DLL_PATH = Pathname.new('D:/').join(
		'Users',
		'Francesco',
		'Desktop',
		'openeuo_131227',
		'OpenEUO',
		'uo.dll'
	).freeze

	RETURN_TYPES = { nil: 0, bool: 1, number: 3, string: 4 }

  ffi_lib DLL_PATH.to_s

  attach_function "version", 		  "Version", 	  [], 					   :int
  attach_function "open", 			  "Open", 		  [],              :int
  attach_function "close", 			  "Close", 		  [:int],          :void
  attach_function "get_string",   "GetString",  [:int, :int],    :pointer
  attach_function "get_integer",  "GetInteger", [:int, :int],    :int
  attach_function "execute",      "Execute",    [:int],          :int
  attach_function "query",        "Query",      [:int],          :int
  attach_function "push_str_ref", "PushStrRef", [:int, :string], :void
  attach_function "set_top",      "SetTop",     [:int, :int],    :void
  attach_function "get_top",      "GetTop",     [:int], 			   :int
  attach_function "get_type",     "GetType",    [:int, :int],    :int

  def self.get_type_name(handle, index)
  	res 			 = get_type(handle, index)
  	return_res = :nil

  	case res
  	when 0 then return_res = :nil
		when 1 then return_res = :bool
		when 3 then return_res = :number
		when 4 then return_res = :string
		else raise "Unknown return type: #{ res }"
		end

		return_res
  end

end

puts "Attaching to uo.dll v#{ UoDll.version }"

handle = UoDll.open

begin
	UoDll.set_top handle, 0

	UoDll.push_str_ref(handle, 'Get')
	UoDll.push_str_ref(handle, 'CharType')

	puts "execute: " + UoDll.execute(handle).to_s
	puts "get_top: " + UoDll.get_top(handle).to_s
	puts "get_type_name: " + UoDll.get_type_name(handle, 1).to_s

	# ptr = UoDll.get_string(handle, 1)
	# puts "result: " + ptr.read_string.force_encoding('UTF-8')
	# to_read_string = UoDll.get_string(handle, 1)
	# puts to_read_string.inspect

	# puts "isnull: #{ to_read_string.null? }"
	# puts "result: " + to_read_string.read_string.force_encoding('UTF-8')
	puts "result: " + UoDll.get_integer(handle, 1).to_s
ensure
	begin
		UoDll.set_top handle, 0
	ensure
		UoDll.close handle
	end
end