/***************************************************************************/ /**
  @file     config_device_state.h
  @brief    config device state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef CONFIG_DEVICE_STATE_H
#define CONFIG_DEVICE_STATE_H

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Changes the current position of the ID array to the next character following CHAR ORDER.
 */
void nextOption(void);
/**
 * @brief Shows the next menu option.
 */
void previousOption(void);

/**
 * @brief Selects the current option and changes the bright of the display. It emits a ADMIN_CONFIG_DEVICE_FINISHED_EV event to the event queue.
 */
void selectOption(void);

#endif /* CONFIG_DEVICE_STATE_H*/