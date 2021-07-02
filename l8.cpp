    #include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <iostream>
//#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <unistd.h>
#define OPEN_LOCK_EXEC_ERROR -1
#define MAXTRIES 5
#define TRY_FAILURE 2
#define LOCK_FAILURE 3






int main(int argc, char* argv[])
{
    int fd, itry = 0;
    struct flock lock;
    if (argc != 2) {
        fprintf(stdout, "Usage- fileName \n");
        exit(EXIT_FAILURE);

    }

    if ((fd = open(argv[1], O_RDWR)) == OPEN_LOCK_EXEC_ERROR) {
        perror(argv[1]);
        exit(EXIT_FAILURE);

    }

    //==
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; //
    while ((fcntl(fd, F_SETLK, &lock) == OPEN_LOCK_EXEC_ERROR))
    {
        if ((errno == EACCES) || (errno == EAGAIN)) {  // Permission denied||Resource temporarily unavailable
            if (itry++ < MAXTRIES) {
                sleep(1);
                continue;

            }
            printf("%s busy -- try later\n", argv[1]);
            exit(TRY_FAILURE);
        }
        perror(argv[1]);
        exit(LOCK_FAILURE);
    }

    
    //
    /*
    * int system(const char *command);
    *
    */
    std::string sCommand(argv[1]);
    std::string st("vim ");
    st = st.append(sCommand);




    //
    if (system(NULL)) {

        //break;     //



        if (system(st.c_str()) == OPEN_LOCK_EXEC_ERROR) {
            printf(" smth wrong");
        }
    }

    //==
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    close(fd);


}