import cv2
import mediapipe as mp
import time
import pygame

# Initialize face mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh()

# Find video source
cap = cv2.VideoCapture(0)

# Initialize width and height at the start of the program
height = -1
width = -1

# Set alarm threshold (in seconds)
ALARM_THRESHOLD = 5

# Initialize timer variables
t1 = time.time()

# Initialize flags
is_alarm_triggered = False
is_head_moving_down = False
is_eyes_closed = False
is_head_moving_left_right = False

# Initialize sound player
pygame.init()

# Load alarm sound
alarm_sound = pygame.mixer.Sound("alarm.mp3")

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
            # Get points for nose tip, left eye, and right eye
            nose_tip_point = facial_landmarks.landmark[30]
            left_eye_point = facial_landmarks.landmark[36]
            right_eye_point = facial_landmarks.landmark[45]

            # Calculate slope of line connecting nose tip and eyes
            slope = (left_eye_point.y - right_eye_point.y) / (left_eye_point.x - right_eye_point.x)

            # Check if slope is greater than a certain threshold (indicating that the head is moving down)
            if slope > 0.5:
                is_head_moving_down = True
            else:
                is_head_moving_down = False

            # Check if eyes are closed (using nose tip and eye points)
            eye_distance = ((left_eye_point.x - right_eye_point.x) ** 2 + (
                        left_eye_point.y - right_eye_point.y) ** 2) ** 0.5
            nose_eye_distance = ((left_eye_point.x - nose_tip_point.x) ** 2 + (
                        left_eye_point.y - nose_tip_point.y) ** 2) ** 0.5
            if eye_distance < 0.1 * nose_eye_distance:
                is_eyes_closed = True
            else:
                is_eyes_closed = False

            # Check if head is moving left or right (using nose tip and eye points)
            if (left_eye_point.x < nose_tip_point.x < right_eye_point.x) or (
                    right_eye_point.x < nose_tip_point.x < left_eye_point.x):
                is_head_moving_left_right = True
            else:
                is_head_moving_left_right = False

            # If any of the drowsy conditions are met, update timer and check if alarm should be triggered
            if is_head_moving_down or is_eyes_closed or is_head_moving_left_right:
                t2 = time.time()
                time_elapsed = t2 - t1
                if time_elapsed >= ALARM_THRESHOLD and not is_alarm_triggered:
                    alarm_sound.play()
                    is_alarm_triggered = True
            else:
                t1 = time.time()
                is_alarm_triggered = False

            # Display image with facial landmarks
        cv2.imshow("Image", image)
        cv2.waitKey(1)

    # Release video capture and close all windows
    cap.release()
    cv2.destroyAllWindows()
