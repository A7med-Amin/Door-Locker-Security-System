# Door-Locker-Security-System
Developing a system to unlock a door using a password.  Used drivers: GPIO, Keypad, LCD, Timer, UART, I2C, EEPROM, Buzzer and DC-Motor. Microcontroller: ATmega32.
used tools: Eclipse / proteus
system flow: 
Step1 – Create a System Password
The LCD should display “Please Enter Password”
Enter a password consists of 5 numbers, Display * in the screen for each number.
Press enter button after entering pass where enter button is key 13
Ask the user to renter the same password for confirmation by display this message “Please re-enter the same Pass” and read confiramtion password
If the two passwords are matched then the system has a password now and save it inside the EEPORM and go to Step 2 
if not repeat step1
when matched the password is saved in external EEPTOM 
Step2 - Main Options
Open Door: +
Change Password: -
Step3 - Open Door +
The LCD should display “Please Enter Password” 
Enter the password then press enter button
if two passwords are matched:
• rotates motor for 15-seconds CW and display a message on the screen “Door is Unlocking” 
• hold the motor for 3-seconds. 
• rotates motor for 15-seconds A-CW and display a message on the screen “Door is Locking”
Step 4 - Change Password -
The LCD should display “Please Enter Password”
if two passwords are matched:
• Repeat Step 1.
Step 5
if the two passwords are unmatched at step 3 (+ : Open Door) or step 4 (- : Change Password)
rapeat reading new password if not valid for 3 times only after that:
• Activate Buzzer for 1-minute. 
• Display error message on LCD for 1 minute.
• System is locked no inputs from Keypad will be accepted during this time period.
• Go to Step 2 the main options again.
