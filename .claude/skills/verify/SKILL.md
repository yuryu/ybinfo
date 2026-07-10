---
name: verify
description: Build and drive YbInfo to verify changes at the GUI surface (launch, open dialogs, screenshot, inspect controls).
---

# Verifying YbInfo

## Build

```powershell
$msbuild = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe
& $msbuild YbInfo.sln /p:Configuration=Debug /p:Platform=x64 /m /v:m /nologo
```

Output lands in `bin\<Platform>\<Configuration>\YbInfo.exe`. Use the Debug build so ATL asserts fire.

## Launch and drive

- The app needs at least one battery device; a USB UPS counts (check with `Get-CimInstance Win32_Battery`). Without one it shows a "no batteries" message box first, then the main dialog.
- Main window: visible top-level window titled `YbInfo` (dialog class `#32770`).
- About dialog: post `WM_SYSCOMMAND` (0x0112) with wParam `IDM_ABOUTBOX` (0x0010) to the main window; it opens modally (title `YbInfoのバージョン情報`). Find it as a second visible `#32770` window in the process.
- Read control text cross-process with `WM_GETTEXTLENGTH`/`WM_GETTEXT` via `SendMessage` — works for Edit controls; `GetWindowText` returns empty for other processes' controls (not a bug).
- Screenshot: `SetProcessDpiAwarenessContext(-4)` first, then `GetWindowRect` + `System.Drawing` `CopyFromScreen`. Briefly set the window `HWND_TOPMOST` (with `SWP_NOACTIVATE`) so nothing overlaps the capture, then restore.
- Write the driver as a PowerShell script (P/Invoke via `Add-Type`, wait loops around window discovery, cleanup at the end) in the session scratchpad and run it as one unit.

## Gotchas

- `YbInfo.rc` is Shift-JIS (`code_page(932)`). Never touch it with Edit/Write tools — they corrupt the Japanese strings. Edit it via a cp932 decode → string replace → cp932 encode round-trip (verify losslessness by re-encoding before writing), then check `git diff` shows only ASCII lines changed.
- Kill the app with `Stop-Process` when done; a running instance holds a lock on the exe and the next link step fails.
- Resources embedded via RCDATA can be checked in the built exe with `LoadLibraryExW(LOAD_LIBRARY_AS_DATAFILE)` + `FindResource`/`LockResource` and compared byte-for-byte against the source file.
