
add_executable(radio
  main.cpp
  AmplifierBox.h
  TunerBox.h
  AmplifierBox.cpp
  TunerBox.cpp
)

target_link_libraries(radio qwt)
