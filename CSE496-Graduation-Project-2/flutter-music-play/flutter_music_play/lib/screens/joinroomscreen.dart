import 'package:audioplayers/audioplayers.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:flutter_music_play/screens/insideroomscreen.dart';
import '../main.dart';
import '../util/constants.dart';
import '../util/model/roomuser.dart';

class JoinRoomPasswordScreen extends StatefulWidget {
  final String roomName;
  final String userId;
  BluetoothDevice server;
  String song_path;
  String duration_value;

  JoinRoomPasswordScreen({required this.roomName,required this.userId,required this.server,required this.song_path,required this.duration_value});

  @override
  _JoinRoomPasswordScreenState createState() => _JoinRoomPasswordScreenState();
}

class _JoinRoomPasswordScreenState extends State<JoinRoomPasswordScreen> {
  final passwordController = TextEditingController();
  FirebaseDatabase referencedatabase=FirebaseDatabase.instanceFor(
    app: Firebase.app(),databaseURL: firebaseDatabaseUrl);

  String pushToken = "";

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    FirebaseMessaging.onMessage.listen((RemoteMessage message) {
      RemoteNotification? notification = message.notification;
      AndroidNotification? androidNotification = message.notification?.android;
      if (notification != null && androidNotification != null) {
        flutterLocalNotificationsPlugin.show(
            notification.hashCode,
            notification.title,
            notification.body,
            NotificationDetails(
                android: AndroidNotificationDetails(channel.id, channel.name,
                    channelDescription: channel.description,
                    color: Colors.blue,
                    playSound: true,
                    icon: '@mipmap/ic_launcher')));
      }
    });
    FirebaseMessaging.onMessageOpenedApp.listen((RemoteMessage message) {
      Logger.log(Logger.logLevel,'A new onMessageOpenedApp event was published');
      RemoteNotification? notification = message.notification;
      AndroidNotification? androidNotification = message.notification?.android;
      if (notification != null && androidNotification != null) {
        showDialog(
            context: context,
            builder: (_) {
              return AlertDialog(
                title: Text(notification.title ?? 'Null'),
                content: SingleChildScrollView(
                  child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [Text(notification.body ?? 'Null')]),
                ),
              );
            });
      }
    });     
  }

  @override
  Widget build(BuildContext context) {
    FirebaseMessaging.instance.getToken().then((value) {
      print("Firebase token is: ");
      print(value);
      pushToken=value!;
    });

    return Scaffold(
      appBar: AppBar(
        title: Text('Enter Room Password'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: SingleChildScrollView(
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.center,
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              SizedBox(height: 120,),
              Text('Room: ${widget.roomName}'),
              TextField(
                controller: passwordController,
                decoration: InputDecoration(
                  labelText: 'Room Password',
                ),
              ),
              SizedBox(height: 16.0),
              ElevatedButton(
                onPressed: () async {
                  final roomName = widget.roomName;
                  final password = passwordController.text;
                  final roomRef = referencedatabase.ref('rooms').child(roomName);
                  final snapshot = await roomRef.once();
                  final roomData = snapshot.snapshot.value as Map<dynamic, dynamic>;
        
                  if (roomData['password'] == password) {
                    // Password is correct, join the room
                    // ...
        
                    var user2Ref=roomRef.child('users').child('${widget.userId}');
                    
        
                    final snapshot = await user2Ref.once();
        
                    final user2Exists = snapshot.snapshot.value!=null;
                    if(!user2Exists)  {
                      final user2 = RoomUser(name: '${widget.userId}', joinedAt: DateTime.now(),cup_is_up: "No",drinking: "No",filling: "No");
                      await roomRef.child('users').child('${widget.userId}').set({
                          //user2.toMap()
                          'name': widget.userId,
                          'joinedAt': DateTime.now().toUtc().toString(),
                          'Filling':'No',
                          'Cup is up':'No',
                          'Drinking':'No',
                          'token' : pushToken,
                      }
                      );
                    }
        
                    Navigator.push(context, MaterialPageRoute(builder: (context) => RoomScreen(roomName: roomName, userId: '${widget.userId}',server: widget.server,song_path: widget.song_path,duration_value: widget.duration_value,)));
        
                  } else {
                    // Password is incorrect, show an error message
                    ScaffoldMessenger.of(context).showSnackBar(
                      SnackBar(
                        content: Text('Incorrect password'),
                        duration: Duration(seconds: 2),
                      ),
                    );
                  }
                },
                child: Text('Join Room'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}