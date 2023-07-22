#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

// Idea from "ls.c" file
char* 
getFileName(char *path) 
{
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  return p;
}

void
findFile(char *path, char *name) 
{
    char buf[512], *p;
    int fd;
    struct stat st;
    struct dirent de;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
        case T_FILE:
            if (strcmp(getFileName(path), name) == 0) {    // equal to file name
                printf("%s\n", path);
            }
            break;
        
        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
                fprintf(2, "find: src path too long\n");
                exit(1);
                break;
            }

            strcpy(buf, path);
            p = buf + strlen(buf);  // point to the end of the buf
            *p++ = '/';

            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;

                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                    continue;
                }

                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;  // indicate the end of the path

                findFile(buf, name);
            }

            break;

    }

    close(fd);
    
}

int 
main(int argc, char *argv[]) {
    // check inputs
    if (argc != 3) {
        fprintf(2, "Usage: find path name\n");
        exit(1);
    }

    findFile(argv[1], argv[2]);
    
    exit(0);
}
