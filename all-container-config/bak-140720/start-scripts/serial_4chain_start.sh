#sudo lxc-start -n onos-controller -d
sudo lxc-start -n ran1 -d
sudo lxc-start -n ran2 -d
sudo lxc-start -n ran3 -d
sudo lxc-start -n ran4 -d
sudo lxc-start -n offload_dgw1 -d
sudo lxc-start -n offload_dgw2 -d
sudo lxc-start -n offload_dgw3 -d
sudo lxc-start -n offload_dgw4 -d
sudo lxc-start -n series_sgw1_1 -d
sudo lxc-start -n series_sgw1_2 -d
sudo lxc-start -n series_sgw2_1 -d
sudo lxc-start -n series_sgw2_2 -d
sudo lxc-start -n series_sgw3_1 -d
sudo lxc-start -n series_sgw3_2 -d
sudo lxc-start -n series_sgw4_1 -d
sudo lxc-start -n series_sgw4_2 -d
sudo lxc-start -n scale_pgw_series -d
sudo lxc-start -n sink -d
sleep 3
sudo lxc-ls --fancy

