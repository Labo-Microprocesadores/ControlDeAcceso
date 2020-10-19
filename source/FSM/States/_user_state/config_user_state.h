/***************************************************************************/ /**
  @file     config_user_state.h
  @brief    config user state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef CONFIG_USER_STATE_H_
#define CONFIG_USER_STATE_H_

#include "../../fsm.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Function to be called when the configuration ends. It emits USER_CONFIG_USER_FINISHED_EV and ADMIN_CONFIG_USER_FINISHED_EV events to the event queue.
 */
void configUser_initFSM(void);
void configUser_finishConfiguration(void);


void configUser_onLKP(void);
void configUser_onPress(void);
void configUser_onEncoderRight(void);
void configUser_onEncoderLeft(void);


#endif /* CONFIG_USER_STATE_H_*/
