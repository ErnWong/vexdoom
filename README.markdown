# vexdoom

[Vex V5](https://www.vexrobotics.com/vexedr/v5) + [DOOM][doom] = vexdoom.

[doom]: https://en.wikipedia.org/wiki/Doom_(1993_video_game)

![Teaser Photo](docs/images/lo-res-teaser.png)

## Installation

1. Make sure you have [PROS for V5 installed](https://pros.cs.purdue.edu/v5/getting-started/index.html).
2. Download / clone this repo to your machine.
```sh
git clone https://github.com/ErnWong/vexdoom.git
```
3. Copy your legally obtained `doom1.wad` file into the `./res` folder.
```sh
mkdir -p ./res
cp /whatever/your/path/is/to/doom1.wad ./res
```
4.
    - If you're on Linux, make sure you have build-essentials and run `./tools/genwadfiles.sh`.
      ```sh
      sudo apt install build-essentials
      ./tools/genwadfiles.sh
      ```
    - If you're on Windows, install [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/install-win10) and do step 4 like you're on linux.
5. Compile
```sh
prosv5 make
```
6. Connect your V5 Brain, and upload the program into it.
```sh
prosv5 upload
```

## Contribute

I probably won't be working on this any more. Feel free to submit pull requests to this project.

## Thanks

The DOOM source code used in this project is based from a [DOOM port](https://github.com/jezze/doom) by Jens Nyberg. Check out the [commit history](https://github.com/ErnWong/vexdoom/commits) to see how the original files were modified.
