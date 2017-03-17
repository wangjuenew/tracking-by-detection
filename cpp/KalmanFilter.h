/**
* Kalman filter implementation using Eigen. Based on the following
* introductory paper:
*
*     http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
*
* @author: Hayk Martirosyan
* @date: 2014.11.15
*/

#include <Eigen/Dense>

#pragma once

class KalmanFilter {

public:

    /**
     * Create a Kalman filter with the specified matrices.
     *   F - System dynamics matrix
     *   H - Output matrix
     *   Q - Process noise covariance
     *   R - Measurement noise covariance
     *   P - Estimate error covariance
     */
    KalmanFilter(
            double dt,
            const Eigen::MatrixXd &F,
            const Eigen::MatrixXd &H,
            const Eigen::MatrixXd &Q,
            const Eigen::MatrixXd &R,
            const Eigen::MatrixXd &P
    );

    /**
     * Create a blank estimator.
     */
    KalmanFilter();

    /**
     * Initialize the filter with initial states as zero.
     */
    void init();

    /**
     * Initialize the filter with a guess for initial states.
     */
    void init(double t0, const Eigen::VectorXd &x0);

    /**
     * Predict next state based on current state.
     * The time step is assumed to remain constant.
     */
    void predict();

    /**
     * Predict next state based on current state,
     * using the given time step.
     */
    void predict(double dt);

    /**
     * Update the estimated state based on measured values.
     * The time step is assumed to remain constant.
     */
    void update(const Eigen::VectorXd &z);

    /**
     * Update the estimated state based on measured values,
     * using the given time step and dynamics matrix.
     */
    void update(const Eigen::VectorXd &y, double dt, const Eigen::MatrixXd &F);

    /**
     * Return the current state and time.
     */
    Eigen::VectorXd state() const { return x_hat; };

    double time() const { return t; };

private:

    // Matrices for computation
    Eigen::MatrixXd F, H, Q, R, P, K, P0;

    // System dimensions
    int m, n;

    // Initial and current time
    double t0, t;

    // Discrete time step
    double dt;

    // Is the filter initialized?
    bool initialized;

    // n-size identity
    Eigen::MatrixXd I;

    // Estimated states
    Eigen::VectorXd x_hat, x_hat_new;
};