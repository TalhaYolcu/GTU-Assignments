import 'dart:async';
import 'dart:io';
import 'dart:math';
import 'dart:typed_data';

import 'package:audioplayers/audioplayers.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:flutter_music_play/main.dart';
import 'package:flutter_music_play/screens/selectbondeddevice.dart';
import 'package:flutter_music_play/screens/selectbondeddevice.dart';

import '../util/song.dart';
import 'discovery.dart';
import 'homepage.dart';


class BTScanScreen extends StatefulWidget {
  @override
  _BTScanScreenState createState() => _BTScanScreenState();
}

class _BTScanScreenState extends State<BTScanScreen> {
 BluetoothState _bluetoothState = BluetoothState.UNKNOWN;

  String _address = "...";
  String _name = "...";

  Timer? _discoverableTimeoutTimer;
  int _discoverableTimeoutSecondsLeft = 0;

  List<Song> songs = [
    Song(name: "A Man Without Love", path: "assets/sounds/Song1.mp3"),
    Song(name: "Alışamadım", path: "assets/sounds/Song2.mp3"),
    Song(name: "Aşk Bir Mevsim", path: "assets/sounds/Song3.mp3"),
    Song(name: "Careless Whisper", path: "assets/sounds/Song4.mp3"),
    Song(name: "Everything I Do", path: "assets/sounds/Song5.mp3"),
    Song(name: "Kumralım", path: "assets/sounds/Song6.mp3"),
    Song(name: "Something Stupid", path: "assets/sounds/Song7.mp3"),
    Song(name: "Romantic", path: "assets/sounds/Song8.mp3")         
  ];
  List<String>durations = [
    "5","6","7","8","9","10","11","12","13","14","15"
  ];

  String song_value = 'A Man Without Love';
  String duration_value = "5";
  String song_path = "assets/sounds/Song1.mp3";
  
  final player = AudioPlayer();

  //ekranları düzenle
  //veriyi al
  //veriyi server a gönder
  //renk kısmını serverdan al
  bool _autoAcceptPairingRequests = false;

  @override
  void initState() {
    super.initState();

    // Get current state
    FlutterBluetoothSerial.instance.state.then((state) {
      setState(() {
        _bluetoothState = state;
      });
    });

    Future.doWhile(() async {
      // Wait if adapter not enabled
      if ((await FlutterBluetoothSerial.instance.isEnabled) ?? false) {
        return false;
      }
      await Future.delayed(Duration(milliseconds: 0xDD));
      return true;
    }).then((_) {
      // Update the address field
      FlutterBluetoothSerial.instance.address.then((address) {
        setState(() {
          _address = address!;
        });
      });
    });

    FlutterBluetoothSerial.instance.name.then((name) {
      setState(() {
        _name = name!;
      });
    });

    // Listen for futher state changes
    FlutterBluetoothSerial.instance
        .onStateChanged()
        .listen((BluetoothState state) {
      setState(() {
        _bluetoothState = state;

        // Discoverable mode is disabled when Bluetooth gets disabled
        _discoverableTimeoutTimer = null;
        _discoverableTimeoutSecondsLeft = 0;
      });
    });
  }

  @override
  void dispose() {
    FlutterBluetoothSerial.instance.setPairingRequestHandler(null);
    _discoverableTimeoutTimer?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Bluetooth Menu'),
      ),
      body: Container(
        child: ListView(
          children: <Widget>[
            Divider(),
            ListTile(title: const Text('Bluetooth Settings')),
            SwitchListTile(
              title: const Text('Enable Bluetooth'),
              value: _bluetoothState.isEnabled,
              onChanged: (bool value) {
                // Do the request and update with the true value then
                future() async {
                  // async lambda seems to not working
                  if (value)
                    await FlutterBluetoothSerial.instance.requestEnable();
                  else
                    await FlutterBluetoothSerial.instance.requestDisable();
                }

                future().then((_) {
                  setState(() {});
                });
              },
            ),
            ListTile(
              title: ElevatedButton(
                  child: const Text('Scan Bluetooth Devices'),
                  onPressed: () async {
                        await Navigator.of(context).push(
                      MaterialPageRoute(
                        builder: (context) {
                          return DiscoveryPage(song_path: song_path,duration_value: duration_value,);
                        },
                      ),
                    );
                  }),
            ),
              ListTile(title: Text("Select song to be played when your valentine's cup is up")),
              SizedBox(
                height: 20,
              ),
              ListTile(
                title: SizedBox(
                  width: 240,
                  child: DropdownButtonHideUnderline(
                    child: DropdownButtonFormField<String>(
                      decoration: InputDecoration(
                          enabledBorder: OutlineInputBorder(
                              borderRadius: BorderRadius.circular(12),
                              borderSide:
                                  BorderSide(width: 2, color: Colors.red))),
                      value: song_value,
                      items: songs
                          .map((item) => DropdownMenuItem<String>(
                              value: item.name,
                              child: Text(
                                item.name,
                                style: TextStyle(fontSize: 15),
                              )))
                          .toList(),
                      onChanged: (item) {
                        setState(() {
                          song_value = item!;
                          String path = "";
                          for(int i =0;i<songs.length;i++) {
                            if(song_value==songs[i].name) {
                              path = songs[i].path;
                              break;
                            }
                          }
                          song_path=path;
                          playSongWithDuration(path,Duration(seconds: 5));
                          onStop();
                        });
                      },
                    ),
                  ),
                ),
              ),
              SizedBox(
                height: 10,
              ),    
              ListTile(title: Text("Select duration of song")),
              SizedBox(
                height: 20,
              ),
              ListTile(
                title: SizedBox(
                  width: 240,
                  child: DropdownButtonHideUnderline(
                    child: DropdownButtonFormField<String>(
                      decoration: InputDecoration(
                        border: OutlineInputBorder(
                              borderRadius: BorderRadius.circular(12),
                              borderSide:
                                  BorderSide(width: 2, color: Colors.red)),
                          enabledBorder: OutlineInputBorder(
                              borderRadius: BorderRadius.circular(12),
                              borderSide:
                                  BorderSide(width: 2, color: Colors.red))),
                      value: duration_value,
                      items: durations
                          .map((item) => DropdownMenuItem<String>(
                              value: item,
                              child: Text(
                                item,
                                style: TextStyle(fontSize: 15),
                              )))
                          .toList(),
                      onChanged: (item) {
                        setState(() {
                          duration_value = item!;
                        });
                      },
                    ),
                  ),
                ),
              ),                      
          ],
        ),
      ),
    );
  }
  void onStop() async {
    await player.pause();
  }

  void playSong(String path) async {
    /*if (!File(path).existsSync()) {
      print("Path does exists\n");
      return;
    }*/
    ByteData bytes = await rootBundle.load(path);
    Uint8List soundbytes =
        bytes.buffer.asUint8List(bytes.offsetInBytes, bytes.lengthInBytes);

    await player.playBytes(soundbytes);
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
    await Future.delayed(Duration(seconds: 5));
    onStop();    
  }



}
