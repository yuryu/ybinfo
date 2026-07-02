# CLAUDE.md

YbInfo is a WTL C++ Windows dialog application that displays battery details
via the `IOCTL_BATTERY_*` interface. Build with `msbuild YbInfo.sln`; WTL is
provided through the vcpkg manifest (see README.md).

## Conventions

- Include what you use: every source/header file explicitly includes the
  headers for the types it uses directly, even when another include already
  provides them transitively. Do not remove an include merely because it is
  redundant through another header.
