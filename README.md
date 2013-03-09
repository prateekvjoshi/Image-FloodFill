# Flood Fill

This code implements OpenCV based flood fill. This algorithm finds the connected pixels around a point and colors that region. I have included a sample input image (inputImage.jpg) along with this project. When you run the program, a window will pop up. You can select a point with your mouse on that window and the surrounding connected region will be colored. There is a file called "CMakeLists.txt". This file will be used to build the project (if you have built OpenCV using cmake). If not, just use the .cpp file in your project and build it. To build using command line, follow the steps below to get it up and running:

	$ cmake .
	$ make
	$ ./main 

The output will be displayed on a window and you can see the objects inside the image being colored.