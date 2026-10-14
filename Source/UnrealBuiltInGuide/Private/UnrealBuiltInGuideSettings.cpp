// Copyright (c) 2026. MIT License.

#include "UnrealBuiltInGuideSettings.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "UUnrealBuiltInGuideSettings"

UUnrealBuiltInGuideSettings::UUnrealBuiltInGuideSettings()
{
	GuideUrl = TEXT("https://ultikynnys.github.io/ue5-style-guide/");
	ButtonLabel = TEXT("Built-in Guide");
	IconPath = GetBundledIconPath();
}

FName UUnrealBuiltInGuideSettings::GetCategoryName() const
{
	// Places the section under Project Settings > Plugins.
	return FName(TEXT("Plugins"));
}

#if WITH_EDITOR
FText UUnrealBuiltInGuideSettings::GetSectionText() const
{
	return LOCTEXT("SectionText", "Unreal Built-in Guide");
}

FText UUnrealBuiltInGuideSettings::GetSectionDescription() const
{
	return LOCTEXT("SectionDescription", "Configures the toolbar button that opens the project's web guide.");
}
#endif

FString UUnrealBuiltInGuideSettings::GetBundledIconPath()
{
	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("UnrealBuiltInGuide")))
	{
		return FPaths::ConvertRelativePathToFull(FPaths::Combine(Plugin->GetBaseDir(), TEXT("Resources"), TEXT("GuideButtonIcon.png")));
	}
	return FString();
}

FString UUnrealBuiltInGuideSettings::GetResolvedIconPath() const
{
	if (!IconPath.IsEmpty() && FPaths::FileExists(IconPath))
	{
		return FPaths::ConvertRelativePathToFull(IconPath);
	}

	const FString Bundled = GetBundledIconPath();
	return FPaths::FileExists(Bundled) ? Bundled : FString();
}

#undef LOCTEXT_NAMESPACE
