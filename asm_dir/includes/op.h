/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

/*
******************************** INTEGER CONSTANTS *****************************
*/


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define HEADER_CHAR			'.'
# define EXTENTION_CHAR			'.'
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define REG_CHAR				'r'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

# define T_REG					1
# define T_DIR					2
# define T_IND					4	

/*
**
*/

# define REG_SIZE				1
# define IND_SIZE				4

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
****************************** OP_TAB DEFINES **********************************
*/

# define OP_NAME			0
# define ARG_NB				1
# define ARG_TYPE 			2
# define OP_CODE 			3
# define CYCLES 			4
# define DESCR 				5
# define CODAGE 			6
# define CARRY 				7

/*
****************************** MACROSES ****************************************
*/

# define DIR_SIZE(label_size) (label_size == 2) ? (2) : (4)
# define MAX_LABEL_NB(label_size) (label_size == 2) ? (0xFFFF) : (0xFFFFFFFF)

/*
****************************** TYPEDEFS ****************************************
*/

typedef struct s_op			t_op;
typedef struct s_header 	t_header;

/*
****************************** STRUCTURES **************************************
*/

struct 						s_op
{
	char					*name;
	char					arg_nb;
	char					arg_type[3];
	int						op_code;
	int						cycles;
	char					*descr;
	char					codage;
	char					carry;
	int 					label_size;
};

struct						s_header
{
	int						magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	int						prog_size;
	char					comment[COMMENT_LENGTH + 1];
};

/*
****************************** DECLARATIONS ************************************
*/

extern t_op    g_op_tab[17];

#endif
