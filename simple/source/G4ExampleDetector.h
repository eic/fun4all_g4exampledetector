// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4_EXAMPLEDETECTOR_H
#define G4_EXAMPLEDETECTOR_H

#include <g4main/PHG4Detector.h>

#include <set>
#include <string>  // for string

class G4LogicalVolume;
class G4VPhysicalVolume;
class PHCompositeNode;
class PHG4Subsystem;
class PHParameters;

class G4ExampleDetector : public PHG4Detector
{
 public:
  //! constructor
  G4ExampleDetector(PHG4Subsystem *subsys, PHCompositeNode *Node, PHParameters *params_array, const std::string &dnam);

  //! destructor
  virtual ~G4ExampleDetector() {}

  //! construct
  virtual void ConstructMe(G4LogicalVolume *world);

  virtual void Print(const std::string &what = "ALL") const;

  //!@name volume accessors
  //@{
  int IsInDIRC(G4VPhysicalVolume *) const;
  //@}

  void SuperDetector(const std::string &name) { m_SuperDetector = name; }
  const std::string SuperDetector() const { return m_SuperDetector; }

 protected:
  PHParameters *m_Params;
  std::set<G4VPhysicalVolume *> m_PhysicalVolumesSet;

  std::string m_SuperDetector;
};

#endif  // G4_EXAMPLEDETECTOR_H
