#sudo tc qdisc add dev enp7s0f1 root netem delay 0.5ms
#sudo tc qdisc del dev enp7s0f1 root netem

sudo ifup br0
sudo cp /home/vikas/resolv.conf /etc/

sudo brctl addbr br1
sudo brctl addbr br2
sudo brctl addbr br3
sudo brctl addbr br4
sudo brctl addbr br5
sudo brctl addbr br6
sudo brctl addbr br7
sudo brctl addbr br8
sudo brctl addbr br9
sudo brctl addbr br10
sudo brctl addbr br11
sudo brctl addbr br12
sudo brctl addbr br13
sudo brctl addbr br14
sudo brctl addbr br15
sudo brctl addbr br16
sudo brctl addbr br17
sudo brctl addbr br18
sudo brctl addbr br19
sudo brctl addbr br20
sudo brctl addbr br21

sudo ip link set br1 up
sudo ip link set br2 up
sudo ip link set br3 up
sudo ip link set br4 up
sudo ip link set br5 up
sudo ip link set br6 up
sudo ip link set br7 up
sudo ip link set br8 up
sudo ip link set br9 up
sudo ip link set br10 up
sudo ip link set br11 up
sudo ip link set br12 up
sudo ip link set br13 up
sudo ip link set br14 up
sudo ip link set br15 up
sudo ip link set br16 up
sudo ip link set br17 up
sudo ip link set br18 up
sudo ip link set br19 up
sudo ip link set br20 up
sudo ip link set br21 up

sudo ifconfig br1 192.168.1.10 netmask 255.255.255.0
# sudo route add default gw 10.126.41.250 br1

sudo ifconfig br2 192.168.2.10 netmask 255.255.255.0
# sudo route add default gw 10.125.41.250 br2

sudo ifconfig br3 192.168.3.10 netmask 255.255.255.0
# sudo route add default gw 10.127.41.250 br3

sudo ifconfig br4 192.168.4.10 netmask 255.255.255.0
# sudo route add default gw 10.128.41.250 br4

sudo ifconfig br5 192.168.5.10 netmask 255.255.255.0
# sudo route add default gw 10.124.41.250 br5

sudo ifconfig br6 192.168.6.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br7 192.168.7.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br8 192.168.8.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br9 192.168.9.10 netmask 255.255.255.0
# sudo route add default gw 10.126.41.250 br1

sudo ifconfig br10 192.168.10.10 netmask 255.255.255.0
# sudo route add default gw 10.125.41.250 br2

sudo ifconfig br11 192.168.11.10 netmask 255.255.255.0
# sudo route add default gw 10.126.41.250 br1

sudo ifconfig br12 192.168.12.10 netmask 255.255.255.0
# sudo route add default gw 10.125.41.250 br2

sudo ifconfig br13 192.168.13.10 netmask 255.255.255.0
# sudo route add default gw 10.127.41.250 br3

sudo ifconfig br14 192.168.14.10 netmask 255.255.255.0
# sudo route add default gw 10.128.41.250 br4

sudo ifconfig br15 192.168.15.10 netmask 255.255.255.0
# sudo route add default gw 10.124.41.250 br5

sudo ifconfig br16 192.168.16.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br17 192.168.17.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br18 192.168.18.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br19 192.168.19.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br20 192.168.20.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6

sudo ifconfig br21 192.168.21.10 netmask 255.255.255.0
# sudo route add default gw 10.123.41.250 br6
#sudo route add -net 192.168.200.0 netmask 255.255.255.0 dev br0

#sudo gedit /var/lib/lxc/ue/config
#lxc.network.type = veth
#lxc.network.link = br0
#lxc.network.flags = up
#lxc.network.hwaddr = 00:16:3e:be:87:65

#To delete ip tables rule
#sudo route del -net 0.0.0.0 gw 10.0.3.1 eth0

