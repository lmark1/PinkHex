import curses
import serial

arduino_port = None

def detect_keypress(win):
    """
        Detects keypress and send it to arduino.
    """

    win.nodelay(True)
    key=""
    win.clear()                
    win.addstr("Detected key:")

           
    while 1:          
        try:                 
            key = win.getkey()         
            win.clear()                
            win.addstr("Detect key: ")
            win.addstr(str(key)) 
           
            # Exit program with "q"
            if key == "q":
                break           

            if (key == "k" or key == "i" or key == "," or 
                key == "w" or key == "s"):

                # Send keypress to arduino serial
                arduino_port.write(key)


        except Exception as e:
            # No input   
            pass         

port_opened = False
# Try opening arduino serial1
try:
    arduino_port = serial.Serial('/dev/ttyACM0', baudrate=115200, timeout=.1)
    port_opened = True
except:
    print("Unable to open port on ACM0, restart arduino or check port name.")

# Try opening on another serial2
if (not port_opened):
    try:
        arduino_port = serial.Serial('/dev/ttyACM1', baudrate=115200, timeout=.1)
        port_opened = True
    except:
        print("Unable to open port on ACM1, restart arduino or check port name.")
    
if (not port_opened):
    print("Unable to open any of the ports, exiting...")
    quit()

curses.wrapper(detect_keypress)