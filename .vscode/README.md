This project ships with a default vscode configuration so that it can be
somewhat usable on https://github.dev out of the box, and serve as a reference
for configuring other editors.

## c_cpp_properties.json

```json
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
