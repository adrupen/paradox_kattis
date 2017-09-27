import sys

def main()
	
	capacity = sys.stdin.read() # Capacity
	n = sys.stdin.read()		# Number of stops

	currently_in_train = 0
	possible = True

	for line in sys.stdin:
		stop = line.split()
		currently_in_train -= int(stop[0])

		if currently_in_train < 0:
			possible = False
			break

		currently_in_train += int(stop[1])

		if currently_in_train > capacity:
			possible = False
			break

		if int(stop[2]) > 0:
			if currently_in_train != capacity:
				possible = False
				break

	if possible:
		print("possible")
	else
		print("impossible")



if __name__ == "__main__":
    main()