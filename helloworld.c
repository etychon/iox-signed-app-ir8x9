# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include<signal.h>

static FILE *fp = NULL;
static char *fullpath = NULL;

static void sig_handler(int signo)
{
  if (signo == SIGINT || signo == SIGKILL || signo == SIGTERM) {
      printf("received signal = %d\n", signo);
      if (fp)
          fclose(fp);
      /* use fullpath */
      if (fullpath)
          free(fullpath);
      exit(0);
  }
}

int main()
{
    signal(SIGINT, sig_handler);
    signal(SIGKILL, sig_handler);
    signal(SIGTERM, sig_handler);
    char* log_dir = getenv("CAF_APP_LOG_DIR");
    size_t dir_len = 0;
    if (log_dir != NULL) {
        dir_len = strlen(log_dir);
    }
    const char *logfile = "helloworld.log";
    /* + 2 because of the '/' and the terminating null character */
    fullpath = malloc(dir_len + strlen(logfile) + 2);
    if (fullpath == NULL) {
        return -1;
    }
    if (log_dir == NULL) {
        // If not "CAF_APP_LOG_DIR" then use just a file in local directory
        sprintf(fullpath, "%s", logfile);
    } else {
        // Otherwise build the commplete path
        sprintf(fullpath, "%s/%s", log_dir, logfile);
    }
    //sleep(10);
    fp;
    fp = fopen(fullpath, "w+");
    while(1) {
        fprintf(fp, "Hello World from IOx App!!!\n");
        sleep(2);
        fflush(fp);
    }
    fclose(fp);
    /* use fullpath */
    free(fullpath);

}
