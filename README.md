# TopDownMultiplayer
This is a Top-Down Multiplayer Template written using C++ and Blueprint for use as a starting point in any Unreal Engine 4 projects.

Current Engine Version of this project : 4.20.3

For the current state of this project visit : https://github.com/Kriptikz/TopDownMultiplayer/projects/1

# What is the goal of this template?
This template was created so people can easily get a Top-Down camera perspective and use it to control and command a unit in a multiplayer environment where the server is authoritative. In order to achieve this, when the TDMPlayerController recieves input on the client it sends an RPC to the server version of the TDMPlayerController and it sends the current mouse world position so the server can do the tracing. For movement we use our TDMPlayerController to tell our characters TDMAIController where we want to move and it AI does the pathfinding. The idea originated here: https://answers.unrealengine.com/questions/34074/does-ue4-have-client-side-prediction-built-in.html

# How to use this template?
-
