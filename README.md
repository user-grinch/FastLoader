# FastLoader – your best companion when adding new props or cars

## 📖 Read Wiki
- [Loading cargrp.dat](https://github.com/user-grinch/FastLoader/wiki/1.-cargrp.dat)
- [Loading FLA Audio.dat](https://github.com/user-grinch/FastLoader/wiki/2.-gtasa_vehicleAudioSettings.cfg)
- [Loading Object.dat](https://github.com/user-grinch/FastLoader/wiki/3.-Objects.dat)

## 🚘 What is FastLoader?

**FastLoader** is a tiny `.asi` plugin that enhances GTA San Andreas modding by fixing what ModLoader doesn't:

- Merges difficult files like `cargrp.dat`, `object.dat`, and `gtasa_vehicleAudioSettings.cfg`
- Prevents crashes and manual merging
- Ensures proper load order and compatibility with Fastman92 Limit Adjuster (FLA)
- Ignore folders with '.' as a prefix, preserving modloader functionality

## 🧐 Key Features

- 🧩 **Fixes ModLoader limitations** (`cargrp.dat`, `object.dat`)
- 🔊 **Automates audio merging** for Fastman92 Limit Adjuster via `gtasa_vehicleAudioSettings.cfg`
- ❌ **No need to touch original `data/` configuration files** – all handled automatically
- 🚀 **Optimized for speed** – minimal startup overhead
- 🛠️ **Compatible with ModLoader & FLA**


## 🛠️ It suits best

- **Silent’s ASI Loader (2025 update by fastman92)** – allows proper load order of `.asi` plugins  → [Download & info](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)


## 📊 Installation

1. Download and install the newest [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)
2. Place `$fastloader.asi` in your main GTA SA directory (where `gta_sa.exe` is)
3. Drop regular text files with `*.fastloader` extension into ModLoader (just like you normally do for ModLoader .txt files) Check the [Wiki](https://github.com/user-grinch/FastLoader/wiki)
4. Launch the game – done!


## ⚙️ How It Works

FastLoader is **guaranteed to run before other plugins**, including:

- ✅ ModLoader
- ✅ Fastman92 Limit Adjuster 

This ensures safe memory access and proper data injection, **without race conditions or file conflicts**.
This behavior is made possible by the latest version of [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173), which guarantees load order of `.asi` plugins.

🧹Plugin must be named `$fastloader.asi`, and make sure it's placed in the main GTA SA directory to ensure it loads early.

📚 File format details are available in the project [Wiki](https://github.com/user-grinch/FastLoader/wiki)


### 🗺️ Fastaman Limit Adjuster - Best Settings
For cargrp.dat loading:

`Cargrp cars per group = 63` 

`Streaming_DesiredNumberOfVehiclesLoaded = 62` 

For object.dat loading:

`Object info entries = 200`

For #VehicleStructs use Open Limit Adjuster default settings. 

### 🗺️ MixSets - Best Settings

Comment out those lines with # to avoid conflicts and to grant a flawless stability.

```
#MinDesiredLoadedVeh  = 4        # (2) Minimum vehicle model variations loaded in memory.
#NumDesiredLoadedVeh  = 36       # (22) How many desired vehicle model variations loaded into memory.
#DelayLoadDesiredVeh  = 250      # (350) Delay time (in number of frames) to load a new vehicle model variation.
#MinLoadedGangVeh     = 4        # (1) Minimum of gang vehicle models loaded in memory.
```

## ⚠️ Fastloader and `.dat` Files

By default, **Fastloader** will ask whether to rename (disable) `cargrp.dat` and `object.dat` files:  
<img width="406" height="147" alt="image" src="https://github.com/user-attachments/assets/8f0e74e7-a8a7-4221-92ec-69f5bb2e6163" />

It will append `.bak` to the file name:  
<img width="178" height="120" alt="image" src="https://github.com/user-attachments/assets/0eee36ad-a553-4e71-936c-d6bdafca4673" />

**Why does this happen?**  
Fastloader starts **before** Modloader. Its task is to add new entries to the original `object.dat` or `cargrp.dat` files stored in `/data`.  
The purpose of Fastloader is to load lines for newly added objects into `object.dat` or to add newly added cars into `cargrp.dat`.  
When you have any object.dat or cargrp.dat inside modloader folder, modloader.asi will load this data again. It will cause the crashes. 

👉 If you just want to load an `object.dat` or `cargrp.dat` file, leave it in Modloader. Don’t use Fastloader for it.  
👉 When adding new props (like *Project Props 3*) or cars with FLA, Fastloader is your friend.  

⚠️ **Important:** Fastloader will only load files with the `.fastloader` extension and only those which are implemented. It will **ignore all others**.


## 📄 License

MIT License – free to use, share, or modify. If you use this in your modpack, please credit and link back to this repository.


## 🤝 Authors

- **Grinch** – Core loader logic, `.asi` development
- **Damix** – Concept, design, testing, and integration ideas

