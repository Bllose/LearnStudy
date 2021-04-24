~\AppData\Local\chia-blockchain\app-1.1.1\resources\app.asar.unpacked\daemon  
chia.exe

1. 首先获取自己的public key 
```
chia keys show
Showing all private keys:

Fingerprint: 2787218046
Master public key (m): 8f3b80b79f6b80e0b1e035057b48f7159831bc5be880f2cef8c143acafad38c0f3192cbd87dd560f994fe1d7839904bf
Master private key (m): 44c2f558eebea6dcd47aa9ceb12c7d5bd4c72434330b6ff1622bc898b5b49d2f
Farmer public key (m/12381/8444/0/0): adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
Pool public key (m/12381/8444/1/0): a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
First wallet key (m/12381/8444/2/0): 8fc4e26b5e582b806dbff90692c9c1f43dbbef9fcf060b777f5b35fb533a17f193aa00be4d369c243ef3331d46142091
First wallet address: xch1smlqd88tpslhatvdecuxvu2a8n74sjv5du9n3g4f29qvlywsjqtq3g2fdy
```  

2. 创建命令中加入自己的public key  
Command: chia plots create [add flags and parameters]

Flags

-k [size]: Define the size of the plot(s). 
For a list of k-sizes and creation times on various systems check out: k-Sizes

-n [number of plots]: The number of plots that will be made, in sequence. 
Once a plot is finished, it will be moved to the final location -d, before starting the next plot in the sequence.

-b [memory buffer size MiB]: Define memory/RAM usage. 
Default is 4608 (4.6 GiB). More RAM will marginally increase speed of plot creation. 
Please bear in mind that this is what is allocated to the plotting algorithm alone. 
Code, container, libraries etc. will require additional RAM from your system.

-f [farmer pk]: **This is your "Farmer Public Key".**  
Utilise this when you want to create plots on other machines for which you do not want to give full chia account access. To find your Chia Farmer Public Key use the following command: chia keys show

-p [pool pk]: **This is your "Pool Public Key".**  
Utilise this when you want to create plots on other machines for which you do not want to give full chia account access. To find your Chia Pool Public Key use the following command: chia keys show

-a [fingerprint]: **This is the key Fingerprint used to select both the Farmer and Pool Public Keys to use.**  
Utilize this when you want to select one key out of several in your keychain. 
To find your Chia Key Fingerprint use the following command: chia keys show

-t [tmp dir]: Define the temporary directory for plot creation. This is where Plotting Phase 1 (Forward Propagation) and Phase 2 (Backpropagation) both occur. The -t dir requires the largest working space: normally about 4 times the size of the final plot.

-2 [tmp dir 2]: Define a secondary temporary directory for plot creation. 
This is where Plotting Phase 3 (Compression) and Phase 4 (Checkpoints) occur. 
Depending on your OS, -2 might default to either -t or -d. 
Therefore, **if either -t or -d are running low on space, it's recommended to set -2 manually.** 
The -2 dir requires an equal amount of working space as the final size of the plot.

-d [final dir]: Define the final location for plot(s). Of course, -d should have enough free space as the final size of the plot. This directory is automatically added to your ~/.chia/VERSION/config/config.yaml file. You can use chia plots remove -d to remove a final directory from the configuration.

-r [number of threads]: 2 is usually optimal. Multithreading is only in phase 1 currently.

-u [number of buckets]: More buckets require less RAM but more random seeks to disk. 
With spinning disks you want less buckets and with NVMe more buckets. 
There is no significant benefit from using smaller buckets - just use 128.

-e [bitfield plotting]: 
Using the -e flag will disable the bitfield plotting algorithm, and revert back to the older b17 plotting style. 
Using the -e flag (bitfield disabled) lowers memory requirement, 
but also writes about 12% more data during creation of the plot. 
For now, SSD temp space will likely plot faster with -e (bitfield back propagation disabled) 
and for slower spinning disks, i.e SATA 5400/7200 rpm, not using -e (bitfield enabled) is a better option.

**Example**

Example below will create a k32 plot and use 4GB (note - not GiB) of memory.
基础命令， 使用4GB内存，建立32k的plot。
```chia plots create -k 32 -b 4000 -t /path/to/temporary/directory -d /path/to/final/directory```

Example 2 below will create a k34 plot and use 8GB of memory, 2 threads and 64 buckets
如果临时存储盘为SSD，推荐使用-e，如果是磁盘则不要使用该标记。
```chia plots create -k 34 -e -b 8000 -r 2 -u 64 -t /path/to/temporary/directory -d /path/to/final/directory```

Example 3 below will create five k32 plots one at a time using 4GB (note - not GiB) of memory.
最终要制作5张图。
```chia plots create -k 32 -b 4000 -t /path/to/temporary/directory -d /path/to/final/directory -n 5```

就我自己的案例来说， 我需要在其他机子上制作我的农田，则使用命令
```
chia plots create -k 34 -e -b 8000 -r 2 -f a2d3a036cc57c3f29b38fa6b021097d7504baaff8756fbe884ba2f4057f5991205a92c535fe96e35468b2e06c47f2d8e -p 836811020c1d625b0e15dab06f11404a0d30b09f9f83f702909c94a5ffc6f0fc5efc443763c0852430c93fa5789ebd9d -a -t /path/to/temporary/directory -d /path/to/final/directory
```
