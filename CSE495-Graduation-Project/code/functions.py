import numpy


def get_points(indices, landmarks):
    pt1 = landmarks[indices[0]]
    pt2 = landmarks[indices[1]]
    pt3 = landmarks[indices[2]]
    pt4 = landmarks[indices[3]]
    pt5 = landmarks[indices[4]]
    pt6 = landmarks[indices[5]]


    return [pt1,pt2,pt3,pt4,pt5,pt6]


def calculate_distance(pt1,pt2):
    x1=pt1.x
    y1=pt1.y

    x2=pt2.x
    y2=pt2.y
    return ((x1 - x2)**2 + (y1 - y2)**2)**0.5

def calculate_one_ear(eye):
    numerator = calculate_distance(eye[1],eye[5])+calculate_distance(eye[2],eye[4])
    denumerator = 2 * calculate_distance(eye[0],eye[3])
    return numerator / denumerator

def calculate_ear(l_eye,r_eye):
    return calculate_one_ear(l_eye),calculate_one_ear(r_eye)

def calculate_slope(right_cheek_point,left_cheek_point,chin_point):
    xr=right_cheek_point.x
    yr=right_cheek_point.y

    xl=left_cheek_point.x
    yl=left_cheek_point.y

    xc=chin_point.x
    yc=chin_point.y

    slope_right = (yc - yr ) / (xc- xr)
    slope_left= (yc - yl) / (xc - xl)
    return slope_right,slope_left


def calculate_angle(slope_right,slope_left):
    angle_right=numpy.arctan(slope_right)
    angle_left=numpy.arctan(slope_left)
    return angle_right,angle_left

