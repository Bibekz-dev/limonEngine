# LimonEngine

LimonEngine is a 3D first person shooter engine, developed as a hobby, to acquire a deeper knowledge of 3D game engine programming. 

It can load a wide variety of models and skeletal animations thanks to Assimp, has realtime directional and point lights/shadows and physics.

You can extend the engine capabilities using exposed API, and design maps using the build-in map designer.

You can check out the [project web site](http://enginmanap.github.io/limonEngine/status.html) 

For a demonstration, check out the video :

[![Limon Engine New map and Editor](http://img.youtube.com/vi/2rBYDD6Z52Q/0.jpg)](https://youtu.be/2rBYDD6Z52Q)


##Building

Dependencies can be installed on Ubuntu 17.10 using:

sudo apt-get install libassimp-dev libbullet-dev libsdl2-dev libsdl2-image-dev libfreetype6-dev libtinyxml2-dev libglew-dev build-essential libglm-dev libtinyxml2-dev

After that, in repository directory
mkdir build
cd build
cmake ../


##Running

### Start up: 
- Engine take a parameter as path of world to load
- If no parameter passed, falls back to /Data/Maps/World001.xml
Note: Save map button in editor mode saves the map to /Data/Maps/CustomWorld001.xml

### In Application:
- Pressing 0 switches to debug mode, renders physics collision meshes and disconnects player from physics ( flying and passing trough objects)
- Pressing " key switches to editor mode, which allows creating maps.
- Pressing + and - changes mouse sensitivity.
- wasd for walking around and mouse for looking around as usual.

### In editor mode:
- Since static and dynamic objects are not generated by same logic, mass settings can't be changed after object creation.
- In animate objects are not allowed to have AI
- You can create animations for doors etc. in editor. For animation creation, time step is 60 for each second.
- When a new animation is created by animation editor, the object used to create the animation assumed to have this animation. You can remove by using the remove animation button.

### Extending with C++
- Engine tries to load custom trigger extentions as "libcustomTriggers.dll" for windows and "libcustomTriggers.so" for linux. If you use a custom action in a map and library is missing, action won't run check this first.
- Custom actions should implement TriggerInterface class.
- and the list of actions should be returned with method "void registerAsTrigger(std::map<std::string, TriggerInterface*(*)(LimonAPI*)>* triggerMap);", sample implementation in CoinPickUpOnTrigger
- If you query a variable that never been set, it will be returned as 0.
- Static values are saved when set in editor, other action results and variables are queried when action runs.