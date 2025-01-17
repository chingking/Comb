//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-758885
//
// All rights reserved.
//
// This file is part of Comb.
//
// For details, see https://github.com/LLNL/Comb
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////

#ifndef _POL_MPI_TYPE_HPP
#define _POL_MPI_TYPE_HPP

#include "config.hpp"

struct mpi_type_component
{
  void* ptr = nullptr;
};

struct mpi_type_group
{
  void* ptr = nullptr;
};

// execution policy indicating that message packing/unpacking should be done
// in MPI using MPI_Types
struct mpi_type_pol {
  static const bool async = false;
  static const char* get_name() { return "mpi_type"; }
  using event_type = int;
  using component_type = mpi_type_component;
  using group_type = mpi_type_group;
};

template < >
struct ExecContext<mpi_type_pol> : MPIContext
{
  using pol = mpi_type_pol;
  using event_type = typename pol::event_type;
  using component_type = typename pol::component_type;
  using group_type = typename pol::group_type;

  using base = MPIContext;

  ExecContext()
    : base()
  { }

  ExecContext(base const& b)
    : base(b)
  { }

  void ensure_waitable()
  {

  }

  template < typename context >
  void waitOn(context& con)
  {
    con.ensure_waitable();
    base::waitOn(con);
  }

  // synchronization functions
  void synchronize()
  {
  }

  group_type create_group()
  {
    return group_type{};
  }

  void start_group(group_type)
  {
  }

  void finish_group(group_type)
  {
  }

  void destroy_group(group_type)
  {

  }

  component_type create_component()
  {
    return component_type{};
  }

  void start_component(group_type, component_type)
  {

  }

  void finish_component(group_type, component_type)
  {

  }

  void destroy_component(component_type)
  {

  }

  // event creation functions
  event_type createEvent()
  {
    return event_type{};
  }

  // event record functions
  void recordEvent(event_type)
  {
  }

  void finish_component_recordEvent(group_type group, component_type component, event_type event)
  {
    finish_component(group, component);
    recordEvent(event);
  }

  // event query functions
  bool queryEvent(event_type)
  {
    return true;
  }

  // event wait functions
  void waitEvent(event_type)
  {
  }

  // event destroy functions
  void destroyEvent(event_type)
  {
  }

  // template < typename body_type >
  // void for_all(IdxT begin, IdxT end, body_type&& body)
  // {
  //   COMB::ignore_unused(pol, begin, end, body);
  //   static_assert(false, "This method should never be used");
  // }

  // template < typename body_type >
  // void for_all_2d(IdxT begin0, IdxT end0, IdxT begin1, IdxT end1, body_type&& body)
  // {
  //   COMB::ignore_unused(pol, begin0, end0, begin1, end1, body);
  //   static_assert(false, "This method should never be used");
  // }

  // template < typename body_type >
  // void for_all_3d(IdxT begin0, IdxT end0, IdxT begin1, IdxT end1, IdxT begin2, IdxT end2, body_type&& body)
  // {
  //   COMB::ignore_unused(pol, begin0, end0, begin1, end1, begin2, end2, body);
  //   static_assert(false, "This method should never be used");
  // }

};

#endif // _POL_MPI_TYPE_HPP
