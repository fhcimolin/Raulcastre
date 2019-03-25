# Raulcastre

Projeto de raycaster

## Compilar

#### CMake

Para compilar o projeto:

```console
$ cmake -B build
$ make -C build
```

Isso irá gerar uma pasta `build/bin` com o conteúdo pronto para distribuição:

```
build/bin
├── pics
│   ├── barrel.png
│   ├── bluestone.png
│   ├── colorstone.png
│   ├── eagle.png
│   ├── greenlight.png
│   ├── greystone.png
│   ├── mossy.png
│   ├── pillar.png
│   ├── purplestone.png
│   ├── redbrick.png
│   └── wood.png
└── raulcastre

1 directory, 12 files
```

O programa pode ser executado a partir da pasta:

```
$ cd build/bin
$ ./raulcastre
```

É importante (no momento) que a pasta `pics` esteja na pasta atual de onde o
executável está sendo chamado (_working directory_).
