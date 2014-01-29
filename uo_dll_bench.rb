require 'singleton'
require 'ffi'
require 'pathname'
# require 'pry'
require 'benchmark'
require File.expand_path('../uo_dll', __FILE__)
require File.expand_path('../uo_dll_ffi', __FILE__)

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

class OpenEuoFfiBase
  include Singleton
  include UoDllFfi

  def self.get_dll_path
    File.expand_path('../uo.dll', __FILE__).to_s.to_win32_path
  end

  def get_type_name(handle, index)
    res        = self.get_type(handle, index)
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

OpenEuo    = OpenEuoBase.instance
OpenEuoFfi = OpenEuoFfiBase.instance

both_oeuos    = [OpenEuo, OpenEuoFfi].freeze
repeats_times = [1_000_000 * 10].freeze
handles       = {}

# Ruby code test
both_oeuos.each do |oeuo|
  oeuo.load!
  puts "uo.dll v#{ oeuo.version }"
  handles[oeuo] = oeuo.open

  oeuo.set_top handles[oeuo], 0
  oeuo.push_str_ref handles[oeuo], "Set"
  oeuo.push_str_ref handles[oeuo], "CliNr"
  oeuo.push_integer handles[oeuo], 1
  puts "execute: #{ oeuo.execute handles[oeuo] }"

  oeuo.set_top handles[oeuo], 0
  oeuo.push_str_ref handles[oeuo], "Get"
  oeuo.push_str_ref handles[oeuo], "CliNr"
  puts "execute: #{ oeuo.execute handles[oeuo] }"
  puts "result: #{ oeuo.get_integer handles[oeuo], 1 }"

  oeuo.set_top handles[oeuo], 0
  oeuo.push_str_ref handles[oeuo], "Get"
  oeuo.push_str_ref handles[oeuo], "CliTitle"
  puts "execute: #{ oeuo.execute handles[oeuo] }"
  puts "result: #{ oeuo.get_string handles[oeuo], 1 }"
end

Benchmark.bm do |bm|
  both_oeuos.each do |oeuo|
    repeats_times.each do |repeat_times|
      bm.report "#{ oeuo.class } #{ repeat_times } times" do
        repeat_times.times do
          oeuo.set_top handles[oeuo], 0
          oeuo.push_str_ref handles[oeuo], "Get"
          oeuo.push_str_ref handles[oeuo], "CliTitle"
          oeuo.execute handles[oeuo]
          oeuo.get_string handles[oeuo], 1

          oeuo.set_top handles[oeuo], 0
          oeuo.push_str_ref handles[oeuo], "Get"
          oeuo.push_str_ref handles[oeuo], "CharPosX"
          oeuo.execute handles[oeuo]
          oeuo.get_integer handles[oeuo], 1

          oeuo.set_top handles[oeuo], 0
          oeuo.push_str_ref handles[oeuo], "Get"
          oeuo.push_str_ref handles[oeuo], "CharPosY"
          oeuo.execute handles[oeuo]
          oeuo.get_integer handles[oeuo], 1
        end
      end
    end
  end
end

both_oeuos.each do |oeuo|
  oeuo.close handles[oeuo]
  oeuo.unload!
end