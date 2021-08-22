
add_executable(refreshtest
  main.cpp
  Settings.h
  CircularBuffer.h
  Panel.h
  Plot.h
  MainWindow.h
  CircularBuffer.cpp
  Panel.cpp
  Plot.cpp
  MainWindow.cpp
)

target_link_libraries(refreshtest qwt)
