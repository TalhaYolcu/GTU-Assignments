import cv2
import mediapipe as mp
import time


from pygame import mixer


# Initialize face mesh using MediaPipe library
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# Find video source (using default webcam)
cap = cv2.VideoCapture(0,cv2.CAP_DSHOW)

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

# Begin infinite loop
while True:
    # Read image from video source
    ret, image = cap.read()

    # If unable to read image, break out of loop
    if ret is False:
        break

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
            up_nose_point_y = (facial_landmarks.landmark[up_nose_index].y + 2 * facial_landmarks.landmark[up_nose_index_2].y) / 3

            # Calculate middle point of nose based on y-coordinates of left and right nose points
            middle_point_y = (right_nose_point.y + left_nose_point.y) / 2

            # If middle point is below upper part of nose, update timer
            if middle_point_y <= up_nose_point_y:
                t2 = time.time()
                time_t = t2 - t1
                D_TIME = D_TIME + time_t
                t1 = t2

                # If drowsy time exceeds wait time, trigger alarm (if it has not already been triggered)
                if D_TIME >= WAIT_TIME:
                    if isDone is False:
                        mixer.music.play()
                    isDrowsy = True
                    isDone = True

            # Display image with facial landmarks
            cv2.imshow("Image", image)
            cv2.waitKey(1)
        # If no face landmarks are detected
        else:
            # Reset drowsy time and timer
            D_TIME = 0
            t1 = time.time()

    # Release video capture and close all windows
    cap.release()
    cv2.destroyAllWindows()