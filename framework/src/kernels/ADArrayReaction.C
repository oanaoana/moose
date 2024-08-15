//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADArrayReaction.h"

registerMooseObject("MooseApp", ADArrayReaction);

InputParameters
ADArrayReaction::validParams()
{
  InputParameters params = ADArrayKernel::validParams();
  params += ADFunctorInterface::validParams();
  params.addParam<MaterialPropertyName>(
      "reaction_coefficient",
      "The name of the reaction, can be scalar, vector, or matrix material property.");
  params.addClassDescription(
      "An automatic differentiation kernel for the array reaction operator ($u$)");
  return params;
}

ADArrayReaction::ADArrayReaction(const InputParameters & parameters)
  : ADArrayKernel(parameters),
    _r(hasMaterialProperty<Real>("reaction_coefficient")
           ? &getMaterialProperty<Real>("reaction_coefficient")
           : nullptr),
    _r_array(hasMaterialProperty<RealEigenVector>("reaction_coefficient")
                 ? &getMaterialProperty<RealEigenVector>("reaction_coefficient")
                 : nullptr),
    _r_2d_array(hasMaterialProperty<RealEigenMatrix>("reaction_coefficient")
                    ? &getMaterialProperty<RealEigenMatrix>("reaction_coefficient")
                    : nullptr)
{
  
}

void
ADArrayReaction::initQpResidual()
{ 
  if (_r_array)
  {
    mooseAssert((*_r_array)[_qp].size() == _var.count(),
                "reaction_coefficient size is inconsistent with the number of components of array "
                "variable");
  }
}

void
ADArrayReaction::computeQpResidual(ADRealEigenVector & residual)
{
  // WARNING: the noalias() syntax is an Eigen optimization tactic, it avoids creating
  // a temporary object for the matrix multiplication on the right-hand-side. However,
  // it should be used with caution because it could cause unintended results,
  // developers should NOT use it if the vector on the left-hand-side appears on the
  // right-hand-side, for instance:
  //   vector = matrix * vector;
  // See http://eigen.tuxfamily.org/dox/group__TopicAliasing.html for more details.
  
  if (_r)
    residual = (*_r)[_qp] * _u[_qp] * _test[_i][_qp];
  else if (_r_array)
    residual = (*_r_array)[_qp].asDiagonal() *_u[_qp] * _test[_i][_qp];
  //else
    //residual.noalias() = (*_r_2d_array)[_qp] * _grad_u[_qp] * _array_grad_test[_i][_qp];
}

/*
RealEigenVector
ADArrayReaction::computeQpJacobian()
{
  if (_r)
    return RealEigenVector::Constant(_var.count(),
                                     _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_r)[_qp]);
  else if (_r_array)
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_r_array)[_qp];
  else
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_r_2d_array)[_qp].diagonal();
}

RealEigenMatrix
ADArrayReaction::computeQpOffDiagJacobian(const MooseVariableFEBase & jvar)
{
  if (jvar.number() == _var.number() && _r_2d_array)
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_r_2d_array)[_qp];
  else
    return ArrayKernel::computeQpOffDiagJacobian(jvar);
}
*/