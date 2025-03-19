#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define thrd_cnt 2000  // Определили количество потоков для удобства


void *unsafe_getlogin(void *arg) {      // Функция, вызываемая каждым потоком
    char *user = getlogin(); // Получаем имя пользователя через getlogin()
    if (user == NULL) {
        printf("Ошибка. getlogin() вернул NULL\n");
    } else {
        printf("Поток №%d: Пользователь: %s\n", (int)arg, user);}} // вывод информации о каждом результате

int main() {
    pthread_t thrd[thrd_cnt];
    for (int i = 0; i < thrd_cnt; i++) {        //запускаем каждый поток с функцией unsafe_getlogin
        if (pthread_create(&thrd[i], NULL, unsafe_getlogin, (void *)i) != 0) {
            perror("pthread_create failed");
            return 1;}}
    for (int i = 0; i < thrd_cnt; i++) {        // Ожидание завершения всех потоков
        pthread_join(thrd[i], NULL);
    }
    return 0;}
