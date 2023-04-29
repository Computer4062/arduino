import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import serial
from time import sleep

arduino = serial.Serial('COM5', 9600)

with open('verified', 'r') as verified:
    verify = verified.read()
    if verify == 'false':
        email = input('Enter your email here: ')
        password = input('Enter your password here: ')
        with open('email', 'w') as emailfile:
            emailfile.write(email)

        with open('password', 'w') as passwordfile:
            passwordfile.write(password)

    with open('verified', 'w') as verified:
        verified.write('true')

sender = open('email', 'r').read()
password = open('password', 'r').read()

server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(sender, password)

while True:
    if arduino.read() == b'w':
        receiver = 'mihan.edirisinghe@gmail.com'
        subject = 'alarm'
        body = 'This is a reminder email'

        message = MIMEMultipart()
        message['from'] = sender
        message['to'] = receiver
        message['subject'] = 'reminder'
        message.attach(MIMEText(body, 'plain'))

        text = message.as_string()
        server.sendmail(sender, receiver, text)

    sleep(5)

server.quit()
arduino.quit()