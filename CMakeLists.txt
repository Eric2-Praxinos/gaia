# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.10)
project (GaiaFull VERSION 1.0)

# Incluez les sous-projets.

add_subdirectory ("lib")
add_subdirectory ("test")
