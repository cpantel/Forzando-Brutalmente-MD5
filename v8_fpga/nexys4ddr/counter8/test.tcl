proc readProbe {pin} {
  refresh_hw_vio [get_hw_vios {hw_vio_1}]
  return [ get_property INPUT_VALUE [get_hw_probes $pin] ]
}

proc writeProbe {value pin } {
	set_property OUTPUT_VALUE $value [get_hw_probes $pin]
	commit_hw_vio [get_hw_probes ${pin}]
}

proc reset {} {
  writeProbe 0 reset_switch
  writeProbe 1 reset_switch
}

proc disable {} {
  writeProbe 0 enable_switch
}

proc enable {} {
  writeProbe 1 enable_switch
}

proc writeHash {hash} {



  writeProbe [ string range $hash  0  7 ] probe_out1
  writeProbe [ string range $hash  8 15 ] probe_out2
  writeProbe [ string range $hash 16 23 ] probe_out3
  writeProbe [ string range $hash 24 31 ] probe_out4
}

proc readResult {} {
  return [ readProbe target]
}

proc isDone {} {
  return [ readProbe status_done ]
}

proc isFound {} {
  return [ readProbe status_found ]
}


reset

disable

writeHash  2d1bbde2acac0afd07646d98154f402e

enable

while { ! ( [ isDone ] ) } {
    after 1000
}


if { [ isFound ] } {
    set result [ readResult ]
    puts [ readResult ]
} else {
    puts "Not found"
}

disable
