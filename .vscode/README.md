This project ships with a default vscode configuration so that it can be somewhat usable on
https://github.dev/jcmdln/ploy out of the box, and serve as a reference for configuring other
editors.

## c_cpp_properties.json
```jsonc
{
  "configurations": [
    {
      "name": "linux-clang-x64",
      "includePath": [
        "${workspaceFolder}/**"
      ],
      "defines": [],
      "compilerPath": "/bin/clang++",
      "intelliSenseMode": "linux-clang-x64",
      "compileCommands": "${workspaceFolder}/builddir/compile_commands.json"
    },
    {
      "name": "linux-gcc-x64",
      "includePath": [
        "${workspaceFolder}/**"
      ],
      "defines": [],
      "compilerPath": "/bin/g++",
      "intelliSenseMode": "linux-gcc-x64",
      "compileCommands": "${workspaceFolder}/builddir/compile_commands.json"
    }
  ],
  "version": 4
}
```

## launch.json
```jsonc
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "(gdb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/builddir/ploy",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "gdb",
      "miDebuggerPath": "/bin/gdb",
      "setupCommands": [
        {
          "description": "Enable pretty-printing for gdb",
          "text": "-enable-pretty-printing",
          "ignoreFailures": true
        }
      ]
    },
    {
      "name": "(lldb) Launch",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/builddir/ploy",
      "args": [],
      "stopAtEntry": false,
      "cwd": "${fileDirname}",
      "environment": [],
      "externalConsole": false,
      "MIMode": "lldb",
      "miDebuggerPath": "/bin/lldb",
      "miDebuggerArgs": ""
    }
  ]
}
```
