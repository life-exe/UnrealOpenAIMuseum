// AI Museum, Copyright LifeEXE. All Rights Reserved.

using UnrealBuildTool;

public class AIMuseum : ModuleRules
{
    public AIMuseum(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

        PublicIncludePaths.AddRange(new string[] { "AIMuseum" });
    }
}
