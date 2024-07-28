#include <iostream>
#include <string>


using namespace std;

/**
 * Suppose you have an existing application that interacts with a third-party API to fetch weather data. 
 * The API has methods like getTemperature(), getHumidity(), and getWindSpeed(). Now, you want to switch 
 * to a different weather service provider that offers a more comprehensive API, but it uses different 
 * method names (fetchTemperature(), fetchHumidity(), fetchWindSpeed()). You can use the Adapter pattern 
 * to adapt the new API to the existing interface expected by your application.
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
    ThirdPartyWeatherService weatherService;

    // Use client code with ThirdPartyWeatherService directly
    // But we just unable to call clientCode(ThirdPartyWeather) as it is not implementing the interface
    // clientCode(&weatherService);

    return 0;
}
