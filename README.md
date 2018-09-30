# TopDownMultiplayer
This is a Top-Down Multiplayer Template written using C++ and Blueprint for use as a starting point in any Unreal Engine 4 projects.

Current Engine Version of this project : 4.20.3

# What is the goal of this template?
This template was created so people can easily get a Top-Down camera perspective and use it to control and command a unit in a multiplayer environment where the server is authoritative. In order to achieve this, when the TDMPlayerController recieves input on the client it sends an RPC to the server version of the TDMPlayerController and it sends the current mouse world position so the server can do the tracing. For movement we use our TDMAIController to issue move commands and have pathfinding. The idea originated here: https://answers.unrealengine.com/questions/34074/does-ue4-have-client-side-prediction-built-in.html

# How to use this template?
-

# Current state of this template:
UNDER ACTIVE DEVELOPMENT as of 9/30/2018

We have setup the TargetableInterface. We have setup the base for right click input in the TDMPlayerController as well as two trace channels so we can trace to a targetable actor or only target the floor. Also in the TDMPlayerController we have set a few variables so the mouse will show up and we will handle input ourselves. My next step is to setup the TDMActor which will inherit from ITargetableInterface so we can create the floor actor and get that in the scene so we can trace to it. After that I need to setup the base of TDMCharacter which will be controlled by a custom AIController called TDMAIController. We use an AIController so we can use built in pathfinding and we use our own version so we can handle when the MoveCompleted. By this point we should have a basic click to move system set up and we can exand on TDMCharacter to have a targeting system. 
