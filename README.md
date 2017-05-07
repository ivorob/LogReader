Generate project files
==============================

Use the following scenario to generate project files:

1. Run VC++ command prompt
2. Invoke the following command to generate project files `cmake -G "Visual Studio 14 2015" path\to\logreader`

Build project
===============================

To build the project you can do the folloing:
1. Invoke the following command: `msbuild LogReader.sln /property:Platform="Win32"`
2. Or use VC++ IDE

Executable
================================

"build" directory contains executable files for x86/x64 architectures
