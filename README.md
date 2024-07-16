# ProtoDUNE BSM LArSoft Code 

Allows for the simulation and analysis of BSM events in ProtoDUNE-HD.

This includes full detector simulation.

## Building

```
git clone https://github.com/CiaranH1997/ProtoDUNE_BSM_LArSoft.git

source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

setup dunesw v09_85_00d00 -q e26:prof

mrb newDev -f v09_85_00d00 -q e26:prof (-f is because /srcs dir already exists. You may need to delete some .bak files)

source localProducts_larsoft_v09_85_00_e26_prof/setup

cd $MRB_BUILDDIR

mrbsetenv

mrb i -j16
```

You should be now ready to run the code!

## Generating HNL Events

Generating HNL events uses the module `HepMCFileGen_module.cc`.

- Use HEPEvt format .txt files to get lists of HNL events.
- Enter location of .txt file into `srcs/protodunedm/protodunedm/hepmcfilegen.fcl`.
- Recompile.
- run: `lar -c job/run_hepmcfilegen.fcl -o gen.root -n 1000`. Choose the specific command line options you need.
- This will generate 1000 HNL events in NP04 at the MCTruth level and output the result to `test_hepmc.root`.

## LArSoft ProtoDUNE Simulation

You can then go further and use the LArSoft G4 particle propogation, detector simulation and reconstruction. At each step you input the file that was outputted by the previous step. You cannot jump straight from MCTruth to detsim!

Geant4 simulation:
```
lar –c standard_g4_protodunehd.fcl -o g4gen.root –s gen.root
```
Detsim simulation:
```
lar –c standard_detsim_protodunehd.fcl -o detsimg4gen.root –s g4gen.root
```
Reconstruction simulation:
```
lar –c standard_reco_protodunehd.fcl -o recodetsimg4gen.root –s detsimg4gen.root
```

## Event Display

Once you reach the detector simulation stage, looking at event displays can be useful:

```
lar -c evd_protoDUNE.fcl detsimg4gen.root
```

It is highly recommended you do this with a [VNC](https://sbnsoftware.github.io/sbndcode_wiki/Viewing_events_remotely_with_VNC.html) viewer!

## Analyzer Modules

- `ProtoDUNEDMAnalyze_module.cc`
- `TriggerPrimitiveProtoDUNE_module.cc`




# Running jobs in cluster using HTCondor

The connection to cluster is already done in the server. So, no commands are required specifically for connecting to the cluster.

## Submitting jobs

<ol>

   <li>Create a script file, say, run1.sh, which have all the commands to do the job.</li>
   <li>Create a submit description file, say, run1.sub, which has the following format:

        
        executable              = run1.sh

        log                     = run1.log
        output                  = run1.out
        error                   = run1.err

        should_transfer_files   = Yes
        when_to_transfer_output = ON_EXIT

        MY.WantOS = "el7"
        +JobFlavour = "longlunch"

        request_cpus            = 1
        request_memory          = 512M
        request_disk            = 1G

        queue
        
  </li>
   <li>Submit the job:

      
      condor_submit run1.sub
      
   </li>
   <li>To check the status:

   
      condor_q
      
   </li>
<ol>