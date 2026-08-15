# Fan Speed Controller (Hand Gesture Controlled)

Control a PC/DC fan's speed in real time using hand tracking. A Python script uses your webcam and [MediaPipe](https://google.github.io/mediapipe/) to track your hand, measures the distance between your thumb tip and index fingertip, and streams a speed value over serial to an Arduino, which drives the fan via PWM.

## How It Works

1. **`controller.py`** opens your webcam and uses MediaPipe Hands to detect hand landmarks.
2. It tracks two landmarks:
   - Landmark `4` — thumb tip
   - Landmark `8` — index fingertip
3. It calculates the pixel distance between these two points.
   - If the distance is **greater than 50px** (fingers spread apart), the speed value ramps **up** by 1 each frame, up to a max of 255.
   - If the distance is **50px or less** (fingers pinched together), the speed value ramps **down** by 1 each frame, down to a min of 0.
4. The current speed value is sent over serial (as text) to the Arduino.
5. **`sketch_apr16a.ino`** reads the incoming serial value and writes it to the fan pin using `analogWrite()`, setting the fan's PWM duty cycle accordingly.

In short: spread your thumb and index finger apart to speed the fan up, pinch them together to slow it down.

## Hardware Requirements

- Arduino board (e.g. Uno/Nano) with PWM-capable pin
- A PWM-controllable fan (or a fan driven through a transistor/MOSFET if it isn't natively PWM-capable)
- USB cable connecting the Arduino to your computer
- A webcam

### Wiring

- Connect the fan control line to **pin 9** on the Arduino (as defined by `#define fan 9` in the sketch).
- Wire the fan's power according to its voltage/current requirements — do not power a 12V fan directly from the Arduino pin. Use an appropriate driver circuit (transistor/MOSFET) if the fan draws more current than the Arduino pin can supply.

## Software Requirements

- Python 3
- [OpenCV](https://pypi.org/project/opencv-python/) (`cv2`)
- [MediaPipe](https://pypi.org/project/mediapipe/)
- [PySerial](https://pypi.org/project/pyserial/)

Install the Python dependencies:

```bash
pip install opencv-python mediapipe pyserial
```

- Arduino IDE to flash `sketch_apr16a.ino` to your board

## Setup & Usage

1. **Flash the Arduino**
   - Open `sketch_apr16a/sketch_apr16a.ino` in the Arduino IDE.
   - Select your board and port, then upload the sketch.

2. **Configure the serial port**
   - In `controller.py`, update the port to match your system:
     ```python
     arduino = serial.Serial('COM5', 9600)
     ```
   - On Windows this will look like `COM3`, `COM5`, etc. On macOS/Linux it will look like `/dev/ttyUSB0` or `/dev/cu.usbmodem*`.
   - Close the Arduino IDE's Serial Monitor before running the script, since only one program can use the serial port at a time.

3. **Run the controller**
   ```bash
   python controller.py
   ```
   - A window will open showing your webcam feed with hand landmarks drawn on it.
   - Spread your thumb and index finger apart to increase fan speed; bring them together to decrease it.
   - Press **`e`** to quit the program.

## Files

| File | Description |
|---|---|
| `controller.py` | Python script for hand tracking and serial communication with the Arduino |
| `sketch_apr16a/sketch_apr16a.ino` | Arduino sketch that reads the serial value and sets fan PWM speed |

## Notes / Possible Improvements

- Speed changes ramp gradually (±1 per frame) rather than jumping directly to a target value, so it takes a moment to reach full speed or a full stop.
- The distance threshold (`50`) and serial port are hardcoded and may need tuning/updating for your setup.
- Only one hand's landmarks are used at a time; behavior with multiple hands in frame is undefined.
