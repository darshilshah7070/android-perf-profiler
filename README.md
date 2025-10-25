
---


# Android Performance Profiler (C CLI)

A simple **command-line performance profiler** for Android (ARM64).  
It monitors **CPU** and **memory usage** in real time.  

Written in **C**, built on your **Linux host**, and run on your Android device via **ADB shell**.  

No root required.

---

## Prerequisites

### On Linux Host:
- **ADB** (Android Debug Bridge)  
- **Android NDK** (r27d recommended)  
- **Git** and **make**

### On Android Device:
- USB debugging enabled  
  (Settings → Developer options → “USB Debugging”)

---

## Setup Instructions

### **1. Install ADB**
Ubuntu/Debian:
```bash
sudo apt update
sudo apt install android-tools-adb -y
````

Verify:

```bash
adb version
```

---

### **2. Install Android NDK**

1. Download the NDK from:
   [https://developer.android.com/ndk/downloads](https://developer.android.com/ndk/downloads)

2. Extract it:

```bash
unzip android-ndk-r27d-linux.zip -d $HOME/
```

3. Set environment variable:

```bash
export NDK_PATH=$HOME/android-ndk-r27d
```

---

### **3. Clone Project**

```bash
git clone https://github.com/darshilshah7070/android-perf-profiler.git
cd android-perf-profiler
```

Project structure:

```
android-perf-profiler/
├── src/             # Source files
├── include/         # Header files
├── Makefile         # Build instructions
└── build/           # Compiled binaries(it will generate after make)
```

---

### **4. Build for Android (ARM64)**

Simply run:

```bash
make
```

The binary will appear at:

```
build/profiler
```

---

### **5. Connect Android Device**

```bash
adb devices
```

Make sure your device is listed.

---

### **6. Push and Run Profiler**

```bash
adb push build/profiler /data/local/tmp/
adb shell
cd /data/local/tmp
chmod +x profiler
./profiler
```

You should see real-time CPU and memory usage.

---

### **7. Clean Build (Optional)**

```bash
make clean
```

---

## How It Works

* Reads `/proc/stat` → CPU usage
* Reads `/proc/meminfo` → Memory usage
* Displays a simple live CLI dashboard.

---

## Makefile Targets

| Command      | Description                |
| ------------ | -------------------------- |
| `make`       | Build Android ARM64 binary |
| `make clean` | Remove build artifacts     |

---

## Troubleshooting

| Problem             | Solution                                                              |
| ------------------- | --------------------------------------------------------------------- |
| `permission denied` | Run `chmod +x profiler` in `/data/local/tmp`                          |
| `exec format error` | Wrong architecture; check with `adb shell getprop ro.product.cpu.abi` |
| Device not detected | Enable USB debugging; run `adb kill-server && adb start-server`       |

---
