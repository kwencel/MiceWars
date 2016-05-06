# MiceWars
A 2D game written in C++ and SDL2 based on Worms concept.

# Build prerequisites
    CMake 3.3 (it will probably compile using older version too, see the last paragraph)
    SDL 2.0
    SDL_image 2.0
    SDL_TTF 2.0

# Build instructions
```
$ cmake .
$ make
```

# Configuration
**Use config.ini file to adjust game settings to your needs.**
```
FPS           Sets the Frames Per Second the game will be running at.
              Doesn't affect the speed of the gameplay itself.

Width         Sets game resolution (X axis)

Height        Sets game resolution (Y axis)
```

# How to play?

Use left and right arrow keys to move your mouse to desired position.
Press space to switch to aiming mode and use up and down arrow keys to place crosshair at desired position.
You can also use 1, 2, 3, 4 keys to change weapon. Finally, press space to fire a chosen weapon.
There is no need to hold space as it doesn't affect the bullet trajectory like in original Worms.
You win when your mice are the last ones standing on the battlefield.

#### Weapons overview

| Key | Weapon  | Damage  | Blast radius | Affected by gravity? |
|-----|---------|:-------:|:------------:|:--------------------:|
| 1   | Shotgun | 30      | Short        |  No                  |
| 2   | Bazooka | 50      | Medium       |  Yes                 |
| 3   | Grenade | 40      | Long         |  Yes                 |
| 4   | Cheese  | 80      | Longest      |  Yes                 |

# Too old CMake version?
Try to change the minimum required version in CMakeLists.txt to match the version you have installed. There shouldn't be any issues.
