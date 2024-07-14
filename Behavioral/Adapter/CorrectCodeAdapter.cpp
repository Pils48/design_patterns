#include <iostream>
#include <string>


using namespace std;

/**
 * In order to translate WeatherService call into ThirdPartyCalls we are implementing WetherServiceAdapter class
 * Which contains ThirdPartyWetherService as the field and call its methods from the methods of adapter.
 */

// Existing WeatherService interface
class WeatherService {
public:
    virtual float getTemperature() const = 0;
    virtual float getHumidity() const = 0;
    virtual float getWindSpeed() const = 0;
    virtual ~WeatherService() {}
};

// Third-party API implementation of WeatherService
class ThirdPartyWeatherService {
public:
    // ThirdPartyWeatherService uses different interface it is not the same WeatherService
    float fetchTemperature() const {
        // Simulate fetching temperature from third-party API
        cout << "Fetching temperature from third-party API" << endl;
        return 25.0f;
    }

    float fetchHumidity() const {
        // Simulate fetching humidity from third-party API
        cout << "Fetching humidity from third-party API" << endl;
        return 60.0f;
    }

    float fetchWindSpeed() const  {
        // Simulate fetching wind speed from third-party API
        cout << "Fetching wind speed from third-party API" << endl;
        return 15.0f;
    }

    // Implementing WeatherService interface using adapter would go here
};

class WetherServiceAdapter : public WeatherService {
private:
    ThirdPartyWeatherService _another_service;
public:
    WetherServiceAdapter(ThirdPartyWeatherService third_party_service) : _another_service(third_party_service)
    {}

    float getTemperature() const override{
        return _another_service.fetchTemperature();
    }

    float getHumidity() const override {
        return _another_service.fetchHumidity();
    }

    float getWindSpeed() const override {
        return _another_service.fetchWindSpeed();
    }
};

// Client code using WeatherService interface
void clientCode(const WeatherService* service) {
    float temperature = service->getTemperature();
    float humidity = service->getHumidity();
    float windSpeed = service->getWindSpeed();

    cout << "Current Weather:" << endl;
    cout << "Temperature: " << temperature << " C" << endl;
    cout << "Humidity: " << humidity << "%" << endl;
    cout << "Wind Speed: " << windSpeed << " km/h" << endl;
}

int main() {
    // Instantiate ThirdPartyWeatherService directly (without adapter implementation)
    ThirdPartyWeatherService weather_service;

    // Use client code with ThirdPartyWeatherService directly
    WetherServiceAdapter weather_adapter(weather_service);
    clientCode(&weather_adapter);

    return 0;
}
