/************************************************************************************************
 * This code was automatically generated by Digital Twin Code Generator tool 0.6.7.
 * Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.
 *
 * Generated Date: 12/4/2019
 ***********************************************************************************************/

#include "deepstream_interface.h"

#define MAX_MESSAGE_SIZE 256

//
//  Callback function declarations and DigitalTwin command names for this interface.
//

static void DeepstreamInterface_Command_SetDeepStreamConfigCallback(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* commandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* commandResponse, void* userInterfaceContext);

//
// Application state associated with this interface.
// It contains the DIGITALTWIN_INTERFACE_CLIENT_HANDLE used for responses in callbacks along with properties set
// and representations of the property update and command callbacks invoked on given interface
//
typedef struct DEEPSTREAM_INTERFACE_STATE_TAG
{
    DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceClientHandle;

} DEEPSTREAM_INTERFACE_STATE;

static DEEPSTREAM_INTERFACE_STATE appState;

// Callback function to process the command "setDeepStreamConfig".
void DeepstreamInterface_Command_SetDeepStreamConfigCallback(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* commandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* commandResponse, void* userInterfaceContext)
{
    DEEPSTREAM_INTERFACE_STATE* interfaceState = (DEEPSTREAM_INTERFACE_STATE*)userInterfaceContext;
    LogInfo("DEEPSTREAM_INTERFACE: setDeepStreamConfig command invoked.");
    LogInfo("DEEPSTREAM_INTERFACE: setDeepStreamConfig request payload=<%.*s>, context=<%p>", (int)commandRequest->requestDataLen, commandRequest->requestData, interfaceState);

    // Get payload string
    char* requestData = (char*)malloc(commandRequest->requestDataLen + 1);
    if (requestData != NULL)
    {
        strncpy(requestData, (char*)commandRequest->requestData, commandRequest->requestDataLen);
        requestData[commandRequest->requestDataLen] = 0;
    }
    else
    {
        LogError("Failed to allocate memory for request payload");
    }

    // Parse request parameters from request payload string
    JSON_Value *jsonValue = NULL;
    jsonValue = json_parse_string((const char*)requestData);

    char* deepStreamConfigPath = NULL;
    mallocAndStrcpy_s(&deepStreamConfigPath, (char*)json_value_get_string(jsonValue));

    // Invoke device command here
    unsigned int statusCode = 200;

    char responsePayload[MAX_MESSAGE_SIZE];

    DEEPSTREAM_SETDEEPSTREAMCONFIG_setDeepStreamConfigResponse response;

    DIGITALTWIN_COMMAND_RESULT commandResult = Deepstream_Command_SetDeepStreamConfig(deepStreamConfigPath, &response, &statusCode);

    // Serialize command response payload

    if (commandResult == DIGITALTWIN_COMMAND_OK &&
        Deepstream_SerializeSetDeepStreamConfigCommandResponse(&response, responsePayload, MAX_MESSAGE_SIZE))
    {
        DigitalTwinClientHelper_SetCommandResponse(commandResponse, (const unsigned char*)responsePayload, statusCode);

    }
    else
    {
        LogError("Failed to execute setDeepStreamConfig command");
        const unsigned char errorResponse[] = "\"Failed to execute setDeepStreamConfig command\"";
        DigitalTwinClientHelper_SetCommandResponse(commandResponse, errorResponse, statusCode);
    }

    free(requestData);

    if (jsonValue)
    {
        json_value_free(jsonValue);
    }

    if (deepStreamConfigPath != NULL)
    {
        free(deepStreamConfigPath);
    }

}

// DigitalTwinSample_ProcessCommandUpdate receives commands from the server.  This implementation acts as a simple dispatcher
// to the functions to perform the actual processing.
void DeepstreamInterface_ProcessCommandUpdate(const DIGITALTWIN_CLIENT_COMMAND_REQUEST* dtCommandRequest, DIGITALTWIN_CLIENT_COMMAND_RESPONSE* dtCommandResponse, void* userInterfaceContext)
{
    if (strcmp(dtCommandRequest->commandName, DeepstreamInterface_SetDeepStreamConfigCommand) == 0)
    {
        DeepstreamInterface_Command_SetDeepStreamConfigCallback(dtCommandRequest, dtCommandResponse, userInterfaceContext);
        return;
    }

    // If the command is not implemented by this interface, by convention we return a 501 error to server.
    LogError("DEEPSTREAM_INTERFACE: Command name <%s> is not associated with this interface", dtCommandRequest->commandName);
    const unsigned char commandNotImplementedResponse[] = "\"Requested command not implemented on this interface\"";
    (void)DigitalTwinClientHelper_SetCommandResponse(dtCommandResponse, commandNotImplementedResponse, 501);
}

// DeepstreamInterface_TelemetryCallback is invoked when a DigitalTwin telemetry message is either successfully delivered to the service or else fails.
static void DeepstreamInterface_TelemetryCallback(DIGITALTWIN_CLIENT_RESULT digitalTwinTelemetryStatus, void* userContextCallback)
{
    (void)userContextCallback;
    if (digitalTwinTelemetryStatus == DIGITALTWIN_CLIENT_OK)
    {
        SendTelemetry_Succeeded_Callback("Deepstream");
        LogInfo("DEEPSTREAM_INTERFACE: DigitalTwin successfully delivered telemetry message.");
    }
    else
    {
        SendTelemetry_Error_Callback("Deepstream");
        LogError("DEEPSTREAM_INTERFACE: DigitalTwin failed to deliver telemetry message, error=<%s> ", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, digitalTwinTelemetryStatus));
    }
}

DIGITALTWIN_CLIENT_RESULT DeepstreamInterface_Telemetry_SendAll()
{
    if (appState.interfaceClientHandle == NULL)
    {
        LogError("DEEPSTREAM_INTERFACE: interfaceClientHandle is required to be initialized before sending telemetries");
    }

    DIGITALTWIN_CLIENT_RESULT result;

    char combinedMessage[MAX_MESSAGE_SIZE];
    char telemetryValue[MAX_MESSAGE_SIZE];

    // Send multiple telemetries in a single message
    sprintf(combinedMessage, "{");

    Deepstream_SerializeDeepstream_statusTelemetry(telemetryValue, MAX_MESSAGE_SIZE);

    sprintf(combinedMessage + strlen(combinedMessage), "\"%s\":%s,", DeepstreamInterface_Deepstream_statusTelemetry, telemetryValue);

    Deepstream_SerializeDeepstream_detectionsTelemetry(telemetryValue, MAX_MESSAGE_SIZE);

    sprintf(combinedMessage + strlen(combinedMessage), "\"%s\":%s", DeepstreamInterface_Deepstream_detectionsTelemetry, telemetryValue);

    sprintf(combinedMessage + strlen(combinedMessage), "}");

    if ((result = DigitalTwin_InterfaceClient_SendTelemetryAsync(appState.interfaceClientHandle, (unsigned char*)combinedMessage, strlen(combinedMessage),
        DeepstreamInterface_TelemetryCallback, NULL)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("DEEPSTREAM_INTERFACE: DigitalTwin_InterfaceClient_SendTelemetryAsync failed for sending telemetry.");
    }

    return result;
}

// DeepstreamInterface_InterfaceRegisteredCallback is invoked when this interface
// is successfully or unsuccessfully registered with the service, and also when the interface is deleted.
static void DeepstreamInterface_InterfaceRegisteredCallback(DIGITALTWIN_CLIENT_RESULT dtInterfaceStatus, void* userInterfaceContext)
{
    LogInfo("DeepstreamInterface_InterfaceRegisteredCallback with status=<%s>, userContext=<%p>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, dtInterfaceStatus), userInterfaceContext);
    if (dtInterfaceStatus == DIGITALTWIN_CLIENT_OK)
    {
        // Once the interface is registered, send our reported properties to the service.  
        // It *IS* safe to invoke most DigitalTwin API calls from a callback thread like this, though it 
        // is NOT safe to create/destroy/register interfaces now.
        LogInfo("DEEPSTREAM_INTERFACE: Interface successfully registered.");
    }
    else if (dtInterfaceStatus == DIGITALTWIN_CLIENT_ERROR_INTERFACE_UNREGISTERING)
    {
        // Once an interface is marked as unregistered, it cannot be used for any DigitalTwin SDK calls.
        LogInfo("DEEPSTREAM_INTERFACE: Interface received unregistering callback.");
    }
    else
    {
        LogError("DEEPSTREAM_INTERFACE: Interface received failed, status=<%s>.", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, dtInterfaceStatus));
    }
}

//
// Create DigitalTwin interface client handle
//
DIGITALTWIN_INTERFACE_CLIENT_HANDLE DeepstreamInterface_Create()
{
    DIGITALTWIN_INTERFACE_CLIENT_HANDLE interfaceHandle;
    DIGITALTWIN_CLIENT_RESULT result;

    memset(&appState, 0, sizeof(DEEPSTREAM_INTERFACE_STATE));

    if ((result = DigitalTwin_InterfaceClient_Create(DeepstreamInterfaceId,  DeepstreamInterfaceInstanceName, DeepstreamInterface_InterfaceRegisteredCallback, (void*)&appState, &interfaceHandle)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("DEEPSTREAM_INTERFACE: Unable to allocate interface client handle for interfaceId=<%s>, interfaceInstanceName=<%s>, error=<%s>", DeepstreamInterfaceId, DeepstreamInterfaceInstanceName, MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
        interfaceHandle = NULL;
    }

    else if ((result = DigitalTwin_InterfaceClient_SetCommandsCallback(interfaceHandle, DeepstreamInterface_ProcessCommandUpdate, (void*)&appState)) != DIGITALTWIN_CLIENT_OK)
    {
        LogError("DEEPSTREAM_INTERFACE: DigitalTwin_InterfaceClient_SetCommandsCallbacks failed. error=<%s>", MU_ENUM_TO_STRING(DIGITALTWIN_CLIENT_RESULT, result));
        DeepstreamInterface_Close(interfaceHandle);
        interfaceHandle = NULL;
    }

    else
    {
        LogInfo("DEEPSTREAM_INTERFACE: Created DIGITALTWIN_INTERFACE_CLIENT_HANDLE successfully for interfaceId=<%s>, interfaceInstanceName=<%s>, handle=<%p>", DeepstreamInterfaceId, DeepstreamInterfaceInstanceName, interfaceHandle);
        appState.interfaceClientHandle = interfaceHandle;
    }

    return interfaceHandle;
}

void DeepstreamInterface_Close(DIGITALTWIN_INTERFACE_CLIENT_HANDLE digitalTwinInterfaceClientHandle)
{
    // On shutdown, in general the first call made should be to DigitalTwin_InterfaceClient_Destroy.
    // This will block if there are any active callbacks in this interface, and then
    // mark the underlying handle such that no future callbacks shall come to it.
    DigitalTwin_InterfaceClient_Destroy(digitalTwinInterfaceClientHandle);

    // After DigitalTwin_InterfaceClient_Destroy returns, it is safe to assume
    // no more callbacks shall arrive for this interface and it is OK to free
    // resources callbacks otherwise may have needed.

}
