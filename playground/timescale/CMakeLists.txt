
add_executable(timescale
  main.cpp
  MainWindow.cpp
  MainWindow.h
  Panel.cpp
  Panel.h
  Plot.cpp
  Plot.h
  Settings.h
)

target_link_libraries(timescale qwt)
