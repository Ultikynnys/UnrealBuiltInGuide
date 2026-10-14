// Copyright (c) 2026. MIT License.

#include "UnrealBuiltInGuide.h"

#include "Framework/Commands/UICommandInfo.h"
#include "HAL/PlatformProcess.h"
#include "Textures/SlateIcon.h"
#include "ToolMenu.h"
#include "ToolMenuEntry.h"
#include "ToolMenuSection.h"
#include "ToolMenus.h"
#include "UnrealBuiltInGuideSettings.h"
#include "UnrealBuiltInGuideStyle.h"

DEFINE_LOG_CATEGORY(LogUnrealBuiltInGuide);

#define LOCTEXT_NAMESPACE "FUnrealBuiltInGuideModule"

namespace
{
	// The slim Play toolbar hosts the built-in play controls and the Platforms dropdown.
	const FName PlayToolBarMenuName(TEXT("LevelEditor.LevelEditorToolBar.PlayToolBar"));
	const FName PlaySectionName(TEXT("Play"));
	const FName ButtonName(TEXT("UnrealBuiltInGuide.Button"));

	UUnrealBuiltInGuideSettings* GetSettings()
	{
		return GetMutableDefault<UUnrealBuiltInGuideSettings>();
	}
}

void FUnrealBuiltInGuideModule::StartupModule()
{
	FUnrealBuiltInGuideStyle::Initialize();
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUnrealBuiltInGuideModule::RegisterMenus));

	SettingsChangedHandle = GetSettings()->OnSettingChanged().AddRaw(this, &FUnrealBuiltInGuideModule::OnSettingsChanged);
}

void FUnrealBuiltInGuideModule::ShutdownModule()
{
	GetSettings()->OnSettingChanged().Remove(SettingsChangedHandle);

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FUnrealBuiltInGuideStyle::Shutdown();
}

void FUnrealBuiltInGuideModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Toolbar = UToolMenus::Get()->ExtendMenu(PlayToolBarMenuName);
	if (!Toolbar)
	{
		UE_LOG(LogUnrealBuiltInGuide, Warning, TEXT("Could not extend '%s'; the guide button will not be shown."), *PlayToolBarMenuName.ToString());
		return;
	}

	// The Play section already ends with the built-in Platforms dropdown, so appending
	// here places the guide button immediately to its right.
	FToolMenuSection& Section = Toolbar->FindOrAddSection(PlaySectionName);

	Section.AddEntry(FToolMenuEntry::InitToolBarButton(
		ButtonName,
		FExecuteAction::CreateRaw(this, &FUnrealBuiltInGuideModule::OpenGuide),
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateRaw(this, &FUnrealBuiltInGuideModule::GetButtonLabel)),
		LOCTEXT("ButtonTooltip", "Open the Unreal Built-in Guide"),
		FSlateIcon(FUnrealBuiltInGuideStyle::GetStyleSetName(), FUnrealBuiltInGuideStyle::IconName)
	));
}

void FUnrealBuiltInGuideModule::OpenGuide() const
{
	const FString Url = GetSettings()->GuideUrl;
	if (Url.IsEmpty())
	{
		UE_LOG(LogUnrealBuiltInGuide, Warning, TEXT("No guide URL is configured."));
		return;
	}

	FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
}

FText FUnrealBuiltInGuideModule::GetButtonLabel() const
{
	return FText::FromString(GetSettings()->ButtonLabel);
}

void FUnrealBuiltInGuideModule::OnSettingsChanged(UObject* Settings, FPropertyChangedEvent& PropertyChangedEvent)
{
	FUnrealBuiltInGuideStyle::RefreshIcon(GetSettings()->GetResolvedIconPath());

	if (UToolMenus* ToolMenus = UToolMenus::Get())
	{
		ToolMenus->RefreshAllWidgets();
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealBuiltInGuideModule, UnrealBuiltInGuide)
