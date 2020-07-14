#sudo lxc-start -n onos-controller -d
sudo lxc-start -n ran1 -d
#sudo lxc-start -n ran2 -d
#sudo lxc-start -n ran3 -d
#sudo lxc-start -n ran4 -d
sudo lxc-start -n scale_dgw1 -d
#sudo lxc-start -n scale_dgw2 -d
#sudo lxc-start -n scale_dgw3 -d
#sudo lxc-start -n scale_dgw4 -d
sudo lxc-start -n scale_sgw1_1 -d
sudo lxc-start -n scale_sgw1_2 -d
sudo lxc-start -n scale_sgw2_1 -d
#sudo lxc-start -n scale_sgw2_2 -d
#sudo lxc-start -n scale_sgw3_1 -d
#sudo lxc-start -n scale_sgw3_2 -d
#sudo lxc-start -n scale_sgw4_1 -d
#sudo lxc-start -n scale_sgw4_2 -d
sudo lxc-start -n scale_pgw -d
sudo lxc-start -n sink -d
sleep 3
sudo lxc-ls --fancy
