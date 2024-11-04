import numpy as np
import sys

# Redirect stdout to a file
original_stdout = sys.stdout
with open('output.txt', 'w') as f:
    sys.stdout = f

    # Simulate vector registers
    V1 = np.random.rand(64)
    V2 = np.random.rand(64)
    V3 = np.zeros(64)

    # Simulate vector addition
    def vector_add(v1, v2, result):
        for i in range(64):
            result[i] = v1[i] + v2[i]

    # Perform vector addition
    vector_add(V1, V2, V3)

    print("First few elements of result:")
    print(V3[:5])

# Restore stdout
sys.stdout = original_stdout
