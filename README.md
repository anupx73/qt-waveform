# qt-waveform   
A demo of continuous wave draw using QT Widget. This is a R&D work based on personal interest and learning purpose. It is free to use in any opensource or commercial use.

## Code Brief  
The applicatin consist of main two classes: 

- SerialPort - Data generator class which runs in a thread. SerialPort generates data and emits a signal `dataAvailable` to notify the Widget. The slot implemented in Widget class raw data are enqued and gets copied to another queue for drawing. 

- Widget - The canvas where waveform is being drawn. A timer is fired from Widget c'tor to continuously fire `PaintEvent` to draws a small rectangle `clearRectWidth` at a time. This eliminates any flickering and continues with a smooth wave draw.

Rest the code is self explanatory and easy to follow.
