:- style_check(-singleton).
:- dynamic(student/3).
:- dynamic(room/3).
:- dynamic(course/6).
:- dynamic(instructor/3).
:- dynamic(occupancy/3).

%student database
student(1, [cse101, cse102, cse241], no).
student(2, [cse101, cse102], no).
student(3, [cse101, cse241], no).
student(4, [cse101], no).
student(5, [cse102, cse241], no).
student(6, [cse101, cse102, cse241], yes).
student(7, [cse101, cse102], no).
student(8, [cse101, cse241], yes).
student(9, [cse101], no).
student(10, [cse101, cse343], no).
student(11, [cse101, cse343], no).
student(12, [cse102, cse343], no).
student(13, [cse102, cse343], no).
student(14, [cse102, cse343], no).
student(15, [cse102, cse241], yes).

%occupancy database
occupancy(z23, 8, cse101).
occupancy(z23, 9, cse101).
occupancy(z23, 9, cse102).
occupancy(z23, 12, cse102).
occupancy(z23, 13, cse102).

occupancy(z06, 9, cse241).
occupancy(z06, 10, cse241).
occupancy(z06, 11, cse241).
occupancy(z06, 12, cse241).

occupancy(z10, 15, cse343).
occupancy(z10, 16, cse343).

%instructor database
instructor(gokturk, cse101, projector).
instructor(genc, cse102, smart_board).
instructor(akgul, cse241, no_need).
instructor(kalkan, cse343, smart_board).

%course database
course(cse101, gokturk, 10, 2, z23, projector).
course(cse102, genc, 6, 3, z23, no_need).
course(cse241, akgul, 5, 4, z06, no_need).
course(cse343, kalkan, 10, 2, z10, smart_board).

%room database
room(z06, 10, [handicapped, projector]).
room(z10, 10, [handicapped, smart_board]).
room(z23, 10, [handicapped,projector]).

% Checks conflicts

conflicts(X, Y) :-
  occupancy(A, Z, X),
  occupancy(A, Z, Y),
  not(X = Y).

% Checks given room can be assigned to given course or any course
assign(RoomId, CourseId) :-

    room(RoomID,Cap,A),
    course(CourseId, _, Cap2, _, RoomId2, B),
    (Cap>=Cap2),
    (member(B,A);(B==no_need)).
  

% Checks student can be assigned to given course or any course
enroll(StudentId, CourseId) :-

    student(StudentId,_,H),  
    course(CourseId,_,Cap,_,RoomID,Need),
    room(RoomID, Cap2, NeedList),
    member(Need,NeedList);(Need=no_need),
    (Cap=Cap2),
    (
  	 %If student is hcap,check course need
    (   (H = yes), member(handicapped, NeedList) );
        (H = no)
    ).

%adds students
add_student(StudentID,CourseList,Hcap):-
    \+student(StudentID,_,_),
    assertz(student(StudentID, CourseList,Hcap)).

%adds course
add_course(CourseID, Instructor, Cap, Hour,Room,Need,OccupancyL):-
    \+course(CourseID,_,_,_,_,_),
    assertz(course(CourseID, Instructor, Cap, Hour, Room,Need)),
    add_occupancy(Room,OccupancyL,CourseID).

%adds room
add_room(RoomID, Cap, Properties):-
    \+room(RoomID,_,_),
    assertz(room(RoomID, Cap, Properties)).

%adds occupancy
add_occupancy(Room,[],CourseID).

add_occupancy(Room,[OccupancyF|OccupancyR],CourseID):-
    assertz(occupancy(Room,OccupancyF,CourseID)),
    add_occupancy(Room,OccupancyR,CourseID).


   

