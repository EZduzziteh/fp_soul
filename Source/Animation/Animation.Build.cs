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
            "GameplayTasks",       
			"AIModule",            
			"NavigationSystem" ,   
            "Niagara"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
