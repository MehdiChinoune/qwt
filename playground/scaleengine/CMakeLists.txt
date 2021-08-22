
add_executable(scaleengine
  main.cpp
  MainWindow.cpp
  MainWindow.h
  Plot.cpp
  Plot.h
  TransformPlot.cpp
  TransformPlot.h
)

target_link_libraries(scaleengine qwt)
