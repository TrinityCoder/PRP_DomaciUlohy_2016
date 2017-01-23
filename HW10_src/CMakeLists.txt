# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW10.

add_library(HW10_libdijkstra STATIC
          dijkstra.c
          graph_utils.c
          load_simple.c
          pq_heap-no_update.c)

add_executable(HW10_tgraph_search-time tgraph_search-time.c)

target_link_libraries(HW10_tgraph_search-time PUBLIC HW10_libdijkstra)
target_link_libraries(HW10_tgraph_search-time PUBLIC m)

# Zkopirovani testovacich souboru do build/tests_HW10 slozky:
add_custom_command(TARGET HW10_libdijkstra PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW10_libdijkstra>/tests_HW10
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW10_libdijkstra HW10_tgraph_search-time
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
