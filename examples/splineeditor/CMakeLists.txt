
add_executable(splineeditor
  main.cpp
  ScalePicker.h
  CanvasPicker.h
  Plot.h
  ScalePicker.cpp
  CanvasPicker.cpp
  Plot.cpp
)

target_link_libraries(splineeditor qwt)
