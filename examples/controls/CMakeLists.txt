
add_executable(controls
  main.cpp
  SliderBox.h
  SliderTab.h
  WheelBox.h
  WheelTab.h
  KnobBox.h
  KnobTab.h
  DialBox.h
  DialTab.h
  SliderBox.cpp
  SliderTab.cpp
  WheelBox.cpp
  WheelTab.cpp
  KnobBox.cpp
  KnobTab.cpp
  DialBox.cpp
  DialTab.cpp
)

target_link_libraries(controls qwt)
