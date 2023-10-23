## CSE 221 Group Project (Group 6)
### Group Description
Group members:
1. Yanbo Zhou (yaz093@ucsd.edu)
2. Xiaochuan Yu

AWS Information (https://awsed.ucsd.edu/):
- Instance ID: i-04d3033f0335826d0
- Name: CSE221-23group6

### Machine Description

1. Processor: model, cycle time, cache sizes (L1, L2, instruction, data, etc.)
   ```bash
   - Model: Intel(R) Xeon(R) Platinum 8259CL 
   - CPU MHz: 2.50GHz
   - CPU(s): 2 vCPUs (CPU 0 and CPU 1)
   - L1 data cache: 32 KiB
   - L1 instruction cache: 32 KiB
   - L2 cache: 1 MiB
   - L3 cache: 35.8 MiB
   - Architecture: x86_64
   - NUMA nodes: 1
   ```
2. Memory bus
   ```bash
   Physical Memory Array
           Location: System Board Or Motherboard
           Use: System Memory
           Error Correction Type: Unknown
           Maximum Capacity: 1 GB
           Error Information Handle: Not Provided
           Number Of Devices: 1

   Handle 0x0009, DMI type 17, 34 bytes
   Memory Device
           Array Handle: 0x0008
           Error Information Handle: Not Provided
           Total Width: 72 bits
           Data Width: 64 bits
           Size: 1 GB
           Form Factor: DIMM
           Set: None
           Locator: Not Specified
           Bank Locator: Not Specified
           Type: DDR4
           Type Detail: Static Column Pseudo-static Synchronous Window DRAM
           Speed: 2933 MT/s
           Manufacturer: Not Specified
           Serial Number: Not Specified
           Asset Tag: Not Specified
           Part Number: Not Specified
           Rank: Unknown
           Configured Memory Speed: Unknown
    ```
3. I/O bus
   ```bash
   00:00.0 Host bridge: Intel Corporation 440FX - 82441FX PMC [Natoma]
   00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
   00:01.3 Non-VGA unclassified device: Intel Corporation 82371AB/EB/MB PIIX4 ACPI (rev 08)
   00:03.0 VGA compatible controller: Amazon.com, Inc. Device 1111
   00:04.0 Non-Volatile memory controller: Amazon.com, Inc. NVMe EBS Controller
   00:05.0 Ethernet controller: Amazon.com, Inc. Elastic Network Adapter (ENA)
   ```
4. RAM size
   ```bash
   total: 904 MiB (available for user)
   ```
5. Disk: capacity, RPM, controller cache size
   ```bash
   NVMe SSD, 8GB capacity without cache.
   ```
6. Network card speed
   ```bash
   28Gbps
   ```
7. Operating system (including version/release)
   ```bash
   NAME="Amazon Linux"
   VERSION="2023"
   ID="amzn"
   ID_LIKE="fedora"
   RELEASE="2022/10/01"
   ```

