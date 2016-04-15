# Worsepthread (The sodomization of [Badpthread](https://github.com/735tesla/badpthread) and [p.c](https://github.com/frjalex/p.c)

This is the combination of a dynamic library and a zombie that, when loaded into a process, will execute a function before that process's main that starts a new thread. This new thread will basically fork itself as a UNIX-style daemon (zombie!), launch another process whhich starts another thread, that reads the memory from **last known occupied memory location** and copies them into new memory blocks. This will, eventually, use up about 90% of the total available memory. And, it's safe from being killed by the UNIX kernel's standard memory management function, because it rests and stops allocating more memory for a brief time during the period of `20pi rounds`.

In order to cause more chaos in the system, the `fuck_your_mem ()` function will also fork itself to span across seperate processes, so that one cannot kill every one of them quickly. Further, it starts forking itself to new processes at a **geometric speed** after being run for a while, furtherly stressing the system.

Its original version, <code>p.c</code>, had been tested on a computer with an Intel Core i3-3267u and 8GiBs of RAM. Everytime the system completely crashes (not in the traditional way which it gives you a black/blue screen of death, but it stops you from basically doing any task on the system) and the heat the computer rapidly goes up. Pretty good way to stress a computer though. Anyhow, everytime when I try to take a screenshot, I can't because it crashes my performance monitor, kSnapshot, chrome, and any other usable thing. A snapshot of [735tesla](https://github.com/735tesla) 's Badpthread is placed below.

##Original badpthread analysis
Quoted from [badpthread/README.md](https://github.com/735tesla/badpthread)
```
......
This means that if it is injected into, say, `/bin/ls`, and given an argument of `/tmp/meterpreter`, both will run. You will see ls print the name of the file specified (because that's what ls does) and the program will also run within ls. ls will not terminate until the second program completes.
```
Compiling:
----------
`gcc -o worsepthread.dylib -dynamiclib worsepthread.c`

Example:
---------
`DYLD_INSERT_LIBRARIES=worsepthread.dylib /path/to/host/binary`

Notes:
------
* This won't work with any OS X binaries that use entitlements that disallow DYLD_* environmental variables.
* This won't work on any binaries in which euid != ruid
* This doesn't currently work on linux because you can't load ELF executables like dynamic libraries
    - [Possible workaround](https://grugq.github.io/docs/subversiveld.pdf)

Screen shot:
------------
Again, this is the effect of the original badpthread. You can't really capture worsepthread given it's highly-effective memory allocation system.
![Screen shot of usage](https://i.imgur.com/ZR2kJaA.png)
