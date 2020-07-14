#!/bin/bash

# Stop the containers
#sudo lxc-stop -n root_May

sudo lxc-stop -n onos-controller 
sudo lxc-stop -n ran1
sudo lxc-stop -n ran2
#sudo lxc-stop -n ran_3
#sudo lxc-stop -n ran_4
sudo lxc-stop -n dgw1
sudo lxc-stop -n dgw2
#sudo lxc-stop -n dgw_3
#sudo lxc-stop -n dgw_4
sudo lxc-stop -n sgw1
sudo lxc-stop -n sgw2
#sudo lxc-stop -n sgw_3
#sudo lxc-stop -n sgw_4
sudo lxc-stop -n pgw
sudo lxc-stop -n sink
