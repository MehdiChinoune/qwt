
add_executable(cpuplot
  main.cpp
  CpuPieMarker.cpp
  CpuPieMarker.h
  CpuPlot.cpp
  CpuPlot.h
  CpuStat.cpp
  CpuStat.h
)

target_link_libraries(cpuplot qwt)
