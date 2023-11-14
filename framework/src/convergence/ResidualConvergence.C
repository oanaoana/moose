//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// MOOSE includes
#include "ResidualConvergence.h"

InputParameters
ResidualConvergence::validParams()
{
  InputParameters params = ResidualConvergence::validParams();

  params.addClassDescription("Check ResidualConvergence of the set up problem.");
  MooseEnum convtype("ResidualConvergence=1 space=2");
  MooseEnum convloc("random=1 centroid=2");

  //params.addParam<unsigned int>("steps", 0, "The number of ResidualConvergence steps to perform");
  params.addRequiredParam<MooseEnum>("type", convtype, "The type of ResidualConvergence studied");
  //params.addRequiredParam<MooseEnum>("position", convloc, "The type of ResidualConvergence studied");

  return params;
}

ResidualConvergence::ResidualConvergence(const InputParameters & parameters)
  : Convergence(parameters),
   _fe_problem(*getCheckedPointerParam<FEProblemBase *>("_fe_problem_base")),
   _initialized(false),
   _type(getParam<MooseEnum>("type"))
   //_position(getParam<MooseEnum>("position")),
   //_steps(getParam<unsigned int>("steps"))
{
}

void
ResidualConvergence::checkConvergence()
{

  Moose::out << "Time convergence "<< std::endl;

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




