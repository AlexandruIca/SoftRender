#!/usr/bin/python3

import json

array = []

with open("./compile_commands.json") as f:
    data = json.load(f)
    for obj in data:
        if not obj["file"].endswith("mocs_compilation.cpp"):
            string = ""
            string = string + '{' + '\n'
            string = string + '  "directory": "' + obj["directory"] + '",' + '\n'
            string = string + '  "command": "' + obj["command"] + '",' + '\n'
            string = string + '  "file": "' + obj["file"] + '"' + '\n'
            string = string + '}'
            array.append(string)
    print('[')
    for i in range(0, len(array) - 1):
        print(array[i], end="")
        print(',')
    print(array[len(array) - 1])
    print(']')

