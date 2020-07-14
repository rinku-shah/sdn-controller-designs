#sudo lxc-start -n onos-controller -d
sudo lxc-stop -n ran1 
sudo lxc-stop -n ran2 
sudo lxc-stop -n ran3 
sudo lxc-stop -n ran4 
sudo lxc-stop -n offload_dgw1 
sudo lxc-stop -n offload_dgw2 
sudo lxc-stop -n offload_dgw3 
sudo lxc-stop -n offload_dgw4 
sudo lxc-stop -n series_sgw1_1 
sudo lxc-stop -n series_sgw1_2 
sudo lxc-stop -n series_sgw2_1 
sudo lxc-stop -n series_sgw2_2 
sudo lxc-stop -n series_sgw3_1 
sudo lxc-stop -n series_sgw3_2 
sudo lxc-stop -n series_sgw4_1 
sudo lxc-stop -n series_sgw4_2 
sudo lxc-stop -n scale_pgw_series
sudo lxc-stop -n sink 
sleep 3
sudo lxc-ls --fancy
