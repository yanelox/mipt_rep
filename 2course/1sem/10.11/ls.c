#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>


int main (int argc, char* argv[])
{
    char dir_name[256];
    char buf[256];
    int mode = 0;
    int flag = 0;

    if (argc == 1)
    {
        getcwd (buf, 256);
        strcpy (dir_name, buf);
    }

    else
    {
        for (int i = 1; i < argc; ++i)
            if (strcmp (argv[i], "-l") == 0)
                mode = 1;
            
            else if (flag == 0)
            {
                strcpy (dir_name, argv[i]);
                flag = 1;
            }
    }

    if (flag == 0)
    {
        getcwd (buf, 256);
        strcpy (dir_name, buf);
    }

    DIR* dir = opendir (dir_name);

    struct dirent* res = readdir (dir);

    if (mode == 0)
        while (res)
        {
            if (res->d_name[0] != '.')
                printf ("%s\n", res->d_name);
            
            res = readdir (dir);
        }

    else if (mode == 1)
        while (res)
        {
            struct stat stat_buf;

            if (res->d_name[0] != '.')
            {
                stat (res->d_name, &stat_buf);

                printf ("%ld %ld %ld %ld ", stat_buf.st_atim.tv_sec, stat_buf.st_blksize, stat_buf.st_blocks, stat_buf.st_ctim.tv_sec);
                printf ("%ld %d %ld %d %ld ", stat_buf.st_dev, stat_buf.st_gid, stat_buf.st_ino, stat_buf.st_mode, stat_buf.st_mtim.tv_sec);
                printf ("%ld %ld %ld %d ", stat_buf.st_nlink, stat_buf.st_rdev, stat_buf.st_size, stat_buf.st_uid);
                printf ("%s\n", res->d_name);
            }

            res = readdir (dir);
        }

    closedir (dir);
}