
add_executable(svgmap
  main.cpp
  Plot.cpp
  Plot.h
  svgmap.qrc
)

target_link_libraries(svgmap qwt)
