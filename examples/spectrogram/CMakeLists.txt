
add_executable(spectrogram
  main.cpp
  Plot.h
  Plot.cpp
)

target_link_libraries(spectrogram qwt)
