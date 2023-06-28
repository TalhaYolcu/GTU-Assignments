
import 'dart:math';
import 'dart:typed_data';

import 'package:audioplayers/audioplayers.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_background_service/flutter_background_service.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';

import '../main.dart';
import '../util/btdata.dart';
import '../util/constants.dart';
import '../util/model/hearthWidget.dart';
import '../util/song.dart';
import 'settings.dart';
import 'insideroomscreen.dart';
import 'joinroomscreen.dart';


class MyHomePage extends StatefulWidget {
  MyHomePage({super.key, required this.server,required this.song_path,required this.duration_value});
  final BluetoothDevice server;
  String song_path;
  String duration_value;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  String fillingstr = 'Empty';
  String updownstr = 'Down';
  String drinkstr = 'Not drinking';
  String roomText = "";
  String userIdText = "";
  String pushToken = "";
  //final service = FlutterBackgroundService();
  

  TextEditingController roomtextController = TextEditingController();
  TextEditingController userIdController = TextEditingController();
  final player = AudioPlayer();


  final FirebaseDatabase referencedatabase = FirebaseDatabase.instanceFor(
      app: Firebase.app(), databaseURL: firebaseDatabaseUrl);

  @override
  void dispose() {
    super.dispose();
    roomtextController.dispose();
    userIdController.dispose();
  }

  @override
  void initState() {
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
        title: const Text("Valentine's Cup"),
      ),
      body: Padding(
        padding: const EdgeInsets.all(15.0),
        child: SingleChildScrollView(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          const SizedBox(
            height: 75,
          ),
          const Image(
            image: AssetImage('assets/images/mugs.png'),
            width: 120,
            height: 120,
          ),
          const SizedBox(
            height: 50,
          ),
          TextField(
              controller: userIdController,
              decoration: const InputDecoration(labelText: "Username",labelStyle: TextStyle(color: Colors.red))),
          const SizedBox(
            height: 5,
          ),
          TextField(
              controller: roomtextController,
              decoration: const InputDecoration(
                  labelText: "A room number to join/create",labelStyle: TextStyle(color: Colors.red))),
          const SizedBox(
            height: 10,
          ),
          HeartWidget(
            onPressed: roomEntered, text: 'Create/Join Room'
          ),

          const SizedBox(
            height: 20,
          ),
        ],
      ),
        ),
      ),
    );
  }

  void roomEntered() {
    setState(() {
      roomText = roomtextController.text;
      userIdText = userIdController.text;
    });
    searchforRooms();
  }

  String _generatePassword() {
    // Generate a random 6-digit numeric password
    final random = Random();
    return random.nextInt(999999).toString().padLeft(6, '0');
  }

  void searchforRooms() async {
    Logger.log(Logger.logLevel,"Room name:" + roomText);
    Logger.log(Logger.logLevel,"User Id:" + userIdText);

    try {
      final roomRef = referencedatabase.ref('rooms').child(roomText);

      final snapshot = await roomRef.once();
            Logger.log(Logger.logLevel,"End of func");

      final roomExists = snapshot.snapshot.value != null;
      if (roomExists) {
        Logger.log(Logger.logLevel,'Room Exists');

        //check room is locked or not

        final snapshot = await roomRef.once();
        final roomData = snapshot.snapshot.value as Map<dynamic, dynamic>;
        if (roomData['isLocked']) {
          Logger.log(Logger.logLevel,'Room is locked');
          // Room is locked, show an error message and return to the previous screen
          ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(
              content: Text('This room is full'),
              duration: Duration(seconds: 2),
            ),
          );
        } else {
          Logger.log(Logger.logLevel,'Joining to the room $roomText');
          Navigator.push(
              context,
              MaterialPageRoute(
                  builder: (context) => JoinRoomPasswordScreen(
                      roomName: roomText, userId: userIdText,server:widget.server,song_path:widget.song_path,duration_value:widget.duration_value)));
        }
      } else {
        Logger.log(Logger.logLevel,'Room does not exists');
        // Room does not exist, create a new room and generate a password
        final password = _generatePassword();
        await roomRef.set({
          'password': password,
          'createdAt': DateTime.now().toUtc().toString(),
          'isLocked': false,
          'users': {
            // Add the first user who created the room
            userIdText: {
              'name': userIdText,
              'joinedAt': DateTime.now().toUtc().toString(),
              'Filling': 'No',
              'Cup is up': 'No',
              'Drinking': 'No',
              'token' : pushToken,
            },
          },
        });
        Navigator.push(
            context,
            MaterialPageRoute(
                builder: (context) =>
                    RoomScreen(roomName: roomText, userId: userIdText,server:widget.server,song_path:widget.song_path,duration_value:widget.duration_value)));
      }
    } catch (ex) {
      Logger.log(Logger.logLevel,'EXX');
      Logger.error(ex.toString());
    }
  }
}
