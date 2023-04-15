import cv2
import mediapipe as mp
import os
import serial

#arduino = os.open('COM5', os.O_RDWR)
arduino = serial.Serial('COM5', 9600)

camera = cv2.VideoCapture(0)

mp_hands = mp.solutions.hands
mp_hands_draw = mp.solutions.drawing_utils
mp_hands_style = mp.solutions.drawing_styles

fingerCoordinates = [(8, 6), (12, 10), (16, 14), (20, 18)]
thumbCoordinates = (4, 2)

hands = mp_hands.Hands()
fingercount = 0

while True:
    _,  frame = camera.read()

    img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = hands.process(img_rgb)
    landmarks = result.multi_hand_landmarks

    if landmarks:
        handpoint = []
        for landmark in landmarks:
            mp_hands_draw.draw_landmarks(frame, landmark, mp_hands.HAND_CONNECTIONS)

        for landmark, lm in enumerate(landmark.landmark):
            h, w, d = frame.shape
            ch, cw = int(lm.y * h), int(lm.x * w)

            handpoint.append((cw, ch))

        for point in handpoint:
            cv2.circle(frame, point, 5, (0, 255, 0), cv2.FILLED)

        fingercount =  0

        for coordinate in fingerCoordinates:
            if handpoint[coordinate[0]][1] < handpoint[coordinate[1]][1]:
                fingercount += 1

                value = ' '
                if(fingercount == 1): value = 'a'
                if(fingercount == 2): value = 'b'
                if(fingercount == 3): value = 'c'

                #os.write(arduino, b'a')
                arduino.write(value.encode('utf-8'))

    cv2.rectangle(frame, (50, 50), (100, 100), (0, 255, 0), cv2.FILLED)
    cv2.putText(frame, str(fingercount), (60, 80), 4, cv2.FONT_HERSHEY_PLAIN, (255, 0, 0), 5)

    cv2.imshow("Hand Remote", frame)
    if(cv2.waitKey(1) == ord('e')): break

cv2.destroyAllWindows()
camera.release()

arduino.close()