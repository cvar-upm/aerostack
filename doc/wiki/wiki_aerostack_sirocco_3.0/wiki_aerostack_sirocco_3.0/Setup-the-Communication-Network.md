
To setup the communication network, please read before the related [ROS tutorial](http://wiki.ros.org/ROS/NetworkSetup).

> NOTE: There is no need of a network setup when using an ARDrone as it can be connected directly to the groundstation using WIFI.

Then, follow these steps.

Configure a LAN network connection to communicate ground stations with the rest using ROS. The following image shows one of the used configurations: 

<p align="center">[[Files/ROSNetworkConfig.png]]</p>

Edit the hosts file, all the computers in the network have to be included in it. The IPs have to be the same that is specified in the configuration of each computer's ROS_NETWORK configuration. To edit the hosts file, run: 

    $ sudo gedit /etc/hosts

An example of the content of this file is the following: 

```
127.0.0.1	localhost
127.0.1.1	jespestana-XPS

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters

# ROS_NETWORK, etc.
192.168.1.1	ardrone
192.168.0.10	CVG-JL-Toshiba
192.168.0.10	ROS_10
192.168.0.11	ROS_11
192.168.0.12	carrio-GT70
192.168.0.12	ROS_12
192.168.0.13	SATELLITE-P850
192.168.0.13	ROS_13
192.168.0.20	joselu-Aspire-E1-571
192.168.0.20	ROS_20
192.168.0.21	joselu-Aspire-E1-571-01
192.168.0.21	ROS_21
192.168.0.30	joselu-Q330
192.168.0.30	ROS_30
192.168.0.40	CVG-Desktop01
192.168.0.40	ROS_40
192.168.0.41	CVG-Desktop02
192.168.0.41	ROS_41
```

Finally, restart your network for the configuration changes to take place.