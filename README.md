# Locker

For the configure module, we take locker_id,k,L as the inputs and generate k-random distinct
primes. Initially I assumed at least one of the primes must be greater than k-th root of L. I use
the random function to generate the first prime(p1) with the mentioned condition. Then I divide L
by p1 and make it the new L and assume at least one of the remaining primes must be greater
than the (k-1)th root of the new L. I again use the random function to generate p2 with the
mentioned condition and divide L by p2 and make it the new L. This process is repeated till we
get k primes. Then I find the for each of the corresponding primes when they divide L and these
will be the user keys printed on the screen. The locker_id, k and all the primes are added to the
“config.txt” file.
Next for use model, we ask the user to give the locker_id. We search the text file for the given id
and store the corresponding prime numbers in an array. We ask the user to input the
corresponding remainders as a 4-digit key and store these remainders in another array. We then
apply the Chinese remainder theorem to get the locker key. If user enters any one wrong key,
you will get a wrong locker_id.
For deleting a locker, we ask user to enter a locker_id. We search for the locker_id in the text
file. Except for the locker_id contents, we print the rest of the text file into a new text file and
delete the old one. Then we rename the new one by the old name.
For the Chinese remainder theorem, we take divisors and remainders arrays and also their
sizes as the inputs. We find product of all the divisors. For each divisor, we find the
product/divisor(say m) and find the inverse modulo of that divisor. Finally we take the sum of the
corresponding remainder times inverse modulo times “m” for each of the divisor. The resulting
sum would be the solution.
