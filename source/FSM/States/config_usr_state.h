/***************************************************************************/ /**
  @file     config_usr_state.h
  @brief    config usr state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef CONFIG_USR_STATE_H_
#define CONFIG_USR_STATE_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Function to be called when the configuration ends. It emits a ADMIN_CONFIG_USER_FINISHED_EV event to the event queue.
 */
void finish_configuration(void);

#endif /* CONFIG_USR_STATE_H_*/
