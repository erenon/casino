#Casino::UNO

This is a multiplayer UNO card game based on the client-server architecture written in C++ and JavaScript. The following keywords are related in the current state of the project: C++, JavaScript, node.js, HTML5, CSS3, Socket.IO, publish-subscribe. A few may follow later: Java, Andriod, OpenGL.

Currently there are no easily accessible working versions of the game, however, there are such versions buried deep in the history.

##Directory Structure
The v0.2 branch has a brand new structure as follows:

- docs
- server - acts as a separate npm module
  - lib - server related js files and link to the compiled addon
  - addon - C++ resources
- client-browser - acts as separate npm module, files related to the client are here
