# Matrix library for drones
# how you use it
int main() {
    // Define a 3x3 State Transition Matrix (A)
    DroneMatrix<3, 3, float> A;
    A(0, 0) = 1.0f; A(0, 1) = 0.01f; A(0, 2) = 0.0f;
    A(1, 0) = 0.0f; A(1, 1) = 1.0f;  A(1, 2) = 0.01f;
    A(2, 0) = 0.0f; A(2, 1) = 0.0f;  A(2, 2) = 1.0f;

    // Define a 3x1 State Vector (x_k)
    DroneMatrix<3, 1, float> x_k;
    x_k(0, 0) = 10.0f; // Position
    x_k(1, 0) = 2.0f;  // Velocity
    x_k(2, 0) = 0.1f;  // Acceleration

    // Calculate next state: A * x_k
    DroneMatrix<3, 1, float> x_next = A * x_k;

    std::cout << "Next State Vector:\n";
    x_next.print();

    return 0;
}
