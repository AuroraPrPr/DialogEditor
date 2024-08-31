win32{
    CONFIG(debug, debug|release){
        LIBS += -L../../out/windows_msvc_x64_debug_qmake
        DESTDIR = ../../out/windows_msvc_x64_debug_qmake
    } else {
        LIBS += -L../../out/windows_msvc_x64_release_qmake
        DESTDIR = ../../out/windows_msvc_x64_release_qmake
    }
}


#windows平台下
win32{
    DEFINES += _WINDOWS_SOURCE
}

#linux平台下
unix{
    #linux下只支持64位代码
    DEFINES += _LINUX_SOURCE
}
