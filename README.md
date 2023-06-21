# GAME DATA VISUALIZER

This tool can be used for certain Sonic the Hedgehog games to create realtime progress bars of your score including any
end of level bonus as well as visualizing the score milestones to achieve certain ranks

A Demonstration can be found here using Sonic Colours as an Example

[![Sonic Colours Rank Progress Bar Test](http://img.youtube.com/vi/hROWg-yJelY/0.jpg "Sonic Colours Rank Progress Bar Test")](http://www.youtube.com/watch?v=hROWg-yJelY "Sonic Colors Score Progress Bar Demo")

This project is broken up into 4 parts
- The memory which defines the classes whose job it is to read the processes memory
- The display which is used to actually create the window
- The game data which defines:
  - which addresses in memory held which data
  - how to process that data
  - how the data is to be displayed
- Utilities from a personal reusable library for:
  - byte swapping
  - managing SDL instances

## MEMORY

This folder defines the classes used to read a process's memory.
As of now, only this will only compile on Unix systems.

The base class `abstract_process` given subclasses that define how to read the bytes themselves, can read data for any trivially copiable struct or array of such structs
and reads/writes the correct number of bytes, as well as byte swapping to correct of incompatible endianness.

### Native Process

This subclass is used to define read and write for processes running natively, and as a result, define fairly trivial read/write
operations

### Dolphin Process

This subclass is used for games running withing the Dolphin Emulator. This requires finding the native address Dolphin uses
for the memory of the emulated system as well as translating the emulated address to the native address. Because the Dolphin Emulator emulates
the Nintendo Gamecube and Nintendo Wii systems, which are big endian systems, it also has to check if the native endian to know
if it should byte-swap read and written data.

### Helpers

Inside the include folder [this file](./memory/include/helpers.h) contains some helper macros which will help the data in the game
folder to define which addresses are associated with each value. Using each macro will define a `get_{name}` function which
will get the value of that variable and return the associated type and possibly a `{name}_address` variable to use at a later point.

- `GAME_VARIABLE(type, name, address)`
  - Defines a simple variable associated with a particular address and type.
- `GAME_INDIRECT_VARIABLE(type, name, base, offset)`
  - Defines a variable whose value exists pointed to by a dynamic address.
- `GAME_VARIABLE_OFFSET(type, name, address, offset)`
  - Defines a variable whose value exists at a dynamic offset to a static address.
- `GAME_ARRAY_VARIABLE(type, name, address, size)`
  - Defines an array variable associated with a particular address and type.
  - Also defines a `get_{name}_at` function to get a specific value at a given offset

### Byte Swapping

Withing my custom library, there are utilities to defined to facilitate byte swapping.

First withing [this file](./ox_lib/include/types/_endiable.h), concepts are defined that allow use to test if data can be bytes swapped.
Mostly arithmetic, pointer, and enum types.
The class and associated concept `is_custom_endianable` tests to see if a `endian_swap` method is defined for a type, which can
be used to define custom byte swapping behaviour for certain types.

Using these, [this file](./ox_lib/include/ox/bytes.h) defines the methods to preform the byte swapping.
If it is an integral type, simpling doing some bit shifting is used to swap bytes. For other scalar types, conversion to unsigned before bit shifting.
Lastly, if there is a custom byte-swap function available, simply call that.

## DISPLAY

This folder contains all the code used to use SDL2 to render the progress bar as well as other data.
This uses a simple SDL2 window class from my library which mostly just holds and handles allocated resources.

The two main files are
 - rankX.cpp/hpp
   - [This file](./display/rankX.cpp) defines most of the functions used to draw to the screen.
This includes drawing the progress bar, the rank threshold marks, and the score requirements underneath.
 - display.cpp/hpp
   - This defines the main loop for the progress bar. Using completely static classes as templates, you can define some of the specifics per game
   - The needed static values for the template are:
     - `process_type`: the type of the process class used to read memory
     - `display_dimensions`: the dimensions of the progress window
     - `score_names`: labels used for the different types of scores
     - `render_sleep`: the duration between refreshes
     - `level_state`: struct holding data of current level
     - `static_calculations`: a struct to hold state data that persists. must include a `level_state` called level
     - `read_level_state`: function that reads the which level that is currently loaded
     - `read_stage_data`: function to read the new level data when the level changes
     - `get_rank_data`: function to read the rank requirements
     - `load_rank_text`: loads the textures for the score values as text
     - `draw_state`: calls the draw function from `rank.cpp` to draw level data
     - `draw_data`: call the draw function to draw dynamic data ever `render_sleep`

## GAME

This folder is used to define all the data used for specific games.
Each game usually has the following files:
- [variables.hpp](./games/sonic_adventure_2/include/sa2/variables.hpp)
  - List of game variables with their addresses and types, using the macros defined in them memory helpers file
- [enum.hpp](./games/sonic_adventure_2/include/sa2/enum.hpp)
  - List of any enums you may want to define for convenience
- [structs.hpp](./games/sonic_adventure_2/include/sa2/structs.hpp)
  - List of mock structs used by the games whose data you are reading
- [data_extractor.cpp](./games/sonic_adventure_2/src/data_extractor.cpp)
  - Defines functions that use the function in variables to read, parse, and transform game data into useful data
- [rank_view.hpp](./games/sonic_adventure_2/include/sa2/rank_view.hpp) and [rank_view.cpp](./games/sonic_adventure_2/src/rank_view.cpp)
  - Defines the static class used to template the display functions


