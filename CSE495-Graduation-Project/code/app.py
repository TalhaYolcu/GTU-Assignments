
import cv2
from playsound import playsound
import mediapipe as mp
import time
from functions import get_points
from functions import calculate_ear
from pygame import mixer

# farklı parametlere göre - grafikler - sonuçlar

#set thresholds
EAR_THRESHOLD=0.3
WAIT_TIME=3.0
D_TIME=0

#init face mesh
mp_face_mesh=mp.solutions.face_mesh
face_mesh=mp_face_mesh.FaceMesh()

#set source video
cap=cv2.VideoCapture(0)

height=-1
width=-1

l_eye_indices=[362,385,387,263,373,380]
r_eye_indices=[33,160,158,133,153,144]

mixer.init()
mixer.music.load("alarm.mp3")

isDrowsy=False
isDone=False

t1=time.time()

while True :
    #read image
    ret,image = cap.read()


    if ret is False :
        break


    #take image's width and height
    if(height==-1 | width==-1):
        height,width,_ = image.shape

    #get rgb image
    rgb_image=cv2.cvtColor(image,cv2.COLOR_BGR2RGB)

    #process image
    result=face_mesh.process(rgb_image)

    if result.multi_face_landmarks:
        for facial_landmarks in result.multi_face_landmarks:

            l_eye_points = get_points(l_eye_indices, facial_landmarks.landmark)
            r_eye_points = get_points(r_eye_indices, facial_landmarks.landmark)
            L_EAR_CALCULATED, R_EAR_CALCULATED = calculate_ear(l_eye_points, r_eye_points)

            print(L_EAR_CALCULATED,R_EAR_CALCULATED)
            if (L_EAR_CALCULATED < EAR_THRESHOLD) & (R_EAR_CALCULATED < EAR_THRESHOLD):
                t2=time.time()
                time_t=t2-t1
                D_TIME=D_TIME+time_t
                t1=t2

                if D_TIME >= WAIT_TIME:
                    if(isDone==False):
                        #playsound("alarm.mp3")
                        mixer.music.play()

                    isDrowsy = True
                    isDone=True


            else:
                D_TIME=0
                t1=time.time()

        #if isDrowsy:
            #print("Drowsy...")


        for i in range(0,6):

            pt1=facial_landmarks.landmark[l_eye_indices[i]]
            x=int(pt1.x*width)
            y=int(pt1.y*height)
            cv2.circle(image,(x,y),2,(100,100,0),-1)

            pt2=facial_landmarks.landmark[r_eye_indices[i]]
            x=int(pt2.x*width)
            y=int(pt2.y*height)
            cv2.circle(image,(x,y),2,(100,100,0),-1)



        cv2.imshow("Image", image)

        cv2.waitKey(1)

    else :
        D_TIME=0
        t1=time.time()


