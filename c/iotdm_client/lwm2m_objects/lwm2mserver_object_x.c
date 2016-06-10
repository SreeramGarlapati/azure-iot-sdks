

// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

//
// Simple implementation of IoTHub LWM2M LWM2M Server object
//

//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.

#include "iotdm_internal.h"
#include "iotdm_dispatchers.h"
#include "lwm2mserver_object.h"

DISPATCHER_FORWARD_DECLARATIONS(object_lwm2mserver);

// Property Indices for for lwm2mserver object
#define INDEX_LWM2MSERVER_LIFETIME 0
#define INDEX_LWM2MSERVER_DEFAULTMINIMUMPERIOD 1
#define INDEX_LWM2MSERVER_DEFAULTMAXIMUMPERIOD 2

void set_default_lwm2mserver_property_values(object_lwm2mserver *obj);
IOTHUB_CLIENT_RESULT on_read_lwm2mserver_lifetime(object_lwm2mserver *obj, int64_t *value);
IOTHUB_CLIENT_RESULT on_write_lwm2mserver_lifetime(object_lwm2mserver *obj, int64_t value);
IOTHUB_CLIENT_RESULT on_read_lwm2mserver_defaultminimumperiod(object_lwm2mserver *obj, int64_t *value);
IOTHUB_CLIENT_RESULT on_write_lwm2mserver_defaultminimumperiod(object_lwm2mserver *obj, int64_t value);
IOTHUB_CLIENT_RESULT on_read_lwm2mserver_defaultmaximumperiod(object_lwm2mserver *obj, int64_t *value);
IOTHUB_CLIENT_RESULT on_write_lwm2mserver_defaultmaximumperiod(object_lwm2mserver *obj, int64_t value);


/**********************************************************************************
 * LWM2M Server setters
 *
 **********************************************************************************/
IOTHUB_CLIENT_RESULT set_lwm2mserver_lifetime(uint16_t instanceId, int64_t value)
{
    IOTHUB_CLIENT_RESULT result = IOTHUB_CLIENT_ERROR;
    object_lwm2mserver *obj = get_object_instance(OID_LWM2MSERVER, instanceId);
    if (obj != NULL)
    {
        if (obj->propval_lwm2mserver_lifetime != value)
        {
            LogInfo("LWM2MServer_Lifetime being set to %lld", value);
            obj->propval_lwm2mserver_lifetime = value;

            obj->resourceUpdated[INDEX_LWM2MSERVER_LIFETIME] = (char)true;
        }

        result = IOTHUB_CLIENT_OK;
    }

    return result;
}

IOTHUB_CLIENT_RESULT set_lwm2mserver_defaultminimumperiod(uint16_t instanceId, int64_t value)
{
    IOTHUB_CLIENT_RESULT result = IOTHUB_CLIENT_ERROR;
    object_lwm2mserver *obj = get_object_instance(OID_LWM2MSERVER, instanceId);
    if (obj != NULL)
    {
        if (obj->propval_lwm2mserver_defaultminimumperiod != value)
        {
            LogInfo("LWM2MServer_DefaultMinimumPeriod being set to %lld", value);
            obj->propval_lwm2mserver_defaultminimumperiod = value;

            obj->resourceUpdated[INDEX_LWM2MSERVER_DEFAULTMINIMUMPERIOD] = (char)true;
        }

        result = IOTHUB_CLIENT_OK;
    }

    return result;
}

IOTHUB_CLIENT_RESULT set_lwm2mserver_defaultmaximumperiod(uint16_t instanceId, int64_t value)
{
    IOTHUB_CLIENT_RESULT result = IOTHUB_CLIENT_ERROR;
    object_lwm2mserver *obj = get_object_instance(OID_LWM2MSERVER, instanceId);
    if (obj != NULL)
    {
        if (obj->propval_lwm2mserver_defaultmaximumperiod != value)
        {
            LogInfo("LWM2MServer_DefaultMaximumPeriod being set to %lld", value);
            obj->propval_lwm2mserver_defaultmaximumperiod = value;

            obj->resourceUpdated[INDEX_LWM2MSERVER_DEFAULTMAXIMUMPERIOD] = (char)true;
        }

        result = IOTHUB_CLIENT_OK;
    }

    return result;
}


/**********************************************************************************
 * LWM2M Server creation and destruction
 *
 **********************************************************************************/
static void destroy_lwm2mserver_object(object_lwm2mserver *obj)
{
    if (obj != NULL)
    {
        lwm2m_free(obj);
    }
}

static uint16_t g_next_lwm2mserver_instance_id = 0;
static uint16_t get_next_lwm2mserver_instance_id()
{
    return g_next_lwm2mserver_instance_id++;
}

IOTHUB_CLIENT_RESULT create_lwm2mserver_object(IOTHUB_CLIENT_HANDLE h, uint16_t *instanceId)
{
    IOTHUB_CLIENT_RESULT res = IOTHUB_CLIENT_OK;

    res = REGISTER_DISPATCHERS(OID_LWM2MSERVER, object_lwm2mserver);
    if (res != IOTHUB_CLIENT_OK)
    {
        LogError("Failed registering dispatchers");
        res = IOTHUB_CLIENT_ERROR;
    }

    else
    {
        object_lwm2mserver *obj = (object_lwm2mserver *)lwm2m_malloc(sizeof(object_lwm2mserver));
        if (obj == NULL)
        {
            LogError("malloc failure");
            res = IOTHUB_CLIENT_ERROR;
        }

        else
        {
            memset(obj,0,sizeof(*obj));
            obj->instanceId = get_next_lwm2mserver_instance_id();
            obj->channelHandle = h;
                
            res = add_dm_object(&object_lwm2mserver_instance_list, obj);
            if (res != IOTHUB_CLIENT_OK)
            {
                LogError("adding LWM2M Server object to object list");

                destroy_lwm2mserver_object(obj);
                obj = NULL;
            }

            else
            {
                set_default_lwm2mserver_property_values(obj);
            }
        }

        if (instanceId != NULL)
        {
            *instanceId = (obj == NULL) ? 0 : obj->instanceId;
        }
    }

    return res;
}

object_lwm2mserver *get_lwm2mserver_object(uint16_t instanceId)
{
    object_lwm2mserver *obj = NULL;

    (void)get_dm_object(object_lwm2mserver_instance_list, instanceId, (void*)&obj);

    return obj;
}

#define DO_SIGNAL_RESOURCE_CHANGE(index, property) \
    if (obj->resourceUpdated[index]) \
    { \
        on_resource_value_changed(obj->channelHandle, OID_LWM2MSERVER, obj->instanceId, property); \
        obj->resourceUpdated[index] = (char)false; \
    }

   
void signal_object_lwm2mserver_resource_changed(void *p)
{
    object_lwm2mserver *obj = (object_lwm2mserver*)p;
    DO_SIGNAL_RESOURCE_CHANGE(INDEX_LWM2MSERVER_LIFETIME, PID_LWM2MSERVER_LIFETIME)
    DO_SIGNAL_RESOURCE_CHANGE(INDEX_LWM2MSERVER_DEFAULTMINIMUMPERIOD, PID_LWM2MSERVER_DEFAULTMINIMUMPERIOD)
    DO_SIGNAL_RESOURCE_CHANGE(INDEX_LWM2MSERVER_DEFAULTMAXIMUMPERIOD, PID_LWM2MSERVER_DEFAULTMAXIMUMPERIOD)
}

BEGIN_READ_DISPATCHER(object_lwm2mserver)
    INTEGER_READ(PID_LWM2MSERVER_LIFETIME, on_read_lwm2mserver_lifetime)
    INTEGER_READ(PID_LWM2MSERVER_DEFAULTMINIMUMPERIOD, on_read_lwm2mserver_defaultminimumperiod)
    INTEGER_READ(PID_LWM2MSERVER_DEFAULTMAXIMUMPERIOD, on_read_lwm2mserver_defaultmaximumperiod)
END_READ_DISPATCHER()

BEGIN_EXEC_DISPATCHER(object_lwm2mserver)
END_EXEC_DISPATCHER()

BEGIN_WRITE_DISPATCHER(object_lwm2mserver)
    INTEGER_WRITE(PID_LWM2MSERVER_LIFETIME, on_write_lwm2mserver_lifetime)
    INTEGER_WRITE(PID_LWM2MSERVER_DEFAULTMINIMUMPERIOD, on_write_lwm2mserver_defaultminimumperiod)
    INTEGER_WRITE(PID_LWM2MSERVER_DEFAULTMAXIMUMPERIOD, on_write_lwm2mserver_defaultmaximumperiod)
END_WRITE_DISPATCHER();

BEGIN_OPERATION_LIST(object_lwm2mserver)
    OPERATION(PID_LWM2MSERVER_LIFETIME, OP_RW, LWM2M_TYPE_INTEGER)
    OPERATION(PID_LWM2MSERVER_DEFAULTMINIMUMPERIOD, OP_RW, LWM2M_TYPE_INTEGER)
    OPERATION(PID_LWM2MSERVER_DEFAULTMAXIMUMPERIOD, OP_RW, LWM2M_TYPE_INTEGER)
END_OPERATION_LIST()


