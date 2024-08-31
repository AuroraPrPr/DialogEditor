project(DEMain)

include_directories(${MAIN_LICENSED}/SARibbon/src/SARibbonBar)
link_directories(${MAIN_LICENSED}/SARibbon/bin_qt${Qt5Widgets_VERSION}_${CMAKE_BUILD_TYPE}_${CKMAK_COMPILER_BITS}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SARibbon SARibbonBard)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SARibbon SARibbonBar)
endif()

#添加头文件
set(HEADER_FILE
    BindButtonID.h
    DEBlockTree.h
    DEDelegate.h
    DEDialogTree.h
    DEMainWidget.h
    DEPropTree.h
    DETreeTable.h
    SARibbonHeaders.h
    mainwindow.h
)
#添加源文件
set(SOURCE_FILE
    DEBlockTree.cpp
    DEDialogTree.cpp
    DEMainWidget.cpp
    DEPropTree.cpp
    DETreeTable.cpp
    main.cpp
    mainwindow.cpp
)
#UI
file(GLOB UI_FILE "./*.ui")
qt5_wrap_ui(UI_HEADER ${UI_FILE})
source_group("Qt Files/Ui" FILES ${UI_FILE} ${UI_HEADER})
#MOC
qt5_wrap_cpp(MOC_SOURCE ${HEADER_FILE})
source_group("Qt Files/Moc" FILES ${MOC_SOURCE})

add_executable(DEMain
    ${HEADER_FILE}
    ${SOURCE_FILE}
    ${UI_FILE}
    ${MOC_SOURCE}
    "DEMain.qrc"
    "logo.rc"
)

target_link_libraries(DEMain PRIVATE
    Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets
    DERoot DEPart DEUIBlock
    ${SARibbon}
)
