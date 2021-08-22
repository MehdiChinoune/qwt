
add_executable(scatterplot
  main.cpp
  Plot.h
  Plot.cpp
)

target_link_libraries(scatterplot qwt)
