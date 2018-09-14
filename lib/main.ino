// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

extern "C"{
    #include "src/Xpollute.h"
}

void test_humidity();
void test_temperature();
void test_mq2();
void test_mq7();

int main(){
  test_humidity();
  test_temperature();
  test_mq2();
  test_mq7;
  // ^ TODO : ganti pake define buat switching test
  test_parsing;
  return 0;
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
    uint8_t messageId = 0;
    humidityType testHumidity = 9234;
    humidityType extractedHumidity;
    uint8_t *testPointer = (uint8_t*) &testHumidity;

    xpollute_message_t testMessage;
    construct_xpollute_humidity(&testMessage, startBit, id, testHumidity);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedHumidity = extract_humidity(testMessage.payload);
    printf("Extracted (Humidity): %.2lf\n", extractedHumidity/100.0);
    printf("Test Value (Humidity): %.2lf\n", testHumidity/100.0);
    assert(extractedHumidity == testHumidity);
    printf("xpollute constructor test (Humidity) passed.\n");

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
    printf("xpollute deconstructor test (Humidity) passed.\n");

    xpollute_message_t deconstructedMessage;
    reconstruct_xpollute(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedHumidity = extract_humidity(deconstructedMessage.payload);
    assert(extractedHumidity == testHumidity);
    printf("xpollute reconstructor test (Humidity) passed.\n");

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


void test_temperature()
{
    printf("======================================\n");
    printf("         Payload Temperature Test        \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 1;
    tempType testTemperature = 32;
    tempType extractedTemperature;
    uint8_t *testPointer = (uint8_t*) &testTemperature;

    xpollute_message_t testMessage;
    construct_xpollute_temperature(&testMessage, startBit, id, testTemperature);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedTemperature = extract_temperature(testMessage.payload);
    printf("Extracted (Temperature): %.2lf\n", extractedTemperature/100.0);
    printf("Test Value (Temperature): %.2lf\n", testTemperature/100.0);
    assert(extractedTemperature == testTemperature);
    printf("xpollute constructor test (Temperature) passed.\n");

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
    printf("xpollute deconstructor test (Temperature) passed.\n");

    xpollute_message_t deconstructedMessage;
    reconstruct_xpollute(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedTemperature = extract_temperature(deconstructedMessage.payload);
    assert(extractedTemperature == testTemperature);
    printf("xpollute reconstructor test (Temperature) passed.\n");

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


void test_mq2()
{
    printf("======================================\n");
    printf("         Payload mq2 Test        \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 2;
    mq2Type testmq2 = 32;
    mq2Type extractedmq2;
    uint8_t *testPointer = (uint8_t*) &testmq2;

    xpollute_message_t testMessage;
    construct_xpollute_mq2(&testMessage, startBit, id, testmq2);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedmq2 = extract_mq2(testMessage.payload);
    printf("Extracted (mq2): %.2lf\n", extractedmq2/100.0);
    printf("Test Value (mq2): %.2lf\n", testmq2/100.0);
    assert(extractedmq2 == testmq2);
    printf("xpollute constructor test (mq2) passed.\n");

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
    printf("xpollute deconstructor test (mq2) passed.\n");

    xpollute_message_t deconstructedMessage;
    reconstruct_xpollute(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedmq2 = extract_mq2(deconstructedMessage.payload);
    assert(extractedmq2 == testmq2);
    printf("xpollute reconstructor test (mq2) passed.\n");

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


void test_mq7()
{
    printf("======================================\n");
    printf("         Payload mq7 Test        \n");
    printf("======================================\n");

    /* Functional Assignment */
    // Declaration of input
    uint8_t startBit = 0x0D;
    uint8_t id[] = { 0x0C, 0xF2 };
    uint8_t messageId = 2;
    mq7Type testmq2 = 32;
    mq7Type extractedmq7;
    uint8_t *testPointer = (uint8_t*) &testmq7;

    xpollute_message_t testMessage;
    construct_xpollute_mq7(&testMessage, startBit, id, testmq7);
    assert(testMessage.header.startBit == startBit);
    assert(testMessage.header.id[0] == id[0]);
    assert(testMessage.header.id[1] == id[1]);
    assert(testMessage.header.messageId == messageId);
    extractedmq7 = extract_mq7(testMessage.payload);
    printf("Extracted (mq7): %.2lf\n", extractedmq7/100.0);
    printf("Test Value (mq7): %.2lf\n", testmq7/100.0);
    assert(extractedmq7 == testmq7);
    printf("xpollute constructor test (mq7) passed.\n");

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
    printf("xpollute deconstructor test (mq7) passed.\n");

    xpollute_message_t deconstructedMessage;
    reconstruct_xpollute(&deconstructedMessage, containerMsg);
    assert(deconstructedMessage.header.startBit == startBit);
    assert(deconstructedMessage.header.id[0] == id[0]);
    assert(deconstructedMessage.header.id[1] == id[1]);
    assert(deconstructedMessage.header.messageId == messageId);
    extractedmq7 = extract_mq7(deconstructedMessage.payload);
    assert(extractedmq7 == testmq7);
    printf("xpollute reconstructor test (mq7) passed.\n");

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
