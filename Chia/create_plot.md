# 几个重要文件所属的位置
WINDOWS 
- **chia.exe**  
~\AppData\Local\chia-blockchain\app-1.1.1\resources\app.asar.unpacked\daemon  
- **config.yaml**  
~\.chia\mainnet\config
- 


# 在其他计算机上制作自己的田
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

# 检查田信息  chia plots check -n [num checks] -l -g [substring]
```
~AppData\Local\chia-blockchain\app-1.1.1\resources\app.asar.unpacked\daemon> chia plots check  
2021-04-24T22:42:14.064  chia.plotting.check_plots        : INFO     Loading plots in config.yaml using plot_tools loading code

2021-04-24T22:42:14.126  chia.plotting.plot_tools         : INFO     Searching directories ['E:\\Chia\\plot', 'E:\\Chia\\plot_1']
2021-04-24T22:42:14.189  chia.plotting.plot_tools         : INFO     Found plot E:\Chia\plot\plot-k32-2021-04-24-05-46-459124321b8447a0a085c9ef85bbe0b62dedf8eb333ef829747b6af034e77ba4.plot of size 32
2021-04-24T22:42:14.285  chia.plotting.plot_tools         : INFO     Found plot E:\Chia\plot\plot-k32-2021-04-24-11-46-b828e0fb355ec48c02b079913e7cf89c4c19c07c9b29332a1d252c21a8bcf819.plot of size 32
2021-04-24T22:42:14.301  chia.plotting.plot_tools         : INFO     Found plot E:\Chia\plot_1\plot-k32-2021-04-24-05-48-52ffd34628f97d483fc066bbc437786ffb7a555d0c6bbde96a27d85ac4b5a824.plot of size 32
2021-04-24T22:42:14.316  chia.plotting.plot_tools         : INFO     Found plot E:\Chia\plot_1\plot-k32-2021-04-24-13-25-1910bbab8942bcd65882c1feb648fa3e21749f0fabdd51359fc86cc4e428c16b.plot of size 32
2021-04-24T22:42:14.332  chia.plotting.plot_tools         : INFO     Found plot E:\Chia\plot_1\plot-k32-2021-04-24-13-27-8563c542ea2f4c5f7904649321a9ca6b9863de5e7cc65c73928b66ef3e44db72.plot of size 32
2021-04-24T22:42:14.348  chia.plotting.plot_tools         : INFO     Loaded a total of 5 plots of size 0.4949795533775614 TiB, in 0.2211315631866455 seconds
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO     Starting to test each plot with 30 challenges each

2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO     Testing plot E:\Chia\plot\plot-k32-2021-04-24-05-46-459124321b8447a0a085c9ef85bbe0b62dedf8eb333ef829747b6af034e77ba4.plot k=32
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO        Pool public key: a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO        Farmer public key: adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
2021-04-24T22:42:14.348  chia.plotting.check_plots        : INFO        Local sk: <PrivateKey 31db0ad8bee5bbdcec42d25821f507f15bddee380f5f1c03ceead73caca50537>
2021-04-24T22:42:27.979  chia.plotting.check_plots        : INFO        Proofs 30 / 30, 1.0
2021-04-24T22:42:27.980  chia.plotting.check_plots        : INFO     Testing plot E:\Chia\plot\plot-k32-2021-04-24-11-46-b828e0fb355ec48c02b079913e7cf89c4c19c07c9b29332a1d252c21a8bcf819.plot k=32
2021-04-24T22:42:27.980  chia.plotting.check_plots        : INFO        Pool public key: a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
2021-04-24T22:42:27.986  chia.plotting.check_plots        : INFO        Farmer public key: adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
2021-04-24T22:42:27.986  chia.plotting.check_plots        : INFO        Local sk: <PrivateKey 2c3cad90c5e409d0d4315c814b86f0b072a074ea847b3ac141d2a76c08012c0c>
2021-04-24T22:42:38.651  chia.plotting.check_plots        : INFO        Proofs 24 / 30, 0.8
2021-04-24T22:42:38.651  chia.plotting.check_plots        : INFO     Testing plot E:\Chia\plot_1\plot-k32-2021-04-24-05-48-52ffd34628f97d483fc066bbc437786ffb7a555d0c6bbde96a27d85ac4b5a824.plot k=32
2021-04-24T22:42:38.667  chia.plotting.check_plots        : INFO        Pool public key: a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
2021-04-24T22:42:38.667  chia.plotting.check_plots        : INFO        Farmer public key: adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
2021-04-24T22:42:38.667  chia.plotting.check_plots        : INFO        Local sk: <PrivateKey 277e32c702ccfecac9e0a72e5c0c4542cfeb157d9932b1d905fcf5492f06f755>
2021-04-24T22:42:52.019  chia.plotting.check_plots        : INFO        Proofs 30 / 30, 1.0
2021-04-24T22:42:52.019  chia.plotting.check_plots        : INFO     Testing plot E:\Chia\plot_1\plot-k32-2021-04-24-13-25-1910bbab8942bcd65882c1feb648fa3e21749f0fabdd51359fc86cc4e428c16b.plot k=32
2021-04-24T22:42:52.019  chia.plotting.check_plots        : INFO        Pool public key: a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
2021-04-24T22:42:52.034  chia.plotting.check_plots        : INFO        Farmer public key: adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
2021-04-24T22:42:52.034  chia.plotting.check_plots        : INFO        Local sk: <PrivateKey 4ae898f59ca67b2d7903aa71777ffbfc2c760e80f73684a24b2936de81407025>
2021-04-24T22:43:00.542  chia.plotting.check_plots        : INFO        Proofs 19 / 30, 0.6333
2021-04-24T22:43:00.542  chia.plotting.check_plots        : INFO     Testing plot E:\Chia\plot_1\plot-k32-2021-04-24-13-27-8563c542ea2f4c5f7904649321a9ca6b9863de5e7cc65c73928b66ef3e44db72.plot k=32
2021-04-24T22:43:00.542  chia.plotting.check_plots        : INFO        Pool public key: a02a3c1af12cd5f34ce8dde6d0cb58e64e6d2d5ce8228e2aa9fdd18d1268a1d9bd47d5d2bceb828237d0643ea4904437
2021-04-24T22:43:00.542  chia.plotting.check_plots        : INFO        Farmer public key: adc081fa0e4cd8260687fdb3de0417b4568402f03110b50040d119401f9ea6178bae2fc77e373f4732faaa21dfa60aeb
2021-04-24T22:43:00.542  chia.plotting.check_plots        : INFO        Local sk: <PrivateKey 2b12db76087c81541788cdaa4ccd8922afe7577cb88c2348dc97c17097c004e1>
2021-04-24T22:43:14.375  chia.plotting.check_plots        : INFO        Proofs 31 / 30, 1.0333
2021-04-24T22:43:14.380  chia.plotting.check_plots        : INFO
2021-04-24T22:43:14.381  chia.plotting.check_plots        : INFO
2021-04-24T22:43:14.382  chia.plotting.check_plots        : INFO     Summary
2021-04-24T22:43:14.383  chia.plotting.check_plots        : INFO     Found 5 valid plots, total size 0.49498 TiB
2021-04-24T22:43:14.384  chia.plotting.check_plots        : INFO     5 plots of size 32
```  

**如果只想检查重复的田**  
``` chia plots check  -l -n 0 ```  

**想检查特定目录或者名字或者大小的田**  
```-g``` check only plots with directory or file name containing case-sensitive [substring].  
只检查大小类型为k33的田: ```chia plots check -g k33```  
只检查2020年10月30日创建的田：```chia plots check -g 2020-10-31```
