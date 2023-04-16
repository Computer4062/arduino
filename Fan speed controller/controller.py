import cv2
import mediapipe as mp
import serial

arduino = serial.Serial('COM5', 9600)

x1 = y1 = x2 = y2 = 0
velocity = 0

camera = cv2.VideoCapture(0)

hands = mp.solutions.hands.Hands()
draw = mp.solutions.drawing_utils
style = mp.solutions.drawing_styles

while True:
    _, frame = camera.read()

    rgb_image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    output = hands.process(rgb_image)

    hand_landmarks = output.multi_hand_landmarks

    if hand_landmarks:
        for mark in hand_landmarks:
            draw.draw_landmarks(frame, mark)
            landmarks = mark.landmark

            for id, landmark in enumerate(landmarks):
                x = int(landmark.x * frame.shape[1])
                y = int(landmark.y * frame.shape[0])

                if id == 8:
                    cv2.circle(frame, (x, y), 5, (255, 0, 0), cv2.FILLED)
                    x1, y1 = x, y

                if id == 4:
                    cv2.circle(frame, (x, y), 5, (255, 0, 0), cv2.FILLED)
                    x2, y2 = x, y

                cv2.line(frame, (x1, y1), (x2, y2), (255, 0, 0), 2)
                distance = ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** (0.5) // 4

                if distance > 50:
                    if velocity == 255: velocity += 0
                    else: velocity += 1
                    
                    print(velocity)
                    
                    v = str(velocity)
                    if arduino.is_open:
                        arduino.write(v.encode('utf-8'))
                    else:
                        print("arduino is not availale")
                else:
                    if velocity == 0: velocity += 0
                    else: velocity -= 1
                    
                    print(velocity)
                    
                    v = str(velocity)

                    if arduino.is_open:
                        arduino.write(v.encode('utf-8'))
                    else:
                        print("arduino is not available")

    cv2.imshow("Camera", frame)

    if (cv2.waitKey(1) == ord('e')):
        break

cv2.destroyAllWindows()
camera.release()

arduino.close()
