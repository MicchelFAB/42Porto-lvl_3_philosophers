#include <stdio.h>

int ft_atoi_philo(char *str)
{
	int r;

	r = 0;
	if (str == NULL || str[0] == '-')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		return (-1); 
	return (r);
}

int main()
{
    // Test cases
    printf("%d\n", ft_atoi_philo("123"));      // Expected output: 123
    printf("%d\n", ft_atoi_philo("00123"));    // Expected output: 123
    printf("%d\n", ft_atoi_philo("123abc"));   // Expected output: -1
    printf("%d\n", ft_atoi_philo("   123"));   // Expected output: -1
    printf("%d\n", ft_atoi_philo("123   "));   // Expected output: -1
    printf("%d\n", ft_atoi_philo(""));         // Expected output: -1
    printf("%d\n", ft_atoi_philo("   "));      // Expected output: -1
    printf("%d\n", ft_atoi_philo("-123"));     // Expected output: -1
    printf("%d\n", ft_atoi_philo("abc"));      // Expected output: -1
    printf("%d\n", ft_atoi_philo("12abc34"));  // Expected output: -1

    return 0;
}