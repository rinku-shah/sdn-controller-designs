#Copy Cpu Util
cp /home/vikas/icnp19/scripts/*.txt . 
scp mv@192.168.100.1:/home/mv/scripts/*.txt . 

#Copy stats for offload clone
cp /var/lib/lxc/offload_ran1/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran1/clone_bitwise_lg/stats.csv stats_1.csv
cp /var/lib/lxc/offload_ran2/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran2/clone_bitwise_lg/stats.csv stats_2.csv
cp /var/lib/lxc/offload_ran3/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran3/clone_bitwise_lg/stats.csv stats_3.csv
cp /var/lib/lxc/offload_ran4/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran4/clone_bitwise_lg/stats.csv stats_4.csv

#Change permissions
chmod 777 -R *
