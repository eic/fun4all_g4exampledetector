// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4_EXAMPLESTEPPINGACTION_H
#define G4_EXAMPLESTEPPINGACTION_H

#include <g4main/PHG4SteppingAction.h>

class G4Step;
class G4VPhysicalVolume;
class PHCompositeNode;
class G4ExampleDetector;
class PHG4Hit;
class PHG4HitContainer;
class PHParameters;

class G4ExampleSteppingAction : public PHG4SteppingAction
{
 public:
  //! constructor
  G4ExampleSteppingAction(G4ExampleDetector*, const PHParameters*);

  //! destructor
  virtual ~G4ExampleSteppingAction();

  //! stepping action
  virtual bool UserSteppingAction(const G4Step*, bool);

  //! reimplemented from base class
  virtual void SetInterfacePointers(PHCompositeNode*);

 private:
  //! pointer to the detector
  G4ExampleDetector* m_Detector;
  //! pointer to hit container
  PHG4HitContainer* m_HitContainer;
  PHG4Hit* m_Hit;
  PHG4HitContainer* m_SaveHitContainer;

  G4VPhysicalVolume* m_SaveVolPre;
  G4VPhysicalVolume* m_SaveVolPost;
  int m_SaveTrackId;
  int m_SavePreStepStatus;
  int m_SavePostStepStatus;
  double m_EdepSum;
  double m_EionSum;
};

#endif  // G4_EXAMPLESTEPPINGACTION_H
