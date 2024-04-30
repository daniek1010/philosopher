/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:29:18 by danevans          #+#    #+#             */
/*   Updated: 2024/04/03 22:45:41 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>
// #include "./libft/libft.h"
// #include <sys/time.h>
// #include <pthread.h>
#include "philo.h"

// # define TRUE 1
// # define FALSE 0
// int mode = 0;
pthread_mutex_t mutex;
// int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
// void *routine(void *mad)
// {
// 	int arg = *(int *)mad;
	pthread_mutex_lock(&mutex);
	//printf(" %d  ", prime[(arg)]);
	printf(" %d  ", arg);
	pthread_mutex_unlock(&mutex);
// }
// void *routine1()
// {
// 	for (int i = 0; i < 10000000; i++)
// 	{
// 		//pthread_mutex_lock(&mutex);
// 		mode++;
// 		//pthread_mutex_unlock(&mutex);
// 	}
// 	//printf(" %d  ", prime[(arg)]);
// 	//printf(" %d  ", arg);
	
// }

// int	digit_check(int argc, char *argv[])
// {
// 	int		i;
// 	int		j;
// 	char	*holder;

// 	if (argc == 1)
// 		return (FALSE);
// 	i = 1;
// 	while (i < argc)
// 	{
// 		holder = argv[i];
// 		if (holder == NULL)
// 			return (FALSE);
// 		j = 0;
// 		while (holder[j] != '\0')
// 		{
// 			if (((holder[j] < '0') || (holder[j] > '9' )) && (holder[j] != ' '))
// 			{
// 				// if (holder[j + 1] == 32)
// 				// 	return (FALSE);
// 				return (FALSE);
// 			}
// 			j++;

// 		}
// 		i++;
// 	}
// 	return (TRUE);
// }

int	main(int argc, char *argv[])
{
	t_input input;
	ft_parse(argc, argv, &input);
	printf("value of %ld %ld %ld %ld %ld\n", input.philo_num, input.time_to_die, input.time_to_eat, input.time_to_sleep, input.optional);
}
	
	
	// char **temp = param_split(argc, argv);
	// if (temp == NULL)
	// 	return 0;
	// for (int k = 0; temp[k] != NULL; k++)
	// {
	// 	printf("[%d] = %s\n", k, temp[k]);
	// 	free(temp[k]);
	// }
	// //ft_cleaner(temp);
	// free(temp);

// 	// if (!digit_check(argc, argv))
// 	// {
// 	// 	printf("got heere");
// 	// 	return(FALSE);
// 	// }
	
	pthread_t p1[10];
	pthread_t p2, p3;
// 	// int main = 0;
 pthread_mutex_init(&mutex, NULL);
// 	// for (int j = 0; j < 1000000; j++)
// 	// {
// 	// 		main++;
// 	// }
// 	// int i;
// 	// for (i = 0; i < 10; i++)
// 	// {
// 	// 	pthread_create(&p1[i], NULL, &routine, prime + i);
// 	// 	pthread_join(p1[i], NULL);
// 	// 	printf("what are you saying now %d\n", i);
// 	// 	//pthread_create(&p2[i], NULL, &routine1, NULL);
// 	// }
// 	// // for (i = 0; i < 10; i++)
// 	// //{
		pthread_create(&p2, NULL, &routine1, NULL);
		pthread_join(p2, NULL);
		printf("value mdoe %d\n", mode);
		pthread_create(&p3, NULL, &routine1, NULL);
		pthread_join(p3, NULL);
// 	// 	//printf("from routine1 %d\n", i);
// 	// 	//pthread_create(&p2[i], NULL, &routine1, NULL);
// 	// //}
// 	// // for ( i = 0; i < 10; i++)
// 	// // {
// 	// // 	pthread_join(p1[i], NULL);
// 	// // 	printf("are you here now %d\n", i);
// 	// // 	//pthread_join(p2[i], NULL);
// 	// // }
	
 pthread_mutex_destroy(&mutex);
// 	// printf("value mdoe %d\n", mode);
// 	// printf("value main %d\n", main);
	
// }

// char **ft_splitt(const char *str, char delim) {
//     int i, word_count = 0, word_length = 0, in_word = 0;
//     char **result = NULL;
    
//     // Count the number of words
//     for (i = 0; str[i] != '\0'; i++) {
//         if (str[i] == delim) {
//             if (in_word) {
//                 word_count++;
//                 in_word = 0;
//             }
//         } else {
//             if (!in_word) {
//                 in_word = 1;
//             }
//             word_length++;
//         }
//     }
//     if (in_word) {
//         word_count++;
//     }
    
//     // Allocate memory for the array of strings
//     result = malloc((word_count + 1) * sizeof(char *));
//     if (result == NULL) {
//         return NULL; // Memory allocation failed
//     }
    
//     // Allocate memory for each string and copy the substrings
//     in_word = 0;
//     word_length = 0;
//     int word_index = 0;
//     for (i = 0; str[i] != '\0'; i++) {
//         if (str[i] == delim) {
//             if (in_word) {
//                 result[word_index] = malloc((word_length + 1) * sizeof(char));
//                 if (result[word_index] == NULL) {
//                     // Memory allocation failed, free already allocated memory
//                     for (int j = 0; j < word_index; j++) {
//                         free(result[j]);
//                     }
//                     free(result);
//                     return NULL;
//                 }
//                 strncpy(result[word_index], str + i - word_length, word_length);
//                 result[word_index][word_length] = '\0';
//                 word_index++;
//                 in_word = 0;
//                 word_length = 0;
//             }
//         } else {
//             if (!in_word) {
//                 in_word = 1;
//             }
//             word_length++;
//         }
//     }
//     if (in_word) {
//         result[word_index] = malloc((word_length + 1) * sizeof(char));
//         if (result[word_index] == NULL) {
//             // Memory allocation failed, free already allocated memory
//             for (int j = 0; j < word_index; j++) {
//                 free(result[j]);
//             }
//             free(result);
//             return NULL;
//         }
//         strncpy(result[word_index], str + i - word_length, word_length);
//         result[word_index][word_length] = '\0';
//     }
    
//     // Null-terminate the array of strings
//     result[word_count] = NULL;
    
//     return result;
// }

// void	param_check(int argc, char **argv)
// {
// 	int		i;
// 	int		j;
// 	char	*holder;

// 	if (argc == 1)
// 		perror("agc");
// 	i = 0;
// 	while (++i < argc)
// 	{
// 		holder = argv[i];
// 		j = 0;
// 		while (holder[j] != '\0')
// 		{
// 			if ((holder[j] < 48 || holder[j] > 57) && holder[j] != 32)
// 			{
// 				if (holder[j] != 45)
// 					perror("the");
// 				if ((holder[j] == 45) && (holder[j + 1] == 45))
// 					perror("thw");
// 				if (holder[j] == 32 && holder[j + 1] == 32)
// 					perror("the");
// 			}
// 			j++;
// 		}
// 	}
// }

// char	**check_size(int argc, char *argv[], int *size)
// {
// 	int		i;
// 	int		j;
// 	char	**splitted;
// 	char	**container;

// 	param_check(argc, argv);
// 	container = malloc(sizeof(char *) * argc);
// 	if (container == NULL)
// 		perror("te");
// 	i = 0;
// 	while (++i < argc)
// 	{
// 		splitted = ft_split(argv[i], ' ');
// 		j = -1;
// 		while (splitted[++j] != NULL)
// 		{
// 			container[*size] = malloc(ft_strlen(splitted[j]) + 1);
// 			if (container[*size] == NULL)
// 			{
// 				ft_cleaner(container);
// 				ft_cleaner(splitted);
// 				return NULL;
// 			}
// 			strcpy(container[*size], splitted[j]);
// 			(*size)++;
// 		}
// 		ft_cleaner(splitted);
// 	}
// 	container[*size] = NULL;
// 	return (container);
// }

// int	main(int argc, char *argv[])
// {
// 	int size = 0;
// 	char **temp = check_size(argc, argv, &size);
// 	if (temp == NULL)
// 		return 0;
// 	for (int k = 0; temp[k] != NULL; k++)
// 	{
// 		printf("[%d] = %s\n", k, temp[k]);
// 		free(temp[k]);
// 	}
// 	//ft_cleaner(temp);
// 	free(temp);
// }
