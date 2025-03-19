#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

volatile sig_atomic_t gl_cnt= 0;  // Глобальная переменная

void unsafe_func(int signum) {
    printf("Получен сигнал: %d\n", signum);
    gl_cnt++; // имитируем изменение - изменяем счетчик
    printf("Глобальный счетчик: %d\n", gl_cnt);
}

int main() {
    if (signal(SIGINT, unsafe_func) == SIG_ERR) {   //Обрабатываем сигнал Ctrl+C функцией unsafe_func
        perror("signal error");
        return 1;
    }

    printf("Программа запущена. Введите Ctrl+C для отправки сигнала\n");
    pid_t pid = fork();         //Дублируем нашии процессы
    if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            sleep(1);
            printf("Сигнал SIGINT отправлен\n");
            kill(getppid(), SIGINT);  // Отправка SIGINT в родительский процесс
        }
        return 0;
    } else {
        while (1) {
            sleep(1);
        }
    }
}
