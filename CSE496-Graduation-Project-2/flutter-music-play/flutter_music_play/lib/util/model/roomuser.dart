
class RoomUser {
  final String name;
  final DateTime joinedAt;
  final String cup_is_up;
  final String filling;
  final String drinking;

  RoomUser({required this.name, required this.joinedAt,
            required this.cup_is_up,required this.filling,required this.drinking});

  factory RoomUser.fromMap(Map<Object?, Object?> map) {
    return RoomUser(
      name: map['name'] as String,
      joinedAt: DateTime.parse(map['joinedAt'] as String),
      cup_is_up: map['Cup is up'] as String,
      filling: map['Filling'] as String,
      drinking: map['Drinking'] as String
    );
  }

  Map<Object?, Object?> toMap() {
    return {
      'name': name,
      'joinedAt': joinedAt.toUtc().toString(),
      'Cup is up':cup_is_up,
      'Drinking':drinking,
      'Filling':filling
    };
  }
}
