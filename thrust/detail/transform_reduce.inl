/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file transform_reduce.inl
 *  \brief Inline file for transform_reduce.h.
 */

#include <thrust/detail/config.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/system/detail/generic/select_system.h>
#include <thrust/system/detail/generic/transform_reduce.h>
#include <thrust/system/detail/adl/transform_reduce.h>

namespace thrust
{


template<typename System,
         typename InputIterator, 
         typename UnaryFunction, 
         typename OutputType,
         typename BinaryFunction>
  OutputType transform_reduce(thrust::detail::dispatchable_base<System> &system,
                              InputIterator first,
                              InputIterator last,
                              UnaryFunction unary_op,
                              OutputType init,
                              BinaryFunction binary_op)
{
  using thrust::system::detail::generic::transform_reduce;
  return transform_reduce(system.derived(), first, last, unary_op, init, binary_op);
} // end transform_reduce()


namespace detail
{


template<typename System,
         typename InputIterator, 
         typename UnaryFunction, 
         typename OutputType,
         typename BinaryFunction>
  OutputType strip_const_transform_reduce(const System &system,
                                          InputIterator first,
                                          InputIterator last,
                                          UnaryFunction unary_op,
                                          OutputType init,
                                          BinaryFunction binary_op)
{
  System &non_const_system = const_cast<System&>(system);
  return thrust::transform_reduce(non_const_system, first, last, unary_op, init, binary_op);
} // end transform_reduce()


} // end detail


template<typename InputIterator, 
         typename UnaryFunction, 
         typename OutputType,
         typename BinaryFunction>
  OutputType transform_reduce(InputIterator first,
                              InputIterator last,
                              UnaryFunction unary_op,
                              OutputType init,
                              BinaryFunction binary_op)
{
  using thrust::system::detail::generic::select_system;

  typedef typename thrust::iterator_system<InputIterator>::type System;

  System system;

  return thrust::detail::strip_const_transform_reduce(select_system(system), first, last, unary_op, init, binary_op);
} // end transform_reduce()


} // end namespace thrust

