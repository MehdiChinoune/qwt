
add_executable(tvplot
  main.cpp
  TVPlot.h
  TVPlot.cpp
)

target_link_libraries(tvplot qwt)
