// Copyright (c) 2026. MIT License.

#include "UnrealBuiltInGuideStyle.h"

#include "Brushes/SlateColorBrush.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "Misc/Paths.h"
#include "Styling/SlateStyleRegistry.h"
#include "UnrealBuiltInGuideSettings.h"

TSharedPtr<FSlateStyleSet> FUnrealBuiltInGuideStyle::StyleInstance = nullptr;
const FName FUnrealBuiltInGuideStyle::IconName(TEXT("UnrealBuiltInGuide.Icon"));

FName FUnrealBuiltInGuideStyle::GetStyleSetName()
{
	static const FName StyleSetName(TEXT("UnrealBuiltInGuideStyle"));
	return StyleSetName;
}

const ISlateStyle& FUnrealBuiltInGuideStyle::Get()
{
	check(StyleInstance.IsValid());
	return *StyleInstance;
}

void FUnrealBuiltInGuideStyle::Initialize()
{
	if (StyleInstance.IsValid())
	{
		return;
	}

	StyleInstance = Create();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FUnrealBuiltInGuideStyle::Shutdown()
{
	if (StyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
		StyleInstance.Reset();
	}
}

void FUnrealBuiltInGuideStyle::RefreshIcon(const FString& ResolvedIconPath)
{
	if (StyleInstance.IsValid())
	{
		SetIconBrush(StyleInstance.ToSharedRef(), ResolvedIconPath);
	}
}

TSharedRef<FSlateStyleSet> FUnrealBuiltInGuideStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	SetIconBrush(Style, GetDefault<UUnrealBuiltInGuideSettings>()->GetResolvedIconPath());
	return Style;
}

void FUnrealBuiltInGuideStyle::SetIconBrush(const TSharedRef<FSlateStyleSet>& Style, const FString& ResolvedIconPath)
{
	// The toolbar overrides the size at layout time, so this value is only a fallback.
	const FVector2D IconSize(40.0f, 40.0f);

	if (!ResolvedIconPath.IsEmpty() && FPaths::FileExists(ResolvedIconPath))
	{
		Style->Set(IconName, new FSlateDynamicImageBrush(FName(*ResolvedIconPath), IconSize));
	}
	else
	{
		// Keep the button visible even if no icon file resolves.
		Style->Set(IconName, new FSlateColorBrush(FLinearColor(0.8f, 0.8f, 0.8f, 1.0f)));
	}
}
