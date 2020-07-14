#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-stop -n onos-controller 
sudo lxc-stop -n ran1 
sudo lxc-stop -n offload_dgw1 
sudo lxc-stop -n offload_sgw1 
sudo lxc-stop -n pgw 
sudo lxc-stop -n sink 
sudo lxc-ls --fancy
