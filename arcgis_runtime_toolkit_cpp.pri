#-------------------------------------------------
#  Copyright 2019 ESRI
#
#  All rights reserved under the copyright laws of the United States
#  and applicable international laws, treaties, and conventions.
#
#  You may freely redistribute and use this sample code, with or
#  without modification, provided you include the original copyright
#  notice and use restrictions.
#
#  See the Sample code usage restrictions document for further information.
#-------------------------------------------------

ESRIRUNTIME_QT_VERSION = 100.5
ESRIRUNTIME_QT_MAJOR_VERSION = 100
ESRIRUNTIME_QT_MINOR_VERSION = 5

#-------------------------------------------------
# Compiler options
#-------------------------------------------------

SDK_INSTALL_DIR = "C:/Program Files (x86)/ArcGIS SDKs/Qt100.5"

unix:!macx:!android:!ios {
    eval(QMAKE_TARGET.arch = ""):{
        # QMAKE_TARGET.arch isn't set properly on Linux.
        # If we get a bitset-specific mkspec, use it
        linux-g++-32:QMAKE_TARGET.arch = x86
        linux-g++-64:QMAKE_TARGET.arch = x86_64

        # If we get a generic one, then determine the
        # arch of the machine and assign
        linux-g++:{
            ARCH = $$system(uname -m) # i686 or x86_64
            contains(ARCH, x86_64):{
                QMAKE_TARGET.arch = x86_64
            }
            else{
                QMAKE_TARGET.arch = x86
            }
        } # linux-g++
    } # eval

    QMAKE_CXXFLAGS += --std=c++0x
} # unix

ios {
    QMAKE_IOS_DEPLOYMENT_TARGET = 11.0
}

macx {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13

    QMAKE_POST_LINK  += install_name_tool -change libArcGISRuntimeToolkitCppApi.dylib \"$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x64/lib/libArcGISRuntimeToolkitCppApi.dylib\" $${TARGET}.app/Contents/MacOS/$${TARGET} $$escape_expand(\n\t)
}

#-------------------------------------------------
#  Headers
#-------------------------------------------------

INCLUDEPATH += "$${SDK_INSTALL_DIR}/sdk/toolkit/Plugin/CppApi/include" \
               "$${SDK_INSTALL_DIR}/sdk/toolkit/Plugin/CppApi/include/CoordinateConversion"

#-------------------------------------------------
#  Libraries
#-------------------------------------------------

contains(QMAKE_TARGET.arch, x86):{
  unix:!macx:!android:!ios {
    LIBS += \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x86/lib \
      -lArcGISRuntimeToolkitCppApi
  }
}
else {
  unix:!macx:!android:!ios {
    LIBS += \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x64/lib \
      -L/usr/lib64 \
      -lArcGISRuntimeToolkitCppApi
  }
}

macx:{
  LIBS += \
    -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x64/lib \
    -lArcGISRuntimeToolkitCppApi
}

win32:{
  CONFIG(debug, debug|release) {
    QMAKE_CXXFLAGS += /FS
    QMAKE_LFLAGS += /IGNORE:4099
  }

  contains(QT_ARCH, x86_64):{
    LIBS +=  \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x64/bin \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x64/lib
  }
  else {
    LIBS +=  \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x86/bin \
      -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/x86/lib
  }
  
  CONFIG(debug, debug|release) {
    LIBS += \
      -lArcGISRuntimeToolkitCppApid
  } else {
    LIBS += \
      -lArcGISRuntimeToolkitCppApi
  }
}

android {

    equals(QT_ARCH, i386) {
      ANDROID_ARCH = "x86"
    } else:contains(QT_ARCH, arm64) {
      ANDROID_ARCH = "arm64"
    } else {
      ANDROID_ARCH = "armv7"
    }

    contains(QMAKE_HOST.os, Windows):{

        ANDROIDDIR = $$clean_path($$(ALLUSERSPROFILE)\\EsriRuntimeQt)
        INCLUDEPATH -= "$${SDK_INSTALL_DIR}/sdk/include" \
                       "$${SDK_INSTALL_DIR}/sdk/include/CoordinateConversion"
        INCLUDEPATH += $${ANDROIDDIR}/Qt$${ESRIRUNTIME_QT_VERSION}/include \
                       $${ANDROIDDIR}/Qt$${ESRIRUNTIME_QT_VERSION}/include/CoordinateConversion

        QMAKE_PRE_LINK += $(COPY) \"$${SDK_INSTALL_DIR}\sdk\android\\$${ANDROID_ARCH}\lib\libArcGISRuntimeToolkitCppApi.so\" \"$${OUT_PWD}\libArcGISRuntimeToolkitCppApi.so\" $$escape_expand(\n\t)

        LIBS += \
            -L$${OUT_PWD} \
            -lArcGISRuntimeToolkitCppApi
    }
    else {
        LIBS += \
            -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/$${ANDROID_ARCH}/lib \
            -lArcGISRuntimeToolkitCppApi
    }

    ANDROID_EXTRA_LIBS += \
    $${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/$${ANDROID_ARCH}/lib/libArcGISRuntimeToolkitCppApi.so
}

ios {
    QMAKE_CXXFLAGS += -Wno-deprecated-register

    LIBS += -L$${SDK_INSTALL_DIR}/sdk/$${PLATFORM}/universal/lib \
            -lArcGISRuntimeToolkitCppApi
}

# Set ArcGIS Runtime Toolkit Path for Qml UI files
ARCGIS_TOOLKIT_IMPORT_PATH = $${SDK_INSTALL_DIR}/sdk/toolkit/Import

# Add plugin paths to QML_IMPORT_PATH
QML_IMPORT_PATH += $${ARCGIS_TOOLKIT_IMPORT_PATH}

# Add plugin paths to QMLPATHS
QMLPATHS += $${ARCGIS_TOOLKIT_IMPORT_PATH}

# DEFINES
unix:!macx:!ios {

    contains(QMAKE_HOST.os, Linux):{
      # on some linux platforms the string 'linux' is replaced with 1
      # temporarily replace it with ARCGISRUNTIME_SDK_LINUX_REPLACEMENT
      LINUX_PLATFORM_REPLACEMENT = ARCGISRUNTIME_SDK_LINUX_REPLACEMENT

      ARCGIS_TOOLKIT_IMPORT_PATH = $$replace(ARCGIS_TOOLKIT_IMPORT_PATH, linux, $$LINUX_PLATFORM_REPLACEMENT)

      DEFINES += LINUX_PLATFORM_REPLACEMENT=$$LINUX_PLATFORM_REPLACEMENT
    }
}

# Set ArcGIS Runtime QML Toolkit Path
DEFINES += ARCGIS_TOOLKIT_IMPORT_PATH=\"$$ARCGIS_TOOLKIT_IMPORT_PATH\"
