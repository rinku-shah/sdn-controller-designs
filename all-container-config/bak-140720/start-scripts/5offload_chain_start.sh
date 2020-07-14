#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-start -n onos-controller -d
sudo lxc-start -n ran1 -d
sudo lxc-start -n ran2 -d
sudo lxc-start -n ran3 -d
sudo lxc-start -n ran4 -d
sudo lxc-start -n offload_dgw1 -d
sudo lxc-start -n offload_dgw2 -d
sudo lxc-start -n offload_dgw3 -d
sudo lxc-start -n offload_dgw4 -d
sudo lxc-start -n offload_sgw1 -d
sudo lxc-start -n offload_sgw2 -d
sudo lxc-start -n offload_sgw3 -d
sudo lxc-start -n offload_sgw4 -d
sudo lxc-start -n pgw -d
sudo lxc-start -n sink -d
sudo lxc-ls --fancy
