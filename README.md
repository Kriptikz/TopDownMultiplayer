# TopDownMultiplayer
This is a Top-Down Multiplayer Template with GameplayAbilites where you control only a single character. Written using C++ and Blueprint for use as a starting point in any Unreal Engine 4 projects.

Current Engine Version of this project : 4.20.3

For the current state of this project visit : https://github.com/Kriptikz/TopDownMultiplayer/projects/1

# What is the goal of this template?
  This template was created so people can easily get a Top-Down camera perspective and use it to control and call abilities on a single unit in a multiplayer environment where the server is authoritative. In order to achieve this I am using the GameplayAbilities API. The movement and pathfinding of the Character is handled in an ability task and the cursor HoveredActor and HoveredLocation are networked inside of the Ability using the WaitTargetData() ability task where it is sent over using our custom GameplayAbilityTargetActor_CursorTargetData. The data being sent is a simple FVector and AActor, here the Client has this data being updated constantly, It is only sent to the server when using WaitTargetData().
This is our custom ability task for handling movement and pathfinding:
  
```C++
  UAbilityTask_MoveToTarget* UAbilityTask_GetInRange::MoveToTarget(UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector TargetLocation, AActor* TargetActor)
```
  This ability task moves a Character within the specified Range of the location or actor and then broadcasts a call to the TargetRangeReached delegate.
  Range is usually passed in from getting a Characters attack range. Lowest Range is 10.0f and can be move to a target location directly.
  This task defaults to trying to move to TargetActor but falls back to using TargetLocation if TargetActor is null. So to move to the TargetLocation just don't pass in an actor. 
  
  For the camera I will create a very simple actor with a SpringArm and Camera component and move it around as necessary. This actor will be called TDMPlayerCamera. Anytime the PlayerController possesses a Character we will change the camera from our Character to our TDMPlayerCamera.
  

# How to use this template?
-
