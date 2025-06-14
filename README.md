# FastLoader

## 🚘 What is FastLoader?

**FastLoader** is a tiny `.asi` plugin that enhances GTA San Andreas modding by fixing what ModLoader doesn't:

- Merges difficult files like `cargrp.dat`, `object.dat`, and `gtasa_vehicleAudioSettings.cfg`
- Prevents crashes and manual merging
- Ensures proper load order and compatibility with Fastman92 Limit Adjuster (FLA)

## 🧐 Key Features

- 🧩 **Fixes ModLoader limitations** (`cargrp.dat`, `object.dat`)
- 🔊 **Automates audio merging** for Fastman92 Limit Adjuster via `gtasa_vehicleAudioSettings.cfg`
- ❌ **No need to touch original `data/` configuration files** – all handled automatically
- 🚀 **Optimized for speed** – minimal startup overhead
- 🛠️ **Compatible with ModLoader & FLA**


## 🛠️ It suits best

- **Silent’s ASI Loader (2024 update)** – allows proper load order of `.asi` plugins  → [Download & info](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)


## 📊 Installation

1. Download and install the newest [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)
2. Place `$fastloader.asi` in your main GTA SA directory (where `gta_sa.exe` is)
3. Drop your `*.txt` config files into ModLoader (just like you normally do for ModLoader .txt files) Check the [Wiki](https://github.com/user-grinch/FastLoader/wiki)
4. Launch the game – done!


## ⚙️ How It Works

FastLoader is **guaranteed to run before other plugins**, including:

- ✅ ModLoader
- ✅ Fastman92 Limit Adjuster 

This ensures safe memory access and proper data injection, **without race conditions or file conflicts**.
This behavior is made possible by the latest version of [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173), which guarantees load order of `.asi` plugins.

🧹 Do **not** rename `$fastloader.asi`, and make sure it's placed in the main GTA SA directory to ensure it loads early.

📚 File format details are available in the project [Wiki](https://github.com/user-grinch/FastLoader/wiki)


### 🗺️ Future File Support

Support for more `.dat` and config files is planned – stay tuned for updates!


## 📄 License

MIT License – free to use, share, or modify. If you use this in your modpack, please credit and link back to this repository.


## 🤝 Authors

- **Grinch** – Core loader logic, `.asi` development
- **Damix** – Concept, design, testing, and integration ideas

