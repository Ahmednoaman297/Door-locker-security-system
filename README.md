# Door-locker-security-system
Atmega32
# Door Locker Security System

This project implements a Door Locker Security System using two ATmega32 Microcontrollers operating at 8MHz. The system is designed and implemented based on the layered architecture model:

- **MC1 (HMI_ECU)**: Human Machine Interface with a 2x16 LCD and 4x4 keypad.
- **MC2 (Control_ECU)**: Controls the EEPROM, Buzzer, and DC Motor.

## System Components

### HMI_ECU (MC1)
- **LCD**: 2x16 LCD for displaying messages.
- **Keypad**: 4x4 keypad for user input.
- **Microcontroller**: ATmega32.

### Control_ECU (MC2)
- **EEPROM**: External EEPROM for storing the password.
- **Buzzer**: For alarm activation.
- **DC Motor**: For door locking and unlocking.
- **Microcontroller**: ATmega32.

## System Sequence

### Step 1: Create a System Password
1. **Prompt User**: LCD displays “Please Enter Password”.
2. **Enter Password**: User enters a 5-digit password, displayed as `*` on the screen.
3. **Confirm Password**: LCD prompts “Please re-enter the same Pass”.
4. **Send Passwords to Control_ECU**: HMI_ECU sends both entered passwords via UART.
5. **Password Validation**:
   - If passwords match, save to EEPROM and proceed to Step 2.
   - If passwords don't match, repeat Step 1.

### Step 2: Main Options
The LCD displays the main system options.

### Step 3: Open Door
1. **Prompt User**: LCD displays “Please Enter Password”.
2. **Enter Password**: User enters the password and presses enter.
3. **Password Validation**:
   - If matched:
     - Rotate motor CW for 15 seconds (unlocking) and display “Door is Unlocking”.
     - Hold motor for 3 seconds.
     - Rotate motor ACW for 15 seconds (locking) and display “Door is Locking”.

### Step 4: Change Password
1. **Prompt User**: LCD displays “Please Enter Password”.
2. **Enter Password**: User enters the password and presses enter.
3. **Password Validation**:
   - If matched, repeat Step 1.

### Step 5: Password Mismatch Handling
1. **Retry Password**: If password mismatched in Step 3 or Step 4, prompt user to re-enter password.
2. **Third Attempt**:
   - If mismatched three consecutive times:
     - Activate Buzzer for 1 minute.
     - Display error message on LCD for 1 minute.
     - Lock system inputs from Keypad for this duration.
     - Return to main options (Step 2).
