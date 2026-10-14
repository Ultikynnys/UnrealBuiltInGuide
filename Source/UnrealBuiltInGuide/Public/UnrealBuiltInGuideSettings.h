// Copyright (c) 2026. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UnrealBuiltInGuideSettings.generated.h"

/** Configuration for the "Unreal Built-in Guide" toolbar button. */
UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Unreal Built-in Guide"))
class UNREALBUILTINGUIDE_API UUnrealBuiltInGuideSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UUnrealBuiltInGuideSettings();

	/** Web page opened when the toolbar button is clicked. */
	UPROPERTY(config, EditAnywhere, Category = "Guide", meta = (DisplayName = "Guide URL"))
	FString GuideUrl;

	/**
	 * PNG used as the toolbar button icon. Leave empty to fall back to the favicon
	 * that ships in the plugin's Resources folder.
	 */
	UPROPERTY(config, EditAnywhere, Category = "Guide", meta = (DisplayName = "Button Icon (PNG)", FilePathFilter = "PNG Image (*.png)|*.png"))
	FString IconPath;

	/** Caption drawn next to the toolbar button. Leave empty for an icon-only button. */
	UPROPERTY(config, EditAnywhere, Category = "Guide", meta = (DisplayName = "Button Label"))
	FString ButtonLabel;

	/** Absolute path to the favicon that ships with the plugin. */
	static FString GetBundledIconPath();

	/** The configured icon if it exists on disk, otherwise the bundled favicon. */
	FString GetResolvedIconPath() const;

	virtual FName GetCategoryName() const override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
	virtual FText GetSectionDescription() const override;
#endif
};
