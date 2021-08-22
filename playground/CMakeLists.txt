
set(CMAKE_AUTOMOC ON)

if(QWT_PLOT)
  add_subdirectory(plotmatrix)
  add_subdirectory(timescale)
  add_subdirectory(scaleengine)
  add_subdirectory(rescaler)
  add_subdirectory(shapes)
  add_subdirectory(curvetracker)
  add_subdirectory(vectorfield)
  add_subdirectory(symbols)

  if(QWT_SVG)
    add_subdirectory(svgmap)
    add_subdirectory(graphicscale)
  endif()

endif()
