/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.7.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 12/4/2019
 ***********************************************************************************************/

#include "digitaltwin_serializer.h"

//
// Serialize telemetry data
//

bool Thermalzones_SerializeThermal_zone_0Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_0 = Thermalzones_Telemetry_ReadThermal_zone_0();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_0);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_0 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_0);
    }

    return true;
}

bool Thermalzones_SerializeThermal_zone_1Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_1 = Thermalzones_Telemetry_ReadThermal_zone_1();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_1);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_1 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_1);
    }

    return true;
}

bool Thermalzones_SerializeThermal_zone_2Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_2 = Thermalzones_Telemetry_ReadThermal_zone_2();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_2);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_2 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_2);
    }

    return true;
}

bool Thermalzones_SerializeThermal_zone_3Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_3 = Thermalzones_Telemetry_ReadThermal_zone_3();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_3);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_3 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_3);
    }

    return true;
}

bool Thermalzones_SerializeThermal_zone_4Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_4 = Thermalzones_Telemetry_ReadThermal_zone_4();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_4);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_4 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_4);
    }

    return true;
}

bool Thermalzones_SerializeThermal_zone_5Telemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    double thermal_zone_5 = Thermalzones_Telemetry_ReadThermal_zone_5();

    int neededSize = snprintf(NULL, 0, "%f", thermal_zone_5);

    if (neededSize > size - 1)
    {
        LogError("Failed to build thermal_zone_5 payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%f", thermal_zone_5);
    }

    return true;
}

bool Deepstream_SerializeDeepstream_statusTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    bool deepstream_status = Deepstream_Telemetry_ReadDeepstream_status();

    int neededSize = snprintf(NULL, 0, "%s", deepstream_status ? "true" : "false");

    if (neededSize > size - 1)
    {
        LogError("Failed to build deepstream_status payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%s", deepstream_status ? "true" : "false");
    }

    return true;
}

bool Deepstream_SerializeDeepstream_detectionsTelemetry(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    int deepstream_detections = Deepstream_Telemetry_ReadDeepstream_detections();

    int neededSize = snprintf(NULL, 0, "%d", deepstream_detections);

    if (neededSize > size - 1)
    {
        LogError("Failed to build deepstream_detections payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%d", deepstream_detections);
    }

    return true;
}

//
// Serialize read-only property
//

bool Deviceinfo_SerializeManufacturerProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* manufacturer = Deviceinfo_Property_GetManufacturer();

    int neededSize = snprintf(NULL, 0, "\"%s\"", manufacturer);

    if (neededSize > size - 1)
    {
        LogError("Failed to build manufacturer payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", manufacturer);
    }

    return true;
}

bool Deviceinfo_SerializeModelProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* model = Deviceinfo_Property_GetModel();

    int neededSize = snprintf(NULL, 0, "\"%s\"", model);

    if (neededSize > size - 1)
    {
        LogError("Failed to build model payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", model);
    }

    return true;
}

bool Deviceinfo_SerializeSwVersionProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* swVersion = Deviceinfo_Property_GetSwVersion();

    int neededSize = snprintf(NULL, 0, "\"%s\"", swVersion);

    if (neededSize > size - 1)
    {
        LogError("Failed to build swVersion payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", swVersion);
    }

    return true;
}

bool Deviceinfo_SerializeOsNameProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* osName = Deviceinfo_Property_GetOsName();

    int neededSize = snprintf(NULL, 0, "\"%s\"", osName);

    if (neededSize > size - 1)
    {
        LogError("Failed to build osName payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", osName);
    }

    return true;
}

bool Deviceinfo_SerializeProcessorArchitectureProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* processorArchitecture = Deviceinfo_Property_GetProcessorArchitecture();

    int neededSize = snprintf(NULL, 0, "\"%s\"", processorArchitecture);

    if (neededSize > size - 1)
    {
        LogError("Failed to build processorArchitecture payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", processorArchitecture);
    }

    return true;
}

bool Deviceinfo_SerializeProcessorManufacturerProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    char* processorManufacturer = Deviceinfo_Property_GetProcessorManufacturer();

    int neededSize = snprintf(NULL, 0, "\"%s\"", processorManufacturer);

    if (neededSize > size - 1)
    {
        LogError("Failed to build processorManufacturer payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "\"%s\"", processorManufacturer);
    }

    return true;
}

bool Deviceinfo_SerializeTotalStorageProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    long totalStorage = Deviceinfo_Property_GetTotalStorage();

    int neededSize = snprintf(NULL, 0, "%ld", totalStorage);

    if (neededSize > size - 1)
    {
        LogError("Failed to build totalStorage payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%ld", totalStorage);
    }

    return true;
}

bool Deviceinfo_SerializeTotalMemoryProperty(char * payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    long totalMemory = Deviceinfo_Property_GetTotalMemory();

    int neededSize = snprintf(NULL, 0, "%ld", totalMemory);

    if (neededSize > size - 1)
    {
        LogError("Failed to build totalMemory payload string");
        return false;
    }
    else
    {
        snprintf(payloadBuffer, size, "%ld", totalMemory);
    }

    return true;
}

bool Deepstream_SerializeSetDeepStreamConfigCommandResponse(DEEPSTREAM_SETDEEPSTREAMCONFIG_setDeepStreamConfigResponse* response, char* payloadBuffer, int size)
{
    if (payloadBuffer == NULL)
    {
        return false;
    }

    memset(payloadBuffer, 0, size);

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "description", response->description);

    char * serializedString = json_serialize_to_string(root_value);

    int neededSize = (int)strlen(serializedString);
    if (serializedString == NULL || neededSize > size - 1)
    {
        LogError("Failed to build setDeepStreamConfig payload string");
        return false;
    }
    else
    {
        memcpy(payloadBuffer, serializedString, neededSize);
        free(serializedString);
    }

    json_value_free(root_value);

    return true;
}

