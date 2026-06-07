# OOP-Theory-Project-
Ashna Sami Butt 562
Ayesha Zulqarnain 563

## Compilation and Running

### 🪟 Windows (PowerShell / Command Prompt)
On Windows, you can compile the program using `g++` (via MinGW/MSYS2). 

#### Option 1: Native Wildcard (PowerShell)
PowerShell does not expand wildcards the same way Linux does. Since MinGW's compiler has built-in wildcard expansion, wrap the paths in quotes so they are passed directly to `g++`:
```powershell
g++ -std=c++17 main.cpp "users/*.cpp" "vehicles/*.cpp" "core/*.cpp" "engine/*.cpp" -o transport_system.exe
```

#### Option 2: Explicit List (PowerShell / Command Prompt)
If the wildcard command above gives errors, list the source files explicitly:
```powershell
```

To run on Windows:
```powershell
.\transport_system.exe
```
