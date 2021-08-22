
add_executable(distrowatch
  main.cpp
  BarChart.cpp
  BarChart.h
)

target_link_libraries(distrowatch qwt)
