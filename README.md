## CSE 221 Group Project (Group 6)
### Group Description
Group members:
1. Yanbo Zhou (yaz093@ucsd.edu)
2. Xiaochuan Yu

### How to run our code
In the source code folder, you will see four folders for each operation. Please refer to the following instructions for each operation.
#### CPU, Scheduling, OS

#### Memory
Enter memory folder, then execute the following script in the memory folder:
```shell
make # compile all binary programs
sh preparetest.sh # prepare environment
sh run_ram_access_time.sh # for ram access time experiment
sh run run_ram_bandwidth.sh # for ram bandwidth experiment
sh run_pagefault.sh # for pagefault experiment
```

#### Network

#### Filesystem
Enter file folder, then execute the following script in the file folder:
```shell
make # compile all binary programs
sh preparetest.sh # prepare environment. this will generate files used for the following program
sh run_filecache.sh # for file cache experiment
sh run run_filedirect.sh # for file read time experiment
sh run_filecontention.sh # for file contention experiment
```

Note that for remote file read time, you can use the same script as file read time experiment as shown below, but the difference is that you should run them in NFS folder instead of local folder.
```shell
sh preparetest.sh # prepare environment. this will generate files used for the following program
sh run run_filedirect.sh # for remote file read time experiment
```
