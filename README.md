# Touch Counter for Arduino UNO R4 WiFi

A minimal touch counter that runs on the **Arduino UNO R4 WiFi** board alone, with no buttons, wires or extra components. Touch the small heart printed on the back of the board and the number of touches appears on the built-in 12×8 LED matrix.

## Features

- **No external hardware**: uses the board's built-in capacitive touch pad (the heart on the back, `LOVE_BUTTON`)
- **One touch = one count**: the counter increases only when your finger lands, not while it stays on the pad
- **Static display up to 999**, centered on the LED matrix
- **Scrolling display** for numbers of 1000 and above
- **Serial output** of the current count at 115200 baud

## Hardware

- Arduino UNO R4 WiFi
- USB-C cable

That's it.

## Software requirements

- [Arduino IDE](https://www.arduino.cc/en/software) 2.x
- **Arduino UNO R4 Boards** package (Tools → Board → Boards Manager)
- Libraries (Tools → Manage Libraries):
  - `ArduinoGraphics`
  - `Arduino_CapacitiveTouch`

`Arduino_LED_Matrix` ships with the UNO R4 board package and needs no separate installation.

## Setup

1. Clone or download this repository.
2. Open `compteur_tactile_simple/compteur_tactile_simple.ino` in the Arduino IDE.
3. Select **Arduino UNO R4 WiFi** as the board and choose the correct port.
4. Upload the sketch.
5. Touch the heart on the back of the board and watch the counter go up.

## How it works

1. The sketch reads the capacitive touch sensor every 20 ms.
2. It detects the moment a finger lands on the pad (rising edge), so holding your finger down counts as a single touch.
3. Each new touch increments the counter and redraws the LED matrix.
4. Numbers up to 999 are drawn with a 4×6 pixel font, which fits exactly on the 12-column matrix. Larger numbers scroll using a 5×7 font.

## Configuration

| Setting | Location | Default |
|---|---|---|
| Touch pad | `CapacitiveTouch capteur(LOVE_BUTTON)` | heart on the back of the board |
| Touch sensitivity | `capteur.setThreshold()` in `setup()` | library default (line commented out) |
| Scroll speed | `textScrollSpeed()` in `afficherNombre()` | 50 (lower is faster) |

### Using another pin

Replace `LOVE_BUTTON` with a touch-capable pin such as `D2` or `A1`, then touch the pin directly with your finger (or a wire connected to it). See the `Arduino_CapacitiveTouch` documentation for the full list of supported pins.

## Troubleshooting

- **Touches are not detected, or count on their own**: uncomment `capteur.setThreshold(2000);` in `setup()` and try different values. A lower value makes the pad more sensitive. To find a good value, print `capteur.read()` to the Serial Monitor with and without your finger on the pad, and pick a threshold between the two readings.
- **The count resets when unplugged**: this is expected. The counter is stored in RAM only.
- **Compilation errors about missing headers**: make sure `ArduinoGraphics` and `Arduino_CapacitiveTouch` are installed and that the UNO R4 board package is selected.

## Ideas for improvements

- Save the count to EEPROM so it survives a power cycle
- Add a long-press gesture to reset the counter
- Challenge mode: count as many touches as possible in 10 seconds
- Show the count on an external I2C OLED display

## License

This project is released under the MIT License. See `LICENSE` for details.
