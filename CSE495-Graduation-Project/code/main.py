

import cv2
import mediapipe as mp
import time

#face mesh

mp_face_mesh=mp.solutions.face_mesh
face_mesh=mp_face_mesh.FaceMesh()

cap=cv2.VideoCapture(0)

isDrowsy=False
start=0
end=0
inital_set=False


while True:


    #Image
    ret,image = cap.read()
    if ret is False :
        break

    height,width,_ = image.shape

    rgb_image=cv2.cvtColor(image,cv2.COLOR_BGR2RGB)


    #process image
    #facial landmarks
    result=face_mesh.process(rgb_image)




    for facial_landmarks in result.multi_face_landmarks:

        end=time.time()

        if (end - start >= 5 & isDrowsy == True):
            print("OH NOOOOO")


        if inital_set==False:

            initial_max_difference=facial_landmarks.landmark[244].y*height-facial_landmarks.landmark[189].y*height
            initial_set=True

        l_eye_up_y=facial_landmarks.landmark[159].y
        l_eye_up_left_y=facial_landmarks.landmark[133].y

        if int(l_eye_up_left_y-l_eye_up_y) < int(initial_max_difference/2):
            if isDrowsy == False:
                start = time.time()
                isDrowsy=True

        else:
            isDrowsy=False






        for i in range(0,468):

            pt1=facial_landmarks.landmark[i]
            x=int(pt1.x*width)
            y=int(pt1.y*height)

            cv2.circle(image,(x,y),2,(100,100,0),-1)


    cv2.imshow("Image",image)

    cv2.waitKey(1)
