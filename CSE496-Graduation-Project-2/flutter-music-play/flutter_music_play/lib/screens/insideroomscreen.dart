

import 'dart:async';
import 'dart:convert';
import 'dart:io';
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
import '../util/constants.dart';
import '../util/model/roomuser.dart';
import 'package:flutter/widgets.dart';
import 'package:http/http.dart' as http;



class _Message {
  int whom;
  String text;

  _Message(this.whom, this.text);
}

class RoomScreen extends StatefulWidget {
  final String roomName;
  final String userId;
  BluetoothDevice server;
  String song_path;
  String duration_value;
  RoomScreen({required this.roomName, required this.userId,required this.server,required this.song_path,required this.duration_value});

  @override
  _RoomScreenState createState() => _RoomScreenState();
}

class _RoomScreenState extends State<RoomScreen> {
  FirebaseDatabase referencedatabase = FirebaseDatabase.instanceFor(
    app: Firebase.app(),databaseURL: firebaseDatabaseUrl
  );

  late DatabaseReference roomRef;
  late StreamSubscription roomSubscription;
  static final clientID = 0;
  BluetoothConnection? connection;

  List<_Message> messages = List<_Message>.empty(growable: true);
  String _messageBuffer = '';

  final TextEditingController textEditingController = new TextEditingController();

  bool isConnecting = true;
  bool get isConnected => (connection?.isConnected ?? false);

  bool isDisconnecting = false;

  String _lastMessage=' ';
  int receivedDistance=0;
  String cupStatus = "DOWN";
  bool firstMessageSent=false;
  final player = AudioPlayer();
  //final service = FlutterBackgroundService();

  Future<void> onBackgroundMessage(RemoteMessage message) async {
      playSongWithDuration(widget.song_path, Duration(seconds: int.parse(widget.duration_value)));
  }

  @override
  void initState() {
    super.initState();







    FirebaseMessaging.onBackgroundMessage(onBackgroundMessage);

    FirebaseMessaging.onMessage.listen((RemoteMessage message) {
      RemoteNotification? notification = message.notification;
      AndroidNotification? androidNotification = message.notification?.android;
      print("Notification arrived!");
      playSongWithDuration(widget.song_path, Duration(seconds: int.parse(widget.duration_value)));

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
      playSongWithDuration(widget.song_path, Duration(seconds: int.parse(widget.duration_value)));

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




    BluetoothConnection.toAddress(widget.server.address).then((_connection) {
      print('Connected to the device');
      connection = _connection;
      setState(() {
        isConnecting = false;
        isDisconnecting = false;
      });
    
      connection!.input!.listen(_onDataReceived).onDone(() {
        // Example: Detect which side closed the connection
        // There should be `isDisconnecting` flag to show are we are (locally)
        // in middle of disconnecting process, should be set before calling
        // `dispose`, `finish` or `close`, which all causes to disconnect.
        // If we except the disconnection, `onDone` should be fired as result.
        // If we didn't except this (no flag set), it means closing by remote.
        if (isDisconnecting) {
          print('Disconnecting locally!');
        } else {
          print('Disconnected remotely!');
        }
        if (this.mounted) {
          setState(() {});
        }
      });
    }).catchError((error) {
      print('Cannot connect, exception occured');
      print(error);
    });


    try {
      roomRef = referencedatabase.ref('rooms').child(widget.roomName);


      // Listen for changes to the room data
      roomSubscription = roomRef.onValue.listen((event) async {
        if(this.mounted) {
          final roomData = event.snapshot.value as Map<dynamic, dynamic>;
          print("Room data has been converted to map");
          final usersData = roomData['users'] as Map<dynamic,dynamic>;
          final users = usersData.entries.map((entry) => RoomUser.fromMap(entry.value)).toList();

          if (users.length==2) {
            // Room is full, lock the room
            roomRef.update({'isLocked': true});
          }
        }

      });
    }
    catch(ex) {
      print(ex);
    }
  }

  @override
  void dispose() {
    // Clean up the room subscription

    

    roomSubscription.cancel();
        // Avoid memory leak (`setState` after dispose) and disconnect
    if (isConnected) {
      isDisconnecting = true;
      connection?.dispose();
      connection = null;
    }
    textEditingController.dispose();
    messages.clear();
    roomRef.remove();
    
    super.dispose();
  }
  
  Future<bool> _onWillPop() async {
       return (await showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Are you sure?'),
        content: const Text('Do you want to exit?'),
        actions: <Widget>[
          TextButton(
            onPressed: () => Navigator.of(context).pop(false),
            child: const Text('No'),
          ),
          TextButton(
            onPressed: sendBeforeExit ,
            child: const Text('Yes'),
          ),
        ],
      ),
    )) ?? false; 
  }

  @override
  Widget build(BuildContext context) {
      final serverName = widget.server.name ?? "Unknown";

      if(!firstMessageSent && isConnected) {
        try {
          _sendMessage('+');

          firstMessageSent=true;
        }
        catch(ex) {
          print(ex.toString());
        }
      }


    return WillPopScope(
      onWillPop: _onWillPop,
      child: Container(
        child: Scaffold(
          appBar: AppBar(
            title: Text(widget.roomName),
          ),
          body: Container(
            child: StreamBuilder(
              stream: roomRef.child('users').onValue,
              builder: (context, snapshot) {
                if (snapshot.hasData) {
                  
                  try {
                  final usersData = snapshot.data!.snapshot.value as Map<dynamic, dynamic>;
            
                  final users = usersData.entries.map((entry) => RoomUser.fromMap(entry.value)).toList();
            
                  if (users.isEmpty) {
                    // Room is empty, remove the room
                    roomSubscription.cancel();
                    roomRef.remove();
                    Navigator.pop(context);
                    return SizedBox.shrink();
                  }
                  else {
                    try {
                      return Column(
                        children: [
                          SizedBox(height: 20,),
                          Column(
                            mainAxisAlignment: MainAxisAlignment.start,
                            children: [
                              ElevatedButton(onPressed: seeRoomPassword, child: const Text("See Room Password")),
                            ],
                          ),                  
                          const SizedBox(height: 16),
                          Text('You are ${widget.userId}'), // display the current user's ID
                          const SizedBox(height: 16),
                          Text('Your cup is: $cupStatus'),
                          const SizedBox(height: 3,),
                          Container(
                            child: Expanded(
                              child: ListView.builder(
                              itemCount: users.length,
                              itemBuilder: (context, index) {
                                return ListTile(
                                  title: Text("User "+users[index].name+" 's info:"),
                                  subtitle: Column(
                                    children: [
                                      const SizedBox(height: 2,),
                                      Text("Joined at:${users[index].joinedAt}"),
                                      const SizedBox(height: 3,),
                                      Text("Filling:${users[index].filling}"),
                                      const SizedBox(height: 3,),
                                      Text("Cup is up:${users[index].cup_is_up}"),
                                      const SizedBox(height: 3,),
                                      Text("Drinking:${users[index].drinking}"),
                                      const SizedBox(height: 3,),
                                            
                                    ],
                                  ),
                                  
                                );
                              },
                            ) 
                            ),
                          ),
                  
                        ],
                      ) ;
                      }
                      catch(ex) {
                        print("Error on catch"+ex.toString());
                      }
                      return Column(
                        children: [
                          SizedBox(height: 20,),
                          Column(
                            mainAxisAlignment: MainAxisAlignment.start,
                            children: [
                              ElevatedButton(onPressed: seeRoomPassword, child: const Text("See Room Password")),
                            ],
                          )
                        ]);
                        
                    }
                  }
                  catch(ex) {
                    print(ex.toString());
                    
                  }
                      return Column(
                        children: [
                          SizedBox(height: 20,),
                          Column(
                            mainAxisAlignment: MainAxisAlignment.start,
                            children: [
                              ElevatedButton(onPressed: seeRoomPassword, child: const Text("See Room Password")),
                            ],
                          )
                        ]);
                }
                else {
                  return const Center(
                    child: CircularProgressIndicator(),
                  );
                }
              },
            ),
          ),
        ),
      ),
    );
  }
  void sendBeforeExit() async {
    print("- Message is sending...");
    _sendMessage('-');
    print("- Message has been sent");
    Navigator.of(context).pop(true);
  }
  void _onDataReceived(Uint8List data) {
    print("Ondata received");
    // Allocate buffer for parsed data
    int backspacesCounter = 0;
    data.forEach((byte) {
      if (byte == 8 || byte == 127) {
        backspacesCounter++;
      }
    });
    Uint8List buffer = Uint8List(data.length - backspacesCounter);
    int bufferIndex = buffer.length;

    // Apply backspace control character
    backspacesCounter = 0;
    for (int i = data.length - 1; i >= 0; i--) {
      if (data[i] == 8 || data[i] == 127) {
        backspacesCounter++;
      } else {
        if (backspacesCounter > 0) {
          backspacesCounter--;
        } else {
          buffer[--bufferIndex] = data[i];
        }
      }
    }

    // Create message if there is new line character
    String dataString = String.fromCharCodes(buffer);
    int index = buffer.indexOf(13);
    if (~index != 0) {
      setState(() {
        messages.add(
          _Message(
            1,
            backspacesCounter > 0
                ? _messageBuffer.substring(
                    0, _messageBuffer.length - backspacesCounter)
                : _messageBuffer + dataString.substring(0, index),
          ),
        );
        _messageBuffer = dataString.substring(index);
      });
    } else {
      _messageBuffer = (backspacesCounter > 0
          ? _messageBuffer.substring(
              0, _messageBuffer.length - backspacesCounter)
          : _messageBuffer + dataString);
    }
    print("Last message : ");
    try {
      print(messages.last.text);
      _lastMessage=messages.last.text;
    }
    catch(ex) {
      print(ex.toString());
    }


    setState(() {
    try {
        if(_lastMessage.trim()=="UP") {
          if(receivedDistance==0) {
            makeCupIsUpStateOn();
          }
          receivedDistance=1;
          cupStatus="UP";
          
        }
        else if (_lastMessage.trim()=="DOWN" && receivedDistance==1) {
          if(receivedDistance==1) {
            makeCupIsUpStateOff();
            
          }
          receivedDistance=0;
           cupStatus="DOWN";
          
        }
    }
    catch (Ex) {
      print('Couldnt parse\n');
    }      
    });

    setState(() {

    });
  }
  void seeRoomPassword() async {
    roomRef = referencedatabase.ref('rooms').child(widget.roomName);

    final snapshot = await roomRef.once();
    final roomData = snapshot.snapshot.value as Map<dynamic, dynamic>;
    String roomPassword = roomData['password'];
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Room Password'),
        content:  SafeArea(
          child: Row(
            children: [
              Text('Room Password is : $roomPassword',style: const TextStyle(fontSize: 14),),
              IconButton(icon: const Icon(Icons.copy),onPressed:() {
                Clipboard.setData(ClipboardData(text:roomPassword));
                ScaffoldMessenger.of(context).showSnackBar(
                  const SnackBar(content: Text('Text copied to clipboard')),
                );              
              } ,iconSize:20),
            
            ],
          ),
        ) ,
        actions: <Widget>[
      TextButton(
        onPressed: () {
          Navigator.of(context).pop(); // Close the dialog
        },
        child: const Text('OK'),
      ),
        ],
      ),);
  }

  void _sendMessage(String text) async {
    print("Message send start");
    text = text.trim();
    textEditingController.clear();

    if (text.length > 0) {
      try {
        connection!.output.add(ascii.encode('+'));
        //connection!.output.add(Uint8List.fromList(utf8.encode(text + "\r\n")));
        await connection!.output.allSent;

      } catch (e) {
        // Ignore error, but notify state
        setState(() {});
      }
    }
    print("Message has been send");

  }
  void makeCupIsUpStateOn() async {
    try {
      var CupIsUp=referencedatabase.ref('rooms').child(widget.roomName).child("users").child(widget.userId).child("Cup is up");
      final snapshot = await CupIsUp.once();
      String newValue = "Yes";
      CupIsUp.set(newValue);

      
      //send notification here
      try {
        sendNotification();
      }
      catch(ex) {
        print(ex.toString());
      }
    }
    catch(ex) {
      print(ex);
    } 
  }
  void makeCupIsUpStateOff() async {
    try {
      var CupIsUp=referencedatabase.ref('rooms').child(widget.roomName).child("users").child(widget.userId).child("Cup is up");
      final snapshot = await CupIsUp.once();
      String newValue = "No";
      CupIsUp.set(newValue);
    }
    catch(ex) {
      print(ex);
    } 
  } 
  void sendNotification() async {
    String oppositeName = "";
    String oppositeToken = "";
    try {
      var usersRef = referencedatabase.ref('rooms').child(widget.roomName).child('users');

      final snapshot = await usersRef.once();
      if(snapshot!=null) {
        Map<dynamic,dynamic>? usersData = snapshot.snapshot.value as Map<dynamic, dynamic>?;
        usersData?.forEach((key, value) {
          if(value['name']!=widget.userId) {
            oppositeName = value['name'];
            oppositeToken = value['token'];
            
          }
        });
      }
      if(oppositeToken.isNotEmpty && oppositeName.isNotEmpty) {
          var url = Uri.parse(firebaseApiUrl); // Replace with your API endpoint
          var body = json.encode({
            "to" : oppositeToken,
            "notification" : {
              "body" : "Your valentine $oppositeName is drinking, would you?",
              "title" : "Valentine's Cup",
              "subtitle" : "Cup is moved"        
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
    catch(ex) {
      print(ex.toString());
    }


  }
  void onStop() async {
    await player.pause();
  }
  void playSongWithDuration(String path,Duration duration) async {
    /*if (!File(path).existsSync()) {
      print("Path does exists\n");
      return;
    }*/
    ByteData bytes = await rootBundle.load(path);
    Uint8List soundbytes =
        bytes.buffer.asUint8List(bytes.offsetInBytes, bytes.lengthInBytes);
    await player.playBytes(soundbytes);
    await Future.delayed(duration);
    onStop();    
  }
}