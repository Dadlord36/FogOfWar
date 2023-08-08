using UnrealBuildTool;

public class DiscoverableActors_Client : ModuleRules
{
    public DiscoverableActors_Client(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "DiscoverableActors_Shared",
                "ModularGameplay",
                "GameplayMessageRuntime"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore"
            }
        );
    }
}