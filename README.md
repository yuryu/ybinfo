# YbInfo — Yuryu's Battery Information

[![build](https://github.com/yuryu/ybinfo/actions/workflows/build.yml/badge.svg)](https://github.com/yuryu/ybinfo/actions/workflows/build.yml)

A small Windows dialog application that displays detailed information about the
battery devices installed in your PC (capacity, voltage, charge/discharge rate,
cycle count, temperature, chemistry, and more), using the Windows battery
IOCTL interface (`IOCTL_BATTERY_*`).

Originally written in 2003–2008 with MFC; now a WTL application built with
modern Visual Studio.

## Building

Requirements:

- Visual Studio 2022 or later with the "Desktop development with C++" workload
  (including ATL)
- vcpkg (the copy bundled with Visual Studio works)

WTL is pulled in automatically through the vcpkg manifest (`vcpkg.json`).
One-time setup to enable vcpkg's MSBuild integration:

```
vcpkg integrate install
```

Then build from a Developer Command Prompt:

```
msbuild YbInfo.sln /m /p:Configuration=Release /p:Platform=x64
```

or open `YbInfo.sln` in Visual Studio. Binaries are placed under
`bin\<Platform>\<Configuration>\`. Win32, x64, and ARM64 are supported.

Release builds link the C runtime statically, so the resulting exe is
self-contained and does not require the Visual C++ redistributable.

See `readme.txt` for the original documentation in Japanese.

## License

Apache License, Version 2.0. See [LICENSE](LICENSE).

YbInfo uses the Windows Template Library (WTL), which is distributed under
the Microsoft Public License (MS-PL). See
[acknowledgements.txt](acknowledgements.txt), also shown in the About dialog.
