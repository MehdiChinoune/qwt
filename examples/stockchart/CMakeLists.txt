
add_executable(stockchart
  main.cpp
  Legend.h
  GridItem.h
  Plot.h
  QuoteFactory.h
  Legend.cpp
  GridItem.cpp
  Plot.cpp
  QuoteFactory.cpp
)

target_link_libraries(stockchart qwt)
