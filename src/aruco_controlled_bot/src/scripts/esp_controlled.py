
"""
import rospy
from aruco_controlled_bot.msg import MarkerPosition
import paho.mqtt.client as mqtt

# MQTT Broker configuration
MQTT_BROKER = '192.168.235.244'  # Replace with the IP address of your MQTT broker
MQTT_PORT = 1883  # Default MQTT port
MQTT_TOPIC = 'esp32/control'  # MQTT topic to publish control commands
MQTT_TIMEOUT = 10  # Timeout value in seconds

class TeleopBot:
    def __init__(self):
        rospy.init_node('teleop_bot', anonymous=True)
        rospy.Subscriber('marker_position', MarkerPosition, self.position_callback)
        self.prev_command = b's'  # Initialize previous command as stop
        self.client = mqtt.Client()
        self.client.connect(MQTT_BROKER, MQTT_PORT, MQTT_TIMEOUT)

    def position_callback(self, position_msg):
        try:
            # Send control commands based on the marker position
            if position_msg.y < 200:
                # Move forward
                new_command = b'f'
                rospy.loginfo("f")
            elif position_msg.y > 500:
                # Move backward
                new_command = b'b'
                rospy.loginfo("b")
            elif position_msg.x < 350:
                # Turn right
                new_command = b'r'
                rospy.loginfo("r")
            elif position_msg.x > 850:
                # Turn left
                new_command = b'l'
                rospy.loginfo("l")
            else:
                # Stop
                new_command = b's'
                rospy.loginfo("s")

            # Send the new command only if it's different from the previous command
            if new_command != self.prev_command:
                self.client.publish(MQTT_TOPIC, new_command)
                self.prev_command = new_command
                
                # Log the sent command
                rospy.loginfo("Sent command: {}".format(new_command))

        except Exception as e:
            rospy.logerr("Error while sending control command: {}".format(str(e)))

if __name__ == '__main__':
    teleop_bot = TeleopBot()
    rospy.spin()



"""

import rospy
from aruco_controlled_bot.msg import MarkerPosition
import socket

# ESP32 IP address and port
ESP32_IP = '192.168.235.214'  # Replace with the IP address of your ESP32
ESP32_PORT = 80
SOCKET_TIMEOUT = 10  # Timeout value in seconds

class TeleopBot:
    def __init__(self):
        rospy.init_node('teleop_bot', anonymous=True)
        rospy.Subscriber('marker_position', MarkerPosition, self.position_callback)
        self.prev_command = b's'  # Initialize previous command as stop

    def position_callback(self, position_msg):
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            try:
                #s.settimeout(SOCKET_TIMEOUT)
                # Connect to the ESP32
                #rospy.loginfo("trying to connect  to esp32")
                #s.connect((ESP32_IP, ESP32_PORT))
                #rospy.loginfo("connected to esp32")
                # Send control commands based on the marker position
                if position_msg.y < 200:
                    # Move forward
                    new_command = b'f'
                    rospy.loginfo("f")
                elif position_msg.y > 500:
                    # Move backward
                    new_command = b'b'
                    rospy.loginfo("b")
               

                elif position_msg.x < 350:
                    # Turn right
                    new_command = b'r'
                    rospy.loginfo("r")
                elif position_msg.x > 850:
                    # Turn left
                    new_command = b'l'
                    rospy.loginfo("l")

                else:
                    # Stop
                    new_command = b's'
                    rospy.loginfo("s")

                # Send the new command only if it's different from the previous command
                if new_command != self.prev_command:
                    s.connect((ESP32_IP, ESP32_PORT))
                    rospy.loginfo("connected to esp32")
                    s.sendall(new_command)
                    self.prev_command = new_command
                    
                    # Log the sent command
                    rospy.loginfo("Sent command: {}".format(new_command))
                    

            except Exception as e:
                rospy.logerr("Error while sending control command: {}".format(str(e)))

if __name__ == '__main__':
    teleop_bot = TeleopBot()
    rospy.spin()
