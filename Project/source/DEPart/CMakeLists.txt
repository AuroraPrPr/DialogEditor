project(DEPart)
add_compile_definitions(DEPART_LIBRARY)
set(DEPARTINCLUDE ${DE_INCLUDE}/DEPart)

#添加头文件
set(HEADER_FILE
    ${DEPARTINCLUDE}/DEBlock.h
    ${DEPARTINCLUDE}/DEBlockBox.h
    ${DEPARTINCLUDE}/DEBlockContainer.h
    ${DEPARTINCLUDE}/DEDialog.h
    ${DEPARTINCLUDE}/DEPart_global.h
    ${DEPARTINCLUDE}/UICommFun.h
)
#添加源文件
set(SOURCE_FILE
    DEBlock.cpp
    DEBlockBox.cpp
    DEBlockContainer.cpp
    DEDialog.cpp
    UICommFun.cpp
)
#UI
file(GLOB UI_FILE "./*.ui")
qt5_wrap_ui(UI_HEADER ${UI_FILE})
source_group("Qt Files/Ui" FILES ${UI_FILE} ${UI_HEADER})
#MOC
qt5_wrap_cpp(MOC_SOURCE ${HEADER_FILE})
source_group("Qt Files/Moc" FILES ${MOC_SOURCE})

add_library(DEPart SHARED
    ${HEADER_FILE}
    ${SOURCE_FILE}
    ${UI_FILE}
    ${MOC_SOURCE}
)

target_link_libraries(DEPart PRIVATE
    Qt5::Core Qt5::Gui Qt5::Widgets
    DERoot
)
