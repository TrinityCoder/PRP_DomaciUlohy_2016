cmake_minimum_required(VERSION 3.6.1)

# Major verze projektu (to prvni cislo) udava pocet uloh (od zacatku),
# ktere soucasny commit obsahuje, tj. napr. verze 4.0.0 obsahuje
# ulohy HW00 az HW04b (vcetne).
# (Posledni uloha za semestr se jmenuje HW10).
project(CVUT_FEL_PRP_DomaciUlohy_2016 VERSION 6.0 LANGUAGES C)

# Standardne vse kompilujeme s debugovacimi symboly.
set(CMAKE_BUILD_TYPE Debug)

# Vypneme GNU rozsireni jazyka C (toto vynuti kompilaci s --std=c99 misto --std=gnu99)
set(CMAKE_C_EXTENSIONS OFF)

# Nastavime standard jazyka v ulohach na C99...
set(CMAKE_C_STANDARD 99)

# ... a tento standard vynutime.
set(CMAKE_C_STANDARD_REQUIRED ON)

# Pridame -pedantic a -Wall compilation flags.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Werror")

# Nastavime, aby se binarky vsech uloh vytvorily v podslozce 'bin'.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

if(DEFINED MIREK_DBG)
	add_definitions(-DMIREK_DBG=${MIREK_DBG})
endif()

# Pridame podadresare s jednotlivymi ulohami
# (kazda uloha je vlastne samostatny projekt a ma ve svem adresari
# "upresnujici" CMakeLists.txt).
add_subdirectory(HW00)
add_subdirectory(HW01)
add_subdirectory(HW02)
add_subdirectory(HW03)
add_subdirectory(HW04)
add_subdirectory(HW04b)
add_subdirectory(HW05)
add_subdirectory(HW06)

# Nastavime defaultni install prefix na slozku obsahujici korenovy
# CMakeLists.txt...
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install_dir" CACHE PATH
		"Defaultne chceme instalovat lokalne..." FORCE)
endif()

message("     Projekt:  ${PROJECT_NAME}")
message("     Autor:    Miroslav Mares (https://github.com/TrinityCoder)")
message("     Verze:    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
message("     Popis:    Implementace domacich uloh z predmetu Proceduralni programovani,")
message("               ktery byl vyucovan v prvnim semestru ak. roku 2016/2017 na FELu CVUT.")
message("")
message("     CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
message("     CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
if(DEFINED MIREK_DBG)
message("     Passing -DMIREK_DBG=${MIREK_DBG} to preprocessor (applies for all projects) ... TRUE.")
else()
message("     Passing -DMIREK_DBG to preprocessor (applies for all projects) ... FALSE.")
endif()
