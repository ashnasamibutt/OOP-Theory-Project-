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

---

## 💾 Data File Formats

The program saves and loads data from pipe-delimited (`|`) text files located in the root directory.

### 1. `users.txt`
Specifies users in the system. The format depends on the user's role:
* **Admin**: `ADMIN|id|name|email|password|adminCode`
  * *Example*: `ADMIN|1|Admin User|admin@fast.edu|admin123|FAST2026`
* **Student**: `STUDENT|id|name|email|password|rollNumber|department|hasTransportPass`
  * *Example*: `STUDENT|2|Ali Khan|ali@gmail.com|ali123|22i-0123|CS|1`
* **Driver**: `DRIVER|id|name|email|password|licenseNumber|assignedVehicleId|isAvailable`
  * *Example*: `DRIVER|4|Sajid Khan|sajid@gmail.com|sajid123|L-78945|1|0`

### 2. `vehicles.txt`
Specifies vehicles. The format depends on the vehicle type:
* **Bus**: `BUS|id|number|capacity|seatsOccupied|driverName|isActive|hasAC`
  * *Example*: `BUS|1|LHR-8899|40|0|Sajid Khan|1|1`
* **Van**: `VAN|id|number|capacity|seatsOccupied|driverName|isActive|vanModel`
  * *Example*: `VAN|2|ISB-1234|15|1|Muhammad Ali|1|Toyota HiAce`

### 3. `routes.txt`
Specifies transport routes:
* **Format**: `ROUTE|id|startPoint|endPoint|distanceKm|assignedVehicleId`
  * *Example*: `ROUTE|1|Rawalpindi Saddar|FAST NUCES Islamabad|18.5|2`
  * *Note*: Set `assignedVehicleId` to `-1` if no vehicle is assigned.

### 4. `registrations.txt`
Specifies transport passes and billing details:
* **Format**: `PASS|passId|studentId|routeId|vehicleId|status|applyDate|billId|monthlyFee|lateFine|isPaid|dueDate|paymentDate`
  * *Example*: `PASS|1|2|1|2|Approved|06-06-2026|1|925.0|0.0|1|30-06-2026|07-06-2026`
  * *Status Options*: `Pending`, `Approved`, `Rejected`, `Cancelled`

### 5. `counters.txt`
Keeps track of the next unique auto-increment IDs. Contains four lines, each with a single integer:
```text
nextUserId
nextVehicleId
nextRouteId
nextPassId
```
* *Example*:
  ```text
  5
  3
  3
  2
  ```
