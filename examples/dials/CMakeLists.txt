
add_executable(dials
  main.cpp
  AttitudeIndicator.h
  SpeedoMeter.h
  CockpitGrid.h
  CompassGrid.h
  AttitudeIndicator.cpp
  SpeedoMeter.cpp
  CockpitGrid.cpp
  CompassGrid.cpp
)

target_link_libraries(dials qwt)
