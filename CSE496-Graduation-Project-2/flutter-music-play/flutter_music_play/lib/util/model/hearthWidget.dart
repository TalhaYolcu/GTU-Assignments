  import 'package:flutter/material.dart';
  
  
  class HeartWidget extends StatelessWidget {
    final String text;
    final Function onPressed;

    const HeartWidget({super.key, required this.text, required this.onPressed}); 

      @override
  Widget build(BuildContext context) {
    return InkWell(
      onTap: onPressed as void Function()?,
      child: SizedBox(
        width: 125,
        height: 125,
        child: CustomPaint(
          painter: HeartPainter(),
          child: Padding(
            padding: const EdgeInsets.only(top: 8),
            child: Center(
              child: Text(
                text,
                style: const TextStyle(
                  fontSize: 11,
                  fontWeight: FontWeight.bold,
                  color: Colors.white,
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
  }



class HeartPainter extends CustomPainter {
    @override
    void paint(Canvas canvas, Size size) {
      Paint paint = Paint();
      paint
        ..color = Colors.black
        ..style = PaintingStyle.stroke
        ..strokeCap = StrokeCap.round
        ..strokeWidth = 4;

      Paint paint1 = Paint();
      paint1
        ..color = Colors.red
        ..style = PaintingStyle.fill
        ..strokeWidth = 0;

      double width = size.width;
      double height = size.height;

      Path path = Path();
      path.moveTo(0.5 * width, height * 0.35);
      path.cubicTo(0.2 * width, height * 0.1, -0.25 * width, height * 0.6,
          0.5 * width, height);
      path.moveTo(0.5 * width, height * 0.35);
      path.cubicTo(0.8 * width, height * 0.1, 1.25 * width, height * 0.6,
          0.5 * width, height);

      canvas.drawPath(path, paint1);
      canvas.drawPath(path, paint);
    }

    @override
    bool shouldRepaint(CustomPainter oldDelegate) {
      return true;
    }
  }