#!/bin/bash
#export DUNESW_VERSION=v09_65_01d00
#export DUNESW_VERSION=v09_88_00d00
export DUNESW_VERSION=v09_85_00d00
export QUAL="e26:prof"
 
LOCALPROD_65=localProducts_larsoft_v09_65_01_e20_prof
LOCALPROD_88=localProducts_larsoft_v09_88_00_e26_prof
LOCALPROD=localProducts_larsoft_v09_85_00_e26_prof
 
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

 
source /afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/localProducts_larsoft_v09_85_00_e26_prof/setup                                              
 
cd /afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft/srcs
setup dunesw v09_85_00d00 -q e26:prof
mrbslp
cd /afs/cern.ch/work/p/psajitha/public/protodune/ProtoDUNE_BSM_LArSoft
