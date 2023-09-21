// AI Museum, Copyright LifeEXE. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AIMuseumTarget : TargetRules
{
    public AIMuseumTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V4;

        ExtraModuleNames.AddRange(new string[] { "AIMuseum" });
    }
}
