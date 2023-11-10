//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ConvergenceAction.h"

#ifdef LIBMESH_ENABLE_AMR

#include "FEProblem.h"
#include "NonlinearSystemBase.h"
#include "Convergence.h"
#include "Executioner.h"
#include "MooseEnum.h"
#include "RelationshipManager.h"

// libMesh includes
#include "libmesh/transient_system.h"
#include "libmesh/system_norm.h"
#include "libmesh/enum_norm_type.h"

registerMooseAction("MooseApp", ConvergenceAction, "setup_Convergence");
registerMooseAction("MooseApp", ConvergenceAction, "select_point");

ConvergenceAction::ConvergenceAction(const InputParameters & params) : Action(params) {}

void
ConvergenceAction::act()
{
if (_current_task == "setup_Convergence")
  {
    _problem->SetupConvergence();
  }
}

#endif // LIBMESH_ENABLE_AMR
