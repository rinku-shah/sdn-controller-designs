#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

#sudo lxc-stop -n onos-controller 
sudo lxc-stop -n offload_ran1 
sudo lxc-stop -n offload_ran2 
sudo lxc-stop -n offload_ran3 
sudo lxc-stop -n offload_ran4 
sudo lxc-stop -n dgw1 
sudo lxc-stop -n dgw2 
sudo lxc-stop -n dgw3 
sudo lxc-stop -n dgw4 
sudo lxc-stop -n sgw1 
sudo lxc-stop -n sgw2 
sudo lxc-stop -n sgw3 
sudo lxc-stop -n sgw4 
sudo lxc-stop -n pgw-horiz
sudo lxc-stop -n sink 
sudo lxc-ls --fancy
