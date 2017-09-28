import sys

def main():
	
	first_row = sys.stdin.readline().split()
	capacity = int(first_row[0]) 	# Capacity
	n = int(first_row[1])			# Number of stops

	currently_in_train = 0
	possible = True

	for i in range(n):
		stop = sys.stdin.readline().split()
		currently_in_train -= int(stop[0])

		if currently_in_train < 0:
			possible = False

		currently_in_train += int(stop[1])

		if currently_in_train > capacity:
			possible = False

		if int(stop[2]) > 0:
			if currently_in_train != capacity:
				possible = False

		if i == n-1:
			if int(stop[2]) > 0:
				possible = False


	if currently_in_train != 0:
		possible = False

	if possible:
		print("possible")
	else:
		print("impossible")


if __name__ == "__main__":
    main()