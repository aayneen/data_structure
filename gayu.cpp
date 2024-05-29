#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_map> // To put a limit on each Room Type

using namespace std;

// Struct to represent a Booking
struct Booking {
    int id;                // Booking ID
    string guestName;      // Guest's name
    string roomType;       // Type of room booked
    int duration;          // Duration of stay in days
    double pricePerNight;  // Price per night for the room

    // Constructor to initialize Booking object
    Booking(int i, const string& name, const string& room, int dur, double price)
        : id(i), guestName(name), roomType(room), duration(dur), pricePerNight(price) {}

    // Function to calculate the total price for the booking
    double calculateTotalPrice() const {
        return duration * pricePerNight;
    }
};

// Class to manage the hotel booking system
class HotelBookingSystem {
private:
    list<Booking> bookings;  // List of bookings
    unordered_map<string, int> roomTypeCounts;  // Map to keep track of the number of bookings per room type
    unordered_map<string, int> roomTypeLimits;  // Map to store the limit for each room type
    int nextId;  // Next booking ID to be assigned

public:
    // Constructor to initialize the booking system
    HotelBookingSystem() : nextId(1) {
        // Initialize room type limits
        roomTypeLimits["Single Room"] = 2;
        roomTypeLimits["Double Room"] = 2;
        roomTypeLimits["Deluxe Room"] = 3;
        roomTypeLimits["Family Suite Room"] = 1;
    }

    // Static function to display available room types and their prices
    static void displayRoomType() {
        cout << "-----------------------------------------";
        cout << "\n| Available Room Type   | Price   \t|\n";
        cout << "-----------------------------------------\n";
        cout << "|1. Single Room\t\t| RM100\t\t|\n";
        cout << "|2. Double Room\t\t| RM130\t\t|\n";
        cout << "|3. Deluxe Room\t\t| RM230\t\t|\n";
        cout << "|4. Family Suite Room\t| RM320\t\t|\n";
        cout << "-----------------------------------------";
    }

    // Function to add a booking
    void addBooking(const string& guestName, const string& roomType, int duration, double pricePerNight) {
        string newRoomType = roomType;

        // Check if the room type exists in the map, otherwise initialize it
        if (roomTypeCounts.find(roomType) == roomTypeCounts.end()) {
            roomTypeCounts[roomType] = 0;
        }

        int currentCount = roomTypeCounts[roomType];  // Current count of the room type
        int limit = roomTypeLimits[roomType];  // Limit for the room type

        // Check if the booking limit for the room type is reached
        if (currentCount < limit) {
            bookings.emplace_back(nextId++, guestName, roomType, duration, pricePerNight);
            roomTypeCounts[roomType]++;
            cout << "\nBooking added successfully.\n";
        } else {
            // If limit is reached, request user to choose a different room type
            cout << "\nBooking limit reached for room type " << roomType << ".\n";
            displayRoomType();
            cout << "\nEnter new room type: ";
            int roomChoice;
            cin >> roomChoice;
            switch (roomChoice) {
                case 1:
                    newRoomType = "Single Room";
                    pricePerNight = 100;
                    break;
                case 2:
                    newRoomType = "Double Room";
                    pricePerNight = 130;
                    break;
                case 3:
                    newRoomType = "Deluxe Room";
                    pricePerNight = 230;
                    break;
                case 4:
                    newRoomType = "Family Suite Room";
                    pricePerNight = 320;
                    break;
                default:
                    cout << "\nInvalid Choice. Defaulting to Single Room." << endl;
                    newRoomType = "Single Room";
                    pricePerNight = 100;
                    break;
            }

            // Check again if the new room type is available
            if (roomTypeCounts[newRoomType] >= roomTypeLimits[newRoomType]) {
                cout << "\nSorry, the " << newRoomType << " is also fully booked." << endl;
                return;
            }

            // Add the booking with the newly selected room type
            bookings.emplace_back(nextId++, guestName, newRoomType, duration, pricePerNight);
            roomTypeCounts[newRoomType]++;
            cout << "\nBooking added successfully.\n";
        }
    }

    // Function to display all bookings
    void displayBookings() const {
        if (bookings.empty()) {
            cout << "\nNo bookings available.\n";
            return;
        }

        for (const auto& booking : bookings) {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\nDISPLAY BOOKING DATA";
            cout << "\nBooking ID: " << booking.id
                 << "\nGuest Name: " << booking.guestName
                 << "\nRoom Type: " << booking.roomType
                 << "\nDuration: " << booking.duration << " days\n"
                 << "\nPrice per Night: RM" << booking.pricePerNight
                 << "\nTotal Price: RM" << booking.calculateTotalPrice() << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }
    }

    // Function to search for a booking by ID
    void searchBookings(int id) const {
        auto it = find_if(bookings.begin(), bookings.end(), [id](const Booking& b) { return b.id == id; });
        if (it != bookings.end()) {
            const Booking& booking = *it;
            cout << "Booking found:";
            cout << "\nBooking ID: " << booking.id;
            cout << "\nGuest Name: " << booking.guestName;
            cout << "\nRoom Type: " << booking.roomType;
            cout << "\nDuration: " << booking.duration << " days\n";
            cout << "\nPrice per Night: RM" << booking.pricePerNight;
            cout << "\nTotal Price: RM" << booking.calculateTotalPrice() << endl;
        } else {
            cout << "Booking ID " << id << " not found.\n";
        }
    }

    // Function to update a booking by ID
    void updateBookings(int ID) {
        auto it = find_if(bookings.begin(), bookings.end(), [ID](const Booking& b) { return b.id == ID; });
        if (it != bookings.end()) {
            Booking& booking = *it;
            string oldRoomType = booking.roomType;
            cout << "\nUpdate Booking ID: " << ID << endl;
            cout << "Choose data to update: \n";
            cout << "1. Guest Name\n";
            cout << "2. Room Type\n";
            cout << "3. Duration\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter new guest name: ";
                    cin.ignore();
                    getline(cin, booking.guestName);
                    break;
                case 2:
                    cout << "Available Room Types: \n";
                    displayRoomType();
                    cout << "\nEnter new room type: ";
                    cin.ignore();
                    int roomChoice;
                    cin >> roomChoice;
                    switch (roomChoice) {
                        case 1:
                            booking.roomType = "Single Room";
                            booking.pricePerNight = 100;
                            break;
                        case 2:
                            booking.roomType = "Double Room";
                            booking.pricePerNight = 130;
                            break;
                        case 3:
                            booking.roomType = "Deluxe Room";
                            booking.pricePerNight = 230;
                            break;
                        case 4:
                            booking.roomType = "Family Suite Room";
                            booking.pricePerNight = 320;
                            break;
                        default:
                            cout << "\nInvalid Choice. No changes made to room type." << endl;
                            break;
                    }
                    roomTypeCounts[oldRoomType]--;  // Decrement count of the old room type
                    roomTypeCounts[booking.roomType]++;  // Increment count of the new room type
                    break;
                case 3:
                    cout << "Enter new duration (in days): ";
                    cin >> booking.duration;
                    break;
                default:
                    cout << "Invalid choice.\n";
                    return;
            }
            cout << "\nBooking updated successfully.\n";
        } else {
            cout << "\nBooking with ID " << ID << " not found.\n";
        }
    }

    // Function to cancel a booking by ID
    void cancelBooking(int id) {
        auto it = find_if(bookings.begin(), bookings.end(), [id](const Booking& b) { return b.id == id; });
        if (it != bookings.end()) {
            string roomType = it->roomType;
            bookings.erase(it);  // Remove the booking from the list
            roomTypeCounts[roomType]--;  // Decrement the count of the room type
            cout << "\nBooking canceled successfully.\n";
        } else {
            cout << "\nBooking with ID " << id << " not found.\n";
        }
    }
};

// Main function
int main() {
    HotelBookingSystem system;  // Create an instance of the HotelBookingSystem
    int ID;
    int choice;
    int roomChoice;
    string guestName, roomType;
    double pricePerNight;

    // Menu loop
    while (true) {
        cout << "\n-----WELCOME TO GAYU HOTEL-----\n";
        cout << "Gayu Hotel Booking System";
        cout << "\n\tMENU\t\n";
        cout << "1. Add Booking\n";
        cout << "2. Display Bookings\n";
        cout << "3. Search Bookings ID\n";
        cout << "4. Update Bookings\n";
        cout << "5. Cancel Booking\n";
        cout << "6. Exit";
        cout << "\n-------------------------------";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            // Adding a booking
            string guestName;
            int duration;
            cout << "Enter guest name: ";
            cin.ignore();
            getline(cin, guestName);
            HotelBookingSystem::displayRoomType();
            cout << "\nEnter room type: ";
            cin >> roomChoice;
            switch (roomChoice) {
                case 1:
                    roomType = "Single Room";
                    pricePerNight = 100;
                    break;
                case 2:
                    roomType = "Double Room";
                    pricePerNight = 130;
                    break;
                case 3:
                    roomType = "Deluxe Room";
                    pricePerNight = 230;
                    break;
                case 4:
                    roomType = "Family Suite Room";
                    pricePerNight = 320;
                    break;
                default:
                    cout << "\nInvalid Choice. Defaulting to Single room." << endl;
                    roomType = "Single Room";
                    pricePerNight = 100;
                    break;
            }
            cout << "Enter duration (in days): ";
            cin >> duration;
            system.addBooking(guestName, roomType, duration, pricePerNight);
        } else if (choice == 2) {
            // Displaying all bookings
            system.displayBookings();
        } else if (choice == 3) {
            // Searching for a booking by ID
            cout << "Enter booking ID to search: ";
            cin >> ID;
            system.searchBookings(ID);
        } else if (choice == 4) {
            // Updating a booking by ID
            cout << "Enter booking ID to update: ";
            cin >> ID;
            system.updateBookings(ID);
        } else if (choice == 5) {
            // Canceling a booking by ID
            cout << "Enter booking ID to cancel: ";
            cin >> ID;
            system.cancelBooking(ID);
        } else if (choice == 6) {
            // Exiting the program
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
