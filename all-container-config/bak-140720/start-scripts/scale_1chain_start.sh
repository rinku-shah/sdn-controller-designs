#sudo lxc-start -n onos-controller -d
sudo lxc-start -n scale_ran1 -d
sudo lxc-start -n scale_dgw1 -d
sudo lxc-start -n scale_sgw1_1 -d
sudo lxc-start -n scale_sgw1_2 -d
sudo lxc-start -n scale_pgw -d
sudo lxc-start -n sink -d
sleep 3
sudo lxc-ls --fancy
