// Copyright (c) 2026. MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUnrealBuiltInGuide, Log, All);

class FUnrealBuiltInGuideModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenus();
	void OpenGuide() const;
	FText GetButtonLabel() const;
	void OnSettingsChanged(UObject* Settings, struct FPropertyChangedEvent& PropertyChangedEvent);

	FDelegateHandle SettingsChangedHandle;
};
