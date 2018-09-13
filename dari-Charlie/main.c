#include "RoketLink.h"
#include <assert.h>

void manual_assignment_test();
void test_altitude();
void test_latitude();
void test_longitude();
void test_pressure();
void test_temperature();
void test_tracker_yaw();
void test_tracker_pitch();
void test_payload_roll(); 
void test_payload_pitch();
void test_payload_yaw();
void test_humidity();
void test_parsing();

int main () {
    // test_altitude();
    // test_latitude();
    // test_longitude();
    // test_pressure();
    // test_temperature();
    // test_tracker_yaw();
    // test_tracker_pitch();
    // test_payload_roll();
    // test_payload_pitch();
    // test_payload_yaw();
    test_humidity();
    // ^ TODO : ganti pake define buat switching test
    test_parsing();
    return 0;
}

void manual_assignment_test()
{
    printf("======================================\n");
    printf("       Beginning of Manual Test       \n");
    printf("======================================\n");

    // Variable needed
    rocketlink_message_t *pMessage;
    pMessage = (rocketlink_message_t*) malloc(sizeof(rocketlink_message_t));
    altType *pUInt = malloc(sizeof(altType));
    trackerYawType *pInt = malloc(sizeof(trackerYawType));
    latType *pFloat = malloc(sizeof(latType));
    // Data Conversion
    *pUInt = 12345;
    *pInt = -12300;
    *pFloat = 3.14159;
    uint8_t *pChr;
    pChr = (uint8_t*) pUInt;

    // Assignment Process;
    pMessage->header.startBit = 0x0D;
    pMessage->header.id[0] = 0x0A;
    pMessage->header.id[1] = 0x0B;
    pMessage->header.messageId = 0;
    pMessage->payload = pChr;

    // Altitude Test
    printf("Altitude Test Begin\n");
    print_rocketlink(pMessage);
    printf("Altitude Extractor\n");
    altType altitudeCondition =  extract_altitude(pMessage->payload);
    printf("Altitude extracted: %d m \n\n", altitudeCondition);
    assert(altitudeCondition == 12345);

    pChr = (uint8_t*) pInt;
    pMessage->header.messageId = 5;
    pMessage->payload = pChr;
    printf("Yaw Test Begin\n");
    print_rocketlink(pMessage);
    trackerYawType trackerYawCondition = extract_tracker_yaw(pMessage->payload);
    printf("Tracker Yaw extracted: %.2f degree \n\n", (float) (trackerYawCondition/100));

    pChr = (uint8_t*) pFloat;
    pMessage->header.messageId = 2;
    pMessage->payload = pChr;
    printf("Pressure Test Begin\n");
    print_rocketlink(pMessage);
    latType latCondition = extract_pressure(pMessage->payload);
    printf("Pressure extracted: %f \n\n", latCondition);

    free(pInt);
    free(pFloat);
    free(pMessage);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_altitude()
{
    printf("======================================\n");
    printf("            Altitude Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 0;
    altType testAltitude = 250;
    altType extractedAltitude;
    uint8_t *testPointer = (uint8_t*) &testAltitude;

    rocketlink_message_t testMessage;
    construct_rocketlink_altitude(&testMessage, startBit, id, testAltitude);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedAltitude = extract_altitude(testMessage.payload);
    assert(extractedAltitude == testAltitude);
    printf("Rocketlink constructor test (Altitude) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Altitude) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedAltitude = extract_altitude(deconstructedMessage.payload);
    assert(extractedAltitude == testAltitude);
    printf("Rocketlink reconstructor test (Altitude) passed.\n");

    free(testMessage.payload);
    // free(testMessage->payload);
    // free(testMessage);
    free(containerMsg);
    free(deconstructedMessage.payload);
    // free(deconstructedMessage->payload);
    // free(deconstructedMessage);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_latitude()
{
    printf("======================================\n");
    printf("            Latitude Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 1;
    latType testLatitude = -106.141548;
    latType extractedLatitude;
    uint8_t *testPointer = (uint8_t*) &testLatitude;

    rocketlink_message_t testMessage;
    construct_rocketlink_latitude(&testMessage, startBit, id, testLatitude);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedLatitude = extract_latitude(testMessage.payload);
    assert(extractedLatitude == testLatitude);
    printf("Rocketlink constructor test (Latitude) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Latitude) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedLatitude = extract_latitude(deconstructedMessage.payload);
    assert(extractedLatitude == testLatitude);
    printf("Rocketlink reconstructor test (Latitude) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}


void test_longitude()
{
    printf("======================================\n");
    printf("           Longitude Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 2;
    lonType testLongitude = 6.2831648;
    lonType extractedLongitude;
    uint8_t *testPointer = (uint8_t*) &testLongitude;

    rocketlink_message_t testMessage;
    construct_rocketlink_longitude(&testMessage, startBit, id, testLongitude);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedLongitude = extract_longitude(testMessage.payload);
    assert(extractedLongitude == testLongitude);
    printf("Rocketlink constructor test (Longitude) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Longitude) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedLongitude = extract_longitude(deconstructedMessage.payload);
    assert(extractedLongitude == testLongitude);
    printf("Rocketlink reconstructor test (Longitude) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}


void test_pressure()
{
    printf("======================================\n");
    printf("            Pressure Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 3;
    preType testPressure = 123456789;
    preType extractedPressure;
    uint8_t *testPointer = (uint8_t*) &testPressure;

    rocketlink_message_t testMessage;
    construct_rocketlink_pressure(&testMessage, startBit, id, testPressure);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedPressure = extract_pressure(testMessage.payload);
    assert(extractedPressure == testPressure);
    printf("Rocketlink constructor test (Pressure) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Pressure) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedPressure = extract_pressure(deconstructedMessage.payload);
    assert(extractedPressure == testPressure);
    printf("Rocketlink reconstructor test (Pressure) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_temperature()
{
    printf("======================================\n");
    printf("            Temperature Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 4;
    tempType testTemperature = -369852;
    tempType extractedTemperature;
    uint8_t *testPointer = (uint8_t*) &testTemperature;

    rocketlink_message_t testMessage;
    construct_rocketlink_temperature(&testMessage, startBit, id, testTemperature);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedTemperature = extract_temperature(testMessage.payload);
    assert(extractedTemperature == testTemperature);
    printf("Rocketlink constructor test (Temperature) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Temperature) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedTemperature = extract_temperature(deconstructedMessage.payload);
    assert(extractedTemperature == testTemperature);
    printf("Rocketlink reconstructor test (Temperature) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_tracker_yaw()
{
    printf("======================================\n");
    printf("            Tracker_yaw Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 5;
    trackerYawType testTrackerYaw = -106236;
    trackerYawType extractedTrackerYaw;
    uint8_t *testPointer = (uint8_t*) &testTrackerYaw;

    rocketlink_message_t testMessage;
    construct_rocketlink_tracker_yaw(&testMessage, startBit, id, testTrackerYaw);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedTrackerYaw = extract_tracker_yaw(testMessage.payload);
    assert(extractedTrackerYaw == testTrackerYaw);
    printf("Rocketlink constructor test (TrackerYaw) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (TrackerYaw) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedTrackerYaw = extract_tracker_yaw(deconstructedMessage.payload);
    assert(extractedTrackerYaw == testTrackerYaw);
    printf("Rocketlink reconstructor test (TrackerYaw) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_tracker_pitch()
{
    printf("======================================\n");
    printf("            Tracker_pitch Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 6;
    trackerPitchType testTrackerPitch = 17523;
    trackerPitchType extractedTrackerPitch;
    uint8_t *testPointer = (uint8_t*) &testTrackerPitch;

    rocketlink_message_t testMessage;
    construct_rocketlink_tracker_pitch(&testMessage, startBit, id, testTrackerPitch);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedTrackerPitch = extract_tracker_pitch(testMessage.payload);
    assert(extractedTrackerPitch == testTrackerPitch);
    printf("Rocketlink constructor test (TrackerPitch) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (TrackerPitch) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedTrackerPitch = extract_tracker_pitch(deconstructedMessage.payload);
    assert(extractedTrackerPitch == testTrackerPitch);
    printf("Rocketlink reconstructor test (TrackerPitch) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_payload_roll()
{
    printf("======================================\n");
    printf("            Payload Roll Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 7;
    payloadRollType testPayloadRoll = -365723;
    payloadRollType extractedPayloadRoll;
    uint8_t *testPointer = (uint8_t*) &testPayloadRoll;

    rocketlink_message_t testMessage;
    construct_rocketlink_payload_roll(&testMessage, startBit, id, testPayloadRoll);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedPayloadRoll = extract_payload_roll(testMessage.payload);
    assert(extractedPayloadRoll == testPayloadRoll);
    printf("Rocketlink constructor test (PayloadRoll) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (PayloadRoll) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedPayloadRoll = extract_payload_roll(deconstructedMessage.payload);
    assert(extractedPayloadRoll == testPayloadRoll);
    printf("Rocketlink reconstructor test (PayloadRoll) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_payload_pitch()
{
    printf("======================================\n");
    printf("            Payload Pitch Test             \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 8;
    payloadPitchType testPayloadPitch = 753951;
    payloadPitchType extractedPayloadPitch;
    uint8_t *testPointer = (uint8_t*) &testPayloadPitch;

    rocketlink_message_t testMessage;
    construct_rocketlink_payload_pitch(&testMessage, startBit, id, testPayloadPitch);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedPayloadPitch = extract_payload_pitch(testMessage.payload);
    assert(extractedPayloadPitch == testPayloadPitch);
    printf("Rocketlink constructor test (PayloadPitch) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (PayloadPitch) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedPayloadPitch = extract_payload_pitch(deconstructedMessage.payload);
    assert(extractedPayloadPitch == testPayloadPitch);
    printf("Rocketlink reconstructor test (PayloadPitch) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_payload_yaw()
{
    printf("======================================\n");
    printf("            Payload Yaw Test          \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 9;
    payloadYawType testPayloadYaw = 456852;
    payloadYawType extractedPayloadYaw;
    uint8_t *testPointer = (uint8_t*) &testPayloadYaw;

    rocketlink_message_t testMessage;
    construct_rocketlink_payload_yaw(&testMessage, startBit, id, testPayloadYaw);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedPayloadYaw = extract_payload_yaw(testMessage.payload);
    assert(extractedPayloadYaw == testPayloadYaw);
    printf("Rocketlink constructor test (PayloadYaw) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (PayloadYaw) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedPayloadYaw = extract_payload_yaw(deconstructedMessage.payload);
    assert(extractedPayloadYaw == testPayloadYaw);
    printf("Rocketlink reconstructor test (PayloadYaw) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_humidity()
{
    printf("======================================\n");
    printf("         Payload Humidity Test        \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 11;
    humidityType testHumidity = 9234;
    humidityType extractedHumidity;
    uint8_t *testPointer = (uint8_t*) &testHumidity;

    rocketlink_message_t testMessage;
    construct_rocketlink_humidity(&testMessage, startBit, id, testHumidity);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedHumidity = extract_humidity(testMessage.payload);
    printf("Extracted (Humidity): %.2lf\n", extractedHumidity/100.0);
    printf("Test Value (Humidity): %.2lf\n", testHumidity/100.0);
    assert(extractedHumidity == testHumidity);
    printf("Rocketlink constructor test (Humidity) passed.\n");

    /* Reconstruct message from array of char */
    uint8_t *containerMsg;
    deconstruct_message(&containerMsg, &testMessage);
    assert(containerMsg[0] == startBit);
    assert(containerMsg[1] == id[0]);
    assert(containerMsg[2] == id[1]);
    assert(containerMsg[3] == messageId);
    assert(containerMsg[4] == testPointer[0]);
    assert(containerMsg[5] == testPointer[1]);
    assert(containerMsg[6] == testPointer[2]);
    assert(containerMsg[7] == testPointer[3]);
    printf("Rocketlink deconstructor test (Humidity) passed.\n");

    rocketlink_message_t deconstructedMessage;
    reconstruct_rocketlink(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedHumidity = extract_humidity(deconstructedMessage.payload);
    assert(extractedHumidity == testHumidity);
    printf("Rocketlink reconstructor test (PayloadYaw) passed.\n");

    free(testMessage.payload);
    free(containerMsg);
    free(deconstructedMessage.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}

void test_parsing() {
    puts("======================================");
    puts("             Parsing Test             ");
    puts("======================================");

    // Test Input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    latType testPayloadLatitude = -4.156484;
    payloadYawType testPayloadYaw2 = -1245;
    payloadYawType extractedPayloadYaw;
    latType extractedLatitude;
    puts("Test Value and Variable Created.");
    uint8_t testArray[20]; // Input simulation

    rocketlink_message_t testMessage;
    rocketlink_message_t testMessage2;
    construct_rocketlink_latitude(&testMessage, startBit, id, testPayloadLatitude);
    construct_rocketlink_payload_yaw(&testMessage2, startBit, id, testPayloadYaw2);
    puts("Rocketlink constructed.");

    uint8_t *containerMsg; // Container to array version of message
    uint8_t *containerMsg2; // Container to array version of message
    deconstruct_message(&containerMsg, &testMessage);
    deconstruct_message(&containerMsg2, &testMessage2);
    for (int i = 0; i<20; i++) {
        if (i<8) {
            testArray[i] = containerMsg[i];
        } else if ((i>=10) && (i<18)) {
            testArray[i] = containerMsg2[i-10];
        } else {
            testArray[i] = i+100;
        }
    }
    // Print Test Message and Test array
    puts("Test Message 1: StartBit 0x0D, ID 0x0C and 0xF2, Message ID 1, Payload Latitude -4.156484");
    for (int i = 0; i<8; i++) {
        printf("%.2x ",containerMsg[i]);
    }
    printf("\n\n");
    puts("Test Message 2: StartBit 0x0D, ID 0x0C and 0xF2, Message ID 9, Payload Yaw -12.45 degree");
    for (int i = 0; i<8; i++) {
        printf("%.2x ",containerMsg[i]);
    }
    printf("\n\n");
    puts("Test Array: (unaltered)");
    for (int i = 0; i<20; i++) {
        printf("%.2x ",testArray[i]);
    }
    printf("\n\n");

    testArray[2] = 0xFF;
    puts("Test Array: (altered) bit 3 modified to break message 1");
    for (int i = 0; i<20; i++) {
        printf("%.2x ",testArray[i]);
    }
    printf("\n");

    // Parsing Test with the input Message
    rocketlink_message_t output_message;

    for (int i = 0; i<20; i++) {
        if(!parseRocketlink(&output_message,testArray[i],startBit,id)) {
            printf("Message Retrieved.\n");
            if (output_message.header.messageId == 9) {
                extractedPayloadYaw = extract_payload_yaw(output_message.payload);
                free(output_message.payload);
                printf("Extracted Payload Yaw: %.2f\n\n", (float) extractedPayloadYaw/100);
            } else {
                extractedLatitude = extract_latitude(output_message.payload);
                free(output_message.payload);
                printf("Extracted Latitude: %.6f\n\n", extractedLatitude);
            }
        }
    }
    puts("Test Passed.");

    free(testMessage.payload);
    free(testMessage2.payload);
    free(containerMsg);
    free(containerMsg2);
    free(output_message.payload);
    printf("======================================\n");
    printf("              End of Test             \n");
    printf("======================================\n");
    printf("\n\n");
}
