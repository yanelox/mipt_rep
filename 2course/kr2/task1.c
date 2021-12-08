#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

int count_files (char* dir_name)
{
    // printf ("%s\n", dir_name);

    int res = 0;

    char tmp[256];
    memset (tmp, '\0', 256);

    DIR* dir = opendir (dir_name);

    struct dirent* file_res = readdir (dir);

    while (file_res)
    {
        if (file_res->d_name[0] != '.')
        {
            if (file_res->d_type == DT_DIR)
            {
                strncpy (tmp, dir_name, 256);
                strcat  (tmp, "/");
                strcat  (tmp, file_res->d_name);

                res += count_files (tmp);

                memset (tmp, '\0', 256);
            }

            ++res;
        }

        file_res = readdir (dir);
    }

    closedir (dir);

    return res;
}

void print_included_directories (char* dir_name, char* start_name)
{
    char tmp[256];
    char tmp1[256];

    memset (tmp, '\0', 256);

    DIR* dir = opendir (dir_name);

    struct dirent* file_res = readdir (dir);

    while (file_res)
    {
        if (file_res->d_name[0] != '.' && file_res->d_type == DT_DIR)
        {
            strncpy (tmp, dir_name, 256);
            strcat  (tmp, "/");
            strcat  (tmp, file_res->d_name);

            strncpy (tmp1, start_name, 256);
            strcat  (tmp1, "/");
            strcat  (tmp1, file_res->d_name);

            printf ("%s/%s\n", start_name, file_res->d_name);

            print_included_directories (tmp, tmp1);

            memset (tmp,  '\0', 256);
            memset (tmp1, '\0', 256);
        }

        file_res = readdir (dir);
    }

    closedir (dir);
}

int count_files_without (char* dir_name, long int* m, int n)
{
    int key = 0;

    int res = 0;

    char tmp[256];
    memset (tmp, '\0', 256);

    DIR* dir = opendir (dir_name);

    struct dirent* file_res = readdir (dir);

    while (file_res)
    {
        if (file_res->d_name[0] != '.')
        {
            if (file_res->d_type == DT_DIR)
            {
                strncpy (tmp, dir_name, 256);
                strcat  (tmp, "/");
                strcat  (tmp, file_res->d_name);
                
                res += count_files_without (tmp, m, n);

                memset (tmp, '\0', 256);
            }

            for (int i = 0; i < n; ++i)
                if (file_res->d_ino == m[i])
                {
                    key = 1;
                    break;
                }

            if (key != 1)
            {
                ++res;
                m[n] = file_res->d_ino;
                ++n;
            }

            key = 0;
        }

        file_res = readdir (dir);
    }

    closedir (dir);

    return res;
}

int main (int argc, char* argv[])
{
    char dir_name[256];
    memset (dir_name, '\0', 256);

    if (argc == 1)
    {
        getcwd (dir_name, 256);
    }

    else if (argc == 2)
    {
        strncpy (dir_name, argv[1], 256);
    }

    else
    {
        printf ("Incorrect args\n");
        return 0;
    }

    printf ("Count of files: %d\n\n", count_files (dir_name));

    printf ("All included directories:\n");
    print_included_directories (dir_name, "");
    printf ("\n");

    long int m[1024];
    printf ("Count files without hard links: %d\n", count_files_without (dir_name, m, 0));
}