# Weather monitoring application

## Assignment
Write a realization for weather conditions monitoring using OpenWeatherMap API and components from Boost library.

The program is divided into 3 modules:
- `network` - is responsible for connecting to the external server, sending a request, and receiving a response.
- `client` - is responsible for passing data to `network`, processing results from it, and printing results on a screen.
- `application` - is responsible for processing command-line arguments and passing them to `client`.

The program is capable of:
- Showing help , if no arguments present or it was `-h` or `--help` argument;
- Reading city from the console;
- Reading token from console (If not present, check the file `token.txt` in the same directory as executable). 
- Showing information about the weather in specified city:
    - Name of the city
    - Temperature (degree Celsius)
    - Wind velocity (meters per second)
    - Wind direction (degrees)
    
### Receiving a token
1. Open the following site: https://home.openweathermap.org/users/sign_up
2. Sing up there
3. In the purpose field select "Education/science"
4. Check your email, open letter, and press "Verify"
5. Your API will be here: https://home.openweathermap.org/api_keys
6. Read the API doc: https://openweathermap.org/current


### Technologies used:
- [ ] CMake for building
- [ ] boost::asio
- [ ] boost::beast
- [ ] boost::program

### How to use?
1. install boost
2. From terminal:
   - mkdir build/
   - cd build/
   - cmake ..
   - make
   - ./Weather --city Kherson


