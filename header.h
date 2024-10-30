/***************************** Header & Macro *****************************************/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_BUF_LEN 1024
#define CMD_DELIMS " \t\n"
#define MAX_HISTORY 10

/********************************** Function ************************************/

void init_shell();
void handle_signal(int signum);

char *read_command_line();
int parse_command_line(char *cmd, char **cmds);
int parse_command(char *cmd, char **cmd_tokens);
void parse_for_piping(char *cmd);
int parse_for_redirect(char *cmd, char **cmd_tokens);
int execute_command(char **cmd_tokens);

int is_piping(char *cmd);
void handle_redirect_and_piping(char *cmd);
void handle_normal_command(int tokens, char **cmd_tokens);
void add_process(int pid, char *name);
void remove_process(int pid);

int open_input_file();
int open_output_file();

void change_prompt(char *new_prompt);
int cd(char **cmd_tokens, char *cwd, char *base_dir);
void update_cwd_relative(char *cwd);
void pwd(char **cmd_tokens);
void add_to_history(char *cmd);
void print_history();
char *find_command_by_prefix(char *prefix);

/******************************* Variable And Struct ******************************/

struct process_info
{
  int pid, pgid;
  char *name;
  int active;
};

typedef struct process_info process_info;
process_info table[MAX_BUF_LEN];

char base_dir[MAX_BUF_LEN];
char *pipe_cmds[MAX_BUF_LEN];
char cwd[MAX_BUF_LEN];
extern char prompt[MAX_BUF_LEN];
char history[MAX_HISTORY][MAX_BUF_LEN];

pid_t my_pid, my_pgid, fgpid;

char *in_file;
char *out_file;

char **input_token_cmds;
char **output_token_cmds;
char **input_redirect_cmds;
char **output_redirect_cmds;

int job_num;
int shell, shell_pgid;
int output_redi_type, pipe_num;
int piping, input_redi, output_redi;
int is_background, input_idx, ouput_idx;