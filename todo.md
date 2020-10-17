# TODOs

EN TODOS LADOS: 
    - [ ] AGREGAR EVENT QUEUE.
    - [ ] Agregar estados de animacion

En id_state.c, pin_state.c y user_input:
    - [ ] Resetear el timer de timeout en algunas funciones 
    - [ ] En algunas actualizar el display
    - [x] Chequear ID con la base de datos 
    - [x] Tirar eventos a la fsm para cambiar de estados 
    - [ ] Hacer checkCardID
    - [ ] Completar id_fail()
    - [ ] Shifteo del display
    - [ ] Blink del display en el caracter en el que esta el usuario
    
En FSM:
    - [ ] Inicializar cola de eventos
    - [x] Guardar id y pin en una estructura. (Se guarda en base de datos)
    - [x] Hacer getIdArray y getPinArray al pasar de estados.

En main_menu_state.c
    - [ ] Ver como mostrar las cosas en el display 
    - [ ] hacer funciones cardSwipe y initLogin

En fail_state.c
    - [ ] ver bien como definir esas funciones :(

En admin_state.c
    - [ ] Agregar eventos al seleccionar una opcion del display

En usr_state.c
    - [ ] Agregar eventos al seleccionar una opcion del display

En open_state.c
    - [ ] Led On al entrar
    - [ ] Iniciar timer al entrar
    - [ ] Led Off al terminar el timer

En config_me.c
    - [ ] Todo

En config_device.c:
    - [ ] Mostrar en el display las opciones y un titulo
