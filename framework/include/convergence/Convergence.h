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

#include "libmesh/communicator.h"
#include "libmesh/point.h"

#include "nlohmann/json.h"

class UserObject;
class FEProblemBase;
class FEProblem;
class Executioner;
class MooseApp;
class Positions;

class Convergence : public MooseObject
{
public:
  static InputParameters validParams();

  Convergence(const InputParameters & parameters);


private:
  const std::string & _position;
  const std::string & _type;
  bool _initialized;
  const unsigned int _steps;

  //void setParam(const std::string & param_name, const T & param_value);
  void SetupConvergence();

  //FEProblemBase & problemBase() { return _fe_problem; }

  FEProblemBase & _fe_problem;
};
