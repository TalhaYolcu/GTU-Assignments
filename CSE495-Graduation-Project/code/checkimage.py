import cv2
import mediapipe as mp
import time
import cv2
from playsound import playsound
import mediapipe as mp
import time
from functions import get_points
from functions import calculate_ear
from pygame import mixer

# Import additional required libraries
from pygame import mixer
from functions import calculate_slope
from functions import calculate_angle




def check_cheek() :
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

    # Read image
    image = cv2.imread("cheeks1.jpg")


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
                #cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

        for facial_landmarks in result.multi_face_landmarks:
            # Iterate through all facial landmarks

            pt1 = facial_landmarks.landmark[right_cheek_index]
            pt2 = facial_landmarks.landmark[left_cheek_index]
            pt3 = facial_landmarks.landmark[chin_index]

            # Get x and y coordinates of landmark
            x = int(pt1.x * width)
            y = int(pt1.y * height)
            # Draw circle at the landmark
            cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

            x = int(pt2.x * width)
            y = int(pt2.y * height)
            # Draw circle at the landmark
            cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

            x = int(pt3.x * width)
            y = int(pt3.y * height)
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

        if (-0.5 < angle_left < 0):
            print('Drowsy')
            cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                        color=(0, 255, 0), thickness=3)



        elif (-1 < angle_right < 0.6):
            print('Drowsy')
            cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                        color=(0, 255, 0), thickness=3)
        else:
            cv2.putText(image, text='Not drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                        color=(0, 255, 0), thickness=3)

        cv2.imshow("Image", image)

        cv2.waitKey(10000)


def check_head_down():
    # Find video source (using default webcam)
    cap = cv2.VideoCapture(0)

    # Initialize height and width variables
    height = -1
    width = -1

    # Indices for facial landmarks on nose
    right_nose_index = 49
    left_nose_index = 279
    up_nose_index = 195
    up_nose_index_2 = 5

    # Wait time (in seconds) before triggering alarm
    WAIT_TIME = 5.0

    # Initialize drowsy time variable
    D_TIME = 0.0

    # Initialize sound player and load alarm sound
    mixer.init()
    mixer.music.load("alarm.mp3")

    # Initialize timer variables
    t1 = time.time()

    # Initialize flags
    isDrowsy = False
    isDone = False


    # Read image from video source
    image = cv2.imread("headdown.jpg")



    # If width and height have not been set, get them from the image
    if height == -1 or width == -1:
        height, width, _ = image.shape

    # Convert image to RGB
    rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # Process image using MediaPipe face mesh
    result = face_mesh.process(rgb_image)

    # If multiple face landmarks are detected
    if result.multi_face_landmarks:
        for facial_landmarks in result.multi_face_landmarks:
            # Iterate through facial landmarks and draw circles on the image
            # at the points corresponding to certain facial landmarks on the nose
            for i in range(0, 438):
                pt1 = facial_landmarks.landmark[i]
                x = int(pt1.x * width)
                y = int(pt1.y * height)
                if i == left_nose_index or i == right_nose_index or i == up_nose_index or i == up_nose_index_2:
                    cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

            # Get points for right and left sides of nose, and upper part of nose
            right_nose_point = facial_landmarks.landmark[right_nose_index]
            left_nose_point = facial_landmarks.landmark[left_nose_index]
            up_nose_point_y = (facial_landmarks.landmark[up_nose_index].y + 2 * facial_landmarks.landmark[
                up_nose_index_2].y) / 3

            # Calculate middle point of nose based on y-coordinates of left and right nose points
            middle_point_y = (right_nose_point.y + left_nose_point.y) / 2

            # If middle point is below upper part of nose, update timer
            if middle_point_y <= up_nose_point_y:
                print('Drowsy')
                cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                            color=(0, 255, 0), thickness=3)
            else :
                cv2.putText(image, text='Not drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                            color=(0, 255, 0), thickness=3)

            cv2.imshow("Image", image)
            cv2.waitKey(10000)


    # Release video capture and close all windows
    cap.release()
    cv2.destroyAllWindows()


def closed_eye() :
    # set thresholds
    EAR_THRESHOLD = 0.3
    WAIT_TIME = 3.0
    D_TIME = 0

    # init face mesh
    mp_face_mesh = mp.solutions.face_mesh
    face_mesh = mp_face_mesh.FaceMesh()

    # set source video
    cap = cv2.VideoCapture(0)

    height = -1
    width = -1

    l_eye_indices = [362, 385, 387, 263, 373, 380]
    r_eye_indices = [33, 160, 158, 133, 153, 144]

    mixer.init()
    mixer.music.load("alarm.mp3")

    isDrowsy = False
    isDone = False

    t1 = time.time()


    # read image
    image = cv2.imread("closedeye1.jpg")
    #image = cv2.imread("normal.jpg")


    # take image's width and height
    if (height == -1 | width == -1):
        height, width, _ = image.shape

    # get rgb image
    rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    # process image
    result = face_mesh.process(rgb_image)

    if result.multi_face_landmarks:
        for facial_landmarks in result.multi_face_landmarks:

            l_eye_points = get_points(l_eye_indices, facial_landmarks.landmark)
            r_eye_points = get_points(r_eye_indices, facial_landmarks.landmark)
            L_EAR_CALCULATED, R_EAR_CALCULATED = calculate_ear(l_eye_points, r_eye_points)

            if (L_EAR_CALCULATED < EAR_THRESHOLD) & (R_EAR_CALCULATED < EAR_THRESHOLD):
                t2 = time.time()
                time_t = t2 - t1
                D_TIME = D_TIME + time_t
                t1 = t2

                # playsound("alarm.mp3")
                print('Drowsy')
                cv2.putText(image, text='Drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                            color=(0, 255, 0), thickness=3)

            else :
                print('Not drowsy')
                cv2.putText(image, text='Not drowsy', org=(150, 250), fontFace=cv2.FONT_HERSHEY_TRIPLEX, fontScale=3,
                            color=(0, 255, 0), thickness=3)



        # if isDrowsy:
        # print("Drowsy...")

        for i in range(0, 6):
            pt1 = facial_landmarks.landmark[l_eye_indices[i]]
            x = int(pt1.x * width)
            y = int(pt1.y * height)
            cv2.circle(image, (x, y), 2, (100, 100, 0), -1)

            pt2 = facial_landmarks.landmark[r_eye_indices[i]]
            x = int(pt2.x * width)
            y = int(pt2.y * height)
            cv2.circle(image, (x, y), 2, (100, 100, 0), -1)




        cv2.imshow("Image", image)

        cv2.waitKey(10000)




# Initialize face mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()


#closed_eye()
#check_head_down()
check_cheek()
