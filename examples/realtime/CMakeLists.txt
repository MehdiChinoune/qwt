
add_executable(realtime
  main.cpp
  ScrollZoomer.h
  ScrollBar.h
  IncrementalPlot.h
  RandomPlot.h
  MainWindow.h
  ScrollZoomer.cpp
  ScrollBar.cpp
  IncrementalPlot.cpp
  RandomPlot.cpp
  MainWindow.cpp
)

target_link_libraries(realtime qwt)
