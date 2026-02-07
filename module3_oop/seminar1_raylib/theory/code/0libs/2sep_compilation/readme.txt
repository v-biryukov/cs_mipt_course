Для компиляции используйте:

    g++ main.cpp cube.cpp




Для создания статической библиотеки:

    g++ -c cube.cpp
    ar rcs libcube.a cube.o
    
В результате получится файл статической библиотеки libcube.a.




Для создания динамической библиотеки на Linux:

    g++ -fPIC -shared -o libcube.so cube.cpp 

В результате получится файл статической библиотеки libcube.so.




Для создания динамической библиотеки на Windows(MinGW):

    g++ -fPIC -shared -o cube.dll cube.cpp 

При создании cube.dll должна создаться импортная библиотека libcube.a.
Если она не создалась, то можно указать явно:

    g++ -fPIC -shared -o cube.dll -Wl,--out-implib,libcube.a cube.cpp
