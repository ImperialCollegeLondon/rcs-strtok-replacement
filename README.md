# rcs-strtok-replacement

Intel MPI 2018 (all updates) has a bug that manifests on CentOS 8.0 and 8.1 (at time of writing).
This bug causes the MPI process startup to segfault in MPI_Init(). The diagnostic stack trace is:

```
Program received signal SIGSEGV, Segmentation fault.
0x0000155553996b06 in strtok_r () from /lib64/libc.so.6
Missing separate debuginfos, use: dnf debuginfo-install glibc-2.28-42.el8.1.x86_64 libgcc-8.2.1-3.5.el8.x86_64 numactl-devel-2.0.12-2.el8.x86_64
(gdb) bt
#0  0x0000155553996b06 in strtok_r () from /lib64/libc.so.6
#1  0x0000155554b36b61 in __I_MPI___intel_sse2_strtok ()
   from /apps/mpi/intel/2018.1.163/lib/libmpi.so.12
#2  0x00001555549f0925 in MPID_nem_impi_create_numa_nodes_map ()
    at ../../src/mpid/ch3/src/mpid_init.c:458
#3  0x00001555549f3634 in MPID_Init (argc=0x0, argv=0x155554ba1b54,
    requested=1405930120, provided=0x0, has_args=0x3,
    has_env=0x101010101010101) at ../../src/mpid/ch3/src/mpid_init.c:1760
#4  0x000015555499442b in MPIR_Init_thread (argc=0x0, argv=0x155554ba1b54,
    required=1405930120, provided=0x0) at ../../src/mpi/init/initthread.c:717
#5  0x00001555549819bb in PMPI_Init (argc=0x0, argv=0x155554ba1b54)
    at ../../src/mpi/init/init.c:253
#6  0x0000000000401a46 in main ()
```

This can be fixed by LD_PRELOADing this shimmed strtok, which avoids segfaulting on a NULL argument. Example:

```
export LD_PRELOAD=$PWD/libc-strtok-shim.so
mpiexec a.out
```



