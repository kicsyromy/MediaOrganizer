# MediaOrganizer
An application that helps organize and sort TV Shows and movies according to available information from dedicated sites such as TV.com, TheTVDB.com, etc.

It is meant to run on all three major platforms (Windows, OS X, Linux).

Currently the project is on a veary early state. Current development is focused on implementing low-level infrastructure (libMO):
- video playback using a cross platform solution (VLC) - implemented
- file navigation - partially implemented
- backend loading for different metadata sources - not yet implemented
- TDB

The UI is to be implemented using native controls for each platform and one cross-platform solution (Qt).

The project is built using CMake. Build dependencies are:
  - glib
  - gobject
  - libvlc 
  - + all their dependencies
  
This repository serves, currently, mostly as a test-bend for different technologies, frameworks, programming languages, etc.

All/any of this information is subject to change at any time.
