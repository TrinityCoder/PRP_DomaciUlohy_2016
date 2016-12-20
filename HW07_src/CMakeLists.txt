# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW07.

add_executable(HW07 main.c lock.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW07
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	RESOURCE DESTINATION bin/tests_HW07
	)
