// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4EXAMPLE01SUBSYSTEM_H
#define G4EXAMPLE01SUBSYSTEM_H

#include <g4detectors/PHG4DetectorSubsystem.h>

#include <string>

class PHCompositeNode;
class PHG4Detector;
class G4Example01Detector;
class PHG4SteppingAction;

/**
   * \brief Fun4All module to simulate the Barrel PSTOF detector.
   *
   * The detector is constructed and registered via G4Example01Detector
   *
   * The PHG4SteppingAction needs to be written, but will provide the info for the hit time
   *
   * \see G4Example01Detector
   * \see G4Example01Subsystem
   *
   */
class G4Example01Subsystem : public PHG4DetectorSubsystem
{
 public:
  //! constructor
  G4Example01Subsystem(const std::string& name = "JLDIRC");

  //! destructor
  virtual ~G4Example01Subsystem(void)
  {
  }

  /*!
  creates the m_Detector object and place it on the node tree, under "DETECTORS" node (or whatever)
  reates the stepping action and place it on the node tree, under "ACTIONS" node
  creates relevant hit nodes that will be populated by the stepping action and stored in the output DST
  */
  virtual int InitRunSubsystem(PHCompositeNode*);

  //! event processing
  /*!
  get all relevant nodes from top nodes (namely hit list)
  and pass that to the stepping action
  */
  virtual int process_event(PHCompositeNode*);

  //! accessors (reimplemented)
  virtual PHG4Detector* GetDetector() const;
  virtual PHG4SteppingAction* GetSteppingAction() const {return  m_SteppingAction;}
  //! Print info (from SubsysReco)
  virtual void Print(const std::string& what = "ALL") const;

 private:
  void SetDefaultParameters();

  //! detector geometry
  /*! defives from PHG4Detector */
  G4Example01Detector* m_Detector;

  //! particle tracking "stepping" action
  /*! derives from PHG4SteppingActions */
  PHG4SteppingAction* m_SteppingAction;
};

#endif  // G4EXAMPLE01SUBSYSTEM_H
