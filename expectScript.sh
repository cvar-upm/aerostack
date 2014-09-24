#!/usr/bin/expect -b
#Tells interpreter where the expect program is located.  This may need adjusting according to
#your specific environment.  Type ' which expect ' (without quotes) at a command prompt
#to find where it is located on your system and adjust the following line accordingly.
#
#
set gitSubmodule [lindex $argv 0]; # Grab the second command line parameter
set bitbucketUsername [lindex $argv 1]; # Grab the second command line parameter
set bitbucketPassword [lindex $argv 2]; # Grab the third command line parameter

#Do the command
spawn git submodule update $gitSubmodule
#Wait for a response
expect {
"Username for 'https://bitbucket.org': "
	{
	send "$bitbucketUsername\n"
	expect "Password for 'https://$bitbucketUsername@bitbucket.org': "
	send "$bitbucketPassword\n"
	}
""
}
# 
#The interact command is part of the expect script, which tells the script to hand off control to the user.
#This will allow you to continue to stay in the device for issuing future commands, instead of just closing
#the session after finishing running all the commands.`enter code here`
interact
