#!/bin/bash

# Stop the containers
sudo lxc-stop -n onos-controller 
sudo lxc-stop -n ran1
sudo lxc-stop -n ran2
sudo lxc-stop -n ran3
sudo lxc-stop -n ran4
sudo lxc-stop -n dgw1
sudo lxc-stop -n dgw2
sudo lxc-stop -n dgw3
sudo lxc-stop -n dgw4
sudo lxc-stop -n sgw1
sudo lxc-stop -n sgw2
sudo lxc-stop -n sgw3
sudo lxc-stop -n sgw4
sudo lxc-stop -n pgw
sudo lxc-stop -n sink
