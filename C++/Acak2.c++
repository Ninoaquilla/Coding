#include <iostream>
#include <vector>
#include <cmath>
#include <random>

class NeuralLink {
public:
    NeuralLink(int input_size, int output_size) 
        : input_size(input_size), output_size(output_size) {
        // Initialize weights with small random values
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        weights.resize(output_size, std::vector<double>(input_size));
        for (auto& row : weights)
            for (auto& w : row)
                w = dis(gen);

        biases.resize(output_size, 0.0);
    }

    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<double> output(output_size, 0.0);
        for (int i = 0; i < output_size; ++i) {
            for (int j = 0; j < input_size; ++j) {
                output[i] += weights[i][j] * input[j];
            }
            output[i] += biases[i];
            output[i] = sigmoid(output[i]);
        }
        return output;
    }

private:
    int input_size, output_size;
    std::vector<std::vector<double>> weights;
    std::vector<double> biases;

    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }
};

int main() {
    NeuralLink link(3, 2);
    std::vector<double> input = {0.5, -0.3, 0.8};
    std::vector<double> output = link.forward(input);

    std::cout << "Output: ";
    for (double val : output)
        std::cout << val << " ";
    std::cout << std::endl;
    return 0;
}