cmake_minimum_required(VERSION 3.6.1)

# Major verze projektu (to prvni cislo) udava pocet uloh (od zacatku),
# ktere soucasny commit obsahuje, tj. napr. verze 4.0.0 obsahuje
# ulohy HW00 az HW04b (vcetne).
# (Posledni uloha za semestr se jmenuje HW10).
project(CVUT_FEL_PRP_DomaciUlohy_2016 VERSION 9.0 LANGUAGES C)

# Standardne vse kompilujeme s debugovacimi symboly.
set(CMAKE_BUILD_TYPE Debug)

# Vypneme GNU rozsireni jazyka C (toto vynuti kompilaci s --std=c99 misto --std=gnu99)
set(CMAKE_C_EXTENSIONS OFF)

# Nastavime standard jazyka v ulohach na C99...
set(CMAKE_C_STANDARD 99)

# ... a tento standard vynutime.
set(CMAKE_C_STANDARD_REQUIRED ON)

# Pridame -pedantic, -Wall a -Werror compilation flags.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall -Werror")

# Nastavime, aby se binarky vsech uloh vytvorily primo ve slozce build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
# ... to same, ale pro staticke knihovny (pro dynamicke by bylo LIBRARY misto ARCHIVE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Pro pripad, kdy by nekdo omylem spustil "make install", tak aby mu to nezaplavilo
# /usr/local/... slozky, tak se to nainstaluje do slozky install_dir, ktera se vytvori
# v korenovem adresari, kde je naklonovan tento github projekt - pokud by
# z nejakeho duvodu to nekdo fakt chtel instalovat, musi pri volani cmake
# specifikovat -DCMAKE_INSTALL_PREFIX.
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install_dir" CACHE PATH
		"Defaultne chceme instalovat lokalne..." FORCE)
endif()

# Pridame podadresare s jednotlivymi ulohami
# (kazda uloha je vlastne samostatny projekt a ma ve svem adresari
# "upresnujici" CMakeLists.txt).
add_subdirectory(HW00_src)
add_subdirectory(HW01_src)
add_subdirectory(HW02_src)
add_subdirectory(HW03_src)
add_subdirectory(HW04_src)
add_subdirectory(HW04b_src)
add_subdirectory(HW05_src)
#add_subdirectory(HW05b_src)  - neimplementovano (a asi ani nebude)
add_subdirectory(HW06_src)
add_subdirectory(HW07_src)
add_subdirectory(HW08_src)
add_subdirectory(HW09_src)
add_subdirectory(HW10_src)

# (Kopirovani testovaci souboru pro kazdou ulohu je naskriptovane
# v CMakeFile.txt souborech v techto slozkach.)

message("     Projekt:  ${PROJECT_NAME}")
message("     Autor:    Miroslav Mares (https://github.com/TrinityCoder)")
message("     Verze:    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
message("     Popis:    Implementace domacich uloh z predmetu Proceduralni programovani,")
message("               ktery byl vyucovan v prvnim semestru ak. roku 2016/2017 na FELu CVUT.")
message("")
message("     CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
message("     CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
