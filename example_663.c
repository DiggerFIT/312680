#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int gl_cnt = 0;   // Глобальная переменная, которая будет изменяться потоками

void *unsafe_func(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        gl_cnt++;  // Изменение глобальной переменной
    }
}

int main() {
    pthread_t threads[100];
    for (long i = 0; i < 100; i++) {
        if (pthread_create(&threads[i], NULL, unsafe_func, (void *)i) != 0) {
            perror("Ошибка создания потока\n");
            return 1;
        }
    }
    for (int i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL); // Ожидание завершения всех потоков
    }

    printf("Итоговое значение глобальной переменной: %d\n", gl_cnt);
    return 0;
}
