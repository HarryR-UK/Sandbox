#!/bin/bash

g++ -std=c++20 src/*.cpp -o build/SandSimulation -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
