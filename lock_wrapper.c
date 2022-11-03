#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int find(int p[], int y, int x)		// Function returns 1 if a number is present in an array or else returns 0.
{
	int i = 0;
	int flag = 0;
	while(i < x)
	{
		if(p[i] == y)
		{
			flag = 1;
			break;
		}
		i++;
	}
	return flag;
}
int find_lower_bound(int p[], int y, int k)	// Function to find the index of the smallest number in an array which is greater than a given number 
{
	int i = 0;
	int num;
	while(i < k)
	{
		num = i;
		if(p[i] >= y)
			break;
		i++;
	}
	return num;
}


int isPrime(int n)				// Function to check whether a number is prime or not
{
	for (int i = 2; i <= n / i; ++i)
        	if (n % i == 0) 
        		return 0;
	return 1;
}



int configure(int k, char* locker_id, int L)
{
	int primes[k];
	int u[k];
	int j = 0;
	int p[15000];
	int index[9999];
	for(int i = 2; i<=L;i++)
	{
		int rem = L%i;
		if(isPrime(i) && rem < 10000)
		{
			p[j] = i;
			index[j] = j;
			j++;
		}
	}
	int w = 0;
	double L_temp = L;
	int k_temp = k;
	int q = 0;
	srand(time(NULL));
	while( q < k)
	{
		double y = pow(L_temp,1.0/k_temp);
		int temp = find_lower_bound(p , (int)y, j);
		int randomindex = (rand()% (j - temp )) + temp;
		if( find(primes, p[randomindex], q) == 1)
			continue;
		primes[q] = p[randomindex];
		u[q] = L % primes[q];
		L_temp = L_temp / primes[q];
		k_temp -= 1;
		q++;
	}
	
	
	FILE* fp,*fp_temp;
	int status=0;
	char* token;
	char* line = malloc(sizeof(char) * 100);   
					                                                          
	fp = fopen("config", "r+");                                   
	fp_temp = fopen("config_temp", "w+");
					
	while(fgets(line, 100, fp ) != NULL )          
	{
		token = strtok(line, " ");
		if(strcmp(token,locker_id))
		{
			while(token != NULL)
			{
				fprintf(fp_temp,"%s ",token);
				token = strtok(NULL, " ");
			}
		}
		else
			status = 1;
	}
	fprintf(fp,"\n%s %d ",locker_id,k);
	for(int y = 0; y < k; y++)
		fprintf(fp,"%d ", primes[y]);
	int tem;
	if(status == 1)
	{
		printf("\nLocker_id already exists. Press 1 to modify it ");
		scanf("%d", &tem);
		if(tem == 1)
		{
			fprintf(fp_temp,"\n%s %d ",locker_id,k);
				for(int y = 0; y < k; y++)
					fprintf(fp_temp,"%d ", primes[y]);
			printf("\nLocker modified successfully\n");
			printf("The secondary keys are:\n");
			for( int z = 0; z < k; z++)
			{
				if(u[z] / 10 == 0)
					printf("000%d ", u[z]);
				else if(u[z] / 100 == 0)
					printf("00%d ", u[z]);
				else if( u[z] / 1000 == 0)
					printf("0%d ", u[z]);
				else
					printf("%d ", u[z]);
			}
		}
		else
			exit(0);
	}
	else
	{
		fprintf(fp_temp,"\n%s %d ",locker_id,k);
		for(int y = 0; y < k; y++)
			fprintf(fp_temp,"%d ", primes[y]);
		printf("\nNew locker created successfully\n");
		printf("The secondary keys are:\n");
		for( int z = 0; z < k; z++)
		{
			if(u[z] / 10 == 0)
				printf("000%d ", u[z]);
			else if(u[z] / 100 == 0)
				printf("00%d ", u[z]);
			else if( u[z] / 1000 == 0)
				printf("0%d ", u[z]);
			else
				printf("%d ", u[z]);
		}
		printf("\n");
	}
	fclose(fp);
	fclose(fp_temp);
	remove("config");
	rename("config_temp", "config");
}

int inv( int a, int m)			// Function to find inverse modulo of a number with corresponding product divided by the given number
{
	int m0 = m ,t ,q;
	int x0 = 0;
	int x1 = 1;
	while(a > 1)
	{
		q = a / m;
		t = m;
		m = a%m;
		a = t;
		t = x0;
		x0 = x1 - q*x0;
		x1 = t;
	}	
	if(x1 < 0)
		x1 = x1 + m0;
		
	return x1;
	
}


int find_N(int num[], int rem[], int k)	// Chinese remainder theorem to find the number for given sets of divisors and remainders
{
	int product = 1;
	int m[k];
	int N = 0;
	for(int i = 0; i <k; i++)
		product = product * num[i];
	for(int i = 0; i <k; i++)
	{
		m[i] = product / num[i];
		N = N + rem[i] * inv(m[i], num[i]) * m[i];	
	}
	return N % product;	
		
}


int use(char *Locker_id)
{
	FILE* fp;
	int* divisors;
	int* remainders;
	char* token;
	char* line = malloc(sizeof(char) * 100);
	int k;
	fp = fopen("config", "r");
	while ( fgets( line, 100, fp ) != NULL )
	{
		token = strtok(line, " ");
		if( !strcmp(token, Locker_id))
		{
			token = strtok(NULL, " ");
			k = atoi(token);
			divisors = malloc(sizeof(int)*k);
			remainders = malloc(sizeof(int)*k);
			printf("\nNumber of users: %d\n", k); 
			int m = 3;
			char temp_key[4];
			int i = 0;
			while(i < k)
			{
				token = strtok(NULL, " ");
				divisors[i] = atoi(token);
				i++;
			}
			
		}
		token = strtok(NULL, " ");
		
	}
    	fclose(fp);
    	
    	char temp[4];
    	int l =0;
    	while( l < k)
	{
		printf("enter user %d key: ", l+1);
	    	scanf(" %s", temp);
	    	if( strlen(temp) != 4)
	    	{
	    		printf("Please enter a 4-digit key\n");
	    		continue;
	    	}
	    	remainders[l] = atoi(temp);
	    	l++;			    	
	}
	
	return find_N(divisors,remainders,k);
}

int main() 
{
	while(1)
	{
		int temp = 0;
		printf("\n\nMain Menu\n\n1. CONFIGURE\n2. USE\n3. EXIT\n\nPlease enter your preference(1/2/3): ");
		scanf("%d", &temp );
		if(temp == 1)
		{
			while(1)
			{
				temp = 0;
				printf("\n\n1. Add a new locker entry\n2. Delete locker entry\n3. Return to previous menu\n\nPlease enter your new preference(1/2/3):  ");
				scanf("%d", &temp);
				if(temp == 1)
				{
					int k, L;
					char Locker_id[5];
					printf("Enter a value for locker_id: ");
					scanf("%s", Locker_id);
					printf("Enter a value for the key: ");
					scanf("%d", &L);
					printf("Enter a value for number of customers: ");
					scanf("%d", &k);
					configure(k, Locker_id, L);
					break;
				}
				else if(temp == 2)
				{
					FILE *fp, *fp_temp;                                                                     
					int status=0;
					char Locker_id[10];
					char* token;
					char* line = malloc(sizeof(char) * 100);   
							                                                  
					fp = fopen("config", "r");                                   
					fp_temp = fopen("config_temp", "w+");
						
					printf("\nEnter the locker id to be deleted: ");
					scanf(" %[^\n]s", Locker_id);
					while(fgets(line, 100, fp ) != NULL )          
					{
						token = strtok(line, " ");
						if(strcmp(token,Locker_id))
						{
							while(token != NULL)
							{
								fprintf(fp_temp,"%s ",token);
								token = strtok(NULL, " ");
							}
						}
						else
							status = 1;
					}
					if(status == 1)
						printf("\nThe mentioned Locker_id has been deleted successfully");
					else
						printf("\nNo such locker id exists");
					fclose(fp);
					fclose(fp_temp);
					remove("config");
					rename("config_temp", "config");
					break;
				} 		
				else if(temp == 3)
				{
					break;
				}
				else
				{
					printf("please enter 1 or 2 or 3");
				}
			}
		}
		else if(temp == 2)
		{
			char Locker_id[5];
			printf("Enter the locker_id: ");
			scanf(" %s", Locker_id);
			printf("%d\n",use(Locker_id));
		}
		else if(temp == 3)
			exit(0);
		else
		{
			printf("please enter 1 or 2 or 3");
		}
	}
}
