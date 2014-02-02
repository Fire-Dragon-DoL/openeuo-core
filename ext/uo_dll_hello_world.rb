require 'singleton'
require 'ffi'
require 'pathname'
require 'pry'
require File.expand_path('../uo_dll', __FILE__)

class String

  def to_unix_path(end_slash=false)
  	str_path = self
    "#{'/' if str_path[0]=='\\'}#{str_path.split('\\').join('/')}#{'/' if end_slash}" 
  end

  def to_win32_path(end_slash=false)
  	str_path = self
  	str_path = str_path.slice(0,1).capitalize + str_path.slice(1..-1)
    "#{'\\\\' if str_path[0]=='//'}#{str_path.split('/').join('\\')}#{'\\' if end_slash}" 
  end

end

class OpenEuoBase
	include Singleton
	include UoDll

	def self.get_dll_path
		File.expand_path('../uo.dll', __FILE__).to_s.to_win32_path
	end

  def get_type_name(handle, index)
  	res 			 = self.get_type(handle, index)
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

OpenEuo = OpenEuoBase.instance

# C code test
OpenEuo.hello_world

# Ruby code test
OpenEuo.load!
puts "uo.dll v#{ OpenEuo.version }"
handle = OpenEuo.open

OpenEuo.set_top handle, 0
OpenEuo.push_str_ref handle, "Set"
OpenEuo.push_str_ref handle, "CliNr"
OpenEuo.push_integer handle, 1
puts "execute: #{ OpenEuo.execute handle }"

OpenEuo.set_top handle, 0
OpenEuo.push_str_ref handle, "Get"
OpenEuo.push_str_ref handle, "CliNr"
puts "execute: #{ OpenEuo.execute handle }"
puts "result: #{ OpenEuo.get_integer handle, 1 }"

OpenEuo.set_top handle, 0
OpenEuo.push_str_ref handle, "Get"
OpenEuo.push_str_ref handle, "CliTitle"
puts "execute: #{ OpenEuo.execute handle }"
puts "result: #{ OpenEuo.get_string handle, 1 }"

OpenEuo.set_top handle, 0
OpenEuo.push_str_ref handle, "Get"
OpenEuo.push_str_ref handle, "CharPosX"
puts "execute: #{ OpenEuo.execute handle }"
puts "result: #{ OpenEuo.get_integer handle, 1 }"

OpenEuo.set_top handle, 0
OpenEuo.push_str_ref handle, "Get"
OpenEuo.push_str_ref handle, "CharPosY"
puts "execute: #{ OpenEuo.execute handle }"
puts "result: #{ OpenEuo.get_integer handle, 1 }"

OpenEuo.close handle
OpenEuo.unload!