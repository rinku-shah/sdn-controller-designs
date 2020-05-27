#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

#sudo lxc-start -n onos-controller -d
sudo lxc-start -n offload_ran1 -d
sudo lxc-start -n offload_ran2 -d
sudo lxc-start -n offload_ran3 -d
sudo lxc-start -n offload_ran4 -d
sudo lxc-start -n dgw1 -d
sudo lxc-start -n dgw2 -d
sudo lxc-start -n dgw3 -d
sudo lxc-start -n dgw4 -d
sudo lxc-start -n sgw1 -d
sudo lxc-start -n sgw2 -d
sudo lxc-start -n sgw3 -d
sudo lxc-start -n sgw4 -d
#sudo lxc-start -n pgw-horiz -d #with 4 masters
sudo lxc-start -n pgw -d
#sudo lxc-start -n sink -d
sudo lxc-ls --fancy
