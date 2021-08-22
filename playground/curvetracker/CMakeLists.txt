
add_executable(curvetracker
  main.cpp
  CurveTracker.cpp
  CurveTracker.h
  Plot.cpp
  Plot.h
)

target_link_libraries(curvetracker qwt)
