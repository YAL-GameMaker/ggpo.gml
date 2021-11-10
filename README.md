# GGPO.gml

Experimental GameMaker bindings for [GGPO](https://github.com/pond3r/ggpo) using variously unusual tricks.  
Pretty much juggling loaded guns.

## Documentation

Everything is named same as in GGPO C API, except for player functions (which have separate `ggpo_add_local_player` and `ggpo_add_remote_player`) and callback variables.

Check out the sample project for general use!

You can also use "Show extension API" in GMEdit (when right-clicking an extension) to get a full list of functions.

## Building

See [GMSDLL](https://github.com/YAL-GameMaker/GMSDLL) for initial setup;  
Note that you'll have to build the VS solution or download the release - repository does not include pre-built binaries.

## Test project

Currently a very simple project with a couple spaceships zipping around.
You can also press Space to warp, which triggers a misprediction (hint: for presses, store and compare against previous button state)

## Caveats

- Probably not production ready and may never be truly production ready.
- Volatile - e.g. if you pass a _completely empty_ script to one of GGPO callbacks, the _next_ callback will hard crash your game.
- GMS2.3+ only. _Might_ be possible to make work with specific versions of GMS1.4 with other exotic tricks.
- Due to GGPO's API specifics (players have to be initialized immediately), you'll generally have to write a lobby system on top of GGPO.
- Doesn't include any serialization helpers - you'll have to figure out optimal saving/loading yourself.

## Is this used in Rivals of Aether?

\[...as if that wasn't apparent from first public builds having broken time sync]  
Work projects use Haxe-based deterministic netcode implementations compiled to target language (with [sfgml](https://github.com/YAL-Haxe/sfgml) used for targeting GML) to avoid interop issues.

It'd be pretty neat to write a straight Haxe port of GGPO (which would have made it easier to integrate with many languages), but that's a whole lot of work.

As for pure-GML implementations, there's [Platform Fighter Engine](https://springrollgames.itch.io/platform-fighter-engine).

## Does this mean that every GameMaker game can now have rollback netcode?

Absolutely not. In fact, the amount of refactoring required to detach your gameplay logic from GameMaker loop, make everything deterministic, and implement fast state \[de-]serialization makes this completely unaffordable to most games.

Original README follows:

---

# GGPO

![](doc/images/ggpo_header.png)

(日本語ドキュメントは[こちら](README.ja.md))

## What's GGPO?

Traditional techniques account for network transmission time by adding delay to a players input, resulting in a sluggish, laggy game-feel.  Rollback networking uses input prediction and speculative execution to send player inputs to the game immediately, providing the illusion of a zero-latency network.  Using rollback, the same timings, reactions, visual and audio queues, and muscle memory your players build up playing offline will translate directly online.  The GGPO networking SDK is designed to make incorporating rollback networking into new and existing games as easy as possible.  

For more information about the history of GGPO, check out http://ggpo.net/

This repository contains the code, documentation, and sample applications for the SDK.

## Building

Building GGPO is currently only available on Windows, however efforts are being made to port it to other platforms.

### Windows

Windows builds requires both [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/) and [CMake](https://cmake.org/download/).  Make sure you've installed both before starting.  Make sure to add CMake to your path when installing.

- Run the `build_windows.cmd` in the root directory of the SDK to generate the Visual Studio 2019 solution files.   
- Open `build/GGPO.sln` solution for Visual Studio 2019 to compile.

You can also run the `cmake-gui` tool if you prefer. 

## Sample Application

The Vector War application in the source directory contains a simple application which uses GGPO to synchronize the two clients.  The command line arguments are:

```
vectorwar.exe  <localport>  <num players> ('local' | <remote ip>:<remote port>) for each player
```

See the .cmd files in the bin directory for examples on how to start 2, 3, and 4 player games.

## Licensing

GGPO is available under The MIT License. This means GGPO is free for commercial and non-commercial use. Attribution is not required, but appreciated. 
