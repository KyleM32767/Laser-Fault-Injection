puts [lindex $argv 0]

open_hw_manager
connect_hw_server -url 130.215.23.113:3121
refresh_hw_server
current_hw_target [get_hw_targets */xilinx_tcf/Digilent/200300B18CC7B]
set_property PARAM.FREQUENCY 15000000 [get_hw_targets */xilinx_tcf/Digilent/200300B18CC7B]
open_hw_target
current_hw_device [lindex [get_hw_devices] 0]
refresh_hw_device -update_hw_probes false [lindex [get_hw_devices] 0]
set_property PROGRAM.FILE [lindex $argv 0] [lindex [get_hw_devices] 0]
program_hw_devices [lindex [get_hw_devices] 0]
refresh_hw_device [lindex [get_hw_devices] 0]
