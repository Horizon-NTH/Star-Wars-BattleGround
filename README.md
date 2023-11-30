# Star Wars BattleGround

                            ________   ___   ____
                           / __   __| / _ \ |  _ \
                     ______> \ | |   |  _  ||    /_____________________________
                    / _______/ |_|   |_| |_||_|\______________________________ \
                   / /                                                        \ \
                  | |                                                          | |
                  | |                                                          | |
                  | |   ___       __  __  __      _____                      __| |
                  | |  / _ )___ _/ /_/ /_/ /__   / ___/______  __ _____  ___/ /| |
                  | | / _  / _ `/ __/ __/ / -_) / (_ / __/ _ \/ // / _ \/ _  / | |
                  | |/____/\_,_/\__/\__/_/\__/  \___/_/  \___/\_,_/_//_/\_,_/  | |
                  | |                                                          | |
                  | |                                                          | |
                  | |                                                          | |
                   \ \____________________________    _   ___   ____   _______/ /
                    \___________________________  |  | | / _ \ |  _ \ / _______/
                                                | |/\| ||  _  ||    / > \
                                                 \_/\_/ |_| |_||_|\_\|__/

## Introduction

**Star Wars BattleGround** is a small console RPG game based on the Star Wars universe.

## Install Instructions

You can get the source code from scratch or simply install a [realese version](https://github.com/Horizon-NTH/Star-Wars-BattleGround/releases).

* Get source code

    You first need to clone with [git](https://git-scm.com) the [repository](https://github.com/Horizon-NTH/Star-Wars-BattleGround.git)


```bash
    git clone https://github.com/Horizon-NTH/Star-Wars-BattleGround.git
```

* Create build environment

    You need to use [CMake](https://cmake.org/) to generate the build environment for this project. So you have to make sure that you have a working CMake installation on your system.

```bash
    cd Star-Wars-Battleground
    mkdir build && cd build
    cmake ..
```

* Build

  * **CMake**

    You can build directly using [CMake](https://cmake.org/).

    ```bash
    cmake --build .
    ```

    This command will create the executable in `bin/`.

  * **Microsoft Visual Studio**

    You can also use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to launch the project and build it. Simply open the `star-wars-battleground.sln` file with Microsoft Visual Studio.

    ⚠️ Caution! The repository utilizes a data file, so please be mindful of potential errors related to the working directory.