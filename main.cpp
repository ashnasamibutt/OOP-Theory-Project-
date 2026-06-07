#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
using namespace std;

#include "core/DynamicArray.h"
#include "users/Admin.h"
#include "users/Student.h"
#include "users/Driver.h"
#include "vehicles/Bus.h"
#include "vehicles/Van.h"
#include "engine/TransportManager.h"

//  GLOBAL STATE

DynamicArray<User*> users(10);

// Auto-increment ID counters (updated during load)
int nextUserId    = 1;
int nextVehicleId = 1;
int nextRouteId   = 1;
int nextPassId    = 1;

TransportManager manager;

//  INPUT HELPERS


// Clears bad cin state and flushes the input buffer
void clearInput() {
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

// Returns a validated integer within [min, max]
int getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        cout << "  [!] Invalid input. Enter a number between "
             << min << " and " << max << ".\n";
        clearInput();
    }
}

// Returns a non-empty trimmed string
string getStringInput(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) return value;
        cout << "  [!] Input cannot be empty. Try again.\n";
    }
}

// Returns a float greater than zero
float getFloatInput(const string& prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            clearInput();
            return value;
        }
        cout << "  [!] Enter a positive number.\n";
        clearInput();
    }
}

//  USER ARRAY MANAGEMENT

void addUser(User* user) {
    users.push_back(user);
}

User* findUserByEmail(const string& email) {
    for (int i = 0; i < users.getSize(); i++)
        if (users[i]->getEmail() == email)
            return users[i];
    return nullptr;
}

User* findUserById(int id) {
    for (int i = 0; i < users.getSize(); i++)
        if (users[i]->getId() == id)
            return users[i];
    return nullptr;
}

//  PERSISTENCE — USERS

void saveUsers() {
    ofstream out("users.txt");
    if (!out.is_open()) {
        cout << "[Error] Could not open users.txt for writing.\n";
        return;
    }
    for (int i = 0; i < users.getSize(); i++)
        users[i]->saveToFile(out);
    out.close();
    cout << "[Info] Users saved successfully.\n";
}

void loadUsers() {
    ifstream in("users.txt");
    if (!in.is_open()) return;   // First run — file doesn't exist yet

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type;
        getline(ss, type, '|');

        try {
            if (type == "STUDENT") {
                string id, name, email, pass, roll, dept, hasPass;
                getline(ss, id,      '|');  getline(ss, name,    '|');
                getline(ss, email,   '|');  getline(ss, pass,    '|');
                getline(ss, roll,    '|');  getline(ss, dept,    '|');
                getline(ss, hasPass, '|');

                Student* s = new Student(stoi(id), name, email, pass, roll, dept);
                s->setHasTransportPass(stoi(hasPass));
                addUser(s);
                if (stoi(id) >= nextUserId) nextUserId = stoi(id) + 1;
            }
            else if (type == "ADMIN") {
                string id, name, email, pass, code;
                getline(ss, id,   '|');  getline(ss, name,  '|');
                getline(ss, email,'|');  getline(ss, pass,  '|');
                getline(ss, code, '|');

                Admin* a = new Admin(stoi(id), name, email, pass, code);
                addUser(a);
                if (stoi(id) >= nextUserId) nextUserId = stoi(id) + 1;
            }
            else if (type == "DRIVER") {
                string id, name, email, pass, lic, vid, avail;
                getline(ss, id,    '|');  getline(ss, name,  '|');
                getline(ss, email, '|');  getline(ss, pass,  '|');
                getline(ss, lic,   '|');  getline(ss, vid,   '|');
                getline(ss, avail, '|');

                Driver* d = new Driver(stoi(id), name, email, pass, lic);
                d->setAssignedVehicleId(stoi(vid));
                addUser(d);
                if (stoi(id) >= nextUserId) nextUserId = stoi(id) + 1;
            }
        }
        catch (const exception& e) {
            cout << "[Warning] Skipped malformed user record: " << e.what() << "\n";
        }
    }
    in.close();
    cout << "[Info] Users loaded: " << users.getSize() << "\n";
}

//  PERSISTENCE — COUNTERS

void saveCounters() {
    ofstream out("counters.txt");
    if (!out.is_open()) return;
    out << nextUserId    << "\n"
        << nextVehicleId << "\n"
        << nextRouteId   << "\n"
        << nextPassId    << "\n";
    out.close();
}

void loadCounters() {
    ifstream in("counters.txt");
    if (!in.is_open()) return;
    in >> nextUserId >> nextVehicleId >> nextRouteId >> nextPassId;
    in.close();
}

//  DISPLAY HELPERS

void printHeader(const string& title) {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout <<   "║  " << title;
    int padding = 36 - (int)title.length();
    for (int i = 0; i < padding; i++) cout << " ";
    cout << "║\n";
    cout <<   "╚══════════════════════════════════════╝\n";
}

void printDivider() {
    cout << "  ─────────────────────────────────────\n";
}

//  REGISTRATION

void registerUser() {
    printHeader("REGISTER NEW ACCOUNT");
    cout << "  [1] Student\n";
    cout << "  [2] Admin\n";
    cout << "  [3] Driver\n";
    cout << "  [0] Back\n";
    printDivider();

    int choice = getIntInput("  Choose role: ", 0, 3);
    if (choice == 0) return;

    string name  = getStringInput("  Full Name   : ");
    string email = getStringInput("  Email       : ");

    if (findUserByEmail(email)) {
        cout << "  [!] An account with this email already exists.\n";
        return;
    }

    string password = getStringInput("  Password    : ");

    try {
        if (choice == 1) {
            string roll = getStringInput("  Roll Number : ");
            string dept = getStringInput("  Department  : ");
            Student* s  = new Student(nextUserId++, name, email, password, roll, dept);
            addUser(s);
            cout << "  [✓] Student account created. ID: " << s->getId() << "\n";
        }
        else if (choice == 2) {
            string code = getStringInput("  Admin Code  : ");
            Admin* a    = new Admin(nextUserId++, name, email, password, code);
            addUser(a);
            cout << "  [✓] Admin account created. ID: " << a->getId() << "\n";
        }
        else if (choice == 3) {
            string lic = getStringInput("  License No  : ");
            Driver* d  = new Driver(nextUserId++, name, email, password, lic);
            addUser(d);
            cout << "  [✓] Driver account created. ID: " << d->getId() << "\n";
        }
    }
    catch (const invalid_argument& e) {
        cout << "  [!] Registration failed: " << e.what() << "\n";
        nextUserId--;   // Roll back counter on failure
    }
}

//  LOGIN

User* loginUser() {
    printHeader("LOGIN");

    string email    = getStringInput("  Email    : ");
    string password = getStringInput("  Password : ");

    User* user = findUserByEmail(email);
    if (!user) {
        cout << "  [!] No account found with this email.\n";
        return nullptr;
    }
    if (!user->validatePassword(password)) {
        cout << "  [!] Incorrect password.\n";
        return nullptr;
    }

    cout << "  [✓] Welcome, " << user->getName()
         << " (" << user->getRole() << ")\n";
    return user;
}

//  STUDENT MENU

void studentMenu(Student* student) {
    bool loggedIn = true;

    while (loggedIn) {
        printHeader("STUDENT MENU");
        cout << "  [1] View All Routes\n";
        cout << "  [2] Apply for Transport\n";
        cout << "  [3] View My Registration\n";
        cout << "  [4] Cancel Registration\n";
        cout << "  [0] Logout\n";
        printDivider();

        int choice = getIntInput("  Choose: ", 0, 4);

        switch (choice) {

            // ── View Routes ────────────────────────
            case 1:
                manager.displayAllRoutes();
                break;

            // ── Apply for Transport ────────────────
            case 2: {
                if (student->getHasTransportPass()) {
                    cout << "  [!] You already have an active transport registration.\n";
                    break;
                }
                if (manager.getRouteCount() == 0) {
                    cout << "  [!] No routes available at the moment.\n";
                    break;
                }

                manager.displayAllRoutes();
                int routeId = getIntInput("  Enter Route ID to apply: ", 1, 99999);

                Route* route = manager.findRouteById(routeId);
                if (!route) {
                    cout << "  [!] Route ID " << routeId << " not found.\n";
                    break;
                }
                if (route->getAssignedVehicleId() == -1) {
                    cout << "  [!] No vehicle assigned to this route yet.\n";
                    break;
                }

                Vehicle* vehicle = manager.findVehicleById(route->getAssignedVehicleId());
                if (!vehicle || !vehicle->hasAvailableSeat()) {
                    cout << "  [!] Vehicle on this route is full.\n";
                    break;
                }

                // Fee = Rs. 50 per km monthly
                float  fee     = route->getDistanceKm() * 50.0f;
                string dueDate = "30-06-2026";   // Fixed billing cycle

                try {
                    TransportPass* pass = new TransportPass(
                        nextPassId++,
                        student->getId(),
                        route->getRouteId(),
                        vehicle->getVehicleId(),
                        "06-06-2026",
                        fee,
                        dueDate
                    );
                    manager.addPass(pass);
                    student->setHasTransportPass(true);
                    cout << "  [✓] Application submitted. Monthly fee: Rs. " << fee << "\n";
                    cout << "      Awaiting admin approval.\n";
                }
                catch (const exception& e) {
                    cout << "  [!] Application failed: " << e.what() << "\n";
                    nextPassId--;
                }
                break;
            }

            // ── View My Registration ───────────────
            case 3: {
                TransportPass* pass = manager.findPassByStudentId(student->getId());
                if (!pass) {
                    cout << "  [!] You have no active registration.\n";
                    break;
                }
                pass->displayPass();

                // Display route info alongside
                Route* route = manager.findRouteById(pass->getRouteId());
                if (route) route->displayInfo();
                break;
            }

            // ── Cancel Registration ────────────────
            case 4: {
                TransportPass* pass = manager.findPassByStudentId(student->getId());
                if (!pass) {
                    cout << "  [!] You have no active registration to cancel.\n";
                    break;
                }
                if (pass->getStatus() == "Approved") {
                    // Release the seat back
                    Vehicle* vehicle = manager.findVehicleById(pass->getVehicleId());
                    if (vehicle) vehicle->releaseSeat();
                }
                pass->cancel();
                student->setHasTransportPass(false);
                cout << "  [✓] Registration cancelled successfully.\n";
                break;
            }

            case 0:
                cout << "  [✓] Logged out.\n";
                loggedIn = false;
                break;
        }
    }
}

//  ADMIN MENU

void adminMenu(Admin* admin) {
    bool loggedIn = true;

    while (loggedIn) {
        printHeader("ADMIN MENU");
        cout << "  [1]  Add Vehicle\n";
        cout << "  [2]  Remove Vehicle\n";
        cout << "  [3]  View All Vehicles\n";
        cout << "  [4]  Add Route\n";
        cout << "  [5]  Assign Vehicle to Route\n";
        cout << "  [6]  View All Routes\n";
        cout << "  [7]  View Pending Applications\n";
        cout << "  [8]  Approve Application\n";
        cout << "  [9]  Reject Application\n";
        cout << "  [10] View All Passes\n";
        cout << "  [11] Generate Report\n";
        cout << "  [12] Save All Data\n";
        cout << "  [0]  Logout\n";
        printDivider();

        int choice = getIntInput("  Choose: ", 0, 12);

        switch (choice) {

            // ── Add Vehicle ────────────────────────
            case 1: {
                printHeader("ADD VEHICLE");
                cout << "  [1] Bus\n";
                cout << "  [2] Van\n";
                int type = getIntInput("  Vehicle type: ", 1, 2);

                string vnum   = getStringInput("  Vehicle Number : ");
                int    cap    = getIntInput("  Capacity       : ", 1, 100);
                string driver = getStringInput("  Driver Name    : ");

                try {
                    if (type == 1) {
                        cout << "  Has AC? [1] Yes  [0] No\n";
                        int ac = getIntInput("  : ", 0, 1);
                        Bus* bus = new Bus(nextVehicleId++, vnum, cap, driver, (bool)ac);
                        manager.addVehicle(bus);
                    }
                    else {
                        string model = getStringInput("  Van Model : ");
                        Van* van     = new Van(nextVehicleId++, vnum, cap, driver, model);
                        manager.addVehicle(van);
                    }
                }
                catch (const exception& e) {
                    cout << "  [!] Failed: " << e.what() << "\n";
                    nextVehicleId--;
                }
                break;
            }

            // ── Remove Vehicle ─────────────────────
            case 2: {
                manager.displayAllVehicles();
                int vid = getIntInput("  Enter Vehicle ID to remove: ", 1, 99999);
                manager.removeVehicle(vid);
                break;
            }

            // ── View All Vehicles ──────────────────
            case 3:
                manager.displayAllVehicles();
                break;

            // ── Add Route ──────────────────────────
            case 4: {
                printHeader("ADD ROUTE");
                string start = getStringInput("  Start Point  : ");
                string end   = getStringInput("  End Point    : ");
                float  dist  = getFloatInput ("  Distance(km) : ");

                try {
                    Route* route = new Route(nextRouteId++, start, end, dist);
                    manager.addRoute(route);
                    cout << "  [✓] Route added. Monthly fee will be Rs. "
                         << dist * 50.0f << "\n";
                }
                catch (const exception& e) {
                    cout << "  [!] Failed: " << e.what() << "\n";
                    nextRouteId--;
                }
                break;
            }

            // ── Assign Vehicle to Route ────────────
            case 5: {
                manager.displayAllVehicles();
                int vid = getIntInput("  Vehicle ID : ", 1, 99999);
                manager.displayAllRoutes();
                int rid = getIntInput("  Route ID   : ", 1, 99999);
                manager.assignVehicleToRoute(vid, rid);
                break;
            }

            // ── View All Routes ────────────────────
            case 6:
                manager.displayAllRoutes();
                break;

            // ── View Pending Applications ──────────
            case 7:
                manager.displayPendingPasses();
                break;

            // ── Approve Application ────────────────
            case 8: {
                manager.displayPendingPasses();
                int pid = getIntInput("  Pass ID to approve: ", 1, 99999);

                // Mark the student as having an approved pass
                TransportPass* pass = manager.findPassById(pid);
                if (pass) {
                    manager.approvePass(pid);

                    // Sync Student object
                    User* user = findUserById(pass->getStudentId());
                    if (user && user->getRole() == "Student") {
                        Student* s = static_cast<Student*>(user);
                        s->setHasTransportPass(true);
                    }
                }
                else {
                    cout << "  [!] Pass ID not found.\n";
                }
                break;
            }

            // ── Reject Application ─────────────────
            case 9: {
                manager.displayPendingPasses();
                int pid = getIntInput("  Pass ID to reject: ", 1, 99999);

                TransportPass* pass = manager.findPassById(pid);
                if (pass) {
                    manager.rejectPass(pid);

                    // Sync Student object
                    User* user = findUserById(pass->getStudentId());
                    if (user && user->getRole() == "Student") {
                        Student* s = static_cast<Student*>(user);
                        s->setHasTransportPass(false);
                    }
                }
                else {
                    cout << "  [!] Pass ID not found.\n";
                }
                break;
            }

            // ── View All Passes ────────────────────
            case 10:
                manager.displayAllPasses();
                break;

            // ── Generate Report ────────────────────
            case 11: {
                printHeader("SYSTEM REPORT");

                // ── Summary ───────────────────────
                cout << "\n  ┌─────────────────────────────────┐\n";
                cout <<   "  │         SYSTEM SUMMARY          │\n";
                cout <<   "  ├─────────────────────────────────┤\n";
                cout <<   "  │ Total Vehicles   : " << manager.getVehicleCount() << "\n";
                cout <<   "  │ Total Routes     : " << manager.getRouteCount()   << "\n";
                cout <<   "  │ Total Passes     : " << manager.getPassCount()    << "\n";

                // ── Revenue Calculation ───────────
                float   totalRevenue  = 0.0f;
                int     approvedCount = 0;
                int     pendingCount  = 0;
                int     cancelledCount= 0;

                for (int i = 0; i < manager.getPassCount(); i++) {
                    // We iterate via findPassById — build a simple loop
                    // using a known fact that pass IDs start at 1
                }

                // Re-display via displayAllPasses and count inline
                // Since TransportManager doesn't expose the raw array,
                // we calculate from what we know
                cout <<   "  │ Registered Users : " << users.getSize() << "\n";
                cout <<   "  └─────────────────────────────────┘\n";

                // ── Per-Route usage ───────────────
                cout << "\n  ROUTE USAGE\n";
                printDivider();
                for (int rid = 1; rid < nextRouteId; rid++) {
                    Route* r = manager.findRouteById(rid);
                    if (!r) continue;
                    Vehicle* v = (r->getAssignedVehicleId() != -1)
                                    ? manager.findVehicleById(r->getAssignedVehicleId())
                                    : nullptr;

                    cout << "  Route " << r->getRouteId()
                         << " (" << r->getStartPoint() << " → " << r->getEndPoint() << ")"
                         << " | Distance: " << r->getDistanceKm() << " km"
                         << " | Fee: Rs. " << r->getDistanceKm() * 50.0f;

                    if (v)
                        cout << " | Seats: " << v->getSeatsOccupied()
                             << "/" << v->getCapacity();
                    cout << "\n";
                }
                break;
            }

            // ── Save All Data ──────────────────────
            case 12:
                saveUsers();
                manager.saveAll();
                saveCounters();
                cout << "  [✓] All data saved.\n";
                break;

            case 0:
                cout << "  [✓] Logged out.\n";
                loggedIn = false;
                break;
        }
    }
}

// ═══════════════════════════════════════════════════════
//  MAIN MENU
// ═══════════════════════════════════════════════════════

void mainMenu() {
    bool running = true;

    while (running) {
        printHeader("UNIVERSITY TRANSPORT SYSTEM");
        cout << "  [1] Register\n";
        cout << "  [2] Login\n";
        cout << "  [0] Exit\n";
        printDivider();

        int choice = getIntInput("  Choose: ", 0, 2);

        switch (choice) {

            case 1:
                registerUser();
                break;

            case 2: {
                User* user = loginUser();
                if (!user) break;

                string role = user->getRole();

                if (role == "Student")
                    studentMenu(static_cast<Student*>(user));
                else if (role == "Admin")
                    adminMenu(static_cast<Admin*>(user));
                else if (role == "Driver")
                    cout << "  [!] Driver portal not yet implemented.\n";

                break;
            }

            case 0:
                // Auto-save on exit
                cout << "\n  Saving data before exit...\n";
                saveUsers();
                manager.saveAll();
                saveCounters();
                cout << "  Goodbye.\n\n";
                running = false;
                break;
        }
    }
}

// ═══════════════════════════════════════════════════════
//  ENTRY POINT
// ═══════════════════════════════════════════════════════

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    // Load all persisted data
    loadCounters();
    loadUsers();
    manager.loadAll();

    // Launch
    mainMenu();

    // Cleanup
    for (int i = 0; i < users.getSize(); i++) delete users[i];

    return 0;
}