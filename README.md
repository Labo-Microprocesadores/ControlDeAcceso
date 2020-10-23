<h1 align="center">
  <br>
  <img src="images/Grupo2.png" alt="Expenses" width="200">
  <br>
  <p align="center">Control De Acceso<p>
</h1>

<p align="center">
  <a href="#what-is-it">¿Qué es esto?</a> •
  <a href="#getting-started">¿Como correrlo?</a> •
  <a href="#preview">Preview</a> •
</p>



## ¿Qué es esto?

En este repositorio se encuentra una implementación del control de acceso a un edificio de oficinas mediante una tarjeta magnética y un pin (clave de acceso). Para lograr el objetivo se dispone de encoder rotativo, un display de siete segmentos y un lector de tarjetas magnéticas.

Para ello se carga el programa en una placa de desarrollo Freedom K64F.

Dentro de este repositorio se puede encontrar un Manual de Usuario [el cual puede ver en este link](Manual_de_Usuario.pdf), y una presentacion utilizada para explicar las funcionalidades del sistema.
see documentation [puede ver la presentacion aquí](ControlDeAcceso_Grupo2.pdf).

## ¿Como correrlo?

Para correr el programa se necesita disponer de una placa de desarrollo Freedom K64F, una placa que presente un encoder para el control del programa y 4 displays de 7 segmentos todos conectados a un bus de salida para la conexion con la placa, y un lector de tarjetas magnéticas en caso de que se quiera utilizar esta funcionalidad.

Para correrlo se ha de cargar el programa en la placa, para ello se la puede conectar a la computadora y abrir el proyecto con MCUExpreso, el cual es un ID que permite añadir el software a la placa de desarrollo.

## Preview


### Portrait View

![App Working](Demo/ExpensesApp.gif)

### Landscape View

![App Working](Demo/LandscapeExpenses.gif)





