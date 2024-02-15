#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits> // Added for input validation

class Car {
public:
    std::string brand;
    std::string model;
    double dailyRate;
    int quantity; // Number of available cars

    Car(const std::string& brand, const std::string& model, double dailyRate, int quantity)
        : brand(brand), model(model), dailyRate(dailyRate), quantity(quantity) {}
};

class CarRentalSystem {
private:
    std::vector<Car> cars;
    const int maxRentalDays = 7; // Maximum allowed rental days

public:
    CarRentalSystem() {
        // Initialize some cars
        initializeCars();
    }

    void initializeCars() {
        // Add car initialization logic here
    }

    void displayAvailableCarBrands() const {
        // Add display logic for available car brands
    }

    const std::vector<Car>& getCars() const {
        return cars;
    }

    double rentCar(const std::string& brand, const std::string& model, int days) {
        if (days <= 0 || days > maxRentalDays || std::cin.fail()) {
            std::cout << "Invalid number of rental days. Please choose between 1 and " << maxRentalDays << "." << std::endl;
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            return -1.0; // Indicate an error
        }

        auto carIt = std::find_if(cars.begin(), cars.end(),
                                  [brand, model](const Car& car) { return car.brand == brand && car.model == model && car.quantity > 0; });

        if (carIt != cars.end()) {
            double totalRent = carIt->dailyRate * days;
            std::cout << "Cost per day for " << carIt->brand << " " << carIt->model << ": ₹" << carIt->dailyRate << std::endl;
            std::cout << "You have rented a " << carIt->brand << " " << carIt->model << " for " << days << " days." << std::endl;
            std::cout << "Total Rent: ₹" << totalRent << std::endl;

            carIt->quantity--; // Reduce the available quantity

            return totalRent;
        }

        std::cout << "Car not available for rent or out of stock." << std::endl;
        return -1.0; // Indicate an error
    }
};

int main() {
    CarRentalSystem rentalSystem;

    std::cout << "Welcome to Creative Car Rentals!" << std::endl;
    rentalSystem.displayAvailableCarBrands();

    std::string chosenBrand, chosenModel;
    int rentalDays;

    std::cout << "Enter the brand of the car you want to rent: ";
    std::cin >> chosenBrand;

    // Validate the chosen brand
    bool validBrand = std::any_of(rentalSystem.getCars().begin(), rentalSystem.getCars().end(),
                                   [chosenBrand](const Car& car) { return car.brand == chosenBrand; });

    if (!validBrand) {
        std::cout << "Invalid brand. Please choose from the available brands." << std::endl;
        return 1;
    }

    std::cout << "Enter the model of the car you want to rent: ";
    std::cin >> chosenModel;

    // Validate the chosen model within the chosen brand
    bool validModel = std::any_of(rentalSystem.getCars().begin(), rentalSystem.getCars().end(),
                                    [chosenBrand, chosenModel](const Car& car) { return car.brand == chosenBrand && car.model == chosenModel; });

    if (!validModel) {
        std::cout << "Invalid model. Please choose from the available models of the selected brand." << std::endl;
        return 1;
    }

    std::cout << "Enter the number of days you want to rent the car: ";
    std::cin >> rentalDays;

    double totalRent = rentalSystem.rentCar(chosenBrand, chosenModel, rentalDays);

    if (totalRent < 0) {
        std::cout << "Error renting the car. Please try again." << std::endl;
        return 1;
    }

    // ... (unchanged)

    return 0;
}
