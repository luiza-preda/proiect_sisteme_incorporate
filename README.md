# Final project for Embedded Systems Course at University of Craiova, Faculty of Automation, Computers and Electronics, department of Automation and Applied Informatics 

This repository is the final project and is part of the requirements for completing the Embedded System Course. Part of these features are forked form the original repository made by our professor, which is found at: [mamuleanu/embedded-systems-course-atmega328p](https://github.com/mamuleanu/embedded-systems-course-atmega328p)

[![Run Tests](https://github.com/mamuleanu/embedded-systems-course-atmega328p/actions/workflows/tests.yml/badge.svg)](https://github.com/mamuleanu/embedded-systems-course-atmega328p/actions/workflows/tests.yml)


## Features

- **No Arduino Libraries**: Direct register manipulation for maximum control and efficiency.
- **Drivers:**: Modular, documented, and reusable.
    - **GPIO**: Initialization, Write, Read, Toggle.
    - **Interrupts**: External Interrupts (INT0, INT1) with callback support.
    - **Timer**: 1ms System Tick (`Millis()`) using Timer0 CTC mode.
    - **EEPROM**: Read, Write, Update (lifespan-aware).
    - **ADC**: Blocking 10-bit Analog-to-Digital conversion.
    - **PWM**: High-level wrapper for Timer1 (16-bit) and Timer2 (8-bit) PWM generation.
    - **USART**: Asynchronous operation using polling and dinamic frame format.
    - **I2C** : Start, Write, Stop for Master-Slave operations.
    - **LCD** : 4-bit mode, 2 lines.
- **Board Support Package (BSP)**: Pin mappings for **Arduino Nano** and **Uno**.
- **Robust Build System**: `Makefile` for compilation, flashing, and testing.
- **Host-Based Unit Testing**: Run unit tests on your computer without hardware using register mocking.
- **Code Coverage**: Generate HTML reports (`lcov`) to verify test coverage.

## Functionality of the Project:
-	Simulating the climate system in an automobile by controlling the speed of a fan for cooling the temperature using a joystick and rising it by using levels on a single digit 7-segement display and a potentiometer
-	The temperature inside, that is physically induced by a potentiometer for better results, is influenced by the speed of the fan, the level of heat and also the temperature outside
-	Displaying the simulated temperature from the inside of the car on a 16x2 LCD using an I2C module
-	Implementing a graphical interface using Python (source code for this is not included entirely in the project, but il will be explained latter on)
-	The graphical interface shows the temperature on the inside, the temperature on the outside and the status of the system 
-	Warning against excessively low or high temperatures, which raises the issue that the road ahead can become a safety hazard for the vehicle and driving should be proceed with caution. The message is included on the interface


## Roadmap

- [x] GPIO driver
- [x] ADC driver
- [x] EEPROM driver
- [x] Interrupt driver
- [x] Timer driver
- [x] PWM driver
- [x] I2C driver
- [ ] SPI driver
- [x] UART driver
- [ ] Unit tests
- [x] LCD driver


## Project Structure

```
├── bsp/            # Board definitions (uno.h, nano.h)
├── drivers/        # Hardware Abstraction Layer
│   ├── adc/
│   ├── eeprom/
│   ├── gpio/
│   ├── interrupt/
|   ├── i2c/
|   ├── usart/
|   ├── lcd/
│   └── timer/
├── src/            # Application source code (main.c) and all the files for testing different components used and the final code of this project(cod_final.c)
├── test/           # Unit tests & Mocks
│   ├── mocks/      # Mock AVR registers for host testing
│   ├── framework/  # Minimal test runner
│   └── test_*.c    # Unit test files
├── utils/          # Helper macros (BIT manipulations)
└── Makefile        # Build configuration
```

## Build & Flash

### Prerequisites
- `avr-gcc` toolchain
- `avrdude`
- `make`

### Commands
| Command | Description |
|---------|-------------|
| `make all BOARD=nano` | Compile the project for Arduino Nano. |
| `make flash` | Flash the firmware to the connected board. |
| `make clean` | Remove build artifacts. |

## Testing & Coverage

This project supports running unit tests on your host machine (Mac/Linux) by mocking the AVR hardware registers.

### Prerequisites (for coverage)
- `gcc`
- `lcov` (`brew install lcov`)

### Commands
| Command | Description |
|---------|-------------|
| `make test` | Compile and run all unit tests (GPIO, PWM) on the host. |
| `make coverage` | Run tests and generate usage metrics. |
| `make coverage-html` | Generate a visual HTML report of code coverage. |

![Code Coverage Example](/img/code_coverage_example.png)

## Usage Example

```c
#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "bsp/nano.h"

int main(void) {
    
    Timer0_Init();
    GPIO_Init(LED_BUILTIN, GPIO_OUTPUT);

    uint32_t last_time = 0;

    while (1) {
            
        if (Millis() - last_time >= 1000) {
            last_time = Millis();
            GPIO_Toggle(LED_BUILTIN);
        }
    }
}

// PWM Usage Example
#include "drivers/pwm/pwm.h"
#include "bsp/uno.h"

int pwm_example(void) {
    // 50Hz for Servo on D9
    PWM_Init(UNO_D9, 50);
    // 1.5ms pulse (approx neutral)
    // Duty cycle calculation: (1.5ms / 20ms) * ICR1_TOP
    // Wrapper takes 0-255: (1.5/20)*255 = ~19
    PWM_SetDutyCycle(UNO_D9, 19);

    // 1kHz LED Dimming on D11
    PWM_Init(UNO_D11, 1000);
    PWM_SetDutyCycle(UNO_D11, 128); // 50%
    
    return 0;
}
```
## Brief Hardware Components Analysis 
1.	Tow 10	K potentiometers for sensors replacement and one 10K potentiometer for the heat levels 
2.	An active buzzer for the alarm
3.	One seven-segment display which will display the 9 levels of heat of the system
4.	A 3,3 V DC motor, a l298n motor driver and 9V external power supply for the fan
5.	An I2C module and a 16 X 2 LCD for displaying the inside temperature
6.	One Arduino Nano board 
7.	Jumpers of different sizes




## Code Architecture (**final_code.c**)
1.	Function to clear all the segments of the single display 
2.	Function to display a digit by mapping the segments from the data sheet 
3.	Function to display the digit by controlling the value of a potentiometer 
4.	Function to show the temperature on the 16 X 2 display 
5.	Function to change the sound of the buzzer 
6.	In main function is implemented the rest of the code, like the equation to calculate the temperature showed on the display, which is influenced by factors such as the outside temperature


## Graphical Interface Using Python 
### Reading the values using USART and implementing an interface in Python 
-	Used pyserial to access and used the values sent on USB port 
-	Used threading to allow the program to run in parallel more threads 
-	Used customtkinter for more styling themes and options for the design

### Code fragmenents 
```python 

#CARD TEMPERATURA EXTERIOR

outside_frame = ctk.CTkFrame(main_frame, corner_radius=20)
outside_frame.place(relx=0.55, rely=0.1, relwidth=0.4, relheight=0.35)

outside_title = ctk.CTkLabel(
    outside_frame,
    text="Temperatura Exterior",
    font=("Arial", 20, "bold")
)
outside_title.pack(pady=15)

outside_value = ctk.CTkLabel(
    outside_frame,
    text="-- °C",
    font=("Arial", 42, "bold"),
    text_color="orange"
)
outside_value.pack(pady=10)
```

```python
# CITIRE SERIAL

def serial_read():

    while True:

        try:
            line = ser.readline().decode(errors='ignore').strip()

            print("DATE:", line)



            if "Temperatura afara:" in line:

                values = line.split()

                outside_temp = int(values[2])
                inside_temp = int(values[6])


                # UPDATE INTERFATA

                inside_value.configure(
                    text=f"{inside_temp} °C"
                )

                outside_value.configure(
                    text=f"{outside_temp} °C"
                )


                # COLORARE DINAMICA

                if inside_temp > 30:
                    inside_value.configure(text_color="red")
                else:
                    inside_value.configure(text_color="cyan")

                if outside_temp > 45:
                    outside_value.configure(text_color="red")

                elif outside_temp < 4:
                    outside_value.configure(text_color="blue")

                else:
                    outside_value.configure(text_color="orange")


                # STATUS

                update_status(outside_temp)

        except Exception as e:
            print("EROARE:", e)

```

### Some Examples

#### When the temperature outside is above 45 degrees Celsius

<p align="center">
  <img src="https://github.com/user-attachments/assets/dd4dcfe1-e4d8-4351-925f-50700ac70f71"
       width="500"
       alt="Screenshot" />
</p>

#### When the temperature outside is between 5 and 44 degrees 

<p align="center">
  <img src="https://github.com/user-attachments/assets/fa3940f4-4767-4e86-bedd-f0aabdc013c2"
       width="500"
       alt="Screenshot" />
</p>

##### When the temperature outside is below 4 degrees Celsius 

<p align="center">
  <img src="https://github.com/user-attachments/assets/505a9472-411e-436f-bf98-049c6c6b6a6c"
       width="500"
       alt="Screenshot" />
</p>
