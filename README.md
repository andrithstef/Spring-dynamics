
# Physics Simulation

This is a physics simulation written in C++ using SFML. It simulates the behavior of weights connected by springs and includes features such as gravity, torque, and angular momentum to create realistic movements.

## Features

- Place weights and attach springs to simulate their interactions.
- Realistic physics simulation with gravity, torque, and angular momentum.
- Visual representation of weights and springs using SFML graphics.
- Interactive interface for adding and manipulating weights and springs.

## Dependencies

- C++ compiler (supporting C++11 or later)
- SFML library

## Building the Project

To build the project, follow these steps:

1. Clone the repository or download the source code.
2. Install SFML library if not already installed.
3. Open a terminal or command prompt and navigate to the project directory.
4. Run the following command to compile the source code:

```shell
make
```
This command will generate the executable file named PhysicsSimulation.

Run the program using the following command:

```shell
./PhysicsSimulation
```

The simulation will launch, and you can interact with it using the specified controls.


## Usage

The simulation provides the following controls:

- **Place Weight Mode (w)**: Press the `w` key to enter the "Place Weight" mode.
  - Left-click: Place a weight at the clicked position. The weight will not be connected to anything.
  - Press `s`: Place a weight and immediately connect a new spring to it. You can then place the other end of the spring by left-clicking.

- **Place Spring Mode (s)**: Press the `s` key to enter the "Place Spring" mode.
This creates a spring and connects one side at the location of the mouse cursor. If overlapping a weight, it will connect to it.
  - Left-click on a weight: Connect a spring to the clicked weight and enter the "Place Spring" mode. You can then place the other end of the spring by left-clicking anywhere.
  - Left-click on the background: Connect a spring to the background.

- **Pause/Resume**: Press the `Esc` key to pause or resume the simulation.

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to explore, modify, and distribute the code as per the terms of the license.

