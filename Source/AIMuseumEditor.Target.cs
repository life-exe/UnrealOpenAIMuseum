// AI Museum, Copyright LifeEXE. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AIMuseumEditorTarget : TargetRules
{
    public AIMuseumEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;

        ExtraModuleNames.AddRange(new string[] { "AIMuseum" });
    }
}
