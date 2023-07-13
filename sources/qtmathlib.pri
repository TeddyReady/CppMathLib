QT += core gui
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD
VPATH += $$PWD

SOURCES += \#$$PWD/algebrastructures.cpp \
           $$PWD/basemath.cpp \
#           $$PWD/complex.cpp \
#           $$PWD/eulerfunction.cpp \
#           $$PWD/groupproperties.cpp \
#           $$PWD/mebiusfunction.cpp \
            $$PWD/rational.cpp \
#           $$PWD/ringofmembers.cpp \
#           $$PWD/ringresidue.cpp \
#           $$PWD/symbollegandre.cpp \
#           $$PWD/transpositiongroup.cpp \

HEADERS += \#$$PWD/algebrastructures.h \
           $$PWD/basemath.h \
#           $$PWD/complex.h \
#           $$PWD/eulerfunction.h \
#           $$PWD/groupproperties.h \
           $$PWD/include.h \
#           $$PWD/mebiusfunction.h \
           $$PWD/rational.h \
#           $$PWD/ringofmembers.h \
#           $$PWD/ringresidue.h \
#           $$PWD/symbollegandre.h \
#           $$PWD/transpositiongroup.h \
