# Resolution Changer for Windows

This program is a simple desktop resolution changer.

It was made because when changing resolution in Windows 7, it messed up the Aspect Ratio for some unknown reason. However, it is useful still to change the resolution quickly on any other system.

## Usage (`<>` Mandatory, `[]` Optional)…
* (32-Bit) `RES32 <width> <height> [bit depth] [refresh]`.
* (64-Bit) `RES64 <width> <height> [bit depth] [refresh]`.

`[bit-depth]` defaults to `32 bits-per-pixel` if not specified.
`[refresh]` defaults to `60 hertz` if not specified.

## Examples…
* `RES32 800 600`
* `RES64 640 480 16`
* `RES32 320 200 8`
* `RES64 1280 1024 32 75`
* `RES32 1920 1080 32 100`

Note: This program uses WINAPI functions to set the resolution. So only resolutions that your graphics card supports can be set, so it is relativly safe. However, you still use this program AT YOUR OWN RISK as setting resolutions your monitor cannot support or display may damage it and/or may result in you not being able to see your desktop anymore. Remember this program saves the new resolution to the registry so if you've messed up your desktop resolution. You will have to go into the boot menu and run Windows in standard VGA mode and restore the desktop resolution there.
