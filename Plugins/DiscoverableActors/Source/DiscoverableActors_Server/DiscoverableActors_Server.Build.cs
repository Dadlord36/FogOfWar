using UnrealBuildTool;

public class DiscoverableActors_Server : ModuleRules
{
    public DiscoverableActors_Server(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        
        // Add special content folder for DiscoverableActors_Server that will hold server-only assets.
        

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "DiscoverableActors_Shared",
                "GameplayMessageRuntime"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "DeveloperSettings",
            }
        );
    }
}