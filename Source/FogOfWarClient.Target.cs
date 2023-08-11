using UnrealBuildTool;
using System.Collections.Generic;

public class FogOfWarClientTarget : TargetRules
{

public FogOfWarClientTarget( TargetInfo Target) : base(Target)
{
	Type = TargetType.Client;
	DefaultBuildSettings = BuildSettingsVersion.V2;
	IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
	ExtraModuleNames.Add("FogOfWar");
	DisablePlugins.Add("DiscoverableActors_ServerExpansion");
}
}