# Units view count
This is a test project for a job interview. 

The task is: there is a 2D plane with units on it. Units can see at a certain distance and in a certain sector, the program has to calculate for each unit how many other units can it see.
## How to build
```
mkdir build && cd build
cmake ../
cmake --build .
```
To build this project you need to have a `cmake`. If you are using Windows, you should also have `pthreads` library installed.
## How to use
You can use file to provide input data. The file has to be in the following format:
```
[Number of units]
[View distance]
[View sector in degrees]
[Posision1 x] [Posision1 y]
[View direction1 x] [View direction1 y]
 ...
[PosisionN x] [PosisionN y]
[View directionN x] [View directionN y]
```
To use a file simply pass its path as an argument to the executable:
```
unitsViewCount.exe [filepath]
```
This repository has three files that can be used as a test: `test.txt`, `test2.txt` and `test3.txt`
If no file was given, all the data would be randomized.
## Program structure
### radVector
This class represents a radius vector in 2D space.
### unit
This class represents a unit in 2D space. It has a method `bool isInView(radVector point)` that is used to calculate if the unit can see the `point` (i.e another unit with position `point`). It calculates the vector between unit and point (`position - point`) and then checks whether it satisfies these two criteria:
- The vector's length is less than the unit's view distance
- The angle between the vector and unit's view direction is less than the unit's view angle (view angle is half of the unit's view sector)

### main
The main function is in testProj.cpp. It takes all units and then checks for each of them if it can see each other unit. Algorithm complexity is N^2, where N is the number of units.
