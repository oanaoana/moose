//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// MOOSE includes
#include "Convergence.h"

#include "AppFactory.h"
#include "AuxiliarySystem.h"
#include "Executioner.h"
#include "FEProblem.h"
#include "MooseUtils.h"
#include "OutputWarehouse.h"
#include "SetupInterface.h"
#include "UserObject.h"
#include "NonlinearSystemBase.h"
#include "Positions.h"
#include "Transient.h"

#include "libmesh/mesh_tools.h"
#include "libmesh/numeric_vector.h"

// C++ includes
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>

// Call to "uname"
#ifdef LIBMESH_HAVE_SYS_UTSNAME_H
#include <sys/utsname.h>
#endif

InputParameters
Convergence::validParams()
{
  InputParameters params = MooseObject::validParams();

  params.addClassDescription("Check convergence of the set up problem.");
  MooseEnum convtype("time=1 space=2");
  MooseEnum convloc("random=1 centroid=2");

  params.addParam<unsigned int>("steps", 0, "The number of Convergence steps to perform");
  params.addRequiredParam<MooseEnum>("type", convtype, "The type of convergence studied");
  params.addRequiredParam<MooseEnum>("position", convloc, "The type of convergence studied");

  return params;
}

Convergence::Convergence(const InputParameters & parameters)
  : MooseObject(parameters),
  _fe_problem(*getCheckedPointerParam<FEProblemBase *>("_fe_problem_base")),
   _initialized(false),
   _type(getParam<MooseEnum>("type")),
   _position(getParam<MooseEnum>("position")),
   _steps(getParam<unsigned int>("steps"))
{
}

void
Convergence::SetupConvergence()
{

  Moose::out << "Time convergence "<< _type << std::endl;

  /*
  switch (_type)
  {
    case 1:
      Moose::out << "Time convergence " << std::endl;
      break;
    case 2:
      Moose::out << "Space convergence " << std::endl;
      break;
    default:
      mooseError("Unknown convergence type: " + _type);
  }
  */

  _initialized = true;
}




