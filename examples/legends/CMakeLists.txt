
add_executable(legends
  main.cpp
  MainWindow.h
  Panel.h
  Settings.h
  Plot.h
  MainWindow.cpp
  Panel.cpp
  Plot.cpp
)

target_link_libraries(legends qwt)
