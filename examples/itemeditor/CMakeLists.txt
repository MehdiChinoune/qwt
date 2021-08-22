
add_executable(itemeditor
  main.cpp
  Editor.h
  ShapeFactory.h
  Plot.h
  Editor.cpp
  ShapeFactory.cpp
  Plot.cpp
)

target_link_libraries(itemeditor qwt)
