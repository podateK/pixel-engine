find_path(SFML_INCLUDE_DIR SFML/Config.hpp
    HINTS
    $ENV{SFML_DIR}/include
    /usr/local/include
    /usr/include
)

find_library(SFML_SYSTEM_LIBRARY NAMES sfml-system
    HINTS
    $ENV{SFML_DIR}/lib
    /usr/local/lib
    /usr/lib
)

find_library(SFML_WINDOW_LIBRARY NAMES sfml-window
    HINTS
    $ENV{SFML_DIR}/lib
    /usr/local/lib
    /usr/lib
)

find_library(SFML_GRAPHICS_LIBRARY NAMES sfml-graphics
    HINTS
    $ENV{SFML_DIR}/lib
    /usr/local/lib
    /usr/lib
)

find_library(SFML_AUDIO_LIBRARY NAMES sfml-audio
    HINTS
    $ENV{SFML_DIR}/lib
    /usr/local/lib
    /usr/lib
)

find_library(SFML_NETWORK_LIBRARY NAMES sfml-network
    HINTS
    $ENV{SFML_DIR}/lib
    /usr/local/lib
    /usr/lib
)

if(SFML_INCLUDE_DIR)
    file(STRINGS "${SFML_INCLUDE_DIR}/SFML/Config.hpp" SFML_VERSION_LINE
        REGEX "^#define[ \t]+SFML_VERSION_(MAJOR|MINOR|PATCH)$"
    )
    foreach(_comp MAJOR MINOR PATCH)
        foreach(_line ${SFML_VERSION_LINE})
            if(_line MATCHES "^#define[ \t]+SFML_VERSION_${_comp}[ \t]+([0-9]+)$")
                set(SFML_VERSION_${_comp} "${CMAKE_MATCH_1}")
            endif()
        endforeach()
    endforeach()
    set(SFML_VERSION "${SFML_VERSION_MAJOR}.${SFML_VERSION_MINOR}.${SFML_VERSION_PATCH}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SFML
    REQUIRED_VARS SFML_INCLUDE_DIR SFML_SYSTEM_LIBRARY SFML_WINDOW_LIBRARY SFML_GRAPHICS_LIBRARY SFML_AUDIO_LIBRARY
    VERSION_VAR SFML_VERSION
)

if(SFML_FOUND)
    add_library(sfml-system SHARED IMPORTED)
    set_target_properties(sfml-system PROPERTIES
        IMPORTED_LOCATION "${SFML_SYSTEM_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_INCLUDE_DIR}"
    )

    add_library(sfml-window SHARED IMPORTED)
    set_target_properties(sfml-window PROPERTIES
        IMPORTED_LOCATION "${SFML_WINDOW_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_INCLUDE_DIR}"
    )

    add_library(sfml-graphics SHARED IMPORTED)
    set_target_properties(sfml-graphics PROPERTIES
        IMPORTED_LOCATION "${SFML_GRAPHICS_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_INCLUDE_DIR}"
    )

    add_library(sfml-audio SHARED IMPORTED)
    set_target_properties(sfml-audio PROPERTIES
        IMPORTED_LOCATION "${SFML_AUDIO_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${SFML_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(SFML_INCLUDE_DIR SFML_SYSTEM_LIBRARY SFML_WINDOW_LIBRARY SFML_GRAPHICS_LIBRARY SFML_AUDIO_LIBRARY SFML_NETWORK_LIBRARY)
