sudo lxc-destroy -n offload_ran1
sudo lxc-destroy -n offload_ran3
sudo lxc-destroy -n offload_ran4

sudo lxc-clone -o offload_ran2 -n offload_ran1
sudo lxc-clone -o offload_ran2 -n offload_ran3
sudo lxc-clone -o offload_ran2 -n offload_ran4
