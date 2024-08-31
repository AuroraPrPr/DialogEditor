project(DEUIBlock)
add_compile_definitions(DEUIBLOCK_LIBRARY)
set(DEUIBLOCKINCLUDE ${DE_INCLUDE}/DEUIBlock)

#添加头文件
set(HEADER_FILE
    ${DEUIBLOCKINCLUDE}/DEBlockAngularDimension.h
    ${DEUIBLOCKINCLUDE}/DEBlockBasicBase.h
    ${DEUIBLOCKINCLUDE}/DEBlockCommon.h
    ${DEUIBLOCKINCLUDE}/DEBlockDimension.h
    ${DEUIBLOCKINCLUDE}/DEBlockDouble.h
    ${DEUIBLOCKINCLUDE}/DEBlockEnumeration.h
    ${DEUIBLOCKINCLUDE}/DEBlockGroup.h
    ${DEUIBLOCKINCLUDE}/DEBlockInt.h
    ${DEUIBLOCKINCLUDE}/DEBlockLabel.h
    ${DEUIBLOCKINCLUDE}/DEBlockLayoutBase.h
    ${DEUIBLOCKINCLUDE}/DEBlockLinearDimension.h
    ${DEUIBLOCKINCLUDE}/DEBlockNumBase.h
    ${DEUIBLOCKINCLUDE}/DEBlockObject.h
    ${DEUIBLOCKINCLUDE}/DEBlockRadiusDimension.h
    ${DEUIBLOCKINCLUDE}/DEBlockSelectBase.h
    ${DEUIBLOCKINCLUDE}/DEBlockToggle.h
    ${DEUIBLOCKINCLUDE}/DEUIBlock_global.h
    DECtrlLineEdit.h
)
#添加源文件
set(SOURCE_FILE
    DEBlockAngularDimension.cpp
    DEBlockBasicBase.cpp
    DEBlockCommon.cpp
    DEBlockDimension.cpp
    DEBlockDouble.cpp
    DEBlockEnumeration.cpp
    DEBlockGroup.cpp
    DEBlockInt.cpp
    DEBlockLabel.cpp
    DEBlockLayoutBase.cpp
    DEBlockLinearDimension.cpp
    DEBlockNumBase.cpp
    DEBlockObject.cpp
    DEBlockRadiusDimension.cpp
    DEBlockSelectBase.cpp
    DEBlockToggle.cpp
    DECtrlLineEdit.cpp
)
#UI
file(GLOB UI_FILE "./*.ui")
qt5_wrap_ui(UI_HEADER ${UI_FILE})
source_group("Qt Files/Ui" FILES ${UI_FILE} ${UI_HEADER})
#MOC
qt5_wrap_cpp(MOC_SOURCE ${HEADER_FILE})
source_group("Qt Files/Moc" FILES ${MOC_SOURCE})

add_library(DEUIBlock SHARED
    ${HEADER_FILE}
    ${SOURCE_FILE}
    ${UI_FILE}
    ${MOC_SOURCE}
    "DEBlock.qrc"
)

target_link_libraries(DEUIBlock PRIVATE
    Qt5::Core Qt5::Gui Qt5::Widgets
    DERoot DEPart
)
