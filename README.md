# Computer Graphics
Implementing basic computer graphics algorithms in C++ using QT framework for GUI and OpenGL for implementing algorithms.

## ABSTRACT:
This is a computer graphics project in which an application is made to study working of various algorithms. All these algorithms are for how to make basic geometry shape using point plotting technique on the display screen. A computer screen is assumed to be made up of grid like structure in which points can be plotted on the intersection of the lines only.  This grid is assumed to be made of large number of horizontal and vertical lines. The base of all the algorithm is to plot the point on the intersection such that it seems like a continuous geometry object. So, the principle of any object drawing algorithm is to check where to plot the point to draw a continuous object.

## OVERVIEW OF THE APPLICATION:

![Application Screenshot](https://github.com/nadeshseen/qt_opengl/blob/master/Screenshot/Screenshot_20181031_173517.png)

Fig.(2.1) – QT OpenGL Main Window

### Application Structure:
  •	Menu Bar
  •	Tool Bar
  •	OpenGL Widget
  •	Main Window Widget

### Code Structure:

![Project Files](https://github.com/nadeshseen/qt_opengl/blob/master/Screenshot/Screenshot_20180916_110205.png)

Fig.(2.2) – Project Files

### Application Modifications

The whole application is modified using Qt framework. In the earlier version, application is made using the GLUT library. In the modified version, application uses Qt framework to create a ‘Main Window’ which contains the ‘OpenGL Window’. It contains static menu which is always visible unlike earlier version which has to be accessed using right click.

### Major UI Modifications:
  •	Qt Color Dialog Box is used to pick colors which provides number of different options. Earlier, fixed number of colors were defined in the color class

![QColor Dialog Box](https://github.com/nadeshseen/qt_opengl/blob/master/Screenshot/Screenshot_20180916_103146.png)

Fig.(2.3) – QColor Dialog Box

  •	Thickness and Pattern are also selected using a dialog in which the options are limited as they defined at the backend by the programmer.

![Thickness Dialog Box](https://github.com/nadeshseen/qt_opengl/blob/master/Screenshot/Screenshot_20180916_103225.png&s=200)

Fig.(2.4) – Thickness Dialog Box          

![Pattern Dialog Box](https://github.com/nadeshseen/qt_opengl/blob/master/Screenshot/Screenshot_20180916_103300.png&s=200)

 Fig.(2.5) – Pattern Dialog Box
 
 
### Major Functionality Modifications:
•	Objects are stored at the backend. 
•	Properties of each object is stored. 
•	Object can be deleted and restored with all its properties. 
•	Objects can be undone and redone. 
•	Shortcuts are added for frequently used operations. 
•	Objects can be selected and properties of that object can be edited. 
•	Resizing the window does not affect the properties of the objects created. 

### Data Structures Used:
• Vectors
• Array
• Structure
• Classes
• Matrix
