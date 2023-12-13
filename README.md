## CSE 221 Group Project (Group 6)
### Group Description
Group members:
1. Yanbo Zhou (yaz093@ucsd.edu)
2. Xiaochuan Yu

### How to run our code
In the source code folder, you will see four folders for each operation. Please refer to the following instructions for each operation.
#### CPU, Scheduling, OS
Enter CPU-Schedule-OS folder, then execute the following script in the CPU-Schedule-OS folder:
```shell
sudo make run
```
The output is in CPU cycles. To convert cycles to ns in our report, we use the following formula:
```
time = cycles / 2.5e9 * 1e9
```

#### Memory
Enter memory folder, then execute the following script in the memory folder:
```shell
make # compile all binary programs
sh preparetest.sh # prepare environment
sh run_ram_access_time.sh # for ram access time experiment
sh run_ram_bandwidth.sh # for ram bandwidth experiment
sh run_pagefault.sh # for pagefault experiment
```

#### Network
Enter network folder, then execute the following script in the network folder:
```shell
make run
```
This will compile every experiment program. Since all of them are in client-server model, you need to copy the server binary program to the server machine and copy the client binary program to the client machine. Then you can run the server program first, and then run the client program. 
For example:
```shell
./round_trip_server  # run server program
./round_trip_client server_ip_address server_port # run client program

./bandwidth_server  # run server program
./bandwidth_client server_ip_address server_port # run client program

./connection_overhead_server  # run server program
./connection_overhead_client server_ip_address server_port # run client program
```
For output in CPU cycles, we use the following formula to convert cycles to ns in our report:
```
time = cycles / 2.5e9 * 1e9
```

#### Filesystem
Enter file folder, then execute the following script in the file folder:
```shell
make # compile all binary programs
sh preparetest.sh # prepare environment. this will generate files used for the following program
sh run_filecache.sh # for file cache experiment
sh run_filedirect.sh # for file read time experiment
sh run_filecontention.sh # for file contention experiment
```

Note that for remote file read time, you can use the same script as file read time experiment as shown below, but the difference is that you should run them in NFS folder instead of local folder.
```shell
sh preparetest.sh # prepare environment. this will generate files used for the following program
sh run_filedirect.sh # for remote file read time experiment
```
