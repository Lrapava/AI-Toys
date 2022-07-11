# cost function
def cost(m, b, data):
	return sum([(m*x+b-y)**2 for (x, y) in data])/len(data)/2

# partial derivative of cost function for m
def dm(m, b, data):
	return sum([(m*x+b-y)*x for (x, y) in data]) / len(data)

# partial derivative of cost function for b
def db(m, b, data):
	return sum([(m*x+b-y) for (x, y) in data]) / len(data)

# main function
def main():
	# some made up data
	data = [(x, x+1) for x in range(6)]
	# m, b (from y = mx + b) and learning rate
	m, b, alpha = 0.0, 0.0, 0.01

	delta_m, delta_b = alpha*dm(m,b,data), alpha*db(m,b,data)
	# gradient descent
	while (abs(delta_m) > 10**-9 or abs(delta_b) > 10**-9):
		print(f"m: {format(m,'.3f')}; b: {format(b, '.3f')}; cost: {format(cost(m, b, data), '.3f')}")
		m -= delta_m
		b -= delta_b
		delta_m, delta_b = alpha*dm(m,b,data), alpha*db(m,b,data)

	print("Result:", format(m, '.3f'), format(b, '.3f'))

	# cost table for different values of m and b
	table = [[cost(x*0.1, y*0.1, data) for y in range(11)] for x in range(11)]

	for x in table:
		print(" ".join([str(format(y, '.3f')) for y in x]))
	
main()
