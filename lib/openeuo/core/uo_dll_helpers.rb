module Openeuo::Core::UoDllHelpers

  # Gem.win_platform? to discover if we are on windows and convert dll path
  def string_to_win32_path(str, end_slash=false)
    str_path = str
    str_path = str_path.slice(0,1).capitalize + str_path.slice(1..-1)
    "#{'\\\\' if str_path[0]=='//'}#{str_path.split('/').join('\\')}#{'\\' if end_slash}" 
  end

  def get_type_name(handle, index)
    res        = get_type(handle, index)
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