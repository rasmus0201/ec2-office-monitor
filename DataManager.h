/**
 * @file DataManager.h
 * @author Rasmus Sørensen (bundsgaard.rasmus@gmail.com)
 * @brief Data manager header file
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef BUNDSGAARD_DATA_MANAGER_H
#define BUNDSGAARD_DATA_MANAGER_H

#include <string>
#include "mbed.h"
#include "Rtc.h"
#include "Collection.h"

namespace Bundsgaard
{
    /**
     * @brief The class will handle the data of all sensors.
     *        Once the "datastore" is becomming big enough, it
     *        will push the data online and free the local data.
     * 
     */
    class DataManager
    {
        public:
            /**
             * @brief Construct a new Data Manager object
             * 
             * @param rtc 
             */
            DataManager(Rtc* rtc);

            /**
             * @brief Setup the manager. This will create a socket
             *        to the API for reuse on each data-push
             * 
             */
            void Setup();

            /**
             * @brief Push data online to the API
             * 
             */
            void PushToCloud();

            /**
             * @brief Worker will start a new thread where the manager
             *        asynchronously can push data to the cloud.
             * 
             */
            void Worker();

            /**
             * @brief Get the Rtc object
             * 
             * @return Rtc* 
             */
            Rtc* GetRtc();
        
        public:
            Collection* dataStore;

        private:
            Rtc* rtc;
            Thread thread;
            std::string apiUrl;
            NetworkInterface* net;
            TCPSocket* socket;
    };
}

#endif
