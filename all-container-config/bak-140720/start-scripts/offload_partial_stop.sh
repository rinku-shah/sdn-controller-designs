sudo lxc-stop -n offload_sgw1 
sudo lxc-stop -n offload_sgw2 
sudo lxc-stop -n offload_sgw3  
sudo lxc-stop -n offload_sgw4 
sudo lxc-stop -n offload_sgw5  
sudo lxc-stop -n offload_sgw6  

sudo lxc-stop -n offload_dgw1  
sudo lxc-stop -n offload_dgw2  
sudo lxc-stop -n offload_dgw3  
sudo lxc-stop -n offload_dgw4  
sudo lxc-stop -n offload_dgw5  
sudo lxc-stop -n offload_dgw6  

sleep 5
sudo lxc-ls --fancy
