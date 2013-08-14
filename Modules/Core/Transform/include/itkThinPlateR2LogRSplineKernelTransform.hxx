/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkThinPlateR2LogRSplineKernelTransform_hxx
#define __itkThinPlateR2LogRSplineKernelTransform_hxx
#include "itkThinPlateR2LogRSplineKernelTransform.h"

namespace itk
{
template< class TScalar, unsigned int NDimensions >
void
ThinPlateR2LogRSplineKernelTransform< TScalar, NDimensions >::ComputeG(const InputVectorType & x,
                                                                           GMatrixType & gmatrix) const
{
  const TScalar r = x.GetNorm();

  gmatrix.fill(NumericTraits< TScalar >::Zero);
  const TScalar      R2logR =
    ( r > 1e-8 ) ? r *r *vcl_log(r):NumericTraits< TScalar >::Zero;

  gmatrix.fill_diagonal(R2logR);
}

template< class TScalar, unsigned int NDimensions >
void
ThinPlateR2LogRSplineKernelTransform< TScalar, NDimensions >::ComputeDeformationContribution(
  const InputPointType  & thisPoint,
  OutputPointType &
  result) const
{
  unsigned long numberOfLandmarks = this->m_SourceLandmarks->GetNumberOfPoints();

  PointsIterator sp  = this->m_SourceLandmarks->GetPoints()->Begin();

  for ( unsigned int lnd = 0; lnd < numberOfLandmarks; lnd++ )
    {
    InputVectorType        position = thisPoint - sp->Value();
    const TScalar      r = position.GetNorm();
    const TScalar      R2logR =
      ( r > 1e-8 ) ? r *r *vcl_log(r):NumericTraits< TScalar >::Zero;
    for ( unsigned int odim = 0; odim < NDimensions; odim++ )
      {
      result[odim] += R2logR * this->m_DMatrix(odim, lnd);
      }
    ++sp;
    }
}
} // namespace itk
#endif
