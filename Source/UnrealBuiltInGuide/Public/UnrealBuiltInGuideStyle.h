// Copyright (c) 2026. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Styling/ISlateStyle.h"
#include "Styling/SlateStyle.h"

/**
 * Holds the toolbar button brush. The brush is a dynamic image loaded from a PNG on
 * disk so the icon can be swapped at runtime from settings.
 */
class FUnrealBuiltInGuideStyle
{
public:
	static void Initialize();
	static void Shutdown();

	/** Rebuilds the button brush from the given PNG path (empty falls back to a placeholder). */
	static void RefreshIcon(const FString& ResolvedIconPath);

	static FName GetStyleSetName();
	static const ISlateStyle& Get();

	static const FName IconName;

private:
	static TSharedRef<FSlateStyleSet> Create();
	static void SetIconBrush(const TSharedRef<FSlateStyleSet>& Style, const FString& ResolvedIconPath);

	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
