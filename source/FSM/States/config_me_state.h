/***************************************************************************/ /**
  @file     config_me_state.h
  @brief    config me state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef CONFIG_ME_STATE_H_
#define CONFIG_ME_STATE_H_

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Function to be called when the configuration ends. It emits USER_CONFIG_ME_FINISHED_EV and ADMIN_CONFIG_ME_FINISHED_EV events to the event queue.
 */
void configMe_finishConfiguration(void);

#endif /* CONFIG_ME_STATE_H_*/
