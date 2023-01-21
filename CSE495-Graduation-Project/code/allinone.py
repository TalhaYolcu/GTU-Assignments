

import cv2
import mediapipe as mp
import time
from functions import get_points
from functions import calculate_ear

# Import additional required libraries
from pygame import mixer
from functions import calculate_slope
from functions import calculate_angle


def check_eyes(L_EAR_CALCULATED,EAR_THRESHOLD,R_EAR_CALCULATED,t1,D_TIME,isDone):
    # print(L_EAR_CALCULATED,R_EAR_CALCULATED)
    if (L_EAR_CALCULATED < EAR_THRESHOLD) & (R_EAR_CALCULATED < EAR_THRESHOLD):
        t2 = time.time()
        time_t = t2 - t1
        D_TIME = D_TIME + time_t
        t1 = t2

        if D_TIME >= WAIT_TIME:
            if (isDone == False):
                #playsound("alarm.mp3")
                #mixer.music.play()
                return True,D_TIME,t1

            isDrowsy = True
            isDone = True
            return True, D_TIME, t1

    return False,D_TIME,t1

def check_cheeks(angle_left,t1,D_TIME,isDone):
    if (-0.5 < angle_left < 0):
        t2 = time.time()
        time_t = t2 - t1
        D_TIME = D_TIME + time_t
        t1 = t2

        if D_TIME >= WAIT_TIME:
            if (isDone == False):
                #mixer.music.play()
                return True,D_TIME,t1


            isDrowsy = True
            isDone = True
            return True, D_TIME, t1

    elif (0 < angle_right < 0.6):
        t2 = time.time()
        time_t = t2 - t1
        D_TIME = D_TIME + time_t
        t1 = t2

        if D_TIME >= WAIT_TIME:
            if (isDone == False):
                #mixer.music.play()
                return True,D_TIME,t1

            isDrowsy = True
            isDone = True
            return True, D_TIME, t1

    return False,D_TIME,t1

def check_nose(t1,D_TIME,isDone):
    # If middle point is below upper part of nose, update timer
    if middle_point_y <= up_nose_point_y:
        t2 = time.time()
        time_t = t2 - t1
        D_TIME = D_TIME + time_t
        t1 = t2

        # If drowsy time exceeds wait time, trigger alarm (if it has not already been triggered)
        if D_TIME >= WAIT_TIME:
            if isDone is False:
                #mixer.music.play()
                return True,D_TIME,t1

            isDrowsy = True
            isDone = True
            return True, D_TIME, t1

    return False,D_TIME,t1


def drawCircle(pt1,image):
    x = int(pt1.x * width)
    y = int(pt1.y * height)
    cv2.circle(image, (x, y), 2, (100, 100, 0), -1)



# set thresholds and times
EAR_THRESHOLD = 0.3
WAIT_TIME = 3.0
D_TIME = 0

# init face mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# set source video
cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)

#need inits for closed eye
height = -1
width = -1
l_eye_indices = [362, 385, 387, 263, 373, 380]
r_eye_indices = [33, 160, 158, 133, 153, 144]


#need inits for check cheek
# Right cheek index
right_cheek_index = 93
# Left cheek index
left_cheek_index = 323
# Chin index
chin_index = 152
# Set angle
angle = 45

#need inits for head down
# Indices for facial landmarks on nose
right_nose_index = 49
left_nose_index = 279
up_nose_index = 195
up_nose_index_2 = 5


mixer.init()
mixer.music.load("alarm.mp3")

isDrowsy = False
isDone = False

t1 = time.time()


while True:

    ret,image=cap.read()

    if ret is False :
        break

    # If width and height have not been set, get them from the image
    if height == -1 or width == -1:
        height, width, _ = image.shape

    #get rgb image
    rgb_image=cv2.cvtColor(image,cv2.COLOR_BGR2RGB)

    #process image
    result=face_mesh.process(rgb_image)

    if result.multi_face_landmarks:
        for facial_landmarks in result.multi_face_landmarks:


            #closed eyes
            l_eye_points = get_points(l_eye_indices, facial_landmarks.landmark)
            r_eye_points = get_points(r_eye_indices, facial_landmarks.landmark)
            L_EAR_CALCULATED, R_EAR_CALCULATED = calculate_ear(l_eye_points, r_eye_points)

            #check cheeks
            # Get points for right cheek, left cheek, and chin
            right_cheek_point = facial_landmarks.landmark[right_cheek_index]
            left_cheek_point = facial_landmarks.landmark[left_cheek_index]
            chin_point = facial_landmarks.landmark[chin_index]

            # Calculate slopes of lines connecting right cheek, left cheek, and chin
            slope_right, slope_left = calculate_slope(right_cheek_point, left_cheek_point, chin_point)

            # Calculate angles of lines connecting right cheek, left cheek, and chin
            angle_right, angle_left = calculate_angle(slope_right, slope_left)

            #check nose
            # Get points for right and left sides of nose, and upper part of nose
            right_nose_point = facial_landmarks.landmark[right_nose_index]
            left_nose_point = facial_landmarks.landmark[left_nose_index]
            up_nose_point_y = (facial_landmarks.landmark[up_nose_index].y + 2 * facial_landmarks.landmark[up_nose_index_2].y) / 3

            # Calculate middle point of nose based on y-coordinates of left and right nose points
            middle_point_y = (right_nose_point.y + left_nose_point.y) / 2


            #drawcircle for eyes
            for i in range(0, 6):
                pt1 = facial_landmarks.landmark[l_eye_indices[i]]
                x = int(pt1.x * width)
                y = int(pt1.y * height)
                cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

                pt2 = facial_landmarks.landmark[r_eye_indices[i]]
                x = int(pt2.x * width)
                y = int(pt2.y * height)
                cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

            #drawcircle for cheeks
            drawCircle(right_cheek_point,image)
            drawCircle(left_cheek_point,image)
            drawCircle(chin_point,image)

            #drawcircle for noses
            ptleftnose = facial_landmarks.landmark[left_nose_index]
            ptrightnose = facial_landmarks.landmark[right_nose_index]
            ptupnose = facial_landmarks.landmark[up_nose_index]
            ptupnose2 = facial_landmarks.landmark[up_nose_index_2]

            drawCircle(ptleftnose, image)
            drawCircle(ptrightnose, image)
            drawCircle(ptupnose, image)
            drawCircle(ptupnose2, image)

            if (L_EAR_CALCULATED < EAR_THRESHOLD) & (R_EAR_CALCULATED < EAR_THRESHOLD):
                t2=time.time()
                time_t=t2-t1
                D_TIME=D_TIME+time_t
                t1=t2

                if D_TIME >= WAIT_TIME:
                    if(isDone==False):
                        #playsound("alarm.mp3")
                        cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX,
                                    fontScale=3,
                                    color=(0, 255, 0), thickness=3)
                        mixer.music.play()


                    isDrowsy = True
                    isDone=True

            elif middle_point_y <= up_nose_point_y:
                t2 = time.time()
                time_t = t2 - t1
                D_TIME = D_TIME + time_t
                t1 = t2

                # If drowsy time exceeds wait time, trigger alarm (if it has not already been triggered)
                if D_TIME >= WAIT_TIME:
                    if isDone is False:
                        cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX,
                                    fontScale=3,
                                    color=(0, 255, 0), thickness=3)
                        mixer.music.play()
                    isDrowsy = True
                    isDone = True

            elif (-0.5 < angle_left < 0):
                t2 = time.time()
                time_t = t2 - t1
                D_TIME = D_TIME + time_t
                t1 = t2

                if D_TIME >= WAIT_TIME:
                    if (isDone == False):
                        cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX,
                                    fontScale=3,
                                    color=(0, 255, 0), thickness=3)
                        mixer.music.play()

                    isDrowsy = True
                    isDone = True

            elif (0 < angle_right < 0.6):
                t2 = time.time()
                time_t = t2 - t1
                D_TIME = D_TIME + time_t
                t1 = t2

                if D_TIME >= WAIT_TIME:
                    if (isDone == False):
                        cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX,
                                    fontScale=3,
                                    color=(0, 255, 0), thickness=3)
                        mixer.music.play()

                    isDrowsy = True
                    isDone = True



            else :
                D_TIME = 0
                t1 = time.time()
                cv2.putText(image, text='Not drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                        color=(0, 255, 0), thickness=3)



        cv2.imshow("Image", image)

        cv2.waitKey(1)

    else :
        D_TIME=0
        t1=time.time()

