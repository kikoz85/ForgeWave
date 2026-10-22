# LAME in ForgeWave

ForgeWave exports MP3 with **LAME 3.100** (GNU Library General Public License, version 2 or
later; see [`COPYING`](COPYING)). LAME is **not built into ForgeWave**: it is a separate shared
library shipped next to the app and loaded only when you export an MP3, so you can replace it
with your own build.

| System | File |
|---|---|
| macOS | `ForgeWave.app/Contents/Frameworks/libmp3lame.dylib` |
| Windows | `libmp3lame.dll`, next to `ForgeWave.exe` |
| Linux (AppImage) | `usr/bin/libmp3lame.so.0` inside the image |
| Linux (.deb) | `/usr/lib/forgewave/libmp3lame.so.0` |
| Linux (tar.gz) | `libmp3lame.so.0`, next to `forgewave` |

ForgeWave can also be pointed at another copy with the environment variable
`FORGEWAVE_LAME=/path/to/library`. *Settings › About* shows which LAME version is loaded.

## Source

This folder contains the exact source ForgeWave's library is built from: the official
[LAME 3.100 release](https://sourceforge.net/projects/lame/files/lame/3.100/) (SHA-256 of
`lame-3.100.tar.gz`: `ddfe36cab873794038ae2c1210557ad34857a4b6bdc515785d1da9e175b1da1e`),
**unmodified**, limited to the library (`include/`, `libmp3lame/`) and its licence files. The
full official archive is also attached to every ForgeWave release.

ForgeWave adds only two build files, in [`forgewave/`](forgewave):

- `config.h`: the configuration used instead of autotools, the same on every system;
- `libmp3lame.def`: the functions exported by the Windows DLL.

## Building a replacement

The decoder (`mpglib_interface.c`) is not needed. Any build exporting the `lame.h` functions
listed in `forgewave/libmp3lame.def` works. From this folder:

```bash
# macOS (universal: add -arch arm64 -arch x86_64)
cc -O3 -fPIC -shared -DHAVE_CONFIG_H -Iforgewave -Iinclude -Ilibmp3lame \
   $(ls libmp3lame/*.c libmp3lame/vector/*.c | grep -v mpglib_interface) \
   -install_name @rpath/libmp3lame.dylib -o libmp3lame.dylib

# Linux
cc -O3 -fPIC -shared -DHAVE_CONFIG_H -Iforgewave -Iinclude -Ilibmp3lame \
   $(ls libmp3lame/*.c libmp3lame/vector/*.c | grep -v mpglib_interface) \
   -Wl,-soname,libmp3lame.so.0 -o libmp3lame.so.0 -lm
```

```bat
:: Windows, from a "x64 Native Tools Command Prompt for VS"
cl /O2 /LD /DHAVE_CONFIG_H /Iforgewave /Iinclude /Ilibmp3lame libmp3lame\*.c libmp3lame\vector\*.c ^
   /link /DEF:forgewave\libmp3lame.def /OUT:libmp3lame.dll
```

On Windows `mpglib_interface.c` compiles to nothing without `HAVE_MPGLIB`, so the wildcard is
fine. Then replace the file listed above with yours.

---

ForgeWave esporta in MP3 con **LAME 3.100** (LGPL), che non è incorporato nell'app ma è una
libreria separata, caricata solo per l'export MP3 e sostituibile con una tua versione. Qui ci
sono il sorgente ufficiale non modificato, i due file di configurazione di ForgeWave e i
comandi per ricompilarla.
