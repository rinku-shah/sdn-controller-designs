#!/bin/bash

# Stop the containers
#sudo lxc-stop -n onos-controller 
sudo lxc-stop -n scale_ran1
sudo lxc-stop -n dgw1
sudo lxc-stop -n scale_sgw1_1
sudo lxc-stop -n scale_pgw
sudo lxc-stop -n sink
