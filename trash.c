/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 04:50:59 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/28 04:59:07 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// char	*heredoc(char *del)
// {
// 	int 	read_ret;
// 	char	buffer;
// 	int		size_del;
// 	char	*ret;
// 	int		inc;
// 	int		counter;
// 	bool	new_line;
// 	if (!del)
// 		error_msg("Heredoc: Dont have delimiter\n");
// 	size_del = ft_strlen(del);
// 	printf("del %s and size del %d\n", del, size_del);
// 	ret = malloc(sizeof(char) + 1);
// 	if (!ret)
// 		return (NULL);
// 	read_ret = read(0, &buffer, 1);
// 	counter = 0;
// 	printf("counter %d\n", counter);
// 	inc = 0;
// 	new_line = false;
// 	while (++inc && read_ret > 0)
// 	{
// 		if (buffer == '\n')
// 			new_line = true;
// 		else if (new_line && buffer == del[counter])
// 			counter++;
// 		else if (counter != 0)
// 		{
// 			counter = 0;
// 			new_line = false;
// 		}
// 		ret[inc - 1] = buffer;
// 		ret = realloc(ret, sizeof(char) + (inc + 1));
// 		if (counter == size_del - 1)
// 			break;
// 		read_ret = read(0, &buffer, 1);
// 	}
// 	ret[inc] = '\0';
// 	ret = cut_string(ret, 0, ft_strlen(ret) - size_del);
// 	return (ret);
// }
