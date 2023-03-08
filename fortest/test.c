// int k;
// while (cmd_lst != NULL)
// {
// 	k = -1;
// 	printf("path = %s\n", cmd_lst->cmd_path);
// 	if (cmd_lst->cmd_split)
// 	{
// 		while (cmd_lst->cmd_split[++k])
// 			printf("cmd_split = %s\n", cmd_lst->cmd_split[k]);
// 	}
// 	printf("prev = %i\n", cmd_lst->prev);
// 	printf("infile = %i\n", cmd_lst->infile);
// 	printf("outfile = %i\n", cmd_lst->outfile);
// 	int j = -1;
// 	while (cmd_lst->env[++j])
// 		printf("env = %s\n", cmd_lst->env[j]);
// 	printf("env = %s\n", cmd_lst->env[j]);
// 	if (cmd_lst->infile != -1 && cmd_lst->infile != 0)
// 	{
// 		char *line = get_next_line(cmd_lst->infile);
// 		while (line)
// 		{
// 			printf("line = %s\n", line);
// 			line = get_next_line(cmd_lst->infile);
// 		}
// 	}
// 	cmd_lst = cmd_lst->next;
// }


//cat abc | < main.c grep ";2C;2Ca " | ls > a.txt < ahdgsa | << a grep -a -av -äv | echo $USER$shd$/sur "$//GDFS $USEDSSD  $USER "


//if general error exit_status = 1;
//if builtin missused exit_status = 2;
//if script with no exec permission exit_status = 126;
//if command doesnt exist exit_status = 128;
//if program terminated by a fatal signal like seg. fault exit_status = 129;
//if program terminated by ctrl + c exit_status = 130;
// if Exit status out of range (e.g. specifying an invalid exit status code in a script or command) exit_status = 255;

// t_cmds	*err_func(t_cmds *cmd)
// {
// 	t_cmds	*cmd_lst = NULL;
// 	t_cmds	*tmp;

// 	while (cmd != NULL)
// 	{
// 		tmp = cmd->next;
// 		if (cmd->err != 0)
// 		{
// 			set_err(cmd->err_file, cmd->err);
// 			free_cmd(cmd);
// 		}
// 		else
// 			add_cmd(&(cmd_lst), cmd);
// 		cmd = tmp;
// 	}
// 	return (cmd_lst);
// }

//if err =-1 && (infile != -1|| outfile != -1)
// write(2, "shell: ", 7);
// write(2, cmd, ft_strlen(cmd));
// write(2, ": No such file or directory\n", 28);


// t_cmds *tmp;
// while (cmd_lst != NULL)
// {
// 	if (cmd_lst->infile != 0)
// 		close(cmd_lst->infile);
// 	if (cmd_lst->outfile != 1)
// 		close(cmd_lst->outfile);
// 	tmp = cmd_lst->next;
// 	free_cmd(cmd_lst);
// 	cmd_lst = tmp;
// }

// int z = -1;
// while (envp[++z])
// 	free(envp[z]);
// free(envp);


// ^C==76758== Warning: noted but unhandled ioctl 0x2000746e with no size/direction hints.
// ==76758==    This could cause spurious value errors to appear.
// ==76758==    See README_MISSING_SYSCALL_OR_IOCTL for guidance on writing a proper wrapper.