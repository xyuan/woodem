# File generated by kdevelop's qmake manager. 
# ------------------------------------------- 
# Subdir relative project main directory: ./Engine/EngineUnit/MacroMicroElasticRelationships
# Target is a library:  

HEADERS += MacroMicroElasticRelationships.hpp 
SOURCES += MacroMicroElasticRelationships.cpp 
LIBS += -lSDECLinkPhysics \
        -lSDECLinkGeometry \
        -lElasticContactParameters \
        -lMacroMicroContactGeometry \
        -lBodyMacroParameters \
        -lInteractionPhysicsMetaEngine \
        -rdynamic 
QMAKE_LIBDIR = ../../../../../bin \
               ../../../../../bin \
               ../../../../../bin \
               ../../../../../bin \
               ../../../../../bin \
               /usr/local/lib/yade/yade-libs/ 
QMAKE_CXXFLAGS_RELEASE += -lpthread \
                          -pthread 
QMAKE_CXXFLAGS_DEBUG += -lpthread \
                        -pthread 
DESTDIR = ../../../../../bin 
CONFIG += debug \
          warn_on \
          dll 
TEMPLATE = lib 
