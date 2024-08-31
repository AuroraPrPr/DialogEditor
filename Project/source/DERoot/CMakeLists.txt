project(DERoot)
add_compile_definitions(DEROOT_LIBRARY)
set(DEROOTINCLUDE ${DE_INCLUDE}/DERoot)

#添加头文件
set(HEADER_FILE
    ${DEROOTINCLUDE}/DECmd.h
	${DEROOTINCLUDE}/DEPart.h
	${DEROOTINCLUDE}/DECmdCollection.h
	${DEROOTINCLUDE}/DEPartCollection.h
	${DEROOTINCLUDE}/DERoot_global.h
	${DEROOTINCLUDE}/DERoot.h
	${DE_INCLUDE}/DECommon.h
)
#添加源文件
set(SOURCE_FILE
    DEPart.cpp
    DECmdCollection.cpp
    DEPartCollection.cpp
    DERoot.cpp
)
#UI
file(GLOB UI_FILE "./*.ui")
qt5_wrap_ui(UI_HEADER ${UI_FILE})
source_group("Qt Files/Ui" FILES ${UI_FILE} ${UI_HEADER})
#MOC
qt5_wrap_cpp(MOC_SOURCE ${HEADER_FILE})
source_group("Qt Files/Moc" FILES ${MOC_SOURCE})

add_library(DERoot SHARED
    ${HEADER_FILE}
    ${SOURCE_FILE}
    ${UI_FILE}
    ${MOC_SOURCE}
)

target_link_libraries(DERoot PRIVATE
    Qt5::Core Qt5::Gui Qt5::Xml Qt5::Widgets
)