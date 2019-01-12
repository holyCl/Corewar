/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorzhak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 15:53:09 by akorzhak          #+#    #+#             */
/*   Updated: 2018/09/29 15:53:13 by akorzhak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>

/*
****************************** STRING CONSTANTS ********************************
*/

# define FAIL_OPEN_S "Source file is failed to open."
# define INVALID_INPUT "Provided assembly file is invalid."
# define INTERNAL_ERROR "Some internal error occured during assembler running."
# define SYNT_ERR_C "Syntax error at champion comment string."
# define SYNT_ERR_N "Syntax error at champion name string."
# define NO_CMD "Champion does NOT contain Name or Comment."
# define NAME_REDEFINE "Name redefine is forbidden."
# define COMM_REDEFINE "Comment redefine is forbidden."
# define NO_CMND "Champion does NOT contain Comands."
# define INC_LABELNAME "Incorrect name of Label."
# define INC_ARGS "Incorrect count of Arguments."
# define OP_EXIST "Operation does not exist."
# define LEXIC "Lexical error."

/*
****************************** TYPEDEFS ***************************************
*/

typedef struct s_asm		t_asm;
typedef struct s_ints		t_ints;
typedef struct s_asm_str	t_asm_str;

/*
****************************** STRUCTURES **************************************
*/

struct						s_asm
{
	int						s_fd;
	int						cor_fd;
	char					*error_message;
};

struct 						s_ints
{
	int						i;
	int						len;
	int						fl;
	int						temp;
	int						oper;	
};

struct						s_asm_str
{
	char					*label;
	int						label_size;
	int						op_code;
	int						type_arg[3];
	int						arg_cont[3];
	char					*pointer[3];
	int						codage;
	int						size;
	int						nb;
	t_asm_str				*next;
	t_asm_str				*prev;
};

/*
******************************** MAIN FUNCTIONS ********************************
*/

void						init(void *s);
void						init_header(t_header *header);
int							read_file(t_asm *a, t_header *header, \
							t_asm_str **asm_str);
int							validate_header(t_header *header);
void						handle_read_data(t_header *header, \
							t_asm_str **asm_str);
void						find_labels_addresses(t_asm_str **asm_str);
void						record_asm_str(char *src, t_asm_str **asm_str, \
							int nb);
int							ft_wordlen(char *str);
char						*cut_content(char *str);
char						is_empty_str(char *str);
void						error_type(char *line, int nb);
void						free_2d_array(char **arr);

/*
******************************** UTIL FUNCTIONS ********************************
*/

void						calc_initial_size_before_arg(int *size_before_arg, \
							t_asm_str *cur_str);
void						add_to_size_before_arg(int *size_before_arg, \
							t_asm_str *cur_str, int i);

int							exit_with_error(t_asm *a, char **line, \
							char *error_message);

/*
******************************** VIEW FUNCTIONS ********************************
*/

void						display_error_message(char *message);

#endif
