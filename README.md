# Matrix library for drones
# how you use it
int main() {

    // ============================================================
    // 1. Define the State Transition Matrix (A)
    // ------------------------------------------------------------
    // A represents how the drone state evolves from time step k
    // to time step k+1.
    //
    // State vector format:
    // x = [ position
    //       velocity
    //       acceleration ]
    //
    // This uses a simple constant-acceleration model
    // with a timestep dt = 0.01 seconds.
    // ============================================================

    DroneMatrix<3, 3, float> A;

    A(0, 0) = 1.0f;  A(0, 1) = 0.01f; A(0, 2) = 0.0f;
    A(1, 0) = 0.0f;  A(1, 1) = 1.0f;  A(1, 2) = 0.01f;
    A(2, 0) = 0.0f;  A(2, 1) = 0.0f;  A(2, 2) = 1.0f;

    // ============================================================
    // 2. Define Current State Vector (x_k)
    // ------------------------------------------------------------
    // Initial drone state at time step k:
    // position     = 10 meters
    // velocity     = 2 m/s
    // acceleration = 0.1 m/s^2
    // ============================================================

    DroneMatrix<3, 1, float> x_k;

    x_k(0, 0) = 10.0f;  // Position
    x_k(1, 0) = 2.0f;   // Velocity
    x_k(2, 0) = 0.1f;   // Acceleration

    // ============================================================
    // 3. Compute Next State
    // ------------------------------------------------------------
    // State prediction equation:
    //
    // x(k+1) = A * x(k)
    //
    // This predicts the drone's next state using
    // the motion model.
    // ============================================================

    DroneMatrix<3, 1, float> x_next = A * x_k;

    // ============================================================
    // 4. Output Result
    // ============================================================

    std::cout << "Next State Vector:\n";
    x_next.print();

    return 0;
}
