# Report

## MenuSystem

This is an implementation of a menu system that allows a user to create and operate a Turing machine. The program begins by asking the user for the length of the tape, and then presents a menu with various options. These options allow the user to create a new Turing machine, add a state to an existing machine, execute the machine for a certain number of steps, display the current state and tape contents, and quit the program. The program uses two types of Turing machines, DenseTuringMachine and SparseTuringMachine, and allows the user to switch between them. The program also handles errors, such as when a user attempts to add an invalid state or move off the tape.

## SparseTuringMachine

The `SparseTuringMachine` class uses a `std::vector` container called `states` to store all the `TuringMachineState` objects that have been added to the machine. It also uses a `std::unordered_map` container called `state_map` to map the current state and content of the tape head to the index of the corresponding `TuringMachineState` object in the `states` vector. This sparse representation allows for more efficient lookups and updates of the Turing machine's state.

## DenseTuringMachine

The `DenseTuringMachine` class uses a `std::vector` container called `m_states` to store all the `TuringMachineState` objects that have been added to the machine. 

## TuringMachineState

The overloaded `<<` and `>>` operators are used to output and input the state variables to and from streams, respectively.

The overloaded `<`, `>`, and `==` operators are used to compare two states based on their current state and current content.

## TuringTape

The `TuringTape` class implements a tape for a Turing machine. It stores an infinite tape of integers, with the current position of the tape head, and provides methods to move the tape head left and right, get and set the content of the current cell, and print the contents of the tape.