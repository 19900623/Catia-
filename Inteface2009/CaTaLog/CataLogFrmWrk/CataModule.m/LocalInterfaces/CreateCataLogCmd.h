// COPYRIGHT Dassault Systemes 2018
//===================================================================
//
// CreateCataLogCmd.h
// The state chart based command: CreateCataLogCmd
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//CAA2 Wizard Generation Report
//   STATECOMMAND
//End CAA2 Wizard Generation Report
//
//  Oct 2018  Creation: Code generated by the CAA wizard  dell
//===================================================================
#ifndef CreateCataLogCmd_H
#define CreateCataLogCmd_H

#include "CATStateCommand.h"
#include "CATBoolean.h"

class CATIndicationAgent;

//----------------------------------------------------------------------

/**
 * Describe your command here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 * <p>
 * refer to programming resources of Dialog engine framework.
 * (consult base class description).
 */
class CreateCataLogCmd: public CATStateCommand
{
  // Allows customization/internationalization of command's messages
  // ---------------------------------------------------------------
  DeclareResource( CreateCataLogCmd, CATStateCommand )

  public:

  CreateCataLogCmd();
  virtual ~CreateCataLogCmd();

    /**
     * Defines the command automata.
     * <br>
     * <i>(states, transitions and agents)</i>
     */
  virtual void     BuildGraph();

    /**
     * Action associated to state transitions.
     */
  virtual CATBoolean  ActionOne(void * data);

  private:

  CATIndicationAgent	* _Indication;
};

//----------------------------------------------------------------------

#endif
