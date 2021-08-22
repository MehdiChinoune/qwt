
add_executable(oscilloscope
  main.cpp
  SignalData.h
  Plot.h
  Knob.h
  WheelBox.h
  SamplingThread.h
  MainWindow.h
  SignalData.cpp
  Plot.cpp
  Knob.cpp
  WheelBox.cpp
  SamplingThread.cpp
  MainWindow.cpp
)

target_link_libraries(oscilloscope qwt)
