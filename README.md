# PinkHex

six_stepper.ino 
- this program contains the control loop for running 6 stepper motors
- it reads user inputs from the current SerialPort and sets appropriate work mode
- list of available commands and modes is found below
- pin locations and functions are documented in the source code

keyboard2serial.py
- this program should be run in parallel while aruduino is connected and running
- it allows user to input commands from the keyboard which are sent to arduina via current serial port
- if there are no available ports found (tty/ACM0 or tty/ACM1) program terminates with an error message
Commands: 
  - i - forward
  - k - stop
  - , - back
  - w - stand up
  - s - sit down
  
  
Authors: 
Ana Batinovic,
Luka Mikic,
Lovro Markovic
