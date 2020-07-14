#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-start -n onos-controller -d
sudo lxc-start -n ran1 -d
sudo lxc-start -n ran2 -d
#sudo lxc-start -n ran_3 -d
#sudo lxc-start -n ran_4 -d
sudo lxc-start -n dgw1 -d
sudo lxc-start -n dgw2 -d
#sudo lxc-start -n dgw_3 -d
#sudo lxc-start -n dgw_4 -d
sudo lxc-start -n sgw1 -d
sudo lxc-start -n sgw2 -d
#sudo lxc-start -n sgw_3 -d
#sudo lxc-start -n sgw_4 -d
sudo lxc-start -n pgw -d
sudo lxc-start -n sink -d
sudo lxc-ls --fancy
