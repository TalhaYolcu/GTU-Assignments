
import 'package:flutter/material.dart';

class BluetoothData {
  String incomingData;
  bool filling=false;
  bool updown=false;
  bool drinkstate=false;

  void parseIncomingData() {
    final str = incomingData; // example string
    final parts = str.split(' '); // split the string into parts using space as the delimiter
    final values = parts.map((part) => part == '1'); // convert each part to a boolean value
    
    // use the boolean values as needed
    filling = values.elementAt(0);
    updown = values.elementAt(1);
    drinkstate = values.elementAt(2);
    /*
    print('First value: $filling'); 
    print('Second value: $updown');
    print('Third value: $drinkstate');
    */
  }

  BluetoothData({required this.incomingData});
}