import speech_recognition
import pyttsx3
import serial

recognizer = speech_recognition.Recognizer()
arduino = serial.Serial(port = 'COM5', timeout=0)

print("Ready")
while True:
    try:
        with speech_recognition.Microphone() as mic:
            audio = recognizer.listen(mic)

            text = recognizer.recognize_sphinx(audio)
            text = text.lower()

            print(f"Recognize >> {text}")

            arduino.write(text.encode())

    except speech_recognition.UnknownValueError:
        recognizer = speech_recognition.Recognizer()
        continue

arduino.close()
