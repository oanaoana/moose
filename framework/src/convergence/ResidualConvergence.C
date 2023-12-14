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

registerMooseObject("MooseApp", ResidualConvergence);

InputParameters
ResidualConvergence::validParams()
{
  InputParameters params = Convergence::validParams();

  params.addClassDescription("Check ResidualConvergence of the set up problem.");
  //MooseEnum convtype("ResidualConvergence=1 space=2");
  //MooseEnum convloc("random=1 centroid=2");
  params.addRequiredParam<std::string>("variable", "The type of ResidualConvergence studied");

  return params;
}

ResidualConvergence::ResidualConvergence(const InputParameters & parameters)
  : Convergence(parameters),
   _fe_problem(*getCheckedPointerParam<FEProblemBase *>("_fe_problem_base")),
   _initialized(false),
   _var_name(getParam<std::string>("variable"))
   //_position(getParam<MooseEnum>("position")),
   //_steps(getParam<unsigned int>("steps"))
{
}

bool
ResidualConvergence::checkConvergence() const
{

  _console << "Variable to study  "<<_var_name<< std::endl;
  _console << "*********************** "<< std::endl;
  
  return true;
}




