sudo lxc-stop -n sgw1 
sudo lxc-stop -n sgw2 
sudo lxc-stop -n sgw3  
sudo lxc-stop -n sgw4 
sudo lxc-stop -n sgw5  
sudo lxc-stop -n sgw6  

sudo lxc-stop -n dgw1  
sudo lxc-stop -n dgw2  
sudo lxc-stop -n dgw3  
sudo lxc-stop -n dgw4  
sudo lxc-stop -n dgw5  
sudo lxc-stop -n dgw6  

sleep 5
sudo lxc-ls --fancy
