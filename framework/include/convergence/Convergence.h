//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MooseObject.h"
#include "SetupInterface.h"

class Convergence : public MooseObject, public SetupInterface
{
public:
  static InputParameters validParams();

  Convergence(const InputParameters & parameters);

  virtual bool checkConvergence() const = 0;

  //FEProblemBase & _fe_problem;
};
