require File.expand_path('../uo_dll', __FILE__)

class Dummy
	include UoDll

end

puts Dummy.new.test1.inspect