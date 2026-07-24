#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
struct Complex {
    double real;
    double imag;
};
struct Vector {
    float x, y, z;
    int type; 
};
void vectorOperations(struct Vector v1, struct Vector v2, int operation) {
    struct Vector result;
    float dot;

    if (v1.type == 2 && v2.type == 2) {
       
        switch (operation) {
            case 1: 
                result.x = v1.x + v2.x;
                result.y = v1.y + v2.y;
                printf("Addition: (%.2f, %.2f)\n", result.x, result.y);
                break;

            case 2: 
                result.x = v1.x - v2.x;
                result.y = v1.y - v2.y;
                printf("Subtraction: (%.2f, %.2f)\n", result.x, result.y);
                break;

            case 3: 
                dot = v1.x * v2.x + v1.y * v2.y;
                printf("Dot Product: %.2f\n", dot);
                break;

            case 4: 
                printf("Cross Product (scalar): %.2f\n", (v1.x * v2.y - v1.y * v2.x));
                break;

            default:
                printf("Invalid operation selected!\n");
        }

    } else if (v1.type == 3 && v2.type == 3) {
       
        switch (operation) {
            case 1:
                result.x = v1.x + v2.x;
                result.y = v1.y + v2.y;
                result.z = v1.z + v2.z;
                printf("Addition: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                break;

            case 2: 
                result.x = v1.x - v2.x;
                result.y = v1.y - v2.y;
                result.z = v1.z - v2.z;
                printf("Subtraction: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                break;

            case 3: 
                dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
                printf("Dot Product: %.2f\n", dot);
                break;

            case 4: 
                result.x = v1.y * v2.z - v1.z * v2.y;
                result.y = v1.z * v2.x - v1.x * v2.z;
                result.z = v1.x * v2.y - v1.y * v2.x;
                printf("Cross Product: (%.2f, %.2f, %.2f)\n", result.x, result.y, result.z);
                break;

            default:
                printf("Invalid operation selected!\n");
        }

    } else {
        printf("Error: Vector types must match (both 2D or both 3D)\n");
    }}

void display2(float matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++)
            printf("%8.3f ", matrix[i][j]);
        printf("\n");
    }
}

void display3(float matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("%8.3f ", matrix[i][j]);
        printf("\n");
    }
}

void transpose2(float matrix[2][2], float trans[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            trans[j][i] = matrix[i][j];
}

void transpose3(float matrix[3][3], float trans[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            trans[j][i] = matrix[i][j];
}

float determinant2x2(float matrix[2][2]) {
    return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
}

float determinant3x3(float matrix[3][3]) {
    float det;
    det = matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1])
        - matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])
        + matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
    return det;
}

void inverse2x2(float matrix[2][2]) {
    float det = determinant2x2(matrix);
    if (det == 0) {
        printf("Inverse does not exist (Determinant = 0).\n");
        return;
    }

    float inv[2][2];
    inv[0][0] =  matrix[1][1] / det;
    inv[0][1] = -matrix[0][1] / det;
    inv[1][0] = -matrix[1][0] / det;
    inv[1][1] =  matrix[0][0] / det;

    printf("\nInverse Matrix:\n");
    display2(inv);
}

void inverse3x3(float matrix[3][3]) {
    float det = determinant3x3(matrix);
    if (det == 0) {
        printf("Inverse does not exist (Determinant = 0).\n");
        return;
    }

    float adj[3][3], adjT[3][3], inv[3][3];

    adj[0][0] =  (matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]);
    adj[0][1] = -(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0]);
    adj[0][2] =  (matrix[1][0]*matrix[2][1] - matrix[1][1]*matrix[2][0]);
    adj[1][0] = -(matrix[0][1]*matrix[2][2] - matrix[0][2]*matrix[2][1]);
    adj[1][1] =  (matrix[0][0]*matrix[2][2] - matrix[0][2]*matrix[2][0]);
    adj[1][2] = -(matrix[0][0]*matrix[2][1] - matrix[0][1]*matrix[2][0]);
    adj[2][0] =  (matrix[0][1]*matrix[1][2] - matrix[0][2]*matrix[1][1]);
    adj[2][1] = -(matrix[0][0]*matrix[1][2] - matrix[0][2]*matrix[1][0]);
    adj[2][2] =  (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);

    transpose3(adj, adjT);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            inv[i][j] = adjT[i][j] / det;

    printf("\nInverse Matrix:\n");
    display3(inv);
}

void add2(float A[2][2], float B[2][2], float R[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void add3(float A[3][3], float B[3][3], float R[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            R[i][j] = A[i][j] + B[i][j];
}

void sub2(float A[2][2], float B[2][2], float R[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            R[i][j] = A[i][j] - B[i][j];
}

void sub3(float A[3][3], float B[3][3], float R[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            R[i][j] = A[i][j] - B[i][j];
}

void mul2(float A[2][2], float B[2][2], float R[2][2]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            R[i][j] = 0;
            for (int k = 0; k < 2; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
}

void mul3(float A[3][3], float B[3][3], float R[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            R[i][j] = 0;
            for (int k = 0; k < 3; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
}

int matrix() {
    int choice, n;

    printf("===== MATRIX OPERATIONS MENU =====\n");
    printf("1. Determinant\n");
    printf("2. Transpose\n");
    printf("3. Inverse\n");
    printf("4. Addition\n");
    printf("5. Subtraction\n");
    printf("6. Multiplication\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter matrix size (2 for 2x2 or 3 for 3x3): ");
    scanf("%d", &n);

    if (n != 2 && n != 3) {
        printf("Invalid size! Please enter 2 or 3.\n");
        return 0;
    }

    float A2[2][2], B2[2][2], R2[2][2];
    float A3[3][3], B3[3][3], R3[3][3];

    if (choice >= 1 && choice <= 3) {
        if (n == 2) {
            printf("Enter elements of 2x2 Matrix:\n");
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    scanf("%f", &A2[i][j]);
            printf("\nMatrix:\n");
            display2(A2);

            if (choice == 1)
                printf("\nDeterminant = %.3f\n", determinant2x2(A2));
            else if (choice == 2) {
                float T2[2][2];
                transpose2(A2, T2);
                printf("\nTranspose:\n");
                display2(T2);
            } else
                inverse2x2(A2);
        } else {
            printf("Enter elements of 3x3 Matrix:\n");
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    scanf("%f", &A3[i][j]);
            printf("\nMatrix:\n");
            display3(A3);

            if (choice == 1)
                printf("\nDeterminant = %.3f\n", determinant3x3(A3));
            else if (choice == 2) {
                float T3[3][3];
                transpose3(A3, T3);
                printf("\nTranspose:\n");
                display3(T3);
            } else
                inverse3x3(A3);
        }
    }

    else if (choice >= 4 && choice <= 6) {
        if (n == 2) {
            printf("Enter elements of Matrix A:\n");
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    scanf("%f", &A2[i][j]);
            printf("Enter elements of Matrix B:\n");
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    scanf("%f", &B2[i][j]);

            printf("\nMatrix A:\n");
            display2(A2);
            printf("\nMatrix B:\n");
            display2(B2);

            if (choice == 4) {
                add2(A2, B2, R2);
                printf("\nAddition Result:\n");
                display2(R2);
            } else if (choice == 5) {
                sub2(A2, B2, R2);
                printf("\nSubtraction Result:\n");
                display2(R2);
            } else {
                mul2(A2, B2, R2);
                printf("\nMultiplication Result:\n");
                display2(R2);
            }
        } else {
            printf("Enter elements of Matrix A:\n");
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    scanf("%f", &A3[i][j]);
            printf("Enter elements of Matrix B:\n");
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    scanf("%f", &B3[i][j]);

            printf("\nMatrix A:\n");
            display3(A3);
            printf("\nMatrix B:\n");
            display3(B3);

            if (choice == 4) {
                add3(A3, B3, R3);
                printf("\nAddition Result:\n");
                display3(R3);
            } else if (choice == 5) {
                sub3(A3, B3, R3);
                printf("\nSubtraction Result:\n");
                display3(R3);
            } else {
                mul3(A3, B3, R3);
                printf("\nMultiplication Result:\n");
                display3(R3);
            }
        }
    } else {
        printf("Invalid choice! Please select between 1–6.\n");
    }

    return 0;
}


double degToRad(double degrees) {
    return degrees * (PI / 180.0);
}

double radToDeg(double radians) {
    return radians * (180.0 / PI);
}

void calculateSin(double* res) {
    double degrees, radians;
    printf("Enter the angle in degrees: ");
    scanf("%lf", &degrees);
    radians = degToRad(degrees);
    *res = sin(radians);
    printf("sin(%.3f) = %.3f\n", degrees, *res);
}

void calculateCos(double* res) {
    double degrees, radians;
    printf("Enter the angle in degrees: ");
    scanf("%lf", &degrees);
    radians = degToRad(degrees);
    *res = cos(radians);
    printf("cos(%.3f) = %.3f\n", degrees, *res);
}

void calculateTan(double* res) {
    double degrees, radians;
    printf("Enter the angle in degrees: ");
    scanf("%lf", &degrees);
    if (fmod(degrees, 180.0) == 90.0) {
        printf("tan(%.3f) is undefined for angle multiple of 90\n", degrees);
        *res = 0;
        return;
    }
    radians = degToRad(degrees);
    *res = tan(radians);
    printf("tan(%.3f) = %.3f\n", degrees, *res);
}

void calculateAsin(double* res) {
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);
    if (x < -1 || x > 1) {
        printf("Error: sin?¹(x) undefined for |x| > 1\n");
        *res = 0;
        return;
    }
    *res = radToDeg(asin(x));
    printf("sin?¹(%.3f) = %.3f degrees\n", x, *res);
}

void calculateAcos(double* res) {
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);
    if (x < -1 || x > 1) {
        printf("Error: cos?¹(x) undefined for |x| > 1\n");
        *res = 0;
        return;
    }
    *res = radToDeg(acos(x));
    printf("cos?¹(%.3f) = %.3f degrees\n", x, *res);
}

void calculateAtan(double* res) {
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);
    *res = radToDeg(atan(x));
    printf("tan?¹(%.3f) = %.3f degrees\n", x, *res);
}

void decToBinary(int n) {
    int binaryNum[32];
    int i = 0;
    if (n == 0) {
        printf("Binary: 0\n");
        return;
    }
    while (n > 0) {
        binaryNum[i++] = n % 2;
        n /= 2;
    }
    printf("Binary: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", binaryNum[j]);
    printf("\n");
}

void decToOctal(int n) {
    int octalNum[32];
    int i = 0;
    if (n == 0) {
        printf("Octal: 0\n");
        return;
    }
    while (n > 0) {
        octalNum[i++] = n % 8;
        n /= 8;
    }
    printf("Octal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%d", octalNum[j]);
    printf("\n");
}

void decToHex(int n) {
    char hexNum[32];
    int i = 0;
    if (n == 0) {
        printf("Hexadecimal: 0\n");
        return;
    }
    while (n > 0) {
        int r = n % 16;
        hexNum[i++] = (r < 10) ? r + '0' : r - 10 + 'A';
        n /= 16;
    }
    printf("Hexadecimal: ");
    for (int j = i - 1; j >= 0; j--)
        printf("%c", hexNum[j]);
    printf("\n");
}

void solveTwoEquations() {
    float a1, b1, c1, a2, b2, c2, det, x, y;
    printf("\nEnter coefficients for first equation (a1 b1 c1): ");
    scanf("%f %f %f", &a1, &b1, &c1);
    printf("\nEnter coefficients for second equation (a2 b2 c2): ");
    scanf("%f %f %f", &a2, &b2, &c2);
    det = a1 * b2 - a2 * b1;
    if (det == 0)
        printf("\nNo unique solution (Lines are parallel or coincident)\n");
    else {
        x = (c1 * b2 - c2 * b1) / det;
        y = (a1 * c2 - a2 * c1) / det;
        printf("\nSolution:\nX = %.3f\nY = %.3f\n", x, y);
    }
}

void solveThreeEquations() {
    float a1, b1, c1, d1;
    float a2, b2, c2, d2;
    float a3, b3, c3, d3;
    float D, Dx, Dy, Dz;
    printf("\nEnter coefficients for first equation (a1 b1 c1 d1): ");
    scanf("%f %f %f %f", &a1, &b1, &c1, &d1);
    printf("\nEnter coefficients for second equation (a2 b2 c2 d2): ");
    scanf("%f %f %f %f", &a2, &b2, &c2, &d2);
    printf("\nEnter coefficients for third equation (a3 b3 c3 d3): ");
    scanf("%f %f %f %f", &a3, &b3, &c3, &d3);
    D = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);
    Dx = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);
    Dy = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);
    Dz = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);
    if (D == 0)
        printf("\nNo unique solution (Planes are parallel or coincident)\n");
    else
        printf("\nSolution:\nX = %.3f\nY = %.3f\nZ = %.3f\n", Dx / D, Dy / D, Dz / D);
}

void solveQuadratic() {
    float a, b, c, D, r1, r2;
    printf("\nEnter coefficients a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);
    D = b * b - 4 * a * c;
    if (D > 0) {
        r1 = (-b + sqrt(D)) / (2 * a);
        r2 = (-b - sqrt(D)) / (2 * a);
        printf("\nTwo Real windows:\nX1 = %.3f\nX2 = %.3f\n", r1, r2);
    } else if (D == 0) {
        r1 = -b / (2 * a);
        printf("\nOne Real window:\nX = %.3f\n", r1);
    } else {
        float real = -b / (2 * a);
        float imag = sqrt(-D) / (2 * a);
        printf("\nComplex windows:\nX1 = %.3f + %.3fi\nX2 = %.3f - %.3fi\n", real, imag, real, imag);
    }
}

void solveCubic() {
    double a, b, c, d;
    printf("\nEnter coefficients a, b, c, d: ");
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    if (a == 0) {
        printf("Not a cubic equation.\n");
        return;
    }
    double f = ((3 * c / a) - ((b * b) / (a * a))) / 3;
    double g = ((2 * b * b * b / (a * a * a)) - (9 * b * c / (a * a)) + (27 * d / a)) / 27;
    double h = (g * g / 4) + (f * f * f / 27);

    if (h > 0) {
        double R = -(g / 2) + sqrt(h);
        double S = cbrt(R);
        double T = -(g / 2) - sqrt(h);
        double U = cbrt(T);
        double x1 = (S + U) - (b / (3 * a));
        printf("\nOne Real window:\nX1 = %.3f\n", x1);
    } else {
        double i = sqrt((g * g / 4) - h);
        double j = cbrt(i);
        double k = acos(-(g / (2 * i)));
        double L = -j;
        double M = cos(k / 3);
        double N = sqrt(3) * sin(k / 3);
        double P = -(b / (3 * a));
        double x1 = 2 * j * cos(k / 3) - (b / (3 * a));
        double x2 = L * (M + N) + P;
        double x3 = L * (M - N) + P;
        printf("\nThree Real windows:\nX1 = %.3f\nX2 = %.3f\nX3 = %.3f\n", x1, x2, x3);
    }
}

int comp() {
    double result = 0.0, num = 0.0;
    char op, lastOp = '+';

    printf("Enter first number: ");
    if (scanf("%lf", &result) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    while (1) {
        printf("Enter operator (+, -, *, /) & '#' for functions, '=' to finish: ");
        scanf(" %c", &op);
        if (op == '=') break;
        if (op == '#') {
            int nm;
            printf("1) Trigonometry\n2) Log (not done)\n3) x^y (not done)\n4) x^(1/y) (not done)\n");
            scanf("%d", &nm);
            switch (nm) {
                case 1: {
                    int m;
                    printf("\n=== Trigonometric & Inverse Trigonometric Functions ===\n");
                    printf("1. sin(a)\n2. cos(a)\n3. tan(a)\n4. sin?¹(x)\n5. cos?¹(x)\n6. tan?¹(x)\n7. Exit\n");
                    printf("Enter choice: ");
                    scanf("%d", &m);
                    switch (m) {
                        case 1: calculateSin(&num); break;
                        case 2: calculateCos(&num); break;
                        case 3: calculateTan(&num); break;
                        case 4: calculateAsin(&num); break;
                        case 5: calculateAcos(&num); break;
                        case 6: calculateAtan(&num); break;
                        case 7: printf("Exiting trigonometry menu.\n"); continue;
                        default: printf("Invalid choice! Please try again.\n"); continue;
                    }
                } break;
                default:
                    printf("Functionality not implemented yet.\n");
                    continue;
            }
        } else {
            printf("Enter next number: ");
            if (scanf("%lf", &num) != 1) {
                printf("Invalid number input!\n");
                return 1;
            }
        }
        switch (lastOp) {
            case '+': result += num; break;
            case '-': result -= num; break;
            case '*': result *= num; break;
            case '/':
                if (num == 0) {
                    printf("Error: Division by zero.\n");
                    return 1;
                }
                result /= num;
                break;
            default:
                printf("Invalid operator.\n");
                return 1;
        }
      
        lastOp = op;
    }
    printf(" Result: %lf\n", result);
    return 0;
}

void displayComplex(struct Complex c) {
    if (c.imag >= 0)
        printf("Result: %.3f + %.3fi\n", c.real, c.imag);
    else
        printf("Result: %.3f - %.3fi\n", c.real, fabs(c.imag));
}

struct Complex addComplex(struct Complex a, struct Complex b) {
    struct Complex res;
    res.real = a.real + b.real;
    res.imag = a.imag + b.imag;
    return res;
}

struct Complex subComplex(struct Complex a, struct Complex b) {
    struct Complex res;
    res.real = a.real - b.real;
    res.imag = a.imag - b.imag;
    return res;
}

struct Complex mulComplex(struct Complex a, struct Complex b) {
    struct Complex res;
    res.real = a.real * b.real - a.imag * b.imag;
    res.imag = a.real * b.imag + a.imag * b.real;
    return res;
}

struct Complex divComplex(struct Complex a, struct Complex b) {
    struct Complex res;
    double denom = b.real * b.real + b.imag * b.imag;
    if (denom == 0) {
        printf("Error: Division by zero.\n");
        res.real = res.imag = 0;
        return res;
    }
    res.real = (a.real * b.real + a.imag * b.imag) / denom;
    res.imag = (a.imag * b.real - a.real * b.imag) / denom;
    return res;
}

void magArgComplex(struct Complex c) {
    double mag = sqrt(c.real * c.real + c.imag * c.imag);
    double arg = atan2(c.imag, c.real) * (180.0 / PI);
    printf("Magnitude: %.3f\n", mag);
    printf("Argument: %.3f degrees\n", arg);
}

int complexMode() {
    struct Complex c1, c2, result;
    int choice;

    printf("\n==== COMPLEX NUMBER MODE ====\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Magnitude & Argument\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= 4) {
        printf("Enter first complex number (real imag): ");
        scanf("%lf %lf", &c1.real, &c1.imag);
        printf("Enter second complex number (real imag): ");
        scanf("%lf %lf", &c2.real, &c2.imag);
    } else if (choice == 5) {
        printf("Enter complex number (real imag): ");
        scanf("%lf %lf", &c1.real, &c1.imag);
    } else {
        printf("Invalid choice!\n");
        return 0;
    }

    switch (choice) {
        case 1: result = addComplex(c1, c2); displayComplex(result); break;
        case 2: result = subComplex(c1, c2); displayComplex(result); break;
        case 3: result = mulComplex(c1, c2); displayComplex(result); break;
        case 4: result = divComplex(c1, c2); displayComplex(result); break;
        case 5: magArgComplex(c1); break;
        default: printf("Invalid choice!\n"); break;
    }

    return 0;
}


int main() {
    const char* row1[] = {"On", "Mode", "Shift", "Alpha", "X^y", "v", "PI"};
    const char* row2[] = {"7", "8", "9", "X", "(", ")", "%"};
    const char* row3[] = {"4", "5", "6", "-", "sin", "cos", "tan"};
    const char* row4[] = {"1", "2", "3", "+", "log", "ln", "x^-1"};
    const char* row5[] = {"0", ".", "x10^X", "÷", "Ans", ",", "="};

    printf(" _______________________________________________________________________\n");
    printf("|                                                                      |\n");
    printf("|  _________________________________________________________________   |\n");
    printf("| |                                                                 |  |\n");
    printf("| |                    scientific calculator                        |  |\n");
    printf("| |_________________________________________________________________|  |\n");
    printf("|                                                                      |\n");

    printf("|");
    for(int i=0; i<7; i++) printf("  [%-5s] ", row1[i]);
    printf("|\n|");
    for(int i=0; i<7; i++) printf("  [%-5s] ", row2[i]);
    printf("|\n|");
    for(int i=0; i<7; i++) printf("  [%-5s] ", row3[i]);
    printf("|\n|");
    for(int i=0; i<7; i++) printf("  [%-5s] ", row4[i]);
    printf("|\n|");
    for(int i=0; i<7; i++) printf("  [%-5s] ", row5[i]);
    printf("|\n");
    printf("|_______________________________________________________________________|\n");

    printf("\n--- Calculator Functionality ---\n");
    printf("1) comp\n2) complex\n3) equation\n4) base_n\n5) matrix \n6) vector \n");
    int whatfun;
    printf("\nCHOOSE MODE: ");
    scanf("%d", &whatfun);
    switch(whatfun) {
        case 1:
            printf("======== COMP MODE ========\n");
            comp();
            break;
        case 2:
            printf("======== COMPLEX MODE ========\n");
            complexMode();
            break;
        case 3:
        {
            printf("======= EQUATION MODE =======\n");
            int n;
            printf("1) Two Equations\n2) Three Equations\n3) Quadratic\n4) Cubic\n");
            printf("Enter your choice: ");
            scanf("%d", &n);
            switch(n) {
                case 1: solveTwoEquations(); break;
                case 2: solveThreeEquations(); break;
                case 3: solveQuadratic(); break;
                case 4: solveCubic(); break;
                default: printf("Invalid choice!\n"); break;
            }
            break;
        }
        case 4:
        {
            int choice, num;
            printf("========= BASE_N MODE ===========\n");
            printf("1. Decimal to Binary\n2. Decimal to Octal\n3. Decimal to Hexadecimal\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            printf("Enter Decimal Number: ");
            scanf("%d", &num);
            switch(choice) {
                case 1: decToBinary(num); break;
                case 2: decToOctal(num); break;
                case 3: decToHex(num); break;
                default: printf("Invalid choice\n"); break;
            }
            break;
        }
        case 5:
            printf("============ MATRIX MODE ==============\n");
            matrix();
            break;
        case 6:
           struct Vector v1, v2;
    int choice, operation;

    printf("Enter vector type (2 for 2D, 3 for 3D): ");
    scanf("%d", &choice);

    if (choice == 2) {
        v1.type = v2.type = 2;
        printf("Enter v1 (x y): ");
        scanf("%f %f", &v1.x, &v1.y);
        printf("Enter v2 (x y): ");
        scanf("%f %f", &v2.x, &v2.y);
    } else if (choice == 3) {
        v1.type = v2.type = 3;
        printf("Enter v1 (x y z): ");
        scanf("%f %f %f", &v1.x, &v1.y, &v1.z);
        printf("Enter v2 (x y z): ");
        scanf("%f %f %f", &v2.x, &v2.y, &v2.z);
    } else {
        printf("Invalid vector type!\n");
        return 0;
    }

    printf("\nSelect Operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Dot Product\n");
    printf("4. Cross Product\n");
    printf("Enter choice: ");
    scanf("%d", &operation);

    printf("\n");
    vectorOperations(v1, v2, operation);
            break;
        default:
            printf("Invalid mode selection\n");
            break;
    }
    return 0;
}
