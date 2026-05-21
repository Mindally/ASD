Шаблон для разработки и тестирования программ на С++ по предмету "Алгоритмы и структуры данных"

* Integrated Development Environment: Microsoft Visual Studio 
* Build system: cmake (https://ps-group.github.io/cxx/cmake_cheatsheet)
* Tests: gtest

## Работа с системой автоматической сборки cmake

При наличии в проекте сторонних модулей, произвести скачивание при помощи команд:

```
git submodule sync
git submodule update --init --recursive
```

Команды, определяющие версию сборки Visual Studio:

```
cmake -G "Visual Studio 17 2022" ..
```

```
cmake -G "Visual Studio 18 2026" ..
```

Страдание в чистом виде