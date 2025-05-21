# Tres en Raya (Tic-Tac-Toe)

Este es un simple juego de Tres en Raya desarrollado con C++ y QML utilizando Qt y CMake. Permite a dos jugadores competir turnándose para colocar su símbolo (X o O) en un tablero de 3x3.

## Características

- Interfaz gráfica moderna con QML.
- Lógica de juego encapsulada en C++.
- Detección de ganador o empate.
- Reinicio de partida.

## Requisitos

- Qt 5 o superior con soporte para QML.
- CMake 3.10 o superior.
- Un compilador C++ compatible (como GCC o MSVC).

## Instalación

```bash
git clone git@github.com:cgasconb/tres-en-raya.git
cd tres-en-raya/TresEnRaya
mkdir build
cd build
cmake ..
make
./TresEnRaya
```

> Nota: Asegúrate de tener `Qt` y sus herramientas (`qmlscene`, etc.) disponibles en tu PATH.

## Estructura del proyecto

- `main.cpp`: Punto de entrada principal.
- `gamelogic.cpp / .h`: Lógica del juego de Tres en Raya.
- `Main.qml`: Interfaz principal.
- `TresEnRayaBox.qml`: Componente visual del tablero.
- `CMakeLists.txt`: Configuración para construir el proyecto.

## Licencia

Este proyecto está licenciado bajo los términos de la licencia MIT. Ver el archivo [LICENSE](LICENSE) para más detalles.

## Autor

- @cgasconb
