#include "phlio.h"
#include "limits.h"

int	ft_isdigit(int ch)
{
	return ((ch > 47) && (ch < 58));
}

int validate_nbr(char *input)
{
	int	index;

	index = 0;
	if (input[0] == '-' || input[0] == '+')
        index++;
	if (input[index] == '\0')
		return (0);
	while (input[index])
	{
		if (!ft_isdigit(input[index]))
			return (0);
        index++;
	}
	return (1);
}

int		ft_atoi(char *input, int *err)
{
    long num;
	int  sign;
	int index;

	index = 0;
	sign = 1;
	num = 0;
	if (input[index] == '-' || input[index] == '+')
	{
		if (input[index++] == '-')
			sign *= -1;
	}
	while (input[index] >= 48 && input[index] <= 57)
	{
		num = num * 10 + (input[index++] - 48);
        if (num * sign > INT_MAX || num * sign < INT_MIN)
        {
            *err = 1;
            return (-1);
        }
	}
	return (num * sign);
}

int safe_atoi(char *input, int *err)
{
    if (!validate_nbr(input))
    {
        *err = -1;
        return (-1);
    }
    return (ft_atoi(input, err));
}