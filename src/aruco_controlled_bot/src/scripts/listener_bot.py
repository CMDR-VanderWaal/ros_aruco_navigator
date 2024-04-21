#!/usr/bin/env python

import rospy
from aruco_controlled_bot.msg import MarkerPosition

def callback(data):
    rospy.loginfo("Received marker position: roll={}, pitch={}, yaw={}".format(data.roll, data.pitch, data.yaw))

def listener():
    rospy.init_node('listener_bot', anonymous=True)
    rospy.Subscriber('marker_position', MarkerPosition, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()
