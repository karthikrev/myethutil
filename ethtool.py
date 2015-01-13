import extension

nic = "eth1"
speed = extension.getspeed(nic)
print "speed of %s is %s" % (nic, speed)
