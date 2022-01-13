def maxcourse(all_courses,n):
    max_counter=1
    cur_course=0
    for i in range(n):
        if(all_courses[cur_course][1]<=all_courses[i][0]):
            cur_course=i
            max_counter+=1
    return max_counter

start_time = [1, 3, 0, 5, 8, 5]
finish_time = [2, 4, 6, 7, 9, 9]
courses=[]
for i in range(len(start_time)):
    courses.append([start_time[i],finish_time[i]])
print(courses)
print(start_time)
print(finish_time)
print("Max number of course:",maxcourse(courses,len(start_time)))
print("-------------")

