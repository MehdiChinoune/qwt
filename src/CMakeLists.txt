set(HEADERS
  qwt.h
  qwt_abstract_scale_draw.h
  qwt_bezier.h
  qwt_clipper.h
  qwt_color_map.h
  qwt_column_symbol.h
  qwt_date.h
  qwt_date_scale_draw.h
  qwt_date_scale_engine.h
  qwt_dyngrid_layout.h
  qwt_global.h
  qwt_graphic.h
  qwt_interval.h
  qwt_interval_symbol.h
  qwt_math.h
  qwt_magnifier.h
  qwt_null_paintdevice.h
  qwt_painter.h
  qwt_painter_command.h
  qwt_panner.h
  qwt_picker.h
  qwt_picker_machine.h
  qwt_pixel_matrix.h
  qwt_point_3d.h
  qwt_point_polar.h
  qwt_round_scale_draw.h
  qwt_scale_div.h
  qwt_scale_draw.h
  qwt_scale_engine.h
  qwt_scale_map.h
  qwt_spline.h
  qwt_spline_basis.h
  qwt_spline_parametrization.h
  qwt_spline_local.h
  qwt_spline_cubic.h
  qwt_spline_pleasing.h
  qwt_spline_polynomial.h
  qwt_symbol.h
  qwt_system_clock.h
  qwt_text_engine.h
  qwt_text_label.h
  qwt_text.h
  qwt_transform.h
  qwt_widget_overlay.h
)
set(SOURCES
  qwt.cpp
  qwt_abstract_scale_draw.cpp
  qwt_bezier.cpp
  qwt_clipper.cpp
  qwt_color_map.cpp
  qwt_column_symbol.cpp
  qwt_date.cpp
  qwt_date_scale_draw.cpp
  qwt_date_scale_engine.cpp
  qwt_dyngrid_layout.cpp
  qwt_event_pattern.cpp
  qwt_graphic.cpp
  qwt_interval.cpp
  qwt_interval_symbol.cpp
  qwt_math.cpp
  qwt_magnifier.cpp
  qwt_null_paintdevice.cpp
  qwt_painter.cpp
  qwt_painter_command.cpp
  qwt_panner.cpp
  qwt_picker.cpp
  qwt_picker_machine.cpp
  qwt_pixel_matrix.cpp
  qwt_point_3d.cpp
  qwt_point_polar.cpp
  qwt_round_scale_draw.cpp
  qwt_scale_div.cpp
  qwt_scale_draw.cpp
  qwt_scale_map.cpp
  qwt_scale_engine.cpp
  qwt_spline.cpp
  qwt_spline_basis.cpp
  qwt_spline_parametrization.cpp
  qwt_spline_local.cpp
  qwt_spline_cubic.cpp
  qwt_spline_pleasing.cpp
  qwt_spline_polynomial.cpp
  qwt_symbol.cpp
  qwt_system_clock.cpp
  qwt_text_engine.cpp
  qwt_text_label.cpp
  qwt_text.cpp
  qwt_transform.cpp
  qwt_widget_overlay.cpp
)

if(QWT_PLOT)
  list(APPEND HEADERS
    qwt_axis.h
    qwt_axis_id.h
    qwt_curve_fitter.h
    qwt_spline_curve_fitter.h
    qwt_weeding_curve_fitter.h
    qwt_event_pattern.h
    qwt_abstract_legend.h
    qwt_legend.h
    qwt_legend_data.h
    qwt_legend_label.h
    qwt_plot.h
    qwt_plot_renderer.h
    qwt_plot_curve.h
    qwt_plot_dict.h
    qwt_plot_directpainter.h
    qwt_plot_graphicitem.h
    qwt_plot_grid.h
    qwt_plot_histogram.h
    qwt_plot_item.h
    qwt_plot_abstract_barchart.h
    qwt_plot_barchart.h
    qwt_plot_multi_barchart.h
    qwt_plot_intervalcurve.h
    qwt_plot_tradingcurve.h
    qwt_plot_layout.h
    qwt_plot_marker.h
    qwt_plot_zoneitem.h
    qwt_plot_textlabel.h
    qwt_plot_rasteritem.h
    qwt_plot_spectrogram.h
    qwt_plot_spectrocurve.h
    qwt_plot_scaleitem.h
    qwt_plot_legenditem.h
    qwt_plot_seriesitem.h
    qwt_plot_shapeitem.h
    qwt_plot_vectorfield.h
    qwt_plot_abstract_canvas.h
    qwt_plot_canvas.h
    qwt_plot_panner.h
    qwt_plot_picker.h
    qwt_plot_zoomer.h
    qwt_plot_magnifier.h
    qwt_plot_rescaler.h
    qwt_point_mapper.h
    qwt_raster_data.h
    qwt_matrix_raster_data.h
    qwt_vectorfield_symbol.h
    qwt_sampling_thread.h
    qwt_samples.h
    qwt_series_data.h
    qwt_series_store.h
    qwt_point_data.h
    qwt_scale_widget.h
  )
  list(APPEND SOURCES
    qwt_curve_fitter.cpp
    qwt_spline_curve_fitter.cpp
    qwt_weeding_curve_fitter.cpp
    qwt_abstract_legend.cpp
    qwt_legend.cpp
    qwt_legend_data.cpp
    qwt_legend_label.cpp
    qwt_plot.cpp
    qwt_plot_renderer.cpp
    qwt_plot_axis.cpp
    qwt_plot_curve.cpp
    qwt_plot_dict.cpp
    qwt_plot_directpainter.cpp
    qwt_plot_graphicitem.cpp
    qwt_plot_grid.cpp
    qwt_plot_histogram.cpp
    qwt_plot_item.cpp
    qwt_plot_abstract_barchart.cpp
    qwt_plot_barchart.cpp
    qwt_plot_multi_barchart.cpp
    qwt_plot_intervalcurve.cpp
    qwt_plot_zoneitem.cpp
    qwt_plot_tradingcurve.cpp
    qwt_plot_spectrogram.cpp
    qwt_plot_spectrocurve.cpp
    qwt_plot_scaleitem.cpp
    qwt_plot_legenditem.cpp
    qwt_plot_seriesitem.cpp
    qwt_plot_shapeitem.cpp
    qwt_plot_vectorfield.cpp
    qwt_plot_marker.cpp
    qwt_plot_textlabel.cpp
    qwt_plot_layout.cpp
    qwt_plot_abstract_canvas.cpp
    qwt_plot_canvas.cpp
    qwt_plot_panner.cpp
    qwt_plot_rasteritem.cpp
    qwt_plot_picker.cpp
    qwt_plot_zoomer.cpp
    qwt_plot_magnifier.cpp
    qwt_plot_rescaler.cpp
    qwt_point_mapper.cpp
    qwt_raster_data.cpp
    qwt_matrix_raster_data.cpp
    qwt_vectorfield_symbol.cpp
    qwt_sampling_thread.cpp
    qwt_series_data.cpp
    qwt_point_data.cpp
    qwt_scale_widget.cpp
  )
endif()

if(QWT_OPENGL)
  list(APPEND HEADERS qwt_plot_opengl_canvas.h)
  list(APPEND SOURCES qwt_plot_opengl_canvas.cpp)
  if(QT_VERSION_MAJOR VERSION_LESS 6)
    list(APPEND HEADERS qwt_plot_glcanvas.h)
    list(APPEND SOURCES qwt_plot_glcanvas.cpp)
  endif()
endif()

if(QWT_SVG)
  list(APPEND HEADERS qwt_plot_svgitem.h)
  list(APPEND SOURCES qwt_plot_svgitem.cpp)
endif()

if(QWT_POLAR)
  list( APPEND HEADERS
    qwt_polar.h
    qwt_polar_canvas.h
    qwt_polar_curve.h
    qwt_polar_fitter.h
    qwt_polar_grid.h
    qwt_polar_itemdict.h
    qwt_polar_item.h
    qwt_polar_layout.h
    qwt_polar_magnifier.h
    qwt_polar_marker.h
    qwt_polar_panner.h
    qwt_polar_picker.h
    qwt_polar_plot.h
    qwt_polar_renderer.h
    qwt_polar_spectrogram.h
  )
  list(APPEND SOURCES
    qwt_polar_canvas.cpp
    qwt_polar_curve.cpp
    qwt_polar_fitter.cpp
    qwt_polar_grid.cpp
    qwt_polar_item.cpp
    qwt_polar_itemdict.cpp
    qwt_polar_layout.cpp
    qwt_polar_magnifier.cpp
    qwt_polar_marker.cpp
    qwt_polar_panner.cpp
    qwt_polar_picker.cpp
    qwt_polar_plot.cpp
    qwt_polar_renderer.cpp
    qwt_polar_spectrogram.cpp
  )
endif()

if(QWT_WIDGETS)
  list(APPEND HEADERS
    qwt_abstract_slider.h
    qwt_abstract_scale.h
    qwt_arrow_button.h
    qwt_analog_clock.h
    qwt_compass.h
    qwt_compass_rose.h
    qwt_counter.h
    qwt_dial.h
    qwt_dial_needle.h
    qwt_knob.h
    qwt_slider.h
    qwt_thermo.h
    qwt_wheel.h
  )
  list(APPEND SOURCES
    qwt_abstract_slider.cpp
    qwt_abstract_scale.cpp
    qwt_arrow_button.cpp
    qwt_analog_clock.cpp
    qwt_compass.cpp
    qwt_compass_rose.cpp
    qwt_counter.cpp
    qwt_dial.cpp
    qwt_dial_needle.cpp
    qwt_knob.cpp
    qwt_slider.cpp
    qwt_thermo.cpp
    qwt_wheel.cpp
  )
endif()

add_library(qwt_objects OBJECT ${SOURCES} ${HEADERS})

target_include_directories(qwt_objects INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/classincludes>
  $<INSTALL_INTERFACE:${QWT_INSTALL_INCLUDEDIR}>
)

target_link_libraries(qwt_objects PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Concurrent
  Qt${QT_VERSION_MAJOR}::PrintSupport
)

target_compile_definitions(qwt_objects PRIVATE
  QT_NO_KEYWORDS
  QWT_MOC_INCLUDE
)

set_target_properties(qwt_objects PROPERTIES AUTOMOC ON)

if(NOT QWT_PLOT)
  target_compile_definitions(qwt_objects PUBLIC NO_QWT_PLOT)
endif()

if(NOT QWT_POLAR)
  target_compile_definitions(qwt_objects PUBLIC NO_QWT_POLAR)
endif()

if(QWT_WIDGETS)
  target_link_libraries(qwt_objects PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
else()
  target_compile_definitions(qwt_objects PUBLIC NO_QWT_WIDGETS)
endif()

if(QWT_OPENGL)
  target_link_libraries(qwt_objects PUBLIC Qt${QT_VERSION_MAJOR}::OpenGL)
  if(QT_VERSION_MAJOR VERSION_GREATER_EQUAL 6)
    target_link_libraries(qwt_objects PUBLIC Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
  endif()
else()
  target_compile_definitions(qwt_objects PUBLIC QWT_NO_OPENGL)
endif()

if(QWT_SVG)
  target_link_libraries(qwt_objects PUBLIC Qt${QT_VERSION_MAJOR}::Svg)
else()
  target_compile_definitions(qwt_objects PUBLIC QWT_NO_SVG)
endif()


if(WIN32 AND QWT_DLL)
  target_compile_definitions(qwt_objects
    PUBLIC QWT_DLL
    PRIVATE QWT_MAKEDLL
  )
endif()

set(QWT_LIBS "")

if(QWT_DLL)
  add_library(qwt_shared SHARED)
  target_link_libraries(qwt_shared PUBLIC qwt_objects)
  list(APPEND QWT_LIBS qwt_shared)
  set_target_properties(qwt_shared PROPERTIES EXPORT_NAME "Qwt_SHARED")
  set_target_properties(qwt_shared PROPERTIES OUTPUT_NAME "qwt${QWT_NAME_SUFFIX}")
endif()

if(QWT_STATIC)
  add_library(qwt_static STATIC)
  target_link_libraries(qwt_static PUBLIC qwt_objects)
  list(APPEND QWT_LIBS qwt_static)
  set_target_properties(qwt_static PROPERTIES EXPORT_NAME "Qwt_STATIC")
  if((MSVC OR (APPLE AND QWT_FRAMEWORK)) AND QWT_DLL)
    set_target_properties(qwt_static PROPERTIES OUTPUT_NAME "qwt${QWT_NAME_SUFFIX}-static")
  else()
    set_target_properties(qwt_static PROPERTIES OUTPUT_NAME "qwt${QWT_NAME_SUFFIX}")
  endif()
endif()

if(QWT_DLL)
  add_library(qwt ALIAS qwt_shared)
else()
  add_library(qwt ALIAS qwt_static)
endif()

if(QWT_DLL AND NOT APPLE AND NOT MSVC)
  set_target_properties(qwt_shared PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
  )
endif()

if(APPLE AND QWT_FRAMEWORK)
  set_target_properties(${QWT_LIBS} PROPERTIES FRAMEWORK TRUE)
endif()

install(TARGETS ${QWT_LIBS} qwt_objects
  EXPORT QwtTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set(QWT_CONFIG_NAME "Qt${QT_VERSION_MAJOR}Qwt6")

install(EXPORT QwtTargets
  FILE ${QWT_CONFIG_NAME}Targets.cmake
  NAMESPACE "Qwt::"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${QWT_CONFIG_NAME}
)
include(CMakePackageConfigHelpers)

get_target_property(QT_LIBRARIES qwt_objects INTERFACE_LINK_LIBRARIES)
string(JOIN " " QT_LIBRARIES ${QT_LIBRARIES})
string(REPLACE "::" "" QT_LIBRARIES ${QT_LIBRARIES})

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/qwt-config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${QWT_CONFIG_NAME}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${QWT_CONFIG_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${QWT_CONFIG_NAME}ConfigVersion.cmake"
  VERSION "${Qwt_VERSION}"
  COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${QWT_CONFIG_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${QWT_CONFIG_NAME}ConfigVersion.cmake
  DESTINATION lib/cmake/${QWT_CONFIG_NAME}
)

install(FILES ${HEADERS}
  DESTINATION ${QWT_INSTALL_INCLUDEDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/classincludes/
  DESTINATION ${QWT_INSTALL_INCLUDEDIR}
  PATTERN "classincludes.pro" EXCLUDE
)

get_target_property(QWT_COMPILE_DEFINITIONS qwt_objects INTERFACE_COMPILE_DEFINITIONS)
string(JOIN " -D" QWT_COMPILE_DEFINITIONS ${QWT_COMPILE_DEFINITIONS})
string(PREPEND QWT_COMPILE_DEFINITIONS "-D")

set(QWT_PKGCONFIG_FILE ${QWT_CONFIG_NAME}.pc)

configure_file(qwt.pc.in ${QWT_PKGCONFIG_FILE} @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${QWT_PKGCONFIG_FILE}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
