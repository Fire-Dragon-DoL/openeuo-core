require 'singleton'
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

	def get_dll_path
		File.expand_path('../uo.dll', __FILE__).to_s.to_win32_path
	end

end

OpenEuo = OpenEuoBase.instance

OpenEuo.load!
puts OpenEuo.loaded?.inspect