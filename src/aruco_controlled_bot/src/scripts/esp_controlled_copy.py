import rospy
from aruco_controlled_bot.msg import MarkerPosition
import socket

# ESP32 IP address and port
ESP32_IP = '192.168.235.214'  # Replace with the IP address of your ESP32
ESP32_PORT = 80

class TeleopBot:
    def __init__(self):
        rospy.init_node('teleop_bot', anonymous=True)
        rospy.Subscriber('marker_position', MarkerPosition, self.position_callback)

    def position_callback(self, position_msg):
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            try:
                # Connect to the ESP32
                s.connect((ESP32_IP, ESP32_PORT))
                # Send control commands based on the marker position
                if position_msg.y < 200:
                    # Move forward
                    s.sendall(b"f")
                    rospy.loginfo("F")
                elif position_msg.y > 500:
                    # Move backward
                    s.sendall(b"b")
                    rospy.loginfo("b")
                

                elif position_msg.x < 350:
                    # Turn right
                    s.sendall(b"r")
                    rospy.loginfo("r")
                elif position_msg.x > 850:
                    # Turn left
                    s.sendall(b"l")
                    rospy.loginfo("l")
                else:
                    # Stop turning
                    s.sendall(b"st")
                    rospy.loginfo("st")
            except Exception as e:
                rospy.logerr("Error while sending control command: {}".format(str(e)))

if __name__ == '__main__':
    teleop_bot = TeleopBot()
    rospy.spin()
