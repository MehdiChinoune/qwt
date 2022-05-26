
add_executable(graphicscale
  main.cpp
  Canvas.cpp
  Canvas.h
  MainWindow.cpp
  MainWindow.h
)

target_link_libraries(graphicscale qwt)
