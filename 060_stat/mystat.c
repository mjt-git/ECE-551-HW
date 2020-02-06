#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

const char * filetype(
    struct stat sb) {  // determine the filetype, according to sb.st_mode
  const char * ret;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      ret = "block special file";
      break;
    case S_IFCHR:
      ret = "character special file";
      break;
    case S_IFDIR:
      ret = "directory";
      break;
    case S_IFIFO:
      ret = "fifo";
      break;
    case S_IFLNK:
      ret = "symbolic link";
      break;
    case S_IFREG:
      ret = "regular file";
      break;
    case S_IFSOCK:
      ret = "socket";
      break;
    default:
      ret = "unknown";
      break;
  }
  return ret;
}

char firstLetter(struct stat sb) {  // return first letter of human readable permission
  char ret;
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      ret = 'b';
      break;
    case S_IFCHR:
      ret = 'c';
      break;
    case S_IFDIR:
      ret = 'd';
      break;
    case S_IFIFO:
      ret = 'p';
      break;
    case S_IFLNK:
      ret = 'l';
      break;
    case S_IFREG:
      ret = '-';
      break;
    case S_IFSOCK:
      ret = 's';
      break;
    default:
      ret = 'u';  // unknown
      break;
  }
  return ret;
}

char hrpLetter(int comp,
               int condi,
               char NonZeroCH,
               char ZeroCH) {  // return letter from second to tenth
  // comp and condi are the value used to decide the return char; ch1 and ch2 are two possible return char
  if ((comp & condi) != 0) {
    return NonZeroCH;
  }
  else {
    return ZeroCH;
  }
}

char * humReadPerStr(struct stat sb) {  // return human-readable-permission string
  char * str = malloc(11 * sizeof(*str));
  str[0] = firstLetter(sb);
  str[1] = hrpLetter(sb.st_mode, S_IRUSR, 'r', '-');
  str[2] = hrpLetter(sb.st_mode, S_IWUSR, 'w', '-');
  str[3] = hrpLetter(sb.st_mode, S_IXUSR, 'x', '-');
  str[4] = hrpLetter(sb.st_mode, S_IRGRP, 'r', '-');
  str[5] = hrpLetter(sb.st_mode, S_IWGRP, 'w', '-');
  str[6] = hrpLetter(sb.st_mode, S_IXGRP, 'x', '-');
  str[7] = hrpLetter(sb.st_mode, S_IROTH, 'r', '-');
  str[8] = hrpLetter(sb.st_mode, S_IWOTH, 'w', '-');
  str[9] = hrpLetter(sb.st_mode, S_IXOTH, 'x', '-');
  str[10] = '\0';
  return str;
}

void printOneArgu(char * arg) {  // print info for one argument
  struct stat sb;
  if (lstat(arg, &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }
  const char * ftype = filetype(sb);
  char * humReadPer = humReadPerStr(sb);
  struct passwd * pswd = getpwuid(sb.st_uid);
  struct group * gp = getgrgid(sb.st_gid);
  char * accessT = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  char * modiftT = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  char * changeT = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  if (S_ISLNK(sb.st_mode) == 1) {
    char linktarget[256];
    ssize_t len = readlink(arg, linktarget, 256);
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", arg, linktarget);
  }
  else {
    printf("  File: %s\n", arg);
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         sb.st_size,
         sb.st_blocks,
         sb.st_blksize,
         ftype);
  if (S_ISCHR(sb.st_mode) == 1 || S_ISBLK(sb.st_mode) == 1) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           sb.st_ino,
           sb.st_nlink);
  }

  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         sb.st_mode & ~S_IFMT,
         humReadPer,
         sb.st_uid,
         pswd->pw_name,
         sb.st_gid,
         gp->gr_name);
  printf("Access: %s\n", accessT);
  printf("Modify: %s\n", modiftT);
  printf("Change: %s\n", changeT);
  printf(" Birth: -\n");
  free(accessT);
  free(modiftT);
  free(changeT);
  free(humReadPer);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    fprintf(stderr, "Wrong argument number!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < argc; i++) {
    printOneArgu(argv[i]);
  }
  return EXIT_SUCCESS;
}
