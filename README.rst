
.. image:: https://github.com/BoiseState-AdaptLab/AdaptMemBench/blob/master/doc/logo/AdaptMemBench.svg

**AdaptMemBench** is configurable benchmarking framework to measure memory system performance of compute kernels extracted from applications. This framework can be used to explore the design landscape of a target architecture and to guide application-specific optimization decisions. AdaptMemBench supports reproducibility in experimental results and facilitates sharing results. Accommodation of the polyhedral model in the build system provides a convenient testbed for potential code optimizations. Access to hardware performance counters offers insights on the interaction of the application with the memory subsystem. 

Installation
------------

This framework requires the following to be installed:

* GNU GCC (version 6.4 or later)
* Python (version 2.7 or later)
* PAPI (The Performance API)
* ISL (Integer Set Library)
* matplotlib library (version 3.0.3)

Usage
-----

Generating Benchmark Drivers:
Benchmark drivers can be generated for kernels implemented with unified data spaces or distinct (independent) data spaces - use ``adaptMemBench_gen_unifiedDS`` and ``adaptMemBench_gen_distinctDS`` generation scripts respectively. Drivers instrumented with PAPI can be generated using ``adaptMemBench_gen_papi_unifiedDS`` and ``adaptMemBench_gen_papi_distinctDS``


 ``cd src``

 ``python ../generators/adaptMemBench_gen_<option> <kernel>``

This generates a benchmark driver named ``adapt_membench_<option>_<kernel>.cpp``
To compile the driver:


 ``cd -``

 ``make adapt_membench_<option>_<kernel>``

Executing the benchmark driver:

 ``./bin/adapt_membench_<option>_<kernel> --wss <data size value> --num_threads <number of threads> --ntimes <number of repetitions> ...``

Example
-------
To generate a stencil 1D benchmark implemented with unified data spaces,

 ``cd src``

 ``python ../generators/adaptMemBench_gen_unifiedDS stencil_1d``
 
 ``cd -``

 ``make adaptMemBench_gen_unifiedDS_stencil_1d``

 ``./bin/adapt_membench_unifiedDS_stencil_1d --wss 1048576 --num_threads 8 --ntimes 1000``

For detailed instructions, please refer documentation








