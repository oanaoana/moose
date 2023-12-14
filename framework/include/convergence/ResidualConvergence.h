//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Convergence.h"

class ResidualConvergence : public Convergence
{
public:
  static InputParameters validParams();

  ResidualConvergence(const InputParameters & parameters);

  virtual bool checkConvergence() const override;

protected:

  FEProblemBase & _fe_problem;

  bool _initialized;
  const std::string & _var_name;
  //const std::string & _type;
  //const std::string & _position;
  //const unsigned int _steps;

};
