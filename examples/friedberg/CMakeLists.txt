
add_executable(friedberg
  main.cpp
  Friedberg2007.h
  Friedberg2007.cpp
  Plot.h
  Plot.cpp
)

target_link_libraries(friedberg qwt)
