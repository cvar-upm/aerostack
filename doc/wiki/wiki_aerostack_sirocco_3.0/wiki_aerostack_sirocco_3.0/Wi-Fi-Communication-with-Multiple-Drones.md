This section describes how to proceed to establish an adequate communication using Wi-Fi when there are multiple drones. There are two alternative options:
- One to one (each drone to one computer)
- Many to one (several drones to one computer)

### One to one
In this case, you must have the same (or more) number of computers as drones. Each computer connects to a drone's Wi-Fi hotspot. Also, you must have a way of connecting computers to each other, for example a switch or a router. Keep in mind that there are two different subnets, one for the connection to the drone and another for the connection among computers.

After the computers are connected, you must edit the /etc/hosts file to add each computers hostname and their respective IPs.

**NOTE:** To avoid interferences make sure that the drones' hotspots are in different Wi-Fi channels. It also helps if there aren't too many other hotspots in those channels. To change a drone's channel you can use the following script:
```bash
SSID=$(grep ssid_single_player /data/config.ini | awk -F "=" '{print $2}')
ifconfig ath0 down
iwconfig ath0 mode master essid $SSID channel $2
iwconfig ath0 commit
ifconfig ath0 $1 netmask 255.255.255.0 up
```
To run this script login to the drone via telnet, create the script and execute it.
```bash
telnet 192.168.1.1
vi bin/set_IP_ch.sh #Copy the script and close vi
chmod +x bin/set_IP_ch.sh
set_IP_ch.sh 192.168.1.1 <CHANNEL>
```
**NOTE:** Since the drones are MAC-locked by default, when connecting a new computer to a drone, you should press the reset button on the drone to erase the previous computer's MAC address. The button is located under the battery, and you will need a paper clip or similar to press it.

### Many to one
In this case, you should use a router or a computer with a wifi hostpot to which the drones will connect to. To do this, you have to edit the drone's configuration to connect to your router. For detailed instructions see: [Multiple AR Drones](https://github.com/AutonomyLab/ardrone_autonomy/wiki/Multiple-AR-Drones)

#### 1. Edit the drone's pairing setup
First connect to the drone's hotspot, and login via telnet:
```bash
telnet 192.168.1.1
```
  Now edit the following script:
```bash
vi bin/pairing_setup.sh
```
  Look for this line and comment it:
```bash
iptables -A INPUT -m mac --mac-source $MAC_ADDR -j ACCEPT
```
  Then change
```bash
iptables -P INPUT DROP
```
into
```bash
iptables -P INPUT ACCEPT
```

#### 2. Add and execute the wifi setup script
Create the following file
```bash
vi bin/drone_wifi_config.sh
```
Add these lines
```bash
killall udhcpd
ifconfig ath0 down
iwconfig ath0 mode managed essid <ESSID>
iwconfig ath0 commit
ifconfig ath0 <IP_ADDRESS> netmask <NETMASK> up
```
Now make the script executable
```bash
chmod +x bin/drone_wifi_config.sh
```
Finally, exit your telnet session and execute the following command in your computer
```bash
echo drone_wifi_setup.sh | telnet 192.168.1.1
```
Your drone should now be connected to your router

**NOTE**: To insert text in vi, press 'i' before writing some text. To save and exit the file in vi, introduce the following sequence ```ESC shift+z shift+z```

#### 3. Edit the launchers
Edit the file $AEROSTACK_STACK/launchers/ardrone_indoors.launch and add ```args="-ip $(arg drone_ip)"``` to the first ```<node>``` tag.
Now look for the ArDrone Autonomy section of your launcher and add the following parameter: ```drone_ip:=$DRONE_IP```.

##### Ultrasound frequency 
In order to avoid the drones repelling each other when they are in proximity, the following parameter should be modified in the _ardrone\_indoors.launch_ file located in _launchers/ardrone\_launch_
```xml
<param name="ultrasound_freq" value="8" />
```
This parameter can be set to either 7 or 8. Drones with this parameter set to different values won't repel each other.