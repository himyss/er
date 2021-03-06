# Create a library called "libERData" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${Boost_INCLUDE_DIRS}
${ROOT_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/ERData
${CMAKE_SOURCE_DIR}/ERData/NeuRadData
${CMAKE_SOURCE_DIR}/ERData/muSiData
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${BASE_LINK_DIRECTORIES}
${FAIRROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

set(SRCS
NeuRadData/ERNeuRadPoint.cxx
NeuRadData/ERNeuRadFiberPoint.cxx
NeuRadData/ERNeuRadPMTSignal.cxx
NeuRadData/ERNeuRadDigi.cxx
NeuRadData/ERNeuRadStep.cxx
NeuRadData/ERNeuRadHit.cxx

muSiData/ERmuSiPoint.cxx
muSiData/ERmuSiHit.cxx
muSiData/ERmuSiTrack.cxx
muSiData/ERmuSiVertex.cxx

GadastData/ERGadastCsIPoint.cxx
GadastData/ERGadastLaBrPoint.cxx
GadastData/ERGadastStep.cxx

ERStack.cxx
ERMCTrack.cxx
ERMCEventHeader.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
SET(HEADERS ${HEADERS})
set(LINKDEF  ERDataLinkDef.h)
set(LIBRARY_NAME ERData)
set(DEPENDENCIES Base Core)

GENERATE_LIBRARY()
