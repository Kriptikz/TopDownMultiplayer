// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class TopDownMultiplayerTarget : TargetRules
{
	public TopDownMultiplayerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "TopDownMultiplayer" } );
	}
}
