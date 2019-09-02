This project is based off one of my first projects made in C++. At the time the project was a bit ambitious for
my ability but I created it with the very limited knowledge I had. It worked and it is a project I am proud of
but it includes many issues with regards to efficiency and formatting. I have included it with this project to show
the difference of what I am currently working on and what it is originally based off.
(I then learnt later that, although my idea and methods may be unique, the idea predated me by a few decades...)

The goal of this project is to make a multi-level game with different rooms that the player can explore. In the rooms
will include traps, monsters and objects that the player can interract with. This project will also include colours that
can be modified, saving and map creation.

The method that this project uses for its level creation and saving is a basic method that is carried over from the original
version. The level is read from a file (called "map") in the level file. Each line in this file consists of numbers that
represent different objects in the level. Such as "0" being an empty space, "1" being the starting point for the player
and "10" being a wall.
The line number dictates the room number and will be accessed if the player stands on a tile with
the value equal to the negative of that line number. A feature that is not in the old version is the ability to make
custom objects such as projectile launchers (WIP) and things that are not stuck in place on the map. This information can
be modified on the "objects" file.