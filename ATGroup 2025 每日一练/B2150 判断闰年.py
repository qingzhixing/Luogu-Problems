number = int(input())

if number % 100 == 0:
	print("Y" if (number%400==0) else "N")
else:
    print("Y" if (number%4==0) else "N")
