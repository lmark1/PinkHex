import curses
import serial

def detect_keypress(win):
    """
        Detects keypress and send it to arduino.
    """

    win.nodelay(True)
    key=""
    win.clear()                
    win.addstr("Detected key:")

    # Try opening arduino port
    try:
        arduino_port = serial.Serial('/dev/ttyACM0', baudrate=115200, timeout=.1)
    except:
        print("Unable to open port, restart arduino or check port name.")
        return

    while 1:          
        try:                 
            key = win.getkey()         
            win.clear()                
            win.addstr("Detect key: ")
            win.addstr(str(key)) 
           
            # Exit program with "q"
            if key == "q":
                break           

            # Send keypress to arduino serial
            arduino_port.write(key)
        except Exception as e:
            # No input   
            pass         

# Start curses GUI
curses.wrapper(detect_keypress)