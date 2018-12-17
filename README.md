# TopDownMultiplayer
This is a Top-Down Multiplayer Template written using C++ and Blueprint for use as a starting point in any Unreal Engine 4 projects.

Current Engine Version of this project : 4.20.3

For the current state of this project visit : https://github.com/Kriptikz/TopDownMultiplayer/projects/1

# What is the goal of this template?
  This template was created so people can easily get a Top-Down camera perspective and use it to control and command a unit in a multiplayer environment where the server is authoritative. In order to achieve this, I am using a simple command system where the PlayerController has different RPC's you can use to send these commands to the proper place; You can have commands run only on this client, run only on the server, or run on the server and all clients. Some commands will already be added and these include: MoveToLocation, MoveToActor, Attack, and Interact.
  For the camera I have two options:
  1.) Use the one on each Character and move it around as necessary.
  2.) Create a very simple actor with a SpringArm and Camera component and move it around as necessary.
  
  Option #2 seems like it will be easier to control in a lot of different ways so I will use it for the template. One problem is if the Character gets destroyed where will the Camera be? I can also easily create a spectator and can use the same Camera.

# How to use this template?
-
