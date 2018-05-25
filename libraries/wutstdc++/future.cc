// future -*- C++ -*-

// Copyright (C) 2009-2018 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

#include <future>
#include <bits/functexcept.h>

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)
  __future_base::_Result_base::_Result_base() = default;

  __future_base::_Result_base::~_Result_base() = default;

  void
  __future_base::_State_baseV2::_Make_ready::_S_run(void* p)
  {
    unique_ptr<_Make_ready> mr{static_cast<_Make_ready*>(p)};
    if (auto state = mr->_M_shared_state.lock())
      {
  // Use release MO to synchronize with observers of the ready state.
  state->_M_status._M_store_notify_all(_Status::__ready,
      memory_order_release);
      }
  }

  // defined in src/c++11/condition_variable.cc
  extern void
  __at_thread_exit(__at_thread_exit_elt* elt);

  void
  __future_base::_State_baseV2::_Make_ready::_M_set()
  {
    _M_cb = &_Make_ready::_S_run;
    __at_thread_exit(this);
  }
#endif

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std
