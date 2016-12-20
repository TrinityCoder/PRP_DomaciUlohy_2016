# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW06.

add_executable(HW06 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW06
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	RESOURCE DESTINATION bin/tests_HW06
	)
