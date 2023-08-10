using UnrealBuildTool;

public class DiscoverableActorsRepGraph_Server : ModuleRules
{
    public DiscoverableActorsRepGraph_Server(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "ReplicationGraph",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "FogOfWarCommon"
            }
        );
    }
}