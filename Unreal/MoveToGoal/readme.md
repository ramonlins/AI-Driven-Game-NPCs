## Introduction
Hey there! So, Unreal currently lacks a Linux plugin for training agents. I'm working on crafting a straightforward solution to bridge that gap.

You'll find the core code in the Source folder.

## Prerequisites
To execute this project install unreal on linux, copy the project and open it.

To use inference.py is necessary to install numpy and torch.

## Current Progress
On the client side, the environment sends over the agent's 3D location. Meanwhile, over on the server side, the agent gets the environment's observation and shoots back with an action. This action is a 2D location since we're not using the z-axis right now.

Previously, the agent moves pretty randomly, as you can see here:

<img src="demo.gif" width="960" height="540">

Up next on the to-do list:
- Player control [x];
- Implementing rewards [x];
- Getting inference up and running [x];
- Training the agent [];
- Environment (adding walls and a goal) [x];

it still moves randomly, but now is inside walls and have a target:

<img src="demo2.gif" width="960" height="540">

moreover, it can be controlled by keyboard using w(up), s(down), a(left) , d(right) keys:

<img src="demo3.gif" width="960" height="540">

Keep in mind this is all pretty casual. Feel free to dive in and take a look around!

## Limitations
- Uses localhost ports to exchange data between Unreal and Python.
    - Multiple instances can have their ports collide, leading to errors.
- Communication between Unreal and python is not secure.
- On Linux, ports are not released immediately after the communication closes. As such, you cannot reuse ports right after closing a UnityEnvironment.
