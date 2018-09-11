#ifndef ROKETLINK_H
#define ROKETLINK_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Team Identification Number Length
#define ID_LENGTH 2 
// Since all message have maximum of 8 bytes (1 for startBit, 2 for team ID, 1 for Message Id, 4 for payload)
#define MAX_MSG_LENGTH 8

/* Message ID details */
// Boundary Checking variable
#define MIN_MSG_ID 0
#define MAX_MSG_ID 11
// Message ID
#define ROCKETLINK_MSG_ID_ALT 0
#define ROCKETLINK_MSG_ID_GPS_LAT 1
#define ROCKETLINK_MSG_ID_GPS_LON 2
#define ROCKETLINK_MSG_ID_AIR_PRE 3
#define ROCKETLINK_MSG_ID_AIR_TEMP 4
#define ROCKETLINK_MSG_ID_TRACKER_YAW 5
#define ROCKETLINK_MSG_ID_TRACKER_PITCH 6
#define ROCKETLINK_MSG_ID_PAYLOAD_ROLL 7
#define ROCKETLINK_MSG_ID_PAYLOAD_PITCH 8
#define ROCKETLINK_MSG_ID_PAYLOAD_YAW 9
#define ROCKETLINK_MSG_ID_PHOTO 10
#define ROCKETLINK_MSG_ID_HUMIDITY 11

/* Type definition [ID] */
typedef int32_t altType;            // [0] hold altitude with resolution 1m
typedef float latType;              // [1]
typedef float lonType;              // [2]
typedef uint32_t preType;           // [3] hold pressure *100  (100*hPa)
typedef int32_t tempType;           // [4] hold temperature *100 (100*Celcius)
typedef int32_t trackerYawType;     // [5] hold trackerYaw *100 (100*degree)
typedef int32_t trackerPitchType;   // [6] hold trackerPitch *100 (100*degree)
typedef int32_t payloadRollType;    // [7] hold payloadRoll *100 (100*degree)
typedef int32_t payloadPitchType;   // [8] hold payloadPitch *100 (100*degree)
typedef int32_t payloadYawType;     // [9] hold payloadYaw *100 (100*degree)
typedef int32_t humidityType;       // [10] hold humidityType *100 (100*percent)
typedef uint32_t photo;             // [11]

typedef struct rocketlink_header {
    uint8_t startBit;
    uint8_t id[ID_LENGTH];
    uint8_t messageId;
} rocketlink_header_t;

typedef struct rocketlink_message {
    rocketlink_header_t header;
    uint8_t* payload;
    //add crc
} rocketlink_message_t;

/* Construct message function */
uint8_t construct_rocketlink_altitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 altType payload_data);

uint8_t construct_rocketlink_latitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 latType payload_data);

uint8_t construct_rocketlink_longitude(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 lonType payload_data);

uint8_t construct_rocketlink_pressure(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 preType payload_data);

uint8_t construct_rocketlink_temperature(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 tempType payload_data);

uint8_t construct_rocketlink_tracker_yaw(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 trackerYawType payload_data);

uint8_t construct_rocketlink_tracker_pitch(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 trackerPitchType payload_data);

uint8_t construct_rocketlink_payload_roll(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadRollType payload_data);

uint8_t construct_rocketlink_payload_pitch(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadPitchType payload_data);

uint8_t construct_rocketlink_payload_yaw(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 payloadYawType payload_data);

uint8_t construct_rocketlink_humidity(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier,
                                 humidityType payload_data);

/* Extractor function */
altType extract_altitude(uint8_t *payload_data);

latType extract_latitude(uint8_t *payload_data);

lonType extract_longitude(uint8_t *payload_data);

preType extract_pressure(uint8_t *payload_data);

tempType extract_temperature(uint8_t *payload_data);

trackerYawType extract_tracker_yaw(uint8_t *payload_data);

trackerPitchType extract_tracker_pitch(uint8_t *payload_data);

payloadRollType extract_payload_roll(uint8_t *payload_data);

payloadPitchType extract_payload_pitch(uint8_t *payload_data);

payloadYawType extract_payload_yaw(uint8_t *payload_data);

humidityType extract_humidity(uint8_t *payload_data);

/* Helper Function */
// Helper function for the Construct Rocketlink Message
void construct_rocketlink_message(rocketlink_message_t *output_message,
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier, 
                                 uint8_t msg_id,
                                 uint8_t *payload_data);

void construct_rocketlink_header(rocketlink_header_t *header, 
                                 uint8_t unique_word, 
                                 uint8_t *team_identifier, 
                                 uint8_t msg_id);
void construct_rocketlink_payload(uint8_t **output_message,
                                  uint8_t *input_message,
                                  uint8_t msg_id);

// Utility Function
uint8_t return_byte_size(uint8_t message_id);


// Breakdown rocketlink message into character array
void deconstruct_message(uint8_t **output_message,
                       rocketlink_message_t *input_message);


uint8_t reconstruct_rocketlink(rocketlink_message_t *output_message,
                        uint8_t *input_message);

void print_rocketlink(rocketlink_message_t *message);

uint8_t parseRocketlink(rocketlink_message_t* constructed_message,
                        uint8_t incoming_byte,
                        uint8_t unique_word,
                        uint8_t *team_identifier);

#endif

