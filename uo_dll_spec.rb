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

	DLL_PATH = Pathname.new('D:/').join(
		'Users',
		'Francesco',
		'Projects',
		'easyuo-ruby',
		'vendor',
		'openeuo',
		'uo.dll'
	).freeze

	def get_dll_path
		# File.expand_path('../uo.dll', __FILE__).to_s.to_win32_path
		DLL_PATH.to_s.to_win32_path
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
# OpenEuo.load!

# puts "uo.dll v#{ OpenEuo.version }"
OpenEuo.hello_world

# puts "Load status: #{ OpenEuo.loaded? }"
# OpenEuo.load!
# puts "Load status: #{ OpenEuo.loaded? }"

# puts "Attached to uo.dll v#{ OpenEuo.version }"

# handle = OpenEuo.open

# begin
# 	OpenEuo.set_top handle, 0

# 	OpenEuo.push_str_ref(handle, 'Get')
# 	OpenEuo.push_str_ref(handle, 'CharType')

# 	puts "execute: " + OpenEuo.execute(handle).to_s
# 	puts "get_top: " + OpenEuo.get_top(handle).to_s
# 	puts "get_type_name: " + OpenEuo.get_type_name(handle, 1).to_s

# 	# ptr = OpenEuo.get_string(handle, 1)
# 	# puts "result: " + ptr.read_string.force_encoding('UTF-8')
# 	# to_read_string = OpenEuo.get_string(handle, 1)
# 	# puts to_read_string.inspect

# 	# puts "isnull: #{ to_read_string.null? }"
# 	# puts "result: " + to_read_string.read_string.force_encoding('UTF-8')
# 	puts "result: " + OpenEuo.get_integer(handle, 1).to_s
# ensure
# 	begin
# 		OpenEuo.set_top handle, 0
# 	ensure
# 		OpenEuo.close handle
# 	end
# end