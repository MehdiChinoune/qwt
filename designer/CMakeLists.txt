if(QWT_DESIGNER_SELF_CONTAINED)
  add_library(qwt_designer_plugin SHARED
    qwt_designer_plugin.cpp
    qwt_designer_plugin.qrc
    $<TARGET_OBJECTS:qwt_objects>
  )
  target_link_libraries(qwt_designer_plugin PRIVATE qwt_objects)
  target_compile_definitions(qwt_designer_plugin PRIVATE QWT_MAKEDLL)
else()
  add_library(qwt_designer_plugin SHARED
    qwt_designer_plugin.cpp
    qwt_designer_plugin.qrc
  )
  target_link_libraries(qwt_designer_plugin PRIVATE qwt)
endif()

target_link_libraries(qwt_designer_plugin PUBLIC Qt${QT_VERSION_MAJOR}::Designer)

set_target_properties(qwt_designer_plugin PROPERTIES
  AUTOMOC ON
  AUTORCC ON
)

install(TARGETS qwt_designer_plugin
  RUNTIME DESTINATION ${CMAKE_INSTALL_DATADIR}/qwt/plugins
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/qwt/plugins
)
