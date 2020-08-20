#include <string>
#include "mbed.h"
#include "mbedtls_entropy_config.h"
#include "mbed_mem_trace.h"
#include "Rtc.h"
#include "defs.h"
#include "Collection.h"
#include "Sensors.h"
#include "SensorManager.h"

/** PINOUT
 * Led = D2
 * DHT = D4
 * Buzzer = D5
 * Button = D6
 * Sound = A0
 * Light = A1
*/

using namespace Bundsgaard;

InterruptIn button(D6);
DigitalOut led(D2);
DigitalOut buzzer(D5);

SensorManager* manager;

void setup();

int main()
{
    printf("Starting office monitor program\n");

    setup();

    while(true) {
        ThisThread::sleep_for(1000ms);
    }
}

void setup()
{
    printf("Getting default network instance\n");
    NetworkInterface* net = NetworkInterface::get_default_instance();

    if (!net) {
        printf("Error! No network interface found.\n");
        exit(-1);
    }

    // Connect to the network with the default networking interface
    nsapi_size_or_error_t result = net->connect();
    if (result != 0) {
        exit(-1);
    }

    printf("Setting up RTC\n");
    Rtc* rtc = new Rtc(NTP_SYNC_INTERVAL);
    rtc->Start();

    printf("Setting up data manager\n");
    DataManager* dataManager = new DataManager(rtc);
    
    printf("Setting up sensor manager\n");
    SensorManager* manager = new SensorManager(dataManager);
    
    printf("Setting up sensors\n");

    SoundSensor* soundSensor = new SoundSensor(A0, 2100);
    soundSensor->SetName(std::string("Sound"));

    LightSensor* lightSensor = new LightSensor(A1, 2200);
    lightSensor->SetName(std::string("Light"));

    DHTSensor* dhtSensor = new DHTSensor(D4, 2300);
    dhtSensor->SetName(std::string("DHT"));

    manager->AddSensorIn(soundSensor);
    manager->AddSensorIn(lightSensor);
    manager->AddSensorIn(dhtSensor);

    printf("Running manager\n");
    manager->Run();
}
