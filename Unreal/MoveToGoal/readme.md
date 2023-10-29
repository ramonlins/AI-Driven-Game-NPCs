## Introduction
Hey there! So, Unreal currently lacks a Linux plugin for training agents. I'm working on crafting a straightforward solution to bridge that gap.

You'll find the core code in the Source folder. Here's a quick rundown:

- MoveAgentToGoal.h and MoveAgentToGoal.cpp
- Agent.h and Agent.cpp
- SocketClient.h and SocketClient.cpp
- ObservationCollector.h and ObservationCollector.cpp
- SocketServer.py
- inference.py (heads up: this one's still a work in progress and isn't functioning yet)

## Current Progress
On the client side, the environment sends over the agent's 3D location. Meanwhile, over on the server side, the agent gets the environment's observation and shoots back with an action. This action is a 2D location since we're not using the z-axis right now.

Right now, our agent's moving pretty randomly, as you can see here:

![Demo Gif](demo.gif)
Up next on the to-do list:

- Implementing rewards;
- Getting inference up and running;
- Training the agent;
- Final touches on the environment (like adding walls and a goal);

Keep in mind this is all pretty casual. Feel free to dive in and take a look around!

## Limitations
- Uses localhost ports to exchange data between Unreal and Python.
    - Multiple instances can have their ports collide, leading to errors.
- Communication between Unreal and python is not secure.
- On Linux, ports are not released immediately after the communication closes. As such, you cannot reuse ports right after closing a UnityEnvironment.
