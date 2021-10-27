#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>

/*
    1 - сервер инициализирует клиента
    2 - сервер принимает сообщение и отправляет его в n
    3 - клиент без номера принимает и получает номер
    n - клиент с номером n принимает сообщение
*/

struct message 
{
    long mtype;
    
    int num1;

    int num2;

    char mtext[256];
};

int main()
{
    int my_num = 0;

    int x = 0;

    int ftok_id = ftok ("membuf.c", 1);

    int msg_key = msgget (ftok_id, IPC_CREAT | 0666);

    struct message msg;

    size_t m_size = sizeof(struct message) - sizeof(long);

    msg.mtype = 1;

    msgsnd (msg_key, &msg, m_size, 0);

    msgrcv (msg_key, &msg, m_size, 3, 0);

    printf ("%s\n", msg.mtext);

    my_num = msg.num1;

    int fork_id = fork();

    while (42)
    {//TODO: подумать над завершением процесса при отключении сервера
        if (fork_id)
        {
            scanf ("%d", &x);

            if (x != -1 && x != 0)
            {
                fgetc (stdin);
                fgets (msg.mtext, 256, stdin);
                

                msg.mtype = 2;
                msg.num1 = my_num;
                msg.num2 = x;

                msgsnd (msg_key, &msg, m_size, 0);

                x = 0;
            }

            else if (x == -1)
            {
                msg.mtype = 2;
                msg.num1 = my_num;
                msg.num2 = my_num;

                msgsnd (msg_key, &msg, m_size, 0);

                break;
            }
        }

        else
        { 
            msgrcv (msg_key, &msg, m_size, my_num, 0);

            if (msg.num1 != my_num && msg.num2 == my_num)
                printf ("Message from %d: %s\n", msg.num1, msg.mtext);

            else
                break;
        }
    }
}