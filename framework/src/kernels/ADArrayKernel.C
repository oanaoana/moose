//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADArrayKernel.h"

#include "Assembly.h"
#include "MooseVariableFE.h"
#include "MooseVariableScalar.h"
#include "SubProblem.h"
#include "NonlinearSystem.h"

#include "libmesh/threads.h"
#include "libmesh/quadrature.h"

InputParameters
ADArrayKernel::validParams()
{
  InputParameters params = KernelBase::validParams();
  params.registerBase("ADArrayKernel");
  return params;
}

ADArrayKernel::ADArrayKernel(const InputParameters & parameters)
  : KernelBase(parameters),
    MooseVariableInterface<RealEigenVector>(this,
                                            false,
                                            "variable",
                                            Moose::VarKindType::VAR_SOLVER,
                                            Moose::VarFieldType::VAR_FIELD_ARRAY),
    _var(*mooseVariable()),
    _test(_var.phi()),
    _grad_test(_var.gradPhi()),
    _array_grad_test(_var.arrayGradPhi()),
    _phi(_assembly.phi(_var)),
    _grad_phi(_assembly.gradPhi(_var)),
    _u(_var.adSln()),
    _grad_u(_var.adGradSln()),
    _count(_var.count()),
    _work_vector(_count)                                     
{
  addMooseVariableDependency(mooseVariable());

}

void
ADArrayKernel::computeResidual()
{
    /*
  prepareVectorTag(_assembly, _var.number());

  precalculateResidual();
  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
  {
    initQpResidual();
    for (_i = 0; _i < _test.size(); _i++)
    {
      _work_vector.setZero();
      computeQpResidual(_work_vector);
      mooseAssert(_work_vector.size() == _count,
                  "Size of local residual is not equal to the number of array variable compoments");
      _work_vector *= _JxW[_qp] * _coord[_qp];
      _assembly.saveLocalArrayResidual(_local_re, _i, _test.size(), _work_vector);
    }
  }

  accumulateTaggedLocalResidual();

  if (_has_save_in)
  {
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (const auto & var : _save_in)
    {
      auto * avar = dynamic_cast<ArrayMooseVariable *>(var);
      if (avar)
        avar->addSolution(_local_re);
      else
        mooseError("Save-in variable for an array kernel must be an array variable");
    }
  }
  */
}

void
ADArrayKernel::computeJacobian()
{ 
    /*
  prepareMatrixTag(_assembly, _var.number(), _var.number());

  precalculateJacobian();
  for (_qp = 0; _qp < _qrule->n_points(); _qp++)
  {
    initQpJacobian();
    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
      {
        _work_vector = computeQpJacobian() * _JxW[_qp] * _coord[_qp];
        _assembly.saveDiagLocalArrayJacobian(
            _local_ke, _i, _test.size(), _j, _phi.size(), _var.number(), _work_vector);
      }
  }

  accumulateTaggedLocalMatrix();

  if (_has_diag_save_in)
  {
    DenseVector<Number> diag = _assembly.getJacobianDiagonal(_local_ke);
    Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
    for (const auto & var : _diag_save_in)
    {
      auto * avar = dynamic_cast<ArrayMooseVariable *>(var);
      if (avar)
        avar->addSolution(diag);
      else
        mooseError("Save-in variable for an array kernel must be an array variable");
    }
  }
  */
}



void 
ADArrayKernel::computeOffDiagJacobian(unsigned int jvar)
{

}
