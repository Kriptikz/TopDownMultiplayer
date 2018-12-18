# TopDownMultiplayer
This is a Top-Down Multiplayer Template with GameplayAbilites written using C++ and Blueprint for use as a starting point in any Unreal Engine 4 projects.

Current Engine Version of this project : 4.20.3

For the current state of this project visit : https://github.com/Kriptikz/TopDownMultiplayer/projects/1

# What is the goal of this template?
  This template was created so people can easily get a Top-Down camera perspective and use it to control and call abilities on a unit in a multiplayer environment where the server is authoritative. In order to achieve this I am using the GameplayAbilities API. The movement and pathfinding of the Character is handled in an ability task and the cursor hovered actor and target location are networked inside of the Ability using the WaitTargetData() ability task where it is send over using our custom GameplayAbilityTargetActor_CursorTargetData. The data being sent is a simple FVector and AActo; Where the Client has this data being updated constantly, It is only sent to the server when it is asked for.
This is our custom ability task for handling movement and pathfinding:
  
```C++
  UAbilityTask_GetInRange* UAbilityTask_GetInRange::GetInRange(UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector TargetLocation, AActor* TargetActor)
```
  This ability task moves a Character within the specified Range of the location or actor and then broadcasts a call to the TargetRangeReached delegate.
  This task can handle moving directly to an actor or location by simply specifying a low range such as 10.0f. Generally you want the actor to move with attack range though, so you can just get the Characters attack range and pass that.
  This task defaults to trying to move to TargetActor but falls back to using TargetLocation if TargetActor is null. So to move exactly to a specified location within ~10.0f units, simply call the task and pass only a TargetLocation with a range of 10.0f and don't pass anything to TargetActor. 
  
  For the camera I will create a very simple actor with a SpringArm and Camera component and move it around as necessary. This actor will be called TDMPlayerCamera. Anytime the PlayerController possesses a Character we will change the camera from our Character to our TDMPlayerCamera.
  

# How to use this template?
-
