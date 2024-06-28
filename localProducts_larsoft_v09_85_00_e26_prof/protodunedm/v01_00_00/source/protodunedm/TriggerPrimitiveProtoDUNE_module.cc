////////////////////////////////////////////////////////////////////////
// Class:       TriggerPrimitiveProtoDUNE
// Plugin Type: analyzer (Unknown Unknown)
// File:        TriggerPrimitiveProtoDUNE_module.cc
//
// Generated at Mon Apr  8 02:24:48 2024 by Ciaran Hasnip using cetskelgen
// from cetlib version 3.18.02.
//
// Purpose is to access the deltaTick across the longest Muon track
// in a HNL event. This informs the people designing the trigger.
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
#include <TGraph.h>

#include <string>

namespace ana {
  class TriggerPrimitiveProtoDUNE;
}

// Define analyser class
class ana::TriggerPrimitiveProtoDUNE : public art::EDAnalyzer {
public:
  explicit TriggerPrimitiveProtoDUNE(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  TriggerPrimitiveProtoDUNE(TriggerPrimitiveProtoDUNE const&) = delete;
  TriggerPrimitiveProtoDUNE(TriggerPrimitiveProtoDUNE&&) = delete;
  TriggerPrimitiveProtoDUNE& operator=(TriggerPrimitiveProtoDUNE const&) = delete;
  TriggerPrimitiveProtoDUNE& operator=(TriggerPrimitiveProtoDUNE&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  TTree *fSimulationNtuple;
  // TTrees for HNL signal selection

  // Declare member data here.
  unsigned int fEventID;
  unsigned int fRun;
  unsigned int fSubRun;

  art::InputTag fSimulationProducerLabel; ///< The name of the producer that tracked
                                          ///< simulated particles through the detector
  art::InputTag fDetsimProducerLabel;
 
  TH1D *hMuonDeltaTick;
  TH1D *hMuonDeltaWire;

  TGraph *gMuonStartWireVDeltaWire;

  std::string fProcess;

  int fSelectedPDG;                       ///< PDG code of particle we'll focus on

  int fSimPDG;     ///< PDG ID of the particle being processed
  int fSimTrackID; ///< GEANT ID of the particle being processed
  int fPrimaryMuTrackID;
  int fPrimaryPiTrackID;
  int fMother;
  int fNExitingParts;
  int fNContParts;
  int fStartWire;
  int fEndWire;
  int fdeltaWire;
  int fStartTick;
  int fEndTick;
  int fdeltaTick;

  double fStartXYZT[4]; ///< (x,y,z,t) of the true start of the particle
  double fEndXYZT[4];   ///< (x,y,z,t) of the true end of the particle
  double fStartPE[4];   ///< (Px,Py,Pz,E) at the true start of the particle
  double fEndPE[4];     ///< (Px,Py,Pz,E) at the true end of the particle

  double fTrackLength;

  double fPrimaryVertex[4];
  double fPrimaryEnd[4];

  double fPrimaryTrackLength;
  double fEDepDistance;
  double fWiresDistance;

  bool fInFV;


  // Geometry helper objects
  geo::GeometryCore const* fGeometryService; ///< pointer to Geometry provider
  std::vector<double> fFiducialBoundaries;
  std::vector<geo::TPCGeo> vTPCs;
  double fZedge;
  double fWirePitch;
  geo::WireGeo const *fFirstWire_TPC1;
  geo::WireGeo const *fFirstWire_TPC2;
};


// Analyser class constructor
ana::TriggerPrimitiveProtoDUNE::TriggerPrimitiveProtoDUNE(fhicl::ParameterSet const& p)
  : EDAnalyzer{p} 
  , fSimulationProducerLabel(p.get<std::string>("SimulationLabel"))
  , fDetsimProducerLabel(p.get<std::string>("DetsimLabel"))
  , fSelectedPDG(p.get<int>("PDGcode"))

  // More initializers here.
{

  // Get a pointer to the geometry service provider.
  fGeometryService = lar::providerFrom<geo::Geometry>();
  const unsigned int nTPCs = fGeometryService->Cryostat().NTPC();
  for (unsigned int t = 0; t < nTPCs; ++t) {
    const geo::TPCGeo& tpc = fGeometryService->Cryostat().TPC(t);
    vTPCs.push_back(tpc);
  }

  // TPC 1 is the first proper TPC - TPC 0 is for track stubs
  // First arrange fiducial volume
  const geo::TPCGeo& tpc = vTPCs.at(1);
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

  // Now get number of wires and first wire
  const unsigned int nPlanes = tpc.Nplanes();
  std::cout << "TPC 1 has " << nPlanes << " planes." << std::endl;
  const geo::PlaneGeo& plane = tpc.Plane(2);
  const unsigned int nWires = plane.Nwires();
  fWirePitch = plane.WirePitch();
  std::cout << "Plane has " << nWires << " wires with pitch = " << fWirePitch << std::endl;
  std::cout << "Wires measuring " << plane.ViewName(plane.View()) << " view" << std::endl;
 
  fFirstWire_TPC1 = &plane.FirstWire();

  const geo::TPCGeo& tpc2 = vTPCs.at(2);
  const geo::PlaneGeo& plane_tpc2 = tpc2.Plane(2);
  fFirstWire_TPC2 = &plane_tpc2.FirstWire();

  // Call appropriate consumes<>() for any products to be retrieved by this module.
  consumes<std::vector<simb::MCParticle>>(fSimulationProducerLabel);
  consumes<std::vector<sim::SimChannel>>(fDetsimProducerLabel);
}

void ana::TriggerPrimitiveProtoDUNE::analyze(art::Event const& e)
{
  // Implementation of required member function here.
  fEventID = e.id().event();
  fRun = e.run();
  fSubRun = e.subRun();

  fInFV = false;

  // Define a "handle" to point to a vector of the objects.
  art::Handle<std::vector<simb::MCTruth>> truthHandle;
  art::Handle<std::vector<simb::MCParticle>> particleHandle;

  if (!e.getByLabel(fSimulationProducerLabel, particleHandle)) {
    throw cet::exception("TriggerPrimitiveProtoDUNE")
      << " No simb::MCParticle objects in this event - "
	  << " Line " << __LINE__ << " in file " << __FILE__ << std::endl;
  }

  auto simChannelHandle = e.getValidHandle<std::vector<sim::SimChannel>>(fDetsimProducerLabel);

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
        throw cet::exception("TriggerPrimitiveProtoDUNE")
		  << " Vertices of primary particles do not match!" << std::endl;
	  }
	}
	positionStart.GetXYZT(fStartXYZT);
	positionEnd.GetXYZT(fEndXYZT);
    momentumStart.GetXYZT(fStartPE);
    momentumEnd.GetXYZT(fEndPE);

    const double trackLength = (positionEnd - positionStart).Rho();
    fTrackLength = trackLength;

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

	// Must be a primary muon in the fiducial volume
	if (!fInFV) continue;
    if (fMother != 0) continue;
    if (std::fabs(fSimPDG) != 13) continue;

	std::cout << "Looking at a primary muon." << std::endl;

    unsigned short start_tick(0), end_tick(0);

	geo::WireGeo const *start_wire(nullptr);
	geo::WireGeo const *end_wire(nullptr);

	double total_edep_distance(0), total_wire_distance(0);

	for ( auto const& channel : (*simChannelHandle) ) {
	  // get channel number - wire?
      auto const channelNumber = channel.Channel();

	  // stick to just collection plane for now
	  if ( fGeometryService->SignalType( channelNumber ) != geo::kCollection )
        continue;

	  auto chanWires = fGeometryService->ChannelToWire(channelNumber);
	  auto const& timeSlices = channel.TDCIDEMap();

	  for (auto const& timeSlice : timeSlices) {

	    auto const& energyDeposits = timeSlice.second;

		for (auto const& energyDeposit : energyDeposits) {
		  if (energyDeposit.trackID != fSimTrackID) continue;

		  if (start_tick == 0) start_tick = timeSlice.first;
          end_tick = timeSlice.first;

	      for (const auto &wire : chanWires){
			if (!start_wire) {
		      start_wire = fGeometryService->WirePtr(wire);
			}
			end_wire = fGeometryService->WirePtr(wire);
		  }
          if (!start_wire || !end_wire) continue;
		  
		  double wire_distance = std::fabs(end_wire->DistanceFrom(*start_wire));
      
		  TVector3 location(energyDeposit.x, energyDeposit.y, energyDeposit.z);
		  double distance = (location - positionStart.Vect()).Mag();
		  
		  total_edep_distance = distance;
		  total_wire_distance = wire_distance;

		} // end energy dep loop
	  } // end time slice loop
	} // end sim loop

	// Correct for TPC alignment
	geo::TPCGeo tpc_id = fGeometryService->PositionToTPC(start_wire->GetCenter());
	if (tpc_id.GetCenter() == vTPCs.at(1).GetCenter()) {
      fStartWire = (int)(std::fabs(start_wire->DistanceFrom(*fFirstWire_TPC1)) / fWirePitch);
	} else if (tpc_id.GetCenter() == vTPCs.at(2).GetCenter()) {
      fStartWire = (int)(std::fabs(start_wire->DistanceFrom(*fFirstWire_TPC2)) / fWirePitch);
	} else if (tpc_id.GetCenter() == vTPCs.at(5).GetCenter()) {
      fStartWire = (int)(std::fabs(start_wire->DistanceFrom(*fFirstWire_TPC1)) / fWirePitch);
	} else if (tpc_id.GetCenter() == vTPCs.at(6).GetCenter()) {
      fStartWire = (int)(std::fabs(start_wire->DistanceFrom(*fFirstWire_TPC2)) / fWirePitch);
	} else {
      std::cout << "[WARNING] Track starts in stub." << std::endl;
	  fStartWire = 0;
	}
	
	geo::TPCGeo tpc_id_end = fGeometryService->PositionToTPC(end_wire->GetCenter());

	fStartTick = start_tick;
	fEndTick = end_tick;

	int wires_crossed = (int)(total_wire_distance / fWirePitch);
	fdeltaWire = wires_crossed;
	int tick_change = (int)std::fabs(start_tick - end_tick);
    fdeltaTick = tick_change;
	
	if (fdeltaWire > 1000) {
	  geo::TPCGeo tpc_id_end = fGeometryService->PositionToTPC(end_wire->GetCenter());
	  int dWireSubtract;
	  if (tpc_id_end.GetCenter() == vTPCs.at(1).GetCenter()) {
        dWireSubtract = (int)(std::fabs(end_wire->DistanceFrom(*fFirstWire_TPC1)) / fWirePitch);
	  } else if (tpc_id_end.GetCenter() == vTPCs.at(2).GetCenter()) {
        dWireSubtract = (int)(std::fabs(end_wire->DistanceFrom(*fFirstWire_TPC2)) / fWirePitch);
	  } else if (tpc_id_end.GetCenter() == vTPCs.at(5).GetCenter()) {
        dWireSubtract = (int)(std::fabs(end_wire->DistanceFrom(*fFirstWire_TPC1)) / fWirePitch);
	  } else if (tpc_id_end.GetCenter() == vTPCs.at(6).GetCenter()) {
        dWireSubtract = (int)(std::fabs(end_wire->DistanceFrom(*fFirstWire_TPC2)) / fWirePitch);
	  } else {
	    std::cout << "[WARNING] Should not be here!" << std::endl;
		dWireSubtract = 0;
	  }
	  fdeltaWire -= dWireSubtract;
	}

	fEDepDistance = total_edep_distance;
    fWiresDistance = fdeltaWire * fWirePitch;

	std::cout << "TrackLength: " << total_edep_distance << ", MCParticle length: " << trackLength << std::endl;
    std::cout << "Wire dist = " << total_wire_distance << ", dWire = " << fdeltaWire << std::endl;	
    std::cout << "dTick = " << end_tick << " - " << start_tick << " = " << fdeltaTick << std::endl;	

    if (!fdeltaWire) std::cout << "ERROR"<<std::endl;	
    fSimulationNtuple->Fill();
	
	hMuonDeltaTick->Fill(fdeltaTick);
	hMuonDeltaWire->Fill(fdeltaWire);

	gMuonStartWireVDeltaWire->AddPoint(fdeltaWire, fStartWire);
  } // end particle loop

  std::cout << "Histgorams have Nentries = : " << hMuonDeltaTick->GetEntries() << ", " << hMuonDeltaWire->GetEntries() << std::endl;
}

// Define outputs at start of the job
void ana::TriggerPrimitiveProtoDUNE::beginJob()
{
  // Implementation of optional member function here.
  art::ServiceHandle<art::TFileService> tfs;

  hMuonDeltaTick = tfs->make<TH1D>("deltatick", ";#Delta Tick;", 100, 0, 1000);
  hMuonDeltaWire = tfs->make<TH1D>("deltawire", ";#Delta Wire Number;", 100, 0, 1000);
  
  gMuonStartWireVDeltaWire = tfs->make<TGraph>();

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
  fSimulationNtuple->Branch("StartWire", &fStartWire, "StartWire/I");
  fSimulationNtuple->Branch("EndWire", &fEndWire, "EndWire/I");
  fSimulationNtuple->Branch("deltaWire", &fdeltaWire, "deltaWire/I");
  fSimulationNtuple->Branch("StartTick", &fStartTick, "StartTick/I");
  fSimulationNtuple->Branch("EndTick", &fEndTick, "EndTick/I");
  fSimulationNtuple->Branch("deltaTick", &fdeltaTick, "deltaTick/I");
  fSimulationNtuple->Branch("TrackLength", &fTrackLength, "TrackLength/D");
  fSimulationNtuple->Branch("EDepDistance", &fEDepDistance, "EDepDistance/D");
  fSimulationNtuple->Branch("WiresDistance", &fWiresDistance, "WiresDistance/D");
  fSimulationNtuple->Branch("Process", &fProcess, "Process/C");

  fSimulationNtuple->Branch("StartXYZT", fStartXYZT, "StartXYZT[4]/D");
  fSimulationNtuple->Branch("EndXYZT", fEndXYZT, "EndXYZT[4]/D");
  fSimulationNtuple->Branch("PrimaryVertex", fPrimaryVertex, "PrimaryVertex[4]/D");
  fSimulationNtuple->Branch("PrimaryEnd", fPrimaryEnd, "PrimaryEnd[4]/D");
  fSimulationNtuple->Branch("StartPE", fStartPE, "StartPE[4]/D");
  fSimulationNtuple->Branch("EndPE", fEndPE, "EndPE[4]/D");

}

void ana::TriggerPrimitiveProtoDUNE::endJob()
{
  // Implementation of optional member function here.
}

DEFINE_ART_MODULE(ana::TriggerPrimitiveProtoDUNE)
