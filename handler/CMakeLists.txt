project(qBreakpad VERSION 0.2.1.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

find_package(unofficial-breakpad CONFIG REQUIRED)

add_compile_definitions(${PROJECT_NAME} PRIVATE CALIPER)

if(QBREAKPAD_BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC)
    target_compile_definitions(${PROJECT_NAME} PUBLIC QBREAKPAD_STATIC)
else()
    add_library(${PROJECT_NAME} SHARED)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE QBREAKPAD_LIBRARY)

target_sources(${PROJECT_NAME} PRIVATE
    QBreakpadGlobal.h
    QBreakpadHandler.h
    QBreakpadHandler.cpp
    QBreakpadHttpUploader.h
    QBreakpadHttpUploader.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    unofficial::breakpad::libbreakpad
    unofficial::breakpad::libbreakpad_client
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

if(QBREAKPAD_INSTALL)
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${QBREAKPAD_INSTALL_NAME}>"
    )

    install(TARGETS ${PROJECT_NAME}
        EXPORT ${QBREAKPAD_INSTALL_NAME}Targets
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" OPTIONAL
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" OPTIONAL
    )

    # Install headers
    install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/QBreakpadGlobal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/QBreakpadHandler.h
        ${CMAKE_CURRENT_SOURCE_DIR}/QBreakpadHttpUploader.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${QBREAKPAD_INSTALL_NAME}
    )
endif()

if(QBREAKPAD_INSTALL)
    # Add install target
    set(_install_dir ${CMAKE_INSTALL_LIBDIR}/cmake/${QBREAKPAD_INSTALL_NAME})

    # Add version file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${QBREAKPAD_INSTALL_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # Add configuration file
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/${QBREAKPAD_INSTALL_NAME}Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${QBREAKPAD_INSTALL_NAME}Config.cmake"
        INSTALL_DESTINATION ${_install_dir}
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    # Install cmake files
    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${QBREAKPAD_INSTALL_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${QBREAKPAD_INSTALL_NAME}ConfigVersion.cmake"
        DESTINATION ${_install_dir}
    )

    # Install cmake targets files
    install(EXPORT ${QBREAKPAD_INSTALL_NAME}Targets
        FILE "${QBREAKPAD_INSTALL_NAME}Targets.cmake"
        NAMESPACE ${QBREAKPAD_INSTALL_NAME}::
        DESTINATION ${_install_dir}
    )
endif()