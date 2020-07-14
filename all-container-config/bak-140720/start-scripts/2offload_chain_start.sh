#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

sudo lxc-start -n onos-controller -d
sudo lxc-start -n ran1 -d
sudo lxc-start -n offload_dgw1 -d
sudo lxc-start -n offload_sgw1 -d
sudo lxc-start -n pgw -d
sudo lxc-start -n sink -d
sudo lxc-ls --fancy
