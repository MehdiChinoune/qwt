
add_executable(polarspectrogram
  main.cpp
	Plot.h
	PlotWindow.h
	Plot.cpp
	PlotWindow.cpp
)

target_link_libraries(polarspectrogram qwt)
