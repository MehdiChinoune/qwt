
add_executable(polardemo
  main.cpp
	Pixmaps.h
	PlotBox.h
	Plot.h
	SettingsEditor.h
	PlotBox.cpp
	Plot.cpp
	SettingsEditor.cpp
)

target_link_libraries(polardemo qwt)
