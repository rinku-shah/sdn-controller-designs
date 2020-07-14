#!/bin/bash

# Usage: ./terminals.sh
# Do not run as superuser

# Start the containers

#sudo lxc-start -n onos-controller -d
sudo lxc-start -n scale_ran1 -d
sudo lxc-start -n dgw1 -d
sudo lxc-start -n scale_sgw1_1 -d
sudo lxc-start -n scale_pgw -d
sudo lxc-start -n sink -d
sudo lxc-ls --fancy
