//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADArrayDiffusion.h"

registerMooseObject("MooseApp", ADArrayDiffusion);

InputParameters
ADArrayDiffusion::validParams()
{
  InputParameters params = ADArrayKernel::validParams();
  params += ADFunctorInterface::validParams();
  params.addParam<MaterialPropertyName>(
      "diffusion_coefficient",
      "The name of the diffusivity, can be scalar, vector, or matrix material property.");
  params.addClassDescription(
      "The array Laplacian operator ($-\\nabla \\cdot \\nabla u$), with the weak "
      "form of $(\\nabla \\phi_i, \\nabla u_h)$.");
  return params;
}

ADArrayDiffusion::ADArrayDiffusion(const InputParameters & parameters)
  : ADArrayKernel(parameters),
    _d(&getMaterialProperty<Real>("diffusion_coefficient"))
{
  
}

void
ADArrayDiffusion::initQpResidual()
{ 
    //insert asserts
}

void
ADArrayDiffusion::computeQpResidual(ADRealEigenVector & residual)
{
  // WARNING: the noalias() syntax is an Eigen optimization tactic, it avoids creating
  // a temporary object for the matrix multiplication on the right-hand-side. However,
  // it should be used with caution because it could cause unintended results,
  // developers should NOT use it if the vector on the left-hand-side appears on the
  // right-hand-side, for instance:
  //   vector = matrix * vector;
  // See http://eigen.tuxfamily.org/dox/group__TopicAliasing.html for more details.
  
    //residual = (*_d)[_qp] * _grad_u[_qp] * _array_grad_test[_i][_qp];
    residual = _grad_u[_qp]* _array_grad_test[_i][_qp];
  
}

/*
RealEigenVector
ADArrayDiffusion::computeQpJacobian()
{
  if (_d)
    return RealEigenVector::Constant(_var.count(),
                                     _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_d)[_qp]);
  else if (_d_array)
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_d_array)[_qp];
  else
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_d_2d_array)[_qp].diagonal();
}

RealEigenMatrix
ADArrayDiffusion::computeQpOffDiagJacobian(const MooseVariableFEBase & jvar)
{
  if (jvar.number() == _var.number() && _d_2d_array)
    return _grad_phi[_j][_qp] * _grad_test[_i][_qp] * (*_d_2d_array)[_qp];
  else
    return ArrayKernel::computeQpOffDiagJacobian(jvar);
}
*/