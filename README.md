# Unreal Built-in Guide (Unreal Engine 5 plugin)

Adds a button to the Level Editor toolbar that opens a web page, so the guide a team
relies on is one click away inside the editor. The link and the button icon are both
configurable; out of the box it points at the Unreal style guide.

* **Engine:** Unreal Engine 5.6 (Win64).
* **Module:** a single editor module (`Source/UnrealBuiltInGuide`).
* **Default target:** `https://ultikynnys.github.io/ue5-style-guide/`.

## Where the button lives

The button is appended to the **Play** section of the Level Editor toolbar, so it sits
immediately to the right of the built-in **Platforms** dropdown:

```
[ Save ] ... [ Play ▸ ] [ Platforms ▾ ] [ (guide icon) Built-in Guide ]   [ Settings ⚙ ]
```

Clicking it opens the configured URL in your default browser.

## Install

Copy the `UnrealBuiltInGuide` folder into your project's `Plugins/` directory, then
enable **Unreal Built-in Guide** under *Edit → Plugins* (category **Editor**):

```
<YourProject>/Plugins/UnrealBuiltInGuide/
```

Because this is a C++ plugin, opening the project the first time compiles it, so a C++
toolchain (Visual Studio with the "Game development with C++" workload) is required. A
blueprint-only project still needs the toolchain once, to build the plugin module; after
that the button is available like any other editor UI.

## Configuration

Open **Project Settings → Plugins → Unreal Built-in Guide**:

| Setting | Description | Default |
| --- | --- | --- |
| **Guide URL** | Web page opened when the button is clicked. | `https://ultikynnys.github.io/ue5-style-guide/` |
| **Button Icon (PNG)** | PNG file used as the button icon. | the favicon bundled in `Resources/GuideButtonIcon.png` |
| **Button Label** | Caption drawn next to the icon. Leave empty for an icon-only button. | `Built-in Guide` |

Changes apply live: picking a new icon refreshes the toolbar button without a restart.

### Icon

The icon is loaded from a PNG on disk at runtime, so you can point it at any image
without importing an asset into the project. Leave **Button Icon** empty (or pointing at
a file that no longer exists) and the plugin falls back to the favicon it ships with.
The toolbar scales the image to its own icon size, so the source resolution does not
matter much; a square image around 40x40 or larger looks best.

### Pre-seeding the values

The defaults also live in `Config/DefaultEditor.ini` in the plugin folder, so a fixed
team-wide guide URL can be committed with the plugin instead of set per project:

```ini
[/Script/UnrealBuiltInGuide.UnrealBuiltInGuideSettings]
GuideUrl=https://ultikynnys.github.io/ue5-style-guide/
ButtonLabel=Built-in Guide
```

## How it works

* `UnrealBuiltInGuideModule` registers the button through `UToolMenus`, extending
  `LevelEditor.LevelEditorToolBar.PlayToolBar` in the `Play` section
  (`Source/.../Private/UnrealBuiltInGuide.cpp`).
* `FUnrealBuiltInGuideStyle` owns a Slate style set whose icon is an
  `FSlateDynamicImageBrush` loaded from the configured PNG
  (`Source/.../Private/UnrealBuiltInGuideStyle.cpp`).
* `UUnrealBuiltInGuideSettings` is a `UDeveloperSettings` class, so the section appears
  automatically under Project Settings → Plugins and saves to the editor config
  (`Source/.../Public/UnrealBuiltInGuideSettings.h`).

## Support

Open an issue on the repository. Source is a single editor module
(`Source/UnrealBuiltInGuide`).
