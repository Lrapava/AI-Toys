// cost function
function cost(m, b, data) {
	return data.map(p => (m*p[0]+b-p[1])**2).reduce((a, b) => a + b, 0) / data.length / 2
}

// partial derivative of cost function for m
function dm(m, b, data) {
	return data.map(p => (m*p[0]+b-p[1])*p[0]).reduce((a, b) => a + b, 0) / data.length
}

// partial derivative of cost function for b
function db(m, b, data) {
	return data.map(p => (m*p[0]+b-p[1])).reduce((a, b) => a + b, 0) / data.length
}

// made up data
let data = [...Array(6).keys()].map(x => [x, x+1])
// m, b (from y = mx + b) and learning rate
let m = 0.0, b = 0.0, alpha = 0.01
let delta_m = alpha*dm(m, b, data), delta_b = alpha*db(m, b, data)

// gradient descent 
while (Math.abs(delta_m) > 10**-10 || Math.abs(delta_b) > 10**-10) {
	console.log("m: " + m.toFixed(3) + "; b: " + b.toFixed(3) + "; cost: " + cost(m, b, data).toFixed(3))
	m -= delta_m; b -= delta_b;
	delta_m = alpha*dm(m, b, data);
	delta_b = alpha*db(m, b, data);
}

// outputting result
console.log("Result: " + m.toFixed(3) + " " + b.toFixed(3))

// cost table for different values of m and b
let table = [...Array(11).keys()].map(
	x => [...Array(11).keys()].map(y => cost(x*0.1, y*0.1, data)).reduce((a, b) => a+b.toFixed(3)+" ", "")
).reduce((a, b) => a+b+"\n", "")
console.log(table)
