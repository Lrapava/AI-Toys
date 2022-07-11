#include <bits/stdc++.h>
using namespace std;

// cost function
double cost(double m, double b, vector <pair <double, double>> &data) {
	double sum = 0;
	for (auto p : data) {
		double x = p.first, y = p.second;
		double y_ = m*x + b;
		sum += (y_ - y)*(y_-y);
	}
	return sum / double(data.size()) / 2.0;
}

// partial derivative of cost function for m
double dm(double m, double b, vector <pair <double, double>> &data) {
	double sum = 0;
	for (auto p : data) {
		double x = p.first, y = p.second;
		double y_ = m*x + b;
		sum += (y_ - y) * x;
	}
	return sum / double(data.size());
}

// partial derivative of cost function for b
double db(double m, double b, vector <pair <double, double>> &data) {
	double sum = 0;
	for (auto p : data) {
		double x = p.first, y = p.second;
		double y_ = m*x + b;
		sum += (y_ - y);
	}
	return sum / double(data.size());
}

int main() {

	// setting float/double percision
	cout << std::fixed << std::setprecision(3);

	// data points
	vector <pair <double, double>> data = {
		{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}
	};

	// model: y = mx + b; alpha - learning rate
	double m = 0, b = 0, alpha = 0.01;
	double delta_m = alpha*dm(m, b, data), delta_b = alpha*db(m, b, data);

	// gradient descent 
	while (abs(delta_m) > 10e-10 || abs(delta_b) > 10e-10) {
		cout << "m: " << m << "; b: " << b << "; cost: " << cost(m, b, data) << "\n";
		m -= delta_m; b -= delta_b;
		delta_m = alpha*dm(m, b, data);
		delta_b = alpha*db(m, b, data);
	}

	// outputting result 
	cout << "Result: " << m << " " << b << "\n";

	// cost table for different values of m and b
	for (double i = 0; i <= 1; i += 0.1) {
		for (double j = 0; j <= 1; j += 0.1) {
			cout << cost(i, j, data) << " ";
		}
		cout << "\n";
	}
	
}
