#include "ush.h"

static void print_error(char **command, int i){
	mx_printstr(command[i]);
    mx_printstr(" not found \n");

}

static char **yos(char **command){
	if (command[1][0] != '-') {
        char *copy = " ";
        char *buf = " ";
        buf = command[1];
        command[1] = copy;
        for (int i = 2; i < mx_strarr_size(command) + 1; ++i) {
            command[i] = buf;
            buf = command[i + 1];
        }
    }
    return command;
}

static int *flag_parser(char **command,int *flags){
	if(command[1][0] == '-'){
    	flags[0] = mx_is_in_arr(command[1], 's');
    	flags[2] = mx_is_in_arr(command[1], 'a');
    	for (int i = 1; i < mx_strlen(command[1]); ++i) {
    		if (command[1][i] != 's' && command[1][i] != 'a')  {
    			mx_printstr("which: bad option: -");
    			write(1, &command[1][i], 1);
    			mx_printstr("\n");
    			flags[1] = 4;
    			return flags;
    		}
    	}
		return flags;
	}
	flags[0] = 2;
	return flags;
}

static char **getpath(){
	char *path = getenv("PATH");
	char **paths = mx_str_to_arr(path,':');
	return paths;
}

int mx_which(char **command) {
	struct dirent *pDirent;
    DIR *pDir;
	char **paths = getpath();
	int *flags = malloc(sizeof(int*) * 2);
		if (mx_strarr_size(command) > 1) {
			command = yos(command);
			flags = flag_parser(command,flags);
			if (flags[1] != 4) {
				for (int i = 2 , flag = 0;command[i]; i++){
					flag = 0;
					for (int len = 0; paths[len]; len++){
						pDir = opendir (paths[len]);
						while ((pDirent = readdir(pDir)) != NULL) {
		       		 		if (mx_strcmp(pDirent->d_name, command[i])== 0){
		        	    		mx_printstr(mx_three_join(paths[len],"/",pDirent->d_name));
		        	    		mx_printstr("\n");
		           		 		flag++;
		           		 		if (flags[0] == 1)
		       		 				return 1;
		           		 		else if(flags[0] == 2)
		           		 			return 0;
		        				else if (flags[2] == 1)
		        					continue;
		        			}
		       			}
		       		}
		       	if (flag == 0)
		       		print_error(command,i);
		    }
		}
	}
	free(flags);
    return 0;
}

