/*********************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.7.
 *
 * Generated Date: 12/4/2019
 *********************************************************************************************/

#include "pnp_device.h"

// Number of Digital Twins interfaces that this device supports.
#define DIGITALTWIN_INTERFACE_NUM 3

#define DEVICEINFO_INDEX 0

#define THERMALZONES_INDEX 1

#define DEEPSTREAM_INDEX 2

#define DEFAULT_SEND_TELEMETRY_INTERVAL_MS 10000

#define DEVICE_CAPABILITY_MODEL_URI "urn:nvidia:jetson:1"

static DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceClientHandles[DIGITALTWIN_INTERFACE_NUM];
static TICK_COUNTER_HANDLE tickcounter = NULL;
static tickcounter_ms_t lastTickSend;

int pnp_device_initialize(const char* connectionString, const char* trustedCert)
{
    if ((tickcounter = tickcounter_create()) == NULL)
    {
        LogError("tickcounter_create failed");
        return -1;
    }

    DIGITALTWIN_DEVICE_CLIENT_LL_HANDLE digitalTwinDeviceClientHandle = NULL;
    memset(&interfaceClientHandles, 0, sizeof(interfaceClientHandles));

    // Initialize DigitalTwin device handle
    if ((digitalTwinDeviceClientHandle = DigitalTwinClientHelper_InitializeDeviceHandle(connectionString, false, trustedCert)) == NULL)
    {
        LogError("DigitalTwinClientHelper_InitializeDeviceHandle failed");
        return -1;
    }

    // Invoke to the ***Interface_Create - implemented in a separate library - to create DIGITALTWIN_INTERFACE_CLIENT_HANDLE.
    // NOTE: Other than creation and destruction, NO operations may occur on any DIGITALTWIN_INTERFACE_CLIENT_HANDLE
    // until after we've completed its registration (see DigitalTwinClientHelper_RegisterInterfacesAndWait).

    if ((interfaceClientHandles[DEVICEINFO_INDEX] = DeviceinfoInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("DeviceinfoInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[THERMALZONES_INDEX] = ThermalzonesInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("ThermalzonesInterface_Create failed");
        return -1;
    }

    if ((interfaceClientHandles[DEEPSTREAM_INDEX] = DeepstreamInterface_Create(digitalTwinDeviceClientHandle)) == NULL)
    {
        LogError("DeepstreamInterface_Create failed");
        return -1;
    }

    // Register the interface(s) we've created with Azure IoT.  This call will block until interfaces
    // are successfully registered, we get a failure from server, or we timeout.
    if (DigitalTwinClientHelper_RegisterInterfacesAndWait(digitalTwinDeviceClientHandle, DEVICE_CAPABILITY_MODEL_URI, interfaceClientHandles, DIGITALTWIN_INTERFACE_NUM) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("DigitalTwinClientHelper_RegisterInterfacesAndWait failed");
        return -1;
    }

    DigitalTwinClientHelper_Check();

    // report properties

    DeviceinfoInterface_Property_ReportAll();

    tickcounter_get_current_ms(tickcounter, &lastTickSend);
    return 0;
}

void pnp_device_run()
{
    tickcounter_ms_t nowTick;
    tickcounter_get_current_ms(tickcounter, &nowTick);

    if (nowTick - lastTickSend >= DEFAULT_SEND_TELEMETRY_INTERVAL_MS)
    {
        LogInfo("Send telemetry data to IoT Hub");

        ThermalzonesInterface_Telemetry_SendAll();

        DeepstreamInterface_Telemetry_SendAll();

        tickcounter_get_current_ms(tickcounter, &lastTickSend);
    }
    else
    {
        // Just check data from IoT Hub
        DigitalTwinClientHelper_Check();
    }
}

void pnp_device_close()
{
    if (interfaceClientHandles[DEVICEINFO_INDEX] != NULL)
    {
        DeviceinfoInterface_Close(interfaceClientHandles[DEVICEINFO_INDEX]);
    }

    if (interfaceClientHandles[THERMALZONES_INDEX] != NULL)
    {
        ThermalzonesInterface_Close(interfaceClientHandles[THERMALZONES_INDEX]);
    }

    if (interfaceClientHandles[DEEPSTREAM_INDEX] != NULL)
    {
        DeepstreamInterface_Close(interfaceClientHandles[DEEPSTREAM_INDEX]);
    }

    DigitalTwinClientHelper_DeInitialize();
}
