#include <vector>
#include "SensorInterface.h"
#include "DataManager.h"
#include "SensorManager.h"

using namespace Bundsgaard;

SensorManager::SensorManager(DataManager* manager)
{
    this->dataManager = manager;
}

void SensorManager::AddSensorIn(SensorInterface* sensor)
{
    this->sensorsIn.push_back(sensor);
}

void SensorManager::Run()
{
    // this->thread.set_priority(osPriorityAboveNormal);
    this->thread.start(callback(this, &SensorManager::Work));
}

void SensorManager::Work()
{
    while(true) {
        printf("SensorManager::Work()\n");

        for (auto &sensor : this->GetSensorsIn()) {
            sensor->Run(this->dataManager);
        }

        ThisThread::sleep_for(1000ms);
    }
}

std::vector<SensorInterface*> SensorManager::GetSensorsIn()
{
    return this->sensorsIn;
}
