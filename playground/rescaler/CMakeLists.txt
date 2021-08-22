
add_executable(rescaler
  main.cpp
  MainWindow.cpp
  MainWindow.h
  Plot.cpp
  Plot.h
)

target_link_libraries(rescaler qwt)
