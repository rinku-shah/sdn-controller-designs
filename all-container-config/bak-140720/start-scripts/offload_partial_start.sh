sudo lxc-start -n offload_sgw1 -d 
sudo lxc-start -n offload_sgw2 -d 
sudo lxc-start -n offload_sgw3 -d 
sudo lxc-start -n offload_sgw4 -d 
sudo lxc-start -n offload_sgw5 -d 
sudo lxc-start -n offload_sgw6 -d 

sudo lxc-start -n offload_dgw1 -d 
sudo lxc-start -n offload_dgw2 -d 
sudo lxc-start -n offload_dgw3 -d 
sudo lxc-start -n offload_dgw4 -d 
sudo lxc-start -n offload_dgw5 -d 
sudo lxc-start -n offload_dgw6 -d 

sleep 5
sudo lxc-ls --fancy
