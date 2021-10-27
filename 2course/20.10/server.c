#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
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
    int ftok_id = ftok ("membuf.c", 1);

    int msg_key = msgget (ftok_id, IPC_CREAT | 0666);

    struct message msg;

    size_t m_size = sizeof(struct message) - sizeof(long);

    msg.mtype = 1;

    int tmp = 0;

    int x = 4;

    int fork_id = fork();

    // int client_numbers[256];
    // int count_clients = 0;

    while (42)
    {
        if (fork_id)
        {
            msgrcv (msg_key, &msg, m_size, -2, 0);

            if (msg.mtype == 1)
            {
                msg.mtype = 3;
                msg.num1 = x;

                sprintf (msg.mtext, "Clients numbers is from 4 to %d, your number is %d\n", x, x);

                msgsnd (msg_key, &msg, m_size, 0);

                printf ("Client %d connected\n", x);

                ++x;
            }

            else if (msg.mtype == 2)
            {
                if (msg.num1 != msg.num2)
                {
                    printf ("Message from %d to %d: %s\n", msg.num1, msg.num2, msg.mtext);

                    tmp = msg.num2;
                    msg.mtype = tmp;

                    msgsnd (msg_key, &msg, m_size, 0);
                }

                else if (msg.num1 != -1 && msg.num2 != -1)
                {
                    printf ("Client %d disconnected\n", msg.num1);
                }

                else if (msg.num1 == -1 && msg.num2 == -1)
                {
                    printf ("Server is done\n");
                    break;
                }
            }
        }

        else
        {
            int status = 0;

            scanf ("%d", &status);

            if (status == -1)
            {
                msg.mtype = 2;
                msg.num1 = -1;
                msg.num2 = -1;

                msgsnd (msg_key, &msg, m_size, 0);

                for (int i = 4; i < x; ++i)
                {
                    msg.mtype = i;

                    msgsnd (msg_key, &msg, m_size, 0);
                }

                break;
            }
        }
    }
}