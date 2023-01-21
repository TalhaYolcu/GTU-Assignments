import cv2
import mediapipe as mp
import time

# Import additional required libraries
from pygame import mixer
from functions import calculate_slope
from functions import calculate_angle

# This program checks whether the driver moves their head right or left

# Initialize face mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# Find video source
cap = cv2.VideoCapture(0)

# Initialize width and height at the start of the program
height = -1
width = -1

# Set angle
angle = 45

# Waiting for the specific situation
WAIT_TIME = 5.0

# Current drowsy time
D_TIME = 0

# Initialize background sound player
mixer.init()

mixer.music.load("alarm.mp3")

# Right cheek index
right_cheek_index = 93
# Left cheek index
left_cheek_index = 323
# Chin index
chin_index = 152

# Initialize timer variables
t1 = time.time()

# Initialize flags
isDrowsy = False
isDone = False

# Begin infinite loop
while True:

    # Read image
    ret, image = cap.read()

    # If unable to read image, break out of loop
    if ret is False:
        break

    # If width and height have not been set, get them from the image
    if height == -1 or width == -1:
        height, width, _ = image.shape

    # Convert image to RGB
    rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Process image
    result = face_mesh.process(rgb_image)

    # If multiple face landmarks are detected
    if result.multi_face_landmarks:
        for facial_landmarks in result.multi_face_landmarks:
            # Iterate through all facial landmarks
            for i in range(0, 438):
                pt1 = facial_landmarks.landmark[i]
                # Get x and y coordinates of landmark
                x = int(pt1.x * width)
                y = int(pt1.y * height)
                # Draw circle at the landmark
                cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

        # Get points for right cheek, left cheek, and chin
        right_cheek_point = facial_landmarks.landmark[right_cheek_index]
        left_cheek_point = facial_landmarks.landmark[left_cheek_index]
        chin_point = facial_landmarks.landmark[chin_index]

        # Calculate slopes of lines connecting right cheek, left cheek, and chin
        slope_right, slope_left = calculate_slope(right_cheek_point, left_cheek_point, chin_point)

        # Calculate angles of lines connecting right cheek, left cheek, and chin
        angle_right, angle_left = calculate_angle(slope_right, slope_left)

        print(angle_right, angle_left)

        if(-0.5<angle_left<0) :
            t2=time.time()
            time_t=t2-t1
            D_TIME=D_TIME+time_t
            t1=t2

            if D_TIME>=WAIT_TIME:
                if(isDone==False):
                    mixer.music.play()

                isDrowsy=True
                isDone=True

        elif(0<angle_right<0.6) :
            t2=time.time()
            time_t=t2-t1
            D_TIME=D_TIME+time_t
            t1=t2

            if D_TIME>=WAIT_TIME:
                if(isDone==False):
                    mixer.music.play()

                isDrowsy=True
                isDone=True


        cv2.imshow("Image",image)

        cv2.waitKey(1)


    else :
        D_TIME=0
        t1=time.time()

