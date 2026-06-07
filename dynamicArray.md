# Migration Plan: Raw Double Pointers ➔ `DynamicArray`

We have added the `DynamicArray` class template at [core/DynamicArray.h](file:///run/media/ammarbinyasir/InternalDrive/Ammar-Personal/University/Semester2/OOP-LAB/OOP-Theory-Project-/core/DynamicArray.h). 

Below is the exact guide showing which files need to be changed and how to refactor them.

---

## 1. Changes in `main.cpp`

### 🔹 Include the Template Header
At the top of the file, include `DynamicArray.h`:
```cpp
#include "core/DynamicArray.h"
```

### 🔹 Update Global State
Replace the raw pointer array and tracking variables:
```diff
-User**           users        = nullptr;
-int              userCount    = 0;
-int              userCapacity = 10;
+DynamicArray<User*> users(10);
```

### 🔹 Simplify User Insertion & Management
Remove the helper functions for resizing and update `addUser`:
```diff
-void resizeUsers() {
-    userCapacity *= 2;
-    User** temp = new User*[userCapacity];
-    for (int i = 0; i < userCount; i++) temp[i] = users[i];
-    delete[] users;
-    users = temp;
-}
-
 void addUser(User* user) {
-    if (userCount == userCapacity) resizeUsers();
-    users[userCount++] = user;
+    users.push_back(user);
 }
```

### 🔹 Update Loops & Lookups
Throughout `main.cpp`, replace `userCount` with `users.getSize()`. Because `DynamicArray` overloads `operator[]`, indexing via `users[i]` remains completely unchanged.
For example, in `findUserById`:
```diff
-for (int i = 0; i < userCount; i++)
+for (int i = 0; i < users.getSize(); i++)
```

### 🔹 Update Cleanup in `main()`
Remove manual memory deallocation for the array itself:
```diff
     // Cleanup
-    for (int i = 0; i < userCount; i++) delete users[i];
-    delete[] users;
+    for (int i = 0; i < users.getSize(); i++) delete users[i];
```

---

## 2. Changes in `engine/TransportManager.h`

### 🔹 Include the Template Header
Include the template at the top:
```cpp
#include "../core/DynamicArray.h"
```

### 🔹 Replace Core Member Variables
Replace the double-pointer arrays, count variables, capacity variables, and resize helpers:
```diff
 class TransportManager {
 private:
-    Vehicle**       vehicles;
-    int             vehicleCount;
-    int             vehicleCapacity;
-
-    Route**         routes;
-    int             routeCount;
-    int             routeCapacity;
-
-    TransportPass** passes;
-    int             passCount;
-    int             passCapacity;
-
-    // Internal resize helpers
-    void resizeVehicles();
-    void resizeRoutes();
-    void resizePasses();
+    DynamicArray<Vehicle*>       vehicles;
+    DynamicArray<Route*>         routes;
+    DynamicArray<TransportPass*> passes;
```

---

## 3. Changes in `engine/TransportManager.cpp`

### 🔹 Simplify Constructor & Destructor
Remove manual array allocations from the constructor:
```diff
 TransportManager::TransportManager()
 {
-    vehicleCapacity = 10;
-    vehicleCount    = 0;
-    vehicles        = new Vehicle*[vehicleCapacity];
-
-    routeCapacity   = 10;
-    routeCount      = 0;
-    routes          = new Route*[routeCapacity];
-
-    passCapacity    = 10;
-    passCount       = 0;
-    passes          = new TransportPass*[passCapacity];
+    // No manual allocations needed; DynamicArray handles its own initialization!
 }
```

Update the destructor to delete the objects, but omit deleting the array shell:
```diff
 TransportManager::~TransportManager() {
-    for (int i = 0; i < vehicleCount; i++) delete vehicles[i];
-    delete[] vehicles;
-
-    for (int i = 0; i < routeCount; i++) delete routes[i];
-    delete[] routes;
-
-    for (int i = 0; i < passCount; i++) delete passes[i];
-    delete[] passes;
+    for (int i = 0; i < vehicles.getSize(); i++) delete vehicles[i];
+    for (int i = 0; i < routes.getSize(); i++) delete routes[i];
+    for (int i = 0; i < passes.getSize(); i++) delete passes[i];
 }
```

### 🔹 Delete Resize Implementations
Completely remove the definitions of:
* `TransportManager::resizeVehicles()`
* `TransportManager::resizeRoutes()`
* `TransportManager::resizePasses()`

### 🔹 Simplify Object Ingestion
In methods like `addVehicle`, `addRoute`, and `addPass`, remove the capacity checks and manual counts:
```diff
 void TransportManager::addVehicle(Vehicle* vehicle) {
     // Validation checks...
-    if (vehicleCount == vehicleCapacity) resizeVehicles();
-    vehicles[vehicleCount++] = vehicle;
+    vehicles.push_back(vehicle);
 }
```

### 🔹 Simplify Object Removal
Using `removeAt(index)` eliminates manual element shifting:
```diff
 bool TransportManager::removeVehicle(int vehicleId) {
-    for (int i = 0; i < vehicleCount; i++) {
+    for (int i = 0; i < vehicles.getSize(); i++) {
         if (vehicles[i]->getVehicleId() == vehicleId) {
             // validation checks...
             delete vehicles[i];
-            vehicles[i] = vehicles[--vehicleCount];
+            vehicles.removeAt(i);
             return true;
         }
     }
```

### 🔹 Replace Counter Variables with `.getSize()`
Replace `vehicleCount`, `routeCount`, and `passCount` references with `.getSize()` throughout the file.
For example:
```diff
-int TransportManager::getVehicleCount() const { return vehicleCount; }
+int TransportManager::getVehicleCount() const { return vehicles.getSize(); }
```
