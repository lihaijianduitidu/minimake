app: main.c utils.c
 gcc -o app main.c utils.c
app: main.c utils.c # ⽬标 `app` 重复定义 
 gcc -o app main.c utils.c
