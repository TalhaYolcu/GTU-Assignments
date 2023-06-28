import 'dart:io';
import 'dart:math';
import 'package:audioplayers/audioplayers.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_background_service/flutter_background_service.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:flutter_music_play/screens/settings.dart';
import 'package:flutter_music_play/screens/insideroomscreen.dart';
import 'package:flutter_music_play/screens/joinroomscreen.dart';
import 'package:flutter_music_play/screens/testNotificationScreen.dart';
import 'package:flutter_music_play/util/back_services.dart';
import 'package:flutter_music_play/util/btdata.dart';
import 'package:flutter_music_play/util/model/hearthWidget.dart';
import 'package:just_audio_background/just_audio_background.dart';
import 'package:permission_handler/permission_handler.dart';
import 'util/song.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_messaging/firebase_messaging.dart';
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'util/constants.dart';

//notificationchannel
const AndroidNotificationChannel channel = AndroidNotificationChannel(
    'high_importance_channel', //id
    'High Importance Notifications', //title
    description: 'This channel is used for important notifications.',
    importance: Importance.high,
    playSound: true);

final FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin =
    FlutterLocalNotificationsPlugin();

//initialize firebase when notification is received in background
Future<void> _firebaseMessagingBackgroundHandler(RemoteMessage message) async {
  await Firebase.initializeApp();
  Logger.log(Logger.logLevel,'A bg message just showed up : ${message.messageId}');

}

Future<void> requestPermissions() async {
  final permissionStatus = await Permission.bluetooth.status;
  if (permissionStatus.isGranted) {
    // Permission already granted, you can proceed with Bluetooth functionality
  } else {
    // Permission not granted, you need to request it
    requestBluetoothPermission();
  }
  final statLoc1 = await Permission.locationAlways.status;
  if(statLoc1.isGranted) {
    
  }
  else {
    requestLocationPermission();
  }

  final statLoc2 = await Permission.bluetoothScan.status;
  if(statLoc2.isGranted) {
    requestScanPermission();
  }
  else {

  }  
  final statLoc3 = await Permission.manageExternalStorage.status;
  if(statLoc3.isGranted) {
    
  }
  else {
    requestExternalStoragePermission();
  }  
  final statLoc4 = await Permission.bluetoothConnect.status;
  if(statLoc4.isGranted) {

  }
  else {
    requestConnectPermission();
  }  
  final statLoc5 = await Permission.bluetoothAdvertise.status;
  if(statLoc5.isGranted) {

  }
  else {
    requestAdvertisePermission();
  }    
}

void requestConnectPermission() async {
  final permissionStatus = await Permission.bluetoothConnect.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }  
}
void requestBluetoothPermission() async {
  final permissionStatus = await Permission.bluetooth.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }
}
void requestExternalStoragePermission() async {
  final permissionStatus = await Permission.manageExternalStorage.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }  
}
void requestScanPermission() async {
  final permissionStatus = await Permission.bluetoothScan.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }  
}
void requestLocationPermission() async {
  final permissionStatus = await Permission.locationAlways.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }  
}
void requestAdvertisePermission() async {
  final permissionStatus = await Permission.bluetoothAdvertise.request();
  if (permissionStatus.isGranted) {
    // Permission granted, you can proceed with Bluetooth functionality
  } else {
    // Permission denied, handle accordingly
  }  
}

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await JustAudioBackground.init(
    androidNotificationChannelId: 'com.ryanheise.bg_demo.channel.audio',
    androidNotificationChannelName: 'Audio playback',
    androidNotificationOngoing: true,
  );

  try {
    final notificationDenied = await Permission.notification.isGranted;
    if(notificationDenied!=true) {
      await Permission.notification.request();
    }
    
    final externalStorageDenied = await Permission.manageExternalStorage.isGranted;
    if (externalStorageDenied!=true) {
      await Permission.manageExternalStorage.request();
    }

    final locationDenied = await Permission.locationAlways.isGranted;
    if (locationDenied!=true) {
      await Permission.locationAlways.request();
    }

    final bluetoothScanDenied = await Permission.bluetoothScan.isGranted;
    if (bluetoothScanDenied!=true) {
      await Permission.bluetoothScan.request();
    }

    final bluetoothDenied = await Permission.bluetooth.isGranted;
    if (bluetoothDenied!=true) {
      await Permission.bluetooth.request();
    }

    final bluetoothConnectDenied = await Permission.bluetoothConnect.isGranted;
    if (bluetoothConnectDenied!=true) {
      await Permission.bluetoothConnect.request();
    }

    final bluetoothAdvertiseDenied = await Permission.bluetoothAdvertise.isGranted;
    if (bluetoothAdvertiseDenied!=true) {
      await Permission.bluetoothAdvertise.request();
    }
    if(await Permission.audio.isGranted!=true) {
      await Permission.audio.request();
    }
    if(await Permission.notification.isGranted!=true) {
      await Permission.notification.request();
    
    }
  }
  catch(ex) {
    print(ex.toString());
  }


  
  

 
  /*await initializeService();
  final service = FlutterBackgroundService();
  bool isRunning = await service.isRunning();

  if(isRunning) {
    service.startService();    
  }
  */
  //init firebase
  await Firebase.initializeApp();

  //handle in background
  FirebaseMessaging.onBackgroundMessage(_firebaseMessagingBackgroundHandler);

  await flutterLocalNotificationsPlugin
      .resolvePlatformSpecificImplementation<
          AndroidFlutterLocalNotificationsPlugin>()
      ?.createNotificationChannel(channel);

  await FirebaseMessaging.instance.setForegroundNotificationPresentationOptions(
      alert: true, badge: true, sound: true);

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Valentine\'s Cup',
      theme: ThemeData(
        primarySwatch: Colors.red,
        visualDensity: VisualDensity.adaptivePlatformDensity
      ),
      home: MainScreen(),
    );
  }
}

class MainScreen extends StatefulWidget {
  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  @override
  Widget build(BuildContext context) {
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
            height: 75,
          ),
          ElevatedButton(onPressed: () {gotoBluetoothSettings(context);} , child: const Text("See Bluetooth Settings to start Drink Coffee")),
          const SizedBox(height: 10,),
          //ElevatedButton(onPressed:() {gotoDebug(context);}, child: const Text("Test Notification")),
        ]
    ))));
  }
  void gotoBluetoothSettings(BuildContext context) {
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) {
          return BTScanScreen();
        }
      ));
  }
  void gotoDebug(BuildContext context) {
    Navigator.of(context).push(
      MaterialPageRoute(
        builder: (context) {
          return const TestNotificationScreen();
        }
      ));    
  }
}