import 'package:audioplayers/audioplayers.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter/material.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:flutter_music_play/util/constants.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

import '../main.dart';

class TestNotificationScreen extends StatefulWidget {
  const TestNotificationScreen({super.key});

  @override
  State<TestNotificationScreen> createState() => _TestNotificationScreenState();
}



class _TestNotificationScreenState extends State<TestNotificationScreen> {

  String firebaseToken="";
  TextEditingController textEditingController=TextEditingController();

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    FirebaseMessaging.onMessage.listen((RemoteMessage message) {
      RemoteNotification? notification = message.notification;
      AndroidNotification? androidNotification = message.notification?.android;
      print("Notification arrived");
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
  void dispose() {
    // TODO: implement dispose
    textEditingController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    FirebaseMessaging.instance.getToken().then((value) {
      print("Firebase token is: ");
      print(value);
      firebaseToken=value!;
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
          const SizedBox(
            height: 75,
          ),
          ElevatedButton(onPressed: () {sendNotificationToOther();} , child: const Text("Send Notification")),
          SizedBox(height: 10,),
          TextField(controller: textEditingController,)

        ]
    ))));
  }
  void sendNotificationToOther() async{
    String oppositeToken = textEditingController.text;

    /*header : 
    Content-Type : application/json
    Authorization : key=ServerKey

    */

    /*
    body :
    "to" : "oppositefirebasekey",
    "notification" : {
      "body" : "Body",
      "title" : "title",
      "subtitle" : "subtitle"
    }
    */

    //url : 

    var url = Uri.parse(firebaseApiUrl); // Replace with your API endpoint
    var body = json.encode({
      "to" : oppositeToken,
      "notification" : {
        "body" : "Body",
        "title" : "title",
        "subtitle" : "subtitle"        
      }
    });
    var header = {
      "Content-Type" : "application/json",
      "Authorization" : fcmServerKey
    };
    var response = await http.post(url, body: body,headers:header);

    if (response.statusCode == 200) {
      // Request was successful
      var responseBody = response.body;
      // Process the response data here
      print(responseBody);
    } else {
      // Request failed
      print('Request failed with status: ${response.statusCode}');
    }
  }
}