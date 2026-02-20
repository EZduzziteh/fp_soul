using UnrealBuildTool;

public class Animation : ModuleRules
{
    public Animation(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "RootMovement",
            "GameplayTasks",       // For AI task support
			"AIModule",            // For AIController and Perception
			"NavigationSystem"     // For MoveTo and pathfinding
		});

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
