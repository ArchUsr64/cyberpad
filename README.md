# cyberpad
Macropad in cyberpunk style

## Features
- 16-key matrix layout
- Two rotary encoders (knobs)
- RGB lighting

## Parts Required
| Part | Quantity | Description |
|  -   |    -     |  -  |
| Raspberry Pi Pico | 1 | Microcontroller that powers the whole thing |
| M3 screw | 8 | Used to mount the top and bottom plates together |
| M2 screw | 4 | Used to mount the raspberry pi pico to the top plate |
| M3 standoff | 4 | Provide spacing between the top and bottom plate to house the electronics |
| Switch | 16 | Key switches mounted to the top plate (both 3-pin and 5-pin work)|
| Keycaps | 16 | Keycaps for the switches |
| Diodes | 16 | Required to achieve n-key rollover |
| USB Cable | 1 | Used to connect the pico to the computer |
| RGB LED | 6 | For RGB lighting, firmware expects common anode type |
| Potentiometer | 3 | Used to control the color of RGB lights |
| Type C breakout board (optional) | 1 | Use TP2 and TP3 test points for external USB port |
| Bump Switch (optional) | 1 | Used to get the board to bootloader mode |

## Wiring

![image](https://github.com/ArchUsr64/cyberpad/assets/83179501/e986ac87-07e0-424e-9d61-23c771e0715e)

The diodes should be connected in `Column to Row` ordering i.e the `cathode` of the diode (the side with the line) should be facing away from the keys and the `cathode` of the diodes in same row should all be connected.  

The `anode` of the diodes should each connect to one pin of the switch and the other pin should be connected straight with all the pins of switches in same column. 
For wiring the Raspberry Pi Pico, the indexing used in the wiring diagram above corresponds to the pico's pinout as follows:

| Row | 0 | 1 | 2 | 3 |
|  -  | - | - | - | - |
| Pin | 5 | 6 | 7 | 8 |

| Column | 0 | 1 | 2 | 3 |
|  -  | - | - | - | - |
| Pin | 20 | 19 | 21 | 22 |
