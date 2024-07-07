////////////////////////////////////////////////////////////////////////
// Class:       ProtoDUNEDMAnalyze
// Plugin Type: analyzer (Unknown Unknown)
// File:        ProtoDUNEDMAnalyze_module.cc
//
// Generated at Mon Apr  8 02:24:48 2024 by Ciaran Hasnip using cetskelgen
// from cetlib version 3.18.02.
////////////////////////////////////////////////////////////////////////

#include "larcore/CoreUtils/ServiceUtil.h"
#include "larcore/Geometry/Geometry.h"
#include "larcorealg/Geometry/GeometryCore.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
//#include "lardata/DetectorInfoServices/DetectorClocksService.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/Simulation/SimChannel.h"
#include "larsim/Simulation/LArG4Parameters.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "nusimdata/SimulationBase/MCTruth.h"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// Additional Framework includes
#include "art_root_io/TFileService.h"

// ROOT includes
#include <TTree.h>
#include <TH1.h>

#include <string>

namespace ana {
  class ProtoDUNEDMAnalyze;
}

// Define analyser class
class ana::ProtoDUNEDMAnalyze : public art::EDAnalyzer {
public:
  explicit ProtoDUNEDMAnalyze(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  ProtoDUNEDMAnalyze(ProtoDUNEDMAnalyze const&) = delete;
  ProtoDUNEDMAnalyze(ProtoDUNEDMAnalyze&&) = delete;
  ProtoDUNEDMAnalyze& operator=(ProtoDUNEDMAnalyze const&) = delete;
  ProtoDUNEDMAnalyze& operator=(ProtoDUNEDMAnalyze&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  TTree *fSimulationNtuple;
  // TTrees for HNL signal selection
  TTree *fHNLSelectNtuple;
  TTree *fTLtoExitMuon;
  TTree *fTLtoExitPion;

  TTree *fTrackLength_muon_tree;
  TTree *fTrackLength_pion_tree;

  // Declare member data here.
  unsigned int fEventID;
  unsigned int fRun;
  unsigned int fSubRun;

  art::InputTag fSimulationProducerLabel; ///< The name of the producer that tracked
                                          ///< simulated particles through the detector
  //art::InputTag fHitProducerLabel;        ///< The name of the producer that created hits
  //art::InputTag fClusterProducerLabel;    ///< The name of the producer that
                                          ///< created clusters
  
  std::string fProcess;

  int fSelectedPDG;                       ///< PDG code of particle we'll focus on

  int fSimPDG;     ///< PDG ID of the particle being processed
  int fSimTrackID; ///< GEANT ID of the particle being processed
  int fPrimaryMuTrackID;
  int fPrimaryPiTrackID;
  int fMother;
  int fNExitingParts;
  int fNContParts;

  double fStartXYZT[4]; ///< (x,y,z,t) of the true start of the particle
  double fEndXYZT[4];   ///< (x,y,z,t) of the true end of the particle
  double fStartPE[4];   ///< (Px,Py,Pz,E) at the true start of the particle
  double fEndPE[4];     ///< (Px,Py,Pz,E) at the true end of the particle

  double fTrackLength;
  double TLmu;
  double TLpi;
  double TLtoexitMuon;
  double TLtoexitPion;



  double fPrimaryVertex[4];
  double fPrimaryEnd[4];

  double fPrimaryTrackLength;
  double fdEdx;
  double fdEdxMu;
  double fdEdxPi;
  double fEMu;
  double fEPi;
  double ftrackLengthToExit;


  int flag_for_muon;
  int flag_for_pion;



  bool fInFV;
  bool fPrimaryExit;
  bool fPrimaryMuExit;
  bool fPrimaryPiExit;
  bool fPrimaryContained;
  bool fPrimaryPiContained;
  bool fPrimaryMuContained;
  bool fPrimaryMuDecay;
  bool fPrimaryPiDecay;
  // Flags for different selections
  bool fSelMuExitPiExit;
  bool fSelMuExitPiCont;
  bool fSelMuContPiExit;
  bool fSelMuContPiCont;
  bool fHNLSelect;

  geo::GeometryCore const* fGeometryService; ///< pointer to Geometry provider
  std::vector<double> fFiducialBoundaries;
  double fZedge;
};


// Analyser class constructor
ana::ProtoDUNEDMAnalyze::ProtoDUNEDMAnalyze(fhicl::ParameterSet const& p)
  : EDAnalyzer{p} 
  , fSimulationProducerLabel(p.get<std::string>("SimulationLabel"))
  , fSelectedPDG(p.get<int>("PDGcode"))

  // More initializers here.
{

  // Get a pointer to the geometry service provider.
  fGeometryService = lar::providerFrom<geo::Geometry>();
  // TPC 1 is the first proper TPC - TPC 0 is for track stubs
  const geo::TPCGeo& tpc = fGeometryService->Cryostat().TPC(1);
  fFiducialBoundaries.push_back(0.); // central x
  fFiducialBoundaries.push_back(tpc.Width() - 0.05*tpc.Width()); // outer x
  fFiducialBoundaries.push_back(0.05*tpc.Height()); // bottom y
  fFiducialBoundaries.push_back(tpc.Height() - 0.05*tpc.Height()); // top y
  fFiducialBoundaries.push_back(0.05*(tpc.Length()*2.));
  fFiducialBoundaries.push_back((tpc.Length()*2.) - 0.05*(tpc.Length()*2));

  for (size_t i=0; i<fFiducialBoundaries.size(); i++) {
    std::cout << "\n bound = " << fFiducialBoundaries.at(i);
  }

  fZedge = tpc.Length()*2.;
  // Call appropriate consumes<>() for any products to be retrieved by this module.
  //consumes<std::vector<simb::MCParticle>>(fSimulationProducerLabel);
}

void ana::ProtoDUNEDMAnalyze::analyze(art::Event const& e)
{
  // Implementation of required member function here.
  fEventID = e.id().event();
  fRun = e.run();
  fSubRun = e.subRun();

  fInFV = false;
  fPrimaryContained = false;
  fPrimaryPiContained = false;
  fPrimaryMuContained = false;
  fPrimaryExit = false;
  fPrimaryMuExit = false;
  fPrimaryPiExit = false;
  fPrimaryMuDecay = false;
  fPrimaryPiDecay = false;
  fSelMuExitPiExit = false;
  fSelMuExitPiCont = false;
  fSelMuContPiExit = false;
  fSelMuContPiCont = false;
  fHNLSelect = false;

  fNExitingParts = 0;
  fNContParts = 0;

  // Define a "handle" to point to a vector of the objects.
  art::Handle<std::vector<simb::MCTruth>> truthHandle;
  art::Handle<std::vector<simb::MCParticle>> particleHandle;

  if (!e.getByLabel(fSimulationProducerLabel, particleHandle)) {
    throw cet::exception("ProtoDUNEDMAnalyze")
      << " No simb::MCParticle objects in this event - "
	  << " Line " << __LINE__ << " in file " << __FILE__ << std::endl;
  }

  //auto simChannelHandle = e.getValidHandle<std::vector<sim::SimChannel>>(fSimulationProducerLabel);


  bool primVset(false);
  
  for (auto const& particle : (*particleHandle)) {
    fSimTrackID = particle.TrackId();


	fSimPDG = particle.PdgCode();
	fProcess = particle.Process();
    fMother = particle.Mother();

	const size_t numberTrajectoryPoints = particle.NumberTrajectoryPoints();
	const int last = numberTrajectoryPoints - 1;

	const TLorentzVector& positionStart = particle.Position(0);
    const TLorentzVector& positionEnd = particle.Position(last);
    const TLorentzVector& momentumStart = particle.Momentum(0);
    const TLorentzVector& momentumEnd = particle.Momentum(last);

    // Set the vertex position - it should be the same value for each event	
	if (fMother == 0 && !primVset) {
	  positionStart.GetXYZT(fPrimaryVertex);
	  positionEnd.GetXYZT(fPrimaryEnd);
	  if (std::fabs(fSimPDG) == 13) fPrimaryMuTrackID = fSimTrackID;
	  if (std::fabs(fSimPDG) == 211) fPrimaryPiTrackID = fSimTrackID;
	  primVset = true;
    } 
	const TLorentzVector& PrimV(fPrimaryVertex);
	const TLorentzVector& PrimEnd(fPrimaryEnd);
	if (fMother == 0 && primVset) {
      if (particle.Position(0) != PrimV) {
        throw cet::exception("ProtoDUNEDMAnalyze")
		  << " Vertices of primary particles do not match!" << std::endl;
	  }
	}
	positionStart.GetXYZT(fStartXYZT);
	positionEnd.GetXYZT(fEndXYZT);
    momentumStart.GetXYZT(fStartPE);
    momentumEnd.GetXYZT(fEndPE);

    const double trackLength = (positionEnd - positionStart).Rho();
    fTrackLength = trackLength;
    if(std::fabs(fSimPDG) == 13)
    { 
      TLmu = trackLength;
      // TLpi = 0;
      fTrackLength_muon_tree->Fill();
    }
    else if (std::fabs(fSimPDG) == 211)
    {
      TLpi = trackLength;
      // TLmu = 0;
      fTrackLength_pion_tree->Fill();
    }
    //const double trackLengthToExit= (positionExit - positionStart).Rho();
    //if (std::fabs(fSimPDG) == 13) {TLtoexitMuon=trackLengthToExit; fHNLSelectNtuple->Fill();}
      //  else if (std::fabs(fSimPDG) == 211) {TLtoexitPion=trackLengthToExit; fHNLSelectNtuple->Fill();} 
      //
	//---------------------------------------
    // Store total event outputs in the TTree
    fSimulationNtuple->Fill();

	//---------------------------------------
	// Now fill selection tree
	//---------------------------------------
    if (std::fabs(fPrimaryVertex[0]) > fFiducialBoundaries.at(0) && 
        std::fabs(fPrimaryVertex[0]) < fFiducialBoundaries.at(1)) {
      if (fPrimaryVertex[1] > fFiducialBoundaries.at(2) && 
          fPrimaryVertex[1] < fFiducialBoundaries.at(3)) {
        if (fPrimaryVertex[2] > fFiducialBoundaries.at(4) && 
            fPrimaryVertex[2] < fFiducialBoundaries.at(5)) {
          fInFV = true;
		}
	  }
	}

	if (!fInFV) continue;

    // Now perform selection
	// Muon must either exit back of ProtoDUNE or decay to a Michel
	// Look at primary particles first, find pion and muon at vertex
    if (positionStart == PrimV) { // starts at vertex

      if (std::fabs(fSimPDG) == 13) fEMu = momentumStart.E();
      if (std::fabs(fSimPDG) == 211) fEPi = momentumStart.E();
        
	  // Loop over trajectory points
      int t(0);
      while (particle.Position(t).Z() < fZedge) t++;
      int exit_trajpoint = t;

      const TLorentzVector& momentumExit = particle.Momentum(exit_trajpoint);
      const TLorentzVector& positionExit = particle.Position(exit_trajpoint);

      const double trackLengthToExit = (positionExit - positionStart).Rho();
      //ftrackLengthToExit=trackLengthToExit;
      fdEdx = (momentumStart - momentumExit).E() / trackLengthToExit;
      if (std::fabs(fSimPDG) == 13) {TLtoexitMuon=trackLengthToExit; fTLtoExitMuon->Fill();}
      else if (std::fabs(fSimPDG) == 211) {TLtoexitPion=trackLengthToExit; fTLtoExitPion->Fill();} 
      if (std::fabs(fSimPDG) == 13) fdEdxMu = (momentumStart - momentumExit).E() / trackLengthToExit;
      if (std::fabs(fSimPDG) == 211) fdEdxPi = (momentumStart - momentumExit).E() / trackLengthToExit;

	  //if (momentumStart.X() < 1. && momentumStart.Y() < 1.) fForwardGoingPrimary = true;
	  
	  if (fEndXYZT[2] > fZedge) { // track leaves back of protodune  
        // Loop over trajectory points

		std::cout << "Exiting Particle: " << fSimPDG << ". t = " << t << ". Tracklength = " << trackLengthToExit<< ", dEdx = " << fdEdx << std::endl;
		fPrimaryExit = true;
		fNExitingParts++;
		if (std::fabs(fSimPDG) == 13) fPrimaryMuExit = true;
		if (std::fabs(fSimPDG) == 211) fPrimaryPiExit = true;
	  } else { // primary particle contained in TPC, look for Michel or determine if pion
	    std::cout << "Contained Particle: " << fSimPDG << std::endl;
	    
		fPrimaryContained = true;
		fNContParts++;
		if (std::fabs(fSimPDG) == 211) fPrimaryPiContained = true;
		if (std::fabs(fSimPDG) == 13) fPrimaryMuContained = true;
	  }
	  std::cout << "PDG: " << fSimPDG << ", NDaughters = " << particle.NumberDaughters() << std::endl;
	} else {
	  if (fPrimaryContained) {
        if ((PrimEnd - positionStart).Rho() < 0.3) { // stats within 3mm of mu end point
	      if (std::fabs(fSimPDG) == 11 && momentumStart.E() < 0.070 && momentumStart.E() > 0.005 && fdEdxMu < 0.004) {
	        std::cout << "Michel Candidate: " << fSimPDG << std::endl;
            // Michel electron found
			fPrimaryMuDecay = true;
	      }
	      //if (std::fabs(fSimPDG) == 13 && fPrimaryPiContained) {
	      if (std::fabs(fSimPDG) == 13) {
	        std::cout << "Pion decay to Muon Candidate: " << fSimPDG << std::endl;
			fPrimaryPiDecay = true;
	      }
	    }
	  }
	}
    if (fPrimaryExit && fdEdxMu < 0.003 && fNExitingParts == 2) fSelMuExitPiExit = true;
    if (fPrimaryExit && fdEdxMu < 0.003 && fNExitingParts == 1 && fNContParts == 1 /*&& fPrimaryPiDecay*/) fSelMuExitPiCont = true;
    if (fPrimaryExit && fNExitingParts == 1 && fNContParts == 1 && fPrimaryMuDecay && !fPrimaryPiDecay) fSelMuContPiExit = true;
	if (!fPrimaryExit && fPrimaryContained && fNContParts == 2 && fPrimaryMuDecay /*&& fPrimaryPiDecay*/) fSelMuContPiCont = true;

	if (fSelMuExitPiExit || fSelMuExitPiCont || fSelMuContPiExit || fSelMuContPiCont) fHNLSelect = true;
  } // end particle loop

  // Selection is for the whole event, so do at end of loop
  fHNLSelectNtuple->Fill();
}
  // if(flag_for_muon==13 && flag_for_pion!=){ fTrackLength_muon_tree->Fill(); }
  // if(flag_for_pion==211){ fTrackLength_pion_tree->Fill(); }
  // Loop over simchannels 
      //  if (std::fabs(fSimPDG) == 13) {TLtoexitMuon=trackLengthToExit; fHNLSelectNtuple->Fill();}
        //      else if (std::fabs(fSimPDG) == 211) {TLtoexitPion=trackLengthToExit; fHNLSelectNtuple->Fill();} 
               


// Define outputs at start of the job
void ana::ProtoDUNEDMAnalyze::beginJob()
{
  // Implementation of optional member function here.
  art::ServiceHandle<art::TFileService> tfs;

  // Get TFileService to create an output tree
  fSimulationNtuple = tfs->make<TTree>("tree", "DM Output Tree");
  fSimulationNtuple->SetAutoSave(0);

  // Add branches to TTree
  fSimulationNtuple->Branch("eventID", &fEventID);
  fSimulationNtuple->Branch("SubRun", &fSubRun, "SubRun/I");
  fSimulationNtuple->Branch("Run", &fRun, "Run/I");
  fSimulationNtuple->Branch("TrackID", &fSimTrackID, "TrackID/I");
  fSimulationNtuple->Branch("PDG", &fSimPDG, "PDG/I");
  fSimulationNtuple->Branch("Mother", &fMother, "Mother/I");
  fSimulationNtuple->Branch("TrackLength", &fTrackLength, "TrackLength/D");
  fSimulationNtuple->Branch("Process", &fProcess, "Process/C");

  fSimulationNtuple->Branch("StartXYZT", fStartXYZT, "StartXYZT[4]/D");
  fSimulationNtuple->Branch("EndXYZT", fEndXYZT, "EndXYZT[4]/D");
  fSimulationNtuple->Branch("PrimaryVertex", fPrimaryVertex, "PrimaryVertex[4]/D");
  fSimulationNtuple->Branch("PrimaryEnd", fPrimaryEnd, "PrimaryEnd[4]/D");
  fSimulationNtuple->Branch("StartPE", fStartPE, "StartPE[4]/D");
  fSimulationNtuple->Branch("EndPE", fEndPE, "EndPE[4]/D");

  fHNLSelectNtuple = tfs->make<TTree>("treeHNLsel", "Selected Output Tree");
  fHNLSelectNtuple->SetAutoSave(0);

  fHNLSelectNtuple->Branch("SelMuExitPiExit", &fSelMuExitPiExit, "SelMuExitPiExit/B");
  fHNLSelectNtuple->Branch("SelMuExitPiCont", &fSelMuExitPiCont, "SelMuExitPiCont/B");
  fHNLSelectNtuple->Branch("SelMuContPiExit", &fSelMuContPiExit, "SelMuContPiExit/B");
  fHNLSelectNtuple->Branch("SelMuContPiCont", &fSelMuContPiCont, "SelMuContPiCont/B");
  fHNLSelectNtuple->Branch("HNLSelect", &fHNLSelect, "HNLSelect/B");
  fHNLSelectNtuple->Branch("PrimaryContained", &fPrimaryContained, "PrimaryContained/B");
  fHNLSelectNtuple->Branch("PrimaryPiContained", &fPrimaryPiContained, "PrimaryPiContained/B");
  fHNLSelectNtuple->Branch("PrimaryMuContained", &fPrimaryMuContained, "PrimaryMuContained/B");
  fHNLSelectNtuple->Branch("PrimaryExit", &fPrimaryExit, "PrimaryExit/B");
  fHNLSelectNtuple->Branch("PrimaryMuExit", &fPrimaryMuExit, "PrimaryMuExit/B");
  fHNLSelectNtuple->Branch("PrimaryPiExit", &fPrimaryPiExit, "PrimaryPiExit/B");
  fHNLSelectNtuple->Branch("PrimaryMuDecay", &fPrimaryMuDecay, "PrimaryMuDecay/B");
  fHNLSelectNtuple->Branch("PrimaryPiDecay", &fPrimaryPiDecay, "PrimaryPiDecay/B");
  fHNLSelectNtuple->Branch("InFV", &fInFV, "InFV/B");
  
  fHNLSelectNtuple->Branch("PDG", &fSimPDG, "PDG/I");
  fHNLSelectNtuple->Branch("NExitingParts", &fNExitingParts, "NExitingParts/I");
  fHNLSelectNtuple->Branch("NContParts", &fNContParts, "NContParts/I");
  fHNLSelectNtuple->Branch("dEdx", &fdEdx, "dEdx/D");
  fHNLSelectNtuple->Branch("dEdxMu", &fdEdxMu, "dEdxMu/D");
  fHNLSelectNtuple->Branch("dEdxPi", &fdEdxPi, "dEdxPi/D");
  fHNLSelectNtuple->Branch("EMu", &fEMu, "EMu/D");
  fHNLSelectNtuple->Branch("EPi", &fEPi, "EPi/D");
  //fHNLSelectNtuple->Branch("TLtoexitmuon",&TLtoexitMuon,"TLtoexitmuon/D");
  //fHNLSelectNtuple->Branch("TLtoexitpion",&TLtoexitPion,"TLtoexitpion/D");





  fTrackLength_muon_tree = tfs->make<TTree>("tracklengthpimu_muon", "TL Tree");
  fTrackLength_muon_tree->SetAutoSave(0);
  fTrackLength_muon_tree->Branch("TLMu", &TLmu, "TLMu/D");
  
  fTrackLength_pion_tree = tfs->make<TTree>("tracklengthpimu_pion", "TL Tree");
  fTrackLength_pion_tree->SetAutoSave(0);
  fTrackLength_pion_tree->Branch("TLPi", &TLpi, "TLPi/D");



  fTLtoExitPion = tfs->make<TTree>("tracklengthtoexit_pimu_pion", "TL to exit Tree");
  fTLtoExitPion->SetAutoSave(0);
  fTLtoExitPion->Branch("TLtoExitPi", &TLtoexitPion, "TLtoExitPi/D");

  fTLtoExitMuon = tfs->make<TTree>("tracklengthtoexit_pimu_muon", "TL to exit Tree");
  fTLtoExitMuon->SetAutoSave(0);
  fTLtoExitMuon->Branch("TLtoExitMu", &TLtoexitMuon, "TLtoExitMu/D");


}

void ana::ProtoDUNEDMAnalyze::endJob()
{
  // Implementation of optional member function here.
}
 DEFINE_ART_MODULE(ana::ProtoDUNEDMAnalyze)

