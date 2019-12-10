#include "G4Example01Subsystem.h"
#include "G4Example01Detector.h"
#include "G4Example01SteppingAction.h"

#include <phparameter/PHParameters.h>

#include <g4main/PHG4HitContainer.h>
#include <g4main/PHG4SteppingAction.h>  // for PHG4SteppingAction

#include <phool/PHCompositeNode.h>
#include <phool/PHIODataNode.h>    // for PHIODataNode
#include <phool/PHNode.h>          // for PHNode
#include <phool/PHNodeIterator.h>  // for PHNodeIterator
#include <phool/PHObject.h>        // for PHObject
#include <phool/getClass.h>

#include <boost/foreach.hpp>

#include <set>  // for set
#include <sstream>

using namespace std;

//_______________________________________________________________________
G4Example01Subsystem::G4Example01Subsystem(const std::string &name)
  : PHG4DetectorSubsystem(name, 0)
  , m_Detector(nullptr)
  , m_SteppingAction(nullptr)
{
  InitializeParameters();
  Name(name);
  SuperDetector(name);
}

//_______________________________________________________________________
int G4Example01Subsystem::InitRunSubsystem(PHCompositeNode *topNode)
{
  PHNodeIterator iter(topNode);
  PHCompositeNode *dstNode = dynamic_cast<PHCompositeNode *>(iter.findFirst("PHCompositeNode", "DST"));

  // create detector
  m_Detector = new G4Example01Detector(this, topNode, Name());
  m_Detector->SuperDetector(SuperDetector());
  m_Detector->OverlapCheck(CheckOverlap());

  set<string> nodes;
  if (GetParams()->get_int_param("active"))
  {
    PHNodeIterator dstIter(dstNode);
    PHCompositeNode *DetNode = dynamic_cast<PHCompositeNode *>(dstIter.findFirst("PHCompositeNode", SuperDetector()));
    if (!DetNode)
    {
      DetNode = new PHCompositeNode(SuperDetector());
      dstNode->addNode(DetNode);
    }
    ostringstream nodename;
    if (SuperDetector() != "NONE")
    {
      nodename << "G4HIT_" << SuperDetector();
    }
    else
    {
      nodename << "G4HIT_" << Name();
    }
    nodes.insert(nodename.str());
    BOOST_FOREACH (string node, nodes)
    {
      PHG4HitContainer *g4_hits = findNode::getClass<PHG4HitContainer>(topNode, node.c_str());
      if (!g4_hits)
      {
        g4_hits = new PHG4HitContainer(node);
        DetNode->addNode(new PHIODataNode<PHObject>(g4_hits, node.c_str(), "PHObject"));
      }
    }
    // create stepping action
    m_SteppingAction = new G4Example01SteppingAction(m_Detector, GetParams());
  }

  return 0;
}

//_______________________________________________________________________
int G4Example01Subsystem::process_event(PHCompositeNode *topNode)
{
  // pass top node to stepping action so that it gets
  // relevant nodes needed internally
  if (m_SteppingAction)
  {
    m_SteppingAction->SetInterfacePointers(topNode);
  }
  return 0;
}

void G4Example01Subsystem::Print(const string &what) const
{
  //cout << "PSTOF Parameters: " << endl;
  if (m_Detector)
  {
    m_Detector->Print(what);
  }
  return;
}

//_______________________________________________________________________
PHG4Detector *G4Example01Subsystem::GetDetector(void) const
{
  return m_Detector;
}

void G4Example01Subsystem::SetDefaultParameters()
{
  // all units are in cm
  set_default_double_param("PixelDy", 4. / 10.);  // dy/10

  set_default_int_param("layers", 6);
}
