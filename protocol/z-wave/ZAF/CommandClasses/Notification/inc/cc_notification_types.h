/**
 * @file
 * Defines notification types for CC Notification.
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef ZAF_COMMANDCLASSES_NOTIFICATION_CC_NOTIFICATION_TYPES_H_
#define ZAF_COMMANDCLASSES_NOTIFICATION_CC_NOTIFICATION_TYPES_H_

#include <ZW_classcmd.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 */

/**
 * Notification type (8 bit).
 */
typedef enum {
  NOTIFICATION_TYPE_NONE,
  NOTIFICATION_TYPE_SMOKE_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SMOKE_ALARM),
  NOTIFICATION_TYPE_CO_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO_ALARM),
  NOTIFICATION_TYPE_CO2_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CO2_ALARM),
  NOTIFICATION_TYPE_HEAT_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HEAT_ALARM),
  NOTIFICATION_TYPE_WATER_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_WATER_ALARM),
  NOTIFICATION_TYPE_ACCESS_CONTROL = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_ACCESS_CONTROL),
  NOTIFICATION_TYPE_HOME_SECURITY = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_HOME_SECURITY),
  NOTIFICATION_TYPE_POWER_MANAGEMENT = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_POWER_MANAGEMENT),
  NOTIFICATION_TYPE_SYSTEM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_SYSTEM),
  NOTIFICATION_TYPE_EMERGENCY_ALARM = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_EMERGENCY_ALARM),
  NOTIFICATION_TYPE_CLOCK = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_CLOCK),
  NOTIFICATION_TYPE_MULTIDEVICE = (0xFF & ICON_TYPE_SPECIFIC_SENSOR_NOTIFICATION_MULTIDEVICE)
} notification_type_t;

/**
 * @}
 * @}
 */

#endif /* ZAF_COMMANDCLASSES_NOTIFICATION_CC_NOTIFICATION_TYPES_H_ */