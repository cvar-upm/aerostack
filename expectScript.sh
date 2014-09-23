#!/usr/bin/expect -b
#Tells interpreter where the expect program is located.  This may need adjusting according to
#your specific environment.  Type ' which expect ' (without quotes) at a command prompt
#to find where it is located on your system and adjust the following line accordingly.
#
#
set gitSubmodule [lindex $argv 0]; # Grab the second command line parameter
set bitbucketUsername [lindex $argv 1]; # Grab the second command line parameter
set bitbucketPassword [lindex $argv 2]; # Grab the third command line parameter


#Use the built in telnet program to connect to an IP and port number
spawn git submodule update $gitSubmodule
#
#The first thing we should see is a User Name prompt
#expect "login as:"
#
#Send a valid username to the device
#send "admin"
#
#The next thing we should see is a Password prompt
expect "Username for 'https://bitbucket.org': "
#
#Send a vaild password to the device
send "$bitbucketUsername\n"
#
#The next thing we should see is a Password prompt
expect "Password for 'https://$bitbucketUsername@bitbucket.org': "
#
#Send a vaild password to the device
send "$bitbucketPassword\n"
# 
#The interact command is part of the expect script, which tells the script to hand off control to the user.
#This will allow you to continue to stay in the device for issuing future commands, instead of just closing
#the session after finishing running all the commands.`enter code here`
interact
