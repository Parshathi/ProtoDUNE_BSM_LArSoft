# Install script for directory: /afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/localProducts_larsoft_v09_85_00_e26_prof")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib" TYPE SHARED_LIBRARY FILES "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/build_slf7.x86_64/protodunedm/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so"
         OLD_RPATH "/cvmfs/larsoft.opensciencegrid.org/products/larcore/v09_10_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcoreobj/v09_09_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/lardataobj/v09_17_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larsim/v09_40_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/nusimdata/v1_27_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/ifdhc/v2_6_20/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art_root_io/v1_11_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcorealg/v09_12_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/clhep/v2_4_5_3a/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/root/v6_26_06b/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art/v3_12_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas_root_io/v1_11_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/boost/v1_80_0/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas/v3_14_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/messagefacility/v2_09_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/fhiclcpp/v4_17_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib/v3_16_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/hep_concurrency/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib_except/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/tbb/v2021_7_0/Linux64bit+3.10-2.17-e26/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libHepMCFileGen_module.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib" TYPE SHARED_LIBRARY FILES "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/build_slf7.x86_64/protodunedm/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so"
         OLD_RPATH "/cvmfs/larsoft.opensciencegrid.org/products/larcore/v09_10_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcoreobj/v09_09_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/lardataobj/v09_17_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larsim/v09_40_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/nusimdata/v1_27_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/ifdhc/v2_6_20/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art_root_io/v1_11_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcorealg/v09_12_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/clhep/v2_4_5_3a/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/root/v6_26_06b/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art/v3_12_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas_root_io/v1_11_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/boost/v1_80_0/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas/v3_14_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/messagefacility/v2_09_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/fhiclcpp/v4_17_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib/v3_16_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/hep_concurrency/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib_except/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/tbb/v2021_7_0/Linux64bit+3.10-2.17-e26/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libProtoDUNEDMAnalyze_module.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib" TYPE SHARED_LIBRARY FILES "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/build_slf7.x86_64/protodunedm/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so"
         OLD_RPATH "/cvmfs/larsoft.opensciencegrid.org/products/larcore/v09_10_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcoreobj/v09_09_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/lardataobj/v09_17_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larsim/v09_40_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/nusimdata/v1_27_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/ifdhc/v2_6_20/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art_root_io/v1_11_04/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/larcorealg/v09_12_02/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/clhep/v2_4_5_3a/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/root/v6_26_06b/Linux64bit+3.10-2.17-e26-p3913-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/art/v3_12_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas_root_io/v1_11_03/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/boost/v1_80_0/Linux64bit+3.10-2.17-e26-prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/canvas/v3_14_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/messagefacility/v2_09_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/fhiclcpp/v4_17_01/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib/v3_16_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/hep_concurrency/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/cetlib_except/v1_08_00/slf7.x86_64.e26.prof/lib:/cvmfs/larsoft.opensciencegrid.org/products/tbb/v2021_7_0/Linux64bit+3.10-2.17-e26/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/slf7.x86_64.e26.prof/lib/libTriggerPrimitiveProtoDUNE_module.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/source/protodunedm" TYPE FILE FILES
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/HepMCFileGen_module.cc"
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/ProtoDUNEDMAnalyze_module.cc"
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/TriggerPrimitiveProtoDUNE_module.cc"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/fcl" TYPE FILE FILES
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/genie_protodunehd.fcl"
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/hepmcfilegen.fcl"
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/protodunedmanalyze.fcl"
    "/afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs/protodunedm/protodunedm/triggerprimitiveprotodune.fcl"
    )
endif()

