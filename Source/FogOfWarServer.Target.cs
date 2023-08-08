using UnrealBuildTool;
using System.Collections.Generic;

public class FogOfWarServerTarget : TargetRules
{
	public FogOfWarServerTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("FogOfWar");
	}
}