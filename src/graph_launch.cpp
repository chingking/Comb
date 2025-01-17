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

#include "config.hpp"

#ifdef COMB_ENABLE_CUDA_GRAPH

#include "graph_launch.hpp"

namespace cuda {

namespace graph_launch {

// Ensure the current batch launched (actually launches batch)
void force_launch(cudaStream_t stream)
{
   // NVTX_RANGE_COLOR(NVTX_CYAN)
   if (get_group().graph != nullptr && get_group().graph->launchable()) {
      get_group().graph->launch(stream);
      new_active_group();
   }
}

// Wait for all batches to finish running
void synchronize(cudaStream_t stream)
{
   // NVTX_RANGE_COLOR(NVTX_CYAN)
   force_launch(stream);

   // perform synchronization
   cudaCheck(cudaStreamSynchronize(stream));
}

} // namespace graph_launch

} // namespace cuda

#endif
