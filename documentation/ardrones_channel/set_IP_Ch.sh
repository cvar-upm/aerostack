DRONE_IP=$1
DRONE_CHANNEL=$2
echo "Setting IP to $DRONE_IP and channel to $DRONE_CHANNEL...Please reconnect."
SSID=`grep ssid_single_player /data/config.ini | awk -F "=" '{print $2}'`
ifconfig ath0 down
iwconfig ath0 mode master essid $SSID channel $DRONE_CHANNEL
iwconfig ath0 commit
ifconfig ath0 $DRONE_IP netmask 255.255.255.0 up

