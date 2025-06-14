# FastLoader

> ⚡ A fast, lightweight text-based data loader that fixes the most troublesome file limitations in ModLoader and automates audio setup for Fastman92 Limit Adjuster (FLA).> 🔁 Copy and Paste into modloader/, no file editing, fully automatic loading via folder detection.

---

## 🚘 What is FastLoader?

**FastLoader** is a tiny `.asi` plugin that enhances GTA San Andreas modding by fixing what ModLoader doesn't:

- Merges difficult files like `cargrp.dat`, `object.dat`, and `gtasa_vehicleAudioSettings.cfg`
- Prevents crashes and manual merging
- Ensures proper load order and compatibility with Fastman92 Limit Adjuster (FLA)



---

## 🧐 Key Features

- 🧩 **Fixes ModLoader limitations** (`cargrp.dat`, `object.dat`)
- 🔊 **Automates audio merging** for Fastman92 Limit Adjuster via `gtasa_vehicleAudioSettings.cfg`
- ❌ **No need to touch original `data/` configuration files** – all handled automatically
- 🚀 **Optimized for speed** – minimal startup overhead
- 🛠️ **Compatible with ModLoader & FLA**

---

## 🛠️ It suits best

- **Silent’s ASI Loader (2024 update)** – allows proper load order of `.asi` plugins  → [Download & info](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)

---

## 📊 Installation

1. Download and install the newest [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173)
2. Place `FastLoader.asi` in your main GTA SA directory (where `gta_sa.exe` is)
3. Drop your `*.txt` config files into ModLoader (just like you normally do for ModLoader .txt files)
4. Launch the game – done!

---

## ⚙️ How It Works

FastLoader is **guaranteed to run before other plugins**, including:

- ✅ ModLoader
- ✅ Fastman92 Limit Adjuster 

This ensures safe memory access and proper data injection, **without race conditions or file conflicts**.

> This behavior is made possible by the latest version of [Silent’s ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/page/5/#findComment-1072560173),> which guarantees load order of `.asi` plugins.

🧹 Do **not** rename `FastLoader.asi`, and make sure it's placed in the main GTA SA directory to ensure it loads early.

📚 More file format details are available in the project Wiki.

---

## 🧪 Advanced Features

### 🔊 `gtasa_vehicleAudioSettings.cfg` support

Tired of manually adding lines to `data/gtasa_vehicleAudioSettings.cfg`?Just place a `.txt` file(s) in ModLoader – FastLoader will find it and merge the contents into the correct spot in the original file **automatically**.

> Works seamlessly with ModLoader – no manual editing required.

---

### 🚗 `cargrp.dat` support

Unlike `handling.cfg` or `vehicles.dat`, **ModLoader doesn’t support merging** for `cargrp.dat`.That’s why FastLoader includes smart logic to:

- Detect specially formatted `cargrp.txt` files inside ModLoader
- Merge their contents directly into `cargrp.dat` at runtime
- Ensure proper, balanced vehicle group spawning

> ✅ No crashes. No manual merging. Just drop and drive.

---

### 🧱 `object.dat` crash fix & merge support

ModLoader has a **known bug** when trying to merge `object.dat`, often causing crashes.FastLoader fixes this:

- Automatically detects `object.txt` files in ModLoader
- Merges lines safely with the main `object.dat`
- Now you can safely use:
  - **ProperFixes**
  - **NextGen Remaster Effects**
  - **Combat FX Upgrade**
  - **Project Props**

> 🔐 Say goodbye to `object.dat` crashes – FastLoader handles it for you.

---

### 🗺️ Future File Support

Support for more `.dat` and config files is planned – stay tuned for updates!

---

## 🔧 Troubleshooting

- Logs are saved in `FastLoader.log` in your game directory
- Check for missing models or incorrectly named files
- For advanced debugging, enable CLEO+ and use `LOGPRINT` commands

---

## 📄 License

MIT License – free to use, share, or modify. If you use this in your modpack, please credit and link back to this repository.

---

## 🤝 Authors

- **Damix** – Concept, design, testing, and integration ideas
- **Grinch** – Core loader logic, `.asi` development
