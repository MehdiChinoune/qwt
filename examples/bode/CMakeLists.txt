
add_executable(bode
  main.cpp
  MainWindow.cpp
  MainWindow.h
  Pixmaps.h
  Plot.cpp
  Plot.h
)

target_link_libraries(bode qwt)
