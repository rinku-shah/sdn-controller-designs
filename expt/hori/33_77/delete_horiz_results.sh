
#Copy Cpu Util
rm /home/vikas/icnp19/scripts/*.txt 
sshpass -p qwer1234 ssh mv@192.168.100.1 -t 'rm -f /home/mv/scripts/*_util.txt'

#Delete stats for offload clone

rm /var/lib/lxc/offload_ran1/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran1/clone_bitwise_lg/stats.csv

rm /var/lib/lxc/offload_ran2/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran2/clone_bitwise_lg/stats.csv

rm /var/lib/lxc/offload_ran3/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran3/clone_bitwise_lg/stats.csv

rm /var/lib/lxc/offload_ran4/rootfs/home/ubuntu/turboepc/turboepc-software/designs/traditional/traditional_byte_based_root/lg/ran4/clone_bitwise_lg/stats.csv

#Change permissions
#chmod 777 -R *
